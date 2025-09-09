//====================================================
//
// �Q�[���V�[������ [game.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"game.h"
#include"manager.h"
#include"meshfield.h"
#include"Time.h"
#include"shockwave.h"
#include"particle3D.h"

// �ÓI�����o�ϐ�
CPlayer* CGame::m_pPlayer = NULL;
CObject3D* CGame::m_pObjecct3D = NULL;
CScore* CGame::m_pScore = NULL;
CTime* CGame::m_pTime = NULL;
CTime* CGame::m_pStartTime = NULL;
CPause* CGame::m_pPause = NULL;
CNoteManager* CGame::m_pNoteManager = NULL;
CShockManager* CGame::m_pShockManager = NULL;
CMeshSphere* CGame::m_pSphere = NULL;
bool CGame::m_bFinish = false;
bool CGame::m_bStart = false;
bool CGame::m_bPause = false;

// �ÓI�����o�֐�
CPlayer* CGame::GetPlayer(void) { return m_pPlayer; };
CScore* CGame::GetScore(void) { return m_pScore; };
CObject3D* CGame::GetObject3D(void) { return m_pObjecct3D; };
CTime* CGame::GetTime(void) { return m_pTime; };

//====================================================
// �R���X�g���N�^
//====================================================
CGame::CGame() :CScene(MODE_GAME)
{
	m_nCntFreamFin = 0;
	m_bFinish = false;
	m_bStart = false;
	m_bPause = false;

	// �J�����̏���������
	CManager::GetCamera()->Init();

	// ��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_SCENE);

	// �|�[�Y���Ă��Ȃ���Ԃ�
	CObject::SetPause(false);
}

//====================================================
// �f�X�g���N�^
//====================================================
CGame::~CGame()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//----------------------------------------------------
	// ��������
	//----------------------------------------------------

	// �����̃}�l�[�W���[
	m_pNoteManager = new CNoteManager;
	m_pNoteManager->Init();

	// �Ռ��g�̃}�l�[�W���[
	m_pShockManager = new CShockManager;
	m_pShockManager->Init();

	// �|���S��
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 500.0f, false, false);
	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 600.0f);
	m_pObjecct3D->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.8f, 1.0f));

	// �X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(1250.0f, 50.0f, 0.0f),7, 50.0f, 100.0f);

	// �v���C���[
	m_pPlayer->SetMotion("data/MODEL/player/motion.txt");
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �v���C���[

	// ����
	m_pStartTime = CTime::Create(CTime::TYPE_CNTDOWN, 3, 1, D3DXVECTOR3(740.0f, 310.0f, 0.0f), 100.0f, 100.0f);
	m_pStartTime->BindTexIndx(CTexture::TYPE_TIMENUMBER);

	// �Ռ��g�̐���
	m_pShockManager->Place(1, 0);

	// �e�N�X�`���N���X�̎擾
	CTexture* pTexture = CManager::GetTexture();

	if (pTexture != nullptr)
	{
		m_pObjecct3D->BindTexIndex(pTexture->TYPE_FILED);
		m_pSphere->BindTexIndex(pTexture->TYPE_SKY);
	}

	// �J�����̎�ސݒ�
	CManager::GetCamera()->SetType(CCamera::TYPE_ASSENT);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CGame::Uninit(void)
{
	// �|�[�Y�̔j��
	if (m_pPause != NULL)
	{
		// �I������
		m_pPause->Uninit();

		// �������̔j��
		delete m_pPause;
		m_pPause = NULL;
	}

	// �����}�l�[�W���[�̔j��
	if (m_pNoteManager != NULL)
	{
		// �I������
		m_pNoteManager->Uninit();

		// �������̔j��
		delete m_pNoteManager;
		m_pNoteManager = NULL;
	}

	// �Ռ��g�}�l�[�W���[�̔j��
	if (m_pShockManager != NULL)
	{
		// �I������
		m_pShockManager->Uninit();

		// �������̔j��
		delete m_pShockManager;
		m_pShockManager = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CGame::Update(void)
{
	if (m_bFinish == false)
	{
		// �|�[�Y���邩�ǂ���
		isPause();

		if (m_pPause != NULL && m_bPause == true)
		{
			// �|�[�Y�̍X�V����
			m_pPause->Update();
		}
	}
	
	// �Q�[���J�n����
	CGame::Start();

	// �Q�[���I������
	CGame::Finish();

	// ���Ԑ؂�Ȃ�
	if (m_pTime != NULL && m_pTime->CTime::GetTimeOver() == true)
	{
		m_bFinish = true;

		// �X�R�A�̋L�^����(�Z�[�u)
		m_pScore->Save("data\\txt\\score.txt");
	}

	if (m_bStart == true)
	{
		if (m_bPause == false)
		{
			// �����̃}�l�[�W���[�̍X�V����
			if (m_pNoteManager->GetNum() <= 0)// �������S�ĂƂ�ꂽ�Ȃ�
			{
				// �t���[���J�E���g
				m_nCntNoteSpan++;

				if (m_nCntNoteSpan >= NOTE_SPAWN)// 90�t���[���o������
				{
					// �����̌Ăяo��(����)
					m_pNoteManager->Spawn();

					// �t���[���J�E���g���Z�b�g
					m_nCntNoteSpan = 0;
				}
			}

			if (m_pShockManager != NULL)
			{
				// �Ռ��g�̃}�l�[�W���[�̍X�V����
				m_pShockManager->Update();
			}
		}
	}

	// �f�o�b�N�\��
	CDebugProc::Print("Num Note�F%d\n", m_pNoteManager->GetNum());// �����̐�

#ifdef _DEBUG

	if (CManager::GetKeyboard()->GetTrigger(DIK_RSHIFT) == true)
	{
		// �X�R�A�̋L�^����(�Z�[�u)
		m_pScore->Save("data\\txt\\score.txt");

		// �t�F�[�h���擾
		CFade* fade = CManager::GetFade();

		// ���U���g�փV�[����ς���
		fade->Set(CScene::MODE_RESULT);
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_C) == true)
	{
		m_pNoteManager->Spawn();
	}
#endif
}

//====================================================
// �`�揈��
//====================================================
void CGame::Draw(void)
{
	if (m_bPause == true && m_pPause != NULL)
	{
		// �|�[�Y�̕`�揈��
		m_pPause->Draw();
	}
}

//====================================================
// �|�[�Y���邩�ǂ���
//====================================================
bool CGame::isPause(void)
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_TAB) == true)
	{
		m_bPause = m_bPause ? false : true;

		// �t���O�Ǘ�
		CObject::SetPause(m_bPause);

		if (m_bPause == true)
		{
			// �������̊m��
			m_pPause = CPause::Create();
		}
	}
	
	if (m_bPause == false)
	{
		if (m_pPause != NULL)
		{
			// �I������
			m_pPause->Uninit();

			// �������̔j��
			delete m_pPause;
			m_pPause = NULL;
		}
	}

	return m_bPause;
}

//====================================================
// �|�[�Y�̐ݒ菈��
//====================================================
void CGame::SetPause(bool Use)
{
	m_bPause = Use;
	CObject::SetPause(Use);
}

//====================================================
// �Q�[���J�n����
//====================================================
void CGame::Start(void)
{
	if (m_pStartTime != NULL)
	{
		if (m_pStartTime->GetTimeOver() == true)
		{
			m_bStart = true;

#ifdef _DEBUG

			// �^�C���̐���
			m_pTime = CTime::Create(CTime::TYPE_CNTDOWN, 60, 4, D3DXVECTOR3(740.0f, 50.0f, 0.0f), 40.0f, 80.0f);
#endif
#ifndef _DEBUG
			// �^�C���̐���
			m_pTime = CTime::Create(CTime::TYPE_CNTDOWN, 90, 4, D3DXVECTOR3(740.0f, 50.0f, 0.0f), 40.0f, 80.0f);
#endif

			// �^�C���̃e�N�X�`������
			//m_pTime->BindTexIndx(CTexture::TYPE_SCORENUMBER);
			m_pTime->BindTexIndx(CTexture::TYPE_TIMENUMBER);

			// �����̐���
			m_pNoteManager->Spawn();

			// �I������
			m_pStartTime->Uninit();
			m_pStartTime = { NULL };

		}
	}
}

//====================================================
// �Q�[���I������
//====================================================
void CGame::Finish(void)
{
	if (m_bFinish == true)
	{
		// �t���[���J�E���g
		m_nCntFreamFin++;

		if (m_nCntFreamFin >= FINISH_REAM)
		{
			m_nCntFreamFin = 0;

			// �t�F�[�h���擾
			CFade* fade = CManager::GetFade();

			// ���U���g�փV�[����ς���
			fade->Set(CScene::MODE_RESULT);
		}
	}
}