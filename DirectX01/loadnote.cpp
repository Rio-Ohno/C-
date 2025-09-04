//====================================================
//
// �����̓Ǎ� [loadnote.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"loadnote.h"

// �ÓI�����o�ϐ�
CLoadtxt* CLoadNote::m_LoadTxt = { NULL };

//====================================================
// �R���X�g���N�^
//====================================================�@
CLoadNote::CLoadNote()
{
	// �ϐ��̏�����
	m_LoadTxt = { NULL };
	m_nInfoCount = 0;
	m_nPosCount = 0;
}

//====================================================
// �f�X�g���N�^�@
//====================================================�@
CLoadNote::~CLoadNote()
{
	// �Ȃ�
}

//====================================================
// �`���Ǎ�
//====================================================�@
void CLoadNote::LoadScript(const char* pFilename, CNotePattern* pNotePattern)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };

	// �O���t�@�C�����J��
	FILE* pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{
		// �������̊m��
		m_LoadTxt = new CLoadtxt;

		while (1)
		{
			fgets(cData, 2, pFile);

			if (*cData != '#')
			{
				strcat(cData1, cData);

				if (strcmp(&cData1[0], "SCRIPT") == 0)// SCRIPT�Ȃ�
				{
					// �R�����g��ǂݔ�΂�
					m_LoadTxt->SkipComment(pFile);

					// ������̏�����
					cData1[0] = { NULL };
					break;
				}
			}
			else
			{
				// �R�����g��ǂݔ�΂�
				m_LoadTxt->SkipComment(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
		}

		// ������Ǎ���
		LoadPattern(pFile, pNotePattern);
		fclose(pFile);
	}

	if (m_LoadTxt != NULL)// ���g������Ȃ�
	{
		// �������̊J��
		delete m_LoadTxt;
		m_LoadTxt = NULL;
	}
}

//====================================================
// �S�p�^�[�����̓Ǎ��@
//====================================================�@
void CLoadNote::LoadPattern(FILE* pFile, CNotePattern* pNotePattern)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	int nData = 0, NumInfo = 0;
	CNoteInfo* apInfo[NUM_PATTERN_NOTE] = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "MAX_NUM") == 0)// MAX_NUM�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_LoadTxt->SkipEqual(pFile);

				// ���l�̎擾
				nData = m_LoadTxt->LoadInt(pFile);

				// ���f�����̐ݒ�
				pNotePattern->SetMaxNum(nData);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "NUM_INFO") == 0)// NUM_INFO�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_LoadTxt->SkipEqual(pFile);

				// ���l�̎擾
				NumInfo = m_LoadTxt->LoadInt(pFile);

				// �p�^�[�����̐ݒ�
				pNotePattern->SetNumInfo(NumInfo);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "INFOSET") == 0)// MOTIONSET�Ȃ�
			{
				// ���[�V�������̓Ǎ�
				apInfo[m_nInfoCount] = LoadInfo(pFile);

				m_nInfoCount++;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_SCRIPT") == 0)
			{
				pNotePattern->SetNoteInfo(apInfo);
				m_nInfoCount = 0;
				break;
			}
		}
		else
		{
			// ������̏�����
			cData1[0] = { NULL };

			if (cData[0] == '#')// #�Ȃ�
			{
				// �R�����g��ǂݔ�΂�
				m_LoadTxt->SkipComment(pFile);
			}
		}
	}
}

//====================================================
// NoteInfo�̓Ǎ��@
//====================================================�@
CNoteInfo* CLoadNote::LoadInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	int nNum = 0;
	CNotePos* apPos[NUM_NOTE] = { NULL };
	CNoteInfo* pInfo = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "NUM_NOTE") == 0)// MAX_NUM�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_LoadTxt->SkipEqual(pFile);

				// ���l�̎擾
				nNum = m_LoadTxt->LoadInt(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "POSSET") == 0)// MOTIONSET�Ȃ�
			{
				// ���[�V�������̓Ǎ�
				apPos[m_nPosCount] = LoadPos(pFile);

				m_nPosCount++;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_INFOSET") == 0)
			{
				pInfo = CNoteInfo::Create(nNum);

				pInfo->SetNotePos(apPos);

				m_nPosCount = 0;
				break;
			}
		}
		else
		{
			// ������̏�����
			cData1[0] = { NULL };

			if (cData[0] == '#')// #�Ȃ�
			{
				// �R�����g��ǂݔ�΂�
				m_LoadTxt->SkipComment(pFile);
			}
		}
	}

	return pInfo;
}

//====================================================
// CNotePos�̓Ǎ��@
//====================================================�@
CNotePos* CLoadNote::LoadPos(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	float afPos[3] = { 0.0f };
	CNotePos* pPos = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "POS") == 0)// MAX_NUM�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_LoadTxt->SkipEqual(pFile);

				// �����̓Ǎ�
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					afPos[nCnt] = m_LoadTxt->LoadFloat(pFile);
				}

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_POSSET") == 0)
			{
				pPos = CNotePos::Create(afPos[0], afPos[1], afPos[2]);

				break;
			}
		}
		else
		{
			// ������̏�����
			cData1[0] = { NULL };

			if (cData[0] == '#')// #�Ȃ�
			{
				// �R�����g��ǂݔ�΂�
				m_LoadTxt->SkipComment(pFile);
			}
		}
	}
	return pPos;
}

//====================================================
// �Ǎ��J�n����
//====================================================�@
void CLoadNote::Load(const char* pFilename, CNotePattern* pNotePattern)
{
	CLoadNote* load = NULL;

	// �������̊m��
	load = new CLoadNote;

	load->LoadScript(pFilename, pNotePattern);

	delete load;
	load = NULL;
}