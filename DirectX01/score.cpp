//==================================================== 
// 
// �X�R�A�@[score.cpp]
// Author: Rio Ohno
// 
//==================================================== 

// �C���N���[�h
#include"score.h"
#include<stdio.h>
#include"manager.h"
#include"input.h"

//// �ÓI�����o�ϐ�
//int CScore::m_nScore = 0;

//==================================================== 
// �R���X�g���N�^
//==================================================== 
CScore::CScore(int nPriority) :CObject(nPriority)
{
	// �l���N���A����
	m_nScore = 0;
	m_nDigit = 0;
	m_Texindx = -1;
}

//==================================================== 
// �f�X�g���N�^
//==================================================== 
CScore::~CScore()
{
	//�@�Ȃ�
}

//==================================================== 
// ����������
//==================================================== 
HRESULT CScore::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		pos.x -= (fWidth + nCnt);

		// �����̐����A�e�N�X�`���̊���
		m_apNumber[nCnt] = CNumber::Create(pos, fWidth, fHeight);
		m_apNumber[nCnt]->CNumber::BindTexindx(m_Texindx);
	}
	return S_OK;
}

//==================================================== 
// �I������
//==================================================== 
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGHT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// �����̏I������
			m_apNumber[nCnt]->CNumber::Uninit();
		}
	}
	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//==================================================== 
// �X�V����
//==================================================== 
void CScore::Update(void)
{
#if _DEBUG
	//�L�[�{�[�h�̎擾
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetPress(DIK_UP) == true)
	{
		// �X�R�A���Z
		CScore::Add(5);
	}
	else if (pKeyboard->GetPress(DIK_DOWN) == true)
	{
		// �X�R�A���Z
		CScore::Diff(5);
	}

#endif
	// �X�R�A�̐ݒ�
	CScore::SetScore();
}

//==================================================== 
// �`�揈��
//==================================================== 
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		// �����̕`�揈��
		m_apNumber[nCnt]->Draw();
	}
}

//==================================================== 
// ��������
//==================================================== 
CScore* CScore::Create(D3DXVECTOR3 pos, int nDigit, float fWidth, float fHeight)
{
	CScore* pScore = NULL;

	// �������̊m��
	pScore = new CScore;

	// �e�N�X�`���C���f�b�N�X�̐ݒ�
	pScore->m_Texindx = CTexture::TYPE_SCORENUMBER;

	// �����̐ݒ�
	if (nDigit <= MAX_SCOREDIGHT)
	{
		pScore->m_nDigit = nDigit;
	}
	else
	{
		pScore->m_nDigit = MAX_SCOREDIGHT;
	}

	// ����������
	pScore->Init(pos, fWidth, fHeight);

	// ��ނ̐ݒ�
	pScore->SetType(TYPE_UI);

	return pScore;
}

//==================================================== 
// �X�R�A�̐ݒ菈��
//==================================================== 
void CScore::SetScore(void)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_nScore,nCnt);
	}

	CDebugProc::Print("score�F%d\n", m_nScore);
}

//==================================================== 
// �e�N�X�`����������
//==================================================== 
void CScore::BindTexIndx(int nTexIndex)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		m_apNumber[nCnt]->BindTexindx(nTexIndex);
	}
}

//==================================================== 
// �X�R�A���Z����
//==================================================== 
void CScore::Add(const int nAdd)
{
	m_nScore += nAdd;
}

//==================================================== 
// �X�R�A���Z����
//==================================================== 
void CScore::Diff(const int nDiff)
{
	if ((m_nScore - nDiff) >= 0)
	{
		m_nScore -= nDiff;
	}
}

//====================================================
// �X�R�A�̏������ݏ��� 
//==================================================== 
void CScore::Save(const char* pFilename)
{
	// �O���t�@�C�����J��
	FILE* pFile = fopen(pFilename, "w");

	if (pFile != NULL)
	{
		// ���l�̏��o
		fprintf(pFile, "SCORE_DATA");

		fprintf(pFile, "\n%08d", m_nScore);

		// �I���̏��o
		fprintf(pFile, "\nEND_SCORE_DATA");

		// �O���t�@�C�������
		fclose(pFile);
	}
}

//==================================================== 
// �X�R�A�̓Ǎ�����
//==================================================== 
int CScore::Load(const char* pFilename)
{
	int nScore = 0;
	// �O���t�@�C�����J��
	FILE* pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{
		char cData = { NULL };
		char cData1[64] = { NULL };

		while (1)
		{
			// �Ǎ�
			cData = fscanf(pFile, "%s", &cData1[0]);

			if ((int)cData1[0] == EOF || (char)cData1[0] == NULL)// �t�@�C���̖��[�A�f�[�^�Ȃ��Ȃ�
			{
				// ���[�v�𔲂���
				break;
			}
			else if (strcmp(&cData1[0], "SCORE_DATA") == 0)// SCORE_DATA�Ȃ�
			{
				// ���l��ǂ݂Ƃ�
				cData = fscanf(pFile, "%08d", &nScore);
			}
			else if (strcmp(&cData1[0], "END_SCORE_DATA") == 0)// END_SCORE_DATA�Ȃ�
			{// �Ǎ�����

				// �O���t�@�C�������
				fclose(pFile);

				// ���[�v���ʂ���
				break;
			}
		}
	}
	return nScore;
}