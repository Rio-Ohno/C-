//====================================================
// 
// �g�̃p�^�[���Ǎ����� [loadshock.cpp]
// Author:Rio Ohno
// 
//====================================================

// �C���N���[�h
#include"loadshock.h"

// �ÓI�����o�ϐ�
CLoadtxt* CLoadShock::m_pLoadTxt = { NULL };
CShockInfo* CShockPattern::m_apInfo[SHOCK_PATTERN_NUM] = { NULL };

//====================================================
// �Ռ��g�̏��̃R���X�g���N�^
//====================================================
CShockInfo::CShockInfo()
{
	// �e�ϐ��̏�����
	m_nFream = 0;
	m_nVanish = 0;
	m_nLife = 0;

	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fRadius = 0.0f;
	m_fSpeed = 0.0f;

	m_bCulling = true;
	m_bCollision = false;
}

//====================================================
// �Ռ��g�̏��̃f�X�g���N�^
//====================================================
CShockInfo::~CShockInfo()
{
	// �Ȃ�
}

//====================================================
// �Ռ��g�̏��̐�������
//====================================================
CShockInfo* CShockInfo::Create(int nFream, int nVanish, int nLife, float fWidth, float fHeight, float fRadius, float fSpeed, bool bCulling, bool bCollision)
{
	CShockInfo* pPattern = NULL;

	// �������̊m��
	pPattern = new CShockInfo;

	// �e�ϐ��̐ݒ�
	pPattern->m_nFream = nFream;
	pPattern->m_nVanish = nVanish;
	pPattern->m_nLife = nLife;
	pPattern->m_fWidth = fWidth;
	pPattern->m_fHeight = fHeight;
	pPattern->m_fRadius = fRadius;
	pPattern->m_fSpeed = fSpeed;
	pPattern->m_bCulling = bCulling;
	pPattern->m_bCollision = bCollision;

	return pPattern;
}

//====================================================
// �Ռ��g�̃p�^�[���̃R���X�g���N�^
//====================================================
CShockPattern::CShockPattern()
{
	// �e�ϐ��̏�����
	for (int nCnt = 0; nCnt < SHOCK_PATTERN_NUM; nCnt++)
	{
		m_apInfo[nCnt] = { NULL };
	}

	m_nNumInfo = 0;
}

//====================================================
// �Ռ��g�̃p�^�[���̃f�X�g���N�^
//====================================================
CShockPattern::~CShockPattern()
{
	// �Ȃ�
}

//====================================================
// �I������
//====================================================
void CShockPattern::Uninit(void)
{
	for (int nCnt = 0; nCnt < SHOCK_PATTERN_NUM; nCnt++)
	{
		if (m_apInfo[nCnt] != NULL)
		{
			// �������̔j��
			delete m_apInfo[nCnt];
			m_apInfo[nCnt] = NULL;
		}
	}
}

//====================================================
// �Ռ��g�̏��ݒ菈��
//====================================================
void CShockPattern::SetInfo(CShockInfo** ppInfo)
{
	for (int nCnt = 0; nCnt < SHOCK_PATTERN_NUM; nCnt++)
	{
		if (ppInfo[nCnt] != NULL)
		{
			m_apInfo[nCnt] = ppInfo[nCnt];
		}
	}
}

//====================================================
// �ʒu�̐ݒ菈��
//====================================================
void CShockPattern::SetPos(D3DXVECTOR3* pos)
{
	for(int nCnt=0;nCnt<SHOCK_NUM;nCnt++)
	{
		if (pos[nCnt] != NULL)
		{
			m_pos[nCnt] = pos[nCnt];
		}
	}
}

//====================================================
// �Ռ��g�̃p�^�[���̓Ǎ��̃R���X�g���N�^
//====================================================
CLoadShock::CLoadShock()
{
	// �e�ϐ��̏�����

	m_pLoadTxt = { NULL };

	m_nCntInfo = 0;
	m_nCntPos = 0;
}

//====================================================
// �Ռ��g�̃p�^�[���̓Ǎ��̃f�X�g���N�^
//====================================================
CLoadShock::~CLoadShock()
{
	// �Ȃ�
}

//====================================================
// �Ռ��g�̃p�^�[���̓Ǎ������Ăяo������
//====================================================
void CLoadShock::Load(const char* FilePass, CShockPattern* pPattern)
{
	CLoadShock* pShock = NULL;

	// �������̊m��
	pShock = new CLoadShock;

	pShock->LoadScript(FilePass, pPattern);

	// �������̔j��
	delete pShock;
	pShock = NULL;
}

//====================================================
// �Ռ��g�̃p�^�[���̓Ǎ��J�n����
//====================================================
void CLoadShock::LoadScript(const char* FilePass, CShockPattern* pPattern)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };

	// �O���t�@�C�����J��
	FILE* pFile = fopen(FilePass, "r");

	if (pFile != NULL)
	{
		// �������̊m��
		m_pLoadTxt = new CLoadtxt;

		while (1)
		{
			fgets(cData, 2, pFile);

			if (*cData != '#')
			{
				strcat(cData1, cData);

				if (strcmp(&cData1[0], "SCRIPT") == 0)// SCRIPT�Ȃ�
				{
					// �R�����g��ǂݔ�΂�
					m_pLoadTxt->SkipComment(pFile);

					// ������̏�����
					cData1[0] = { NULL };
					break;
				}
			}
			else
			{
				// �R�����g��ǂݔ�΂�
				m_pLoadTxt->SkipComment(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
		}

		// ������Ǎ���
		LoadPattern(pFile, pPattern);
		fclose(pFile);
	}

	if (m_pLoadTxt != NULL)// ���g������Ȃ�
	{
		// �������̊J��
		delete m_pLoadTxt;
		m_pLoadTxt = NULL;
	}
}

//====================================================
// �Ռ��g�̃p�^�[���̓Ǎ�����
//====================================================
void CLoadShock::LoadPattern(FILE* pFile, CShockPattern* pPattern)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	int NumInfo = 0;
	CShockInfo* apInfo[SHOCK_PATTERN_NUM] = { NULL };
	D3DXVECTOR3 pos[SHOCK_NUM] = {};

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "MAX_NUM") == 0)// MAX_NUM�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadTxt->SkipEqual(pFile);

				// ���l�̎擾
				NumInfo = m_pLoadTxt->LoadInt(pFile);

				// ���f�����̐ݒ�
				pPattern->SetNumInfo(NumInfo);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "POSSET") == 0)// POSSET�Ȃ�
			{
				// �ʒu�̓Ǎ�
				pos[m_nCntPos] = LoadPos(pFile);

				m_nCntPos++;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "INFOSET") == 0)// MOTIONSET�Ȃ�
			{
				// ���[�V�������̓Ǎ�
				apInfo[m_nCntInfo] = LoadPatternInfo(pFile);

				m_nCntInfo++;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_SCRIPT") == 0)
			{
				pPattern->SetInfo(apInfo);
				pPattern->SetPos(pos);
				m_nCntInfo = 0;
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
				m_pLoadTxt->SkipComment(pFile);
			}
		}
	}
}

//====================================================
// �Ռ��g�̃p�^�[���̏ڍדǍ�����
//====================================================
CShockInfo* CLoadShock::LoadPatternInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	char cData2[16] = { NULL };
	int nFream = 0, nLife = 0, nVanish = 0;
	float fWidth = 0.0f, fHeight = 0.0f, fRadiuse = 0.0f, fSpeed = 0.0f;
	bool bCulling = false, bCollision = false;
	CShockInfo* pInfo = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "FREAM") == 0)// FREAM�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadTxt->SkipEqual(pFile);

				nFream = m_pLoadTxt->LoadInt(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "VANISH") == 0)// VANISH�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadTxt->SkipEqual(pFile);

				nVanish = m_pLoadTxt->LoadInt(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "LIFE") == 0)// LIFE�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadTxt->SkipEqual(pFile);

				nLife = m_pLoadTxt->LoadInt(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "WIDTH") == 0)// WIDTH�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadTxt->SkipEqual(pFile);

				fWidth = m_pLoadTxt->LoadFloat(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "HEIGHT") == 0)// HEIGHT�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadTxt->SkipEqual(pFile);

				fHeight = m_pLoadTxt->LoadFloat(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "RADIUS") == 0)// RADIUS�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadTxt->SkipEqual(pFile);

				fRadiuse = m_pLoadTxt->LoadFloat(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "SPEED") == 0)// SPEED�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadTxt->SkipEqual(pFile);

				fSpeed = m_pLoadTxt->LoadFloat(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "CULLING") == 0)// CULLING�Ȃ�
			{
				// �󔒂̓ǂݔ�΂�
				m_pLoadTxt->SkipBlank(pFile);

				// ������̓Ǎ�
				m_pLoadTxt->LoadPath(pFile, cData2);

				if (strcmp(&cData2[0], "TRUE") == 0 || strcmp(&cData2[0], "true") == 0)
				{
					bCulling = true;
				}

				// ������̏�����
				cData1[0] = { NULL };
				cData2[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "COLLISION") == 0)// COLLISION�Ȃ�
			{
				// �󔒂̓ǂݔ�΂�
				m_pLoadTxt->SkipBlank(pFile);

				// ������̓Ǎ�
				m_pLoadTxt->LoadPath(pFile, cData2);

				if (strcmp(&cData2[0], "TRUE") == 0 || strcmp(&cData2[0], "true") == 0)
				{
					bCollision = true;
				}

				// ������̏�����
				cData1[0] = { NULL };
				cData2[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_INFOSET") == 0)
			{
				// ��������
				pInfo = CShockInfo::Create(nFream, nVanish, nLife, fWidth, fHeight, fRadiuse, fSpeed, bCulling, bCollision);

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
				m_pLoadTxt->SkipComment(pFile);
			}
		}
	}
	return pInfo;
}

//====================================================
// �ʒu�̓Ǎ�����
//====================================================
D3DXVECTOR3 CLoadShock::LoadPos(FILE* pFile)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	float afPos[3] = { 0.0f };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "POS") == 0)// MAX_NUM�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadTxt->SkipEqual(pFile);

				// �����̓Ǎ�
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					afPos[nCnt] = m_pLoadTxt->LoadFloat(pFile);
				}

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_POSSET") == 0)
			{
				pos = D3DXVECTOR3(afPos[0], afPos[1], afPos[2]);

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
				m_pLoadTxt->SkipComment(pFile);
			}
		}
	}
	return pos;
}