//====================================================
//
// �����L���O�V�[������ [ranking.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"ranking.h"
#include<stdio.h>
#include"manager.h"
#include"meshSphere.h"

// �ÓI�����o�ϐ�
CScore* CRanking::m_apScore[NUM_RANK] = { NULL };
CRanking::MODE CRanking::m_mode = CRanking::MODE::MODE_DISPLAY;

//====================================================
// �R���X�g���N�^
//====================================================
CRanking::CRanking()
{
	// �e�����o�ϐ��̏�����
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		m_apScore[nCnt] = { NULL };
	}

	m_nCntFream = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CRanking::~CRanking()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �����L���O�̓Ǎ�����
	Load("data\\txt\\ranking.txt");

	if (m_mode == MODE_GAME)// �Q�[���Ȃ�
	{
		// �o�u���\�[�g
		Sort();
	}

	// �J�����ʒu�̐ݒ�
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 90.0f, -190.0f), D3DXVECTOR3(0.0f, 0.0f, 270.0f));

	// ���̂̐���
	CMeshSphere*pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	pSphere->BindTexIndex(CTexture::TYPE_SKY_RANKING);

	// �X�R�A�̐���
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		// �X�R�A�̐���
		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(815.0f, 200.0f + 110.0f * nCnt, 0.0f), 7, 50.0f, 100.0f);
		m_apScore[nCnt]->BindTexIndx(CTexture::TYPE_TIMENUMBER);

		// �X�R�A�̐ݒ�
		m_apScore[nCnt]->Add(m_nScore[nCnt]);
	}

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CRanking::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CRanking::Update(void)
{
	// �X�y�[�X����������^�C�g����
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) == true)
	{
		CManager::GetFade()->Set(CScene::MODE_TITLE);
	}

	if (m_mode == MODE_DISPLAY)
	{
		// �t���[���J�E���g�A�b�v
		m_nCntFream++;

		if (m_nCntFream >= DISPLAY_FREAM)
		{
			// �t���[���J�E���g���Z�b�g
			m_nCntFream = 0;

			// �^�C�g����
			CManager::GetFade()->Set(CScene::MODE_TITLE);
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CRanking::Draw(void)
{
	// �Ȃ�
}

//====================================================
// �Ǎ�����
//====================================================
void CRanking::Load(const char* FileName)
{
	// �O���t�@�C�����J��
	FILE* pFile = fopen(FileName, "r");

	char aString[32] = {};
	char cData;// �x���悯�p

	int nData[NUM_RANK] = { 0 };

	// �O���t�@�C�����J�����Ȃ�
	if (pFile != NULL)
	{
		while (1)
		{
			// �Ǎ�
			cData = fscanf(pFile, "%s", &aString[0]);

			if ((int)aString[0] == EOF || (char)aString[0] == NULL)// �t�@�C���̖��[�A�f�[�^�Ȃ��Ȃ�
			{
				// ���[�v�𔲂���
				break;
			}
			else if (strcmp(&aString[0], "RANKING_DATA") == 0)// RANKING_DATA�Ȃ�
			{
				// ���l��ǂ݂Ƃ�
				for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
				{
					cData = fscanf(pFile, "%08d", &nData[nCnt]);
				}
			}
			else if (strcmp(&aString[0], "END_RANKING_DATA") == 0)// END_RANKING_DATA�Ȃ�
			{// �Ǎ�����

				// ���l�̕ۑ�
				for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
				{
					m_nScore[nCnt] = nData[nCnt];
				}

				// �t�@�C�������
				fclose(pFile);

				// ���[�v���ʂ���
				break;
			}
		}
	}
}

//====================================================
// �������ݏ���
//====================================================
void CRanking::Save(const char* FileName)
{
	// �O���t�@�C�����J��
	FILE* pFile = fopen(FileName, "w");

	// �O���t�@�C�����J�����Ȃ�
	if (pFile != NULL)
	{
		// ���l�̏��o
		fprintf(pFile, "RANKING_DATA");
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			fprintf(pFile, "\n%08d", m_nScore[nCnt]);
		}

		// �I���̏��o
		fprintf(pFile, "\nEND_RANKING_DATA");

		// �O���t�@�C�������
		fclose(pFile);
	}
}

//====================================================
// �o�u���\�[�g
//====================================================
void CRanking::Sort(void)
{
	// �X�R�A�̓Ǎ�
	int nScore = CScore::Load("data\\txt\\score.txt");

	int anScore[NUM_RANK + 1] = { 0 };

	// ���l�i�[
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		anScore[nCnt] = m_nScore[nCnt];
	}

	anScore[NUM_RANK] = nScore;

	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		for (int nNext = nCntRank + 1; nNext < NUM_RANK + 1; nNext++)// �z��̎��̐��l
		{
			// �~��
			if (anScore[nCntRank] < anScore[nNext])
			{
				int nData = anScore[nCntRank];// �ꎞ�ۑ�

				// ���l�̓���ւ�
				anScore[nCntRank] = anScore[nNext];

				anScore[nNext] = nData;
			}
		}
	}

	// �����L���O�ɑ��
	for (int nRanking = 0; nRanking < NUM_RANK; nRanking++)
	{
		m_nScore[nRanking] = anScore[nRanking];
	}

	// �������ݏ���
	Save("data\\txt\\ranking.txt");
}