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

	m_nRank = -1;
	m_nCntFream = 0;
	m_nCntFreamColor = 0;

	m_bFlashing = false;
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
	Load(SAVEFILE_RANKING);

	if (m_mode == MODE_GAME)// �Q�[���Ȃ�
	{
		// �o�u���\�[�g
		Sort();

		// �����L���O���肵���Ȃ�
		if (m_nRank >= 0)
		{
			// �_�Ńt���O�𗧂Ă�
			m_bFlashing = true;
		}
	}

	// �J�����ʒu�̐ݒ�
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 90.0f, -190.0f), D3DXVECTOR3(0.0f, 0.0f, 270.0f));

	// ���̂̐���
	CMeshSphere*pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	pSphere->BindTexIndex(CTexture::TYPE_SKY_RANKING);

	// 2D�|���S��
	CObject2D* pRanking = CObject2D::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), 720.0f, 150.0f);
	pRanking->BindTexIndx(CTexture::TYPE_RANKING);

	// �X�R�A�̐���
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		// �X�R�A�̐���
		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(840.0f, 200.0f + 110.0f * nCnt, 0.0f), 7, 50.0f, 100.0f);
		m_apScore[nCnt]->BindTexIndx(CTexture::TYPE_TIMENUMBER);
		
		// �X�R�A�̐ݒ�
		m_apScore[nCnt]->Add(m_anScore[nCnt]);
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

	// �����L���O�̃��Z�b�g
	CRanking::Reset();

	if (m_mode == MODE_DISPLAY)// �f�B�X�v���C�Ȃ�
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
	else if(m_mode == MODE_GAME)// �Q�[���Ȃ�
	{
		// �_�ŏ���
		CRanking::Flashing();
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

	// �O���t�@�C�����J�����Ȃ�
	if (pFile != NULL)
	{
		char aString[32] = {};// ������i�[�p
		char cData;// �x���悯�p

		int nData[NUM_RANK] = { 0 };

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
					m_anScore[nCnt] = nData[nCnt];
				}

				// �O���t�@�C�������
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
			fprintf(pFile, "\n%08d", m_anScore[nCnt]);
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
	int nScore = CScore::Load(SAVEFILE_SCORE);

	int anScore[NUM_RANK + 1] = { 0 };

	// ���l�i�[
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		anScore[nCnt] = m_anScore[nCnt];
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
		m_anScore[nRanking] = anScore[nRanking];

		if (m_anScore[nRanking] == nScore)
		{
			// ���ʂ̕ۑ�
			m_nRank = nRanking;
		}
	}

	// ��������
	Save(SAVEFILE_RANKING);
}

//====================================================
// �_�ŏ���
//====================================================
void CRanking::Flashing(void)
{
	if (m_bFlashing == true)
	{
		// �t���[���J�E���g�A�b�v
		m_nCntFreamColor++;

		if (m_nCntFreamColor == 30)
		{
			// �F�̐ݒ�(��)
			m_apScore[m_nRank]->SetColor(D3DXCOLOR(1.0f, 0.9f, 0.31f, 1.0f));
		}
		else if(m_nCntFreamColor>=60)
		{
			// �F�̐ݒ�(��)
			m_apScore[m_nRank]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// �t���[���J�E���g���Z�b�g
			m_nCntFreamColor = 0;
		}
	}
}

//====================================================
// �����L���O�̃��Z�b�g
//====================================================
void CRanking::Reset(void)
{
	// ���V�t�g�������Ȃ���
	if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT) == true)
	{
		// R�@����������
		if (CManager::GetKeyboard()->GetTrigger(DIK_R) == true)
		{
			// ���l�̏�����
			for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
			{
				m_anScore[nCnt] = 0;
			}

			// ��������̐��l�̕ۑ�
			CRanking::Save(SAVEFILE_RANKING);
		}
	}
}
