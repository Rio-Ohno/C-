//====================================================
// 
// �Ռ��g�̊Ǘ����� [shockManager.cpp]
// Author:Rio Ohno
// 
//====================================================

// �C���N���[�h
#include"shockManager.h"

// �ÓI�����o�ϐ�
CShockPattern* CShockManager::m_pPattern = { NULL };
CShockwave* CShockManager::m_apShockWave[SHOCK_NUM] = { NULL };
int CShockManager::m_anCntFream[SHOCK_NUM] = { 0 };
int CShockManager::m_anPatternIndx[SHOCK_NUM] = { -1 };

//====================================================
// �R���X�g���N�^
//====================================================
CShockManager::CShockManager()
{
	// �e�ϐ��̏�����
	for (int nCnt = 0; nCnt < SHOCK_NUM; nCnt++)
	{
		m_apShockWave[nCnt] = { NULL };
		m_anCntFream[nCnt] = 0;
		m_anPatternIndx[nCnt] = -1;
		m_pos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_pPattern = { NULL };
}

//====================================================
// �f�X�g���N�^
//====================================================
CShockManager::~CShockManager()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CShockManager::Init(void)
{
	m_pPattern = new CShockPattern;

	CLoadShock::Load("data/SCRIPT/ShockWave.txt", m_pPattern);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CShockManager::Uninit(void)
{
	// m_apShockWave�͏���ɔj�����ꂻ��

	// �p�^�[���̔j��
	if (m_pPattern != NULL)
	{
		// �I������
		m_pPattern->Uninit();

		// �������̔j��
		delete m_pPattern;
		m_pPattern = NULL;
	}
}

//====================================================
// �X�V����
//====================================================
void CShockManager::Update(void)
{
	for (int nCnt = 0; nCnt < SHOCK_NUM; nCnt++)
	{
		if (m_anPatternIndx[nCnt] >= 0)
		{
			// �t���[���J�E���g�A�b�v
			m_anCntFream[nCnt]++;

			// ���߂�ꂽ�t���[�����ɂȂ�����
			if (m_anCntFream[nCnt] >= m_pPattern->GetInfo()[m_anPatternIndx[nCnt]]->GetFream())
			{
				// �Ռ��g��������
				CShockManager::Spawn(m_anPatternIndx[nCnt]);

				// �t���[���J�E���g���Z�b�g
				m_anCntFream[nCnt] = 0;
			}
		}
	}
}

//====================================================
// �Ռ��g�̐�������
//====================================================
void CShockManager::Spawn(int nPatternIndx)
{
	// �Ռ��g�̐���
	CShockwave* pWave = CShockwave::Create(m_pos[nPatternIndx], D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 1,
		m_pPattern->GetInfo()[nPatternIndx]->GetLife(),
		m_pPattern->GetInfo()[nPatternIndx]->GetWidth(),
		m_pPattern->GetInfo()[nPatternIndx]->GetHeight(),
		m_pPattern->GetInfo()[nPatternIndx]->GetHeight(),
		m_pPattern->GetInfo()[nPatternIndx]->GetSpeed(),
		m_pPattern->GetInfo()[nPatternIndx]->GetCulling(),
		m_pPattern->GetInfo()[nPatternIndx]->GetCollision());

	// �F�̐ݒ�
	pWave->SetColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), true);

	// �����鉉�o�̐ݒ�
	pWave->SetVanish(m_pPattern->GetInfo()[nPatternIndx]->GetVanish());
}

//====================================================
// �ݒu����
//====================================================
void CShockManager::Place(int nPatternIndx, int posIndx)
{
	for (int nCnt = 0; nCnt < SHOCK_NUM; nCnt++)
	{
		if (m_anPatternIndx[nCnt] < 0)
		{
			// �p�^�[���C���f�b�N�X�̐ݒ�
			m_anPatternIndx[nCnt] = nPatternIndx;

			// �ʒu�̐ݒ�
			m_pos[m_anPatternIndx[nCnt]] = m_pPattern->Getpos()[posIndx];

			break;
		}
	}
}