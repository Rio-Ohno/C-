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
#include"meshSphere.h"
#include"Time.h"
#include"shockwave.h"
#include"particle3D.h"

// �ÓI�����o�ϐ�
CPlayer* CGame::m_pPlayer = NULL;
CScore* CGame::m_pScore = NULL;
CObject3D* CGame::m_pObjecct3D = NULL;
CTime* CGame::m_pTime = NULL;
CPause* CGame::m_pPause = NULL;
CNoteManager* CGame::m_pNoteManager = NULL;
CShockManager* CGame::m_pShockManager = NULL;
bool CGame::m_bFinish = false;
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
	m_nCntFinFream = 0;
	m_bFinish = false;
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
	CMeshSphere* pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 500.0f, false, false);
	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, 300.0f);

	// �X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(1250.0f, 50.0f, 0.0f), 50.0f, 100.0f);

	// �v���C���[
	m_pPlayer->SetMotion("data/MODEL/player/motion.txt");
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �v���C���[

	//CMeshField* pMesh = CMeshField:: Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 3, 3, 100, 100);

	// �����̐���
	m_pNoteManager->Spawn();

	// �Ռ��g�̐���
	m_pShockManager->Place(0, 0);

	CShockwave* pWave = CShockwave::Create(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 1, 30, 0.0f, 5.0f, 30.0f, 0.5f, false, true);
	pWave->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), true);
	pWave->SetVanish(90);

#ifdef _DEBUG

	m_pTime = CTime::Create(CTime::TYPE_CNTDOWN, 300, 4, D3DXVECTOR3(740.0f, 50.0f, 0.0f), 40.0f, 80.0f);
#endif
#ifndef _DEBUG
	m_pTime = CTime::Create(CTime::TYPE_CNTDOWN, 90, 4, D3DXVECTOR3(740.0f, 50.0f, 0.0f), 40.0f, 80.0f);
#endif

	// �e�N�X�`������
	m_pTime->BindTexIndx(CTexture::TYPE_SCORENUMBER);

	// �e�N�X�`���N���X�̎擾
	CTexture* pTexture = CManager::GetTexture();

	if (pTexture != nullptr)
	{
		m_pObjecct3D->BindTexIndex(pTexture->TYPE_FILED);
		pSphere->BindTexIndex(pTexture->Register("data/TEXTURE/BG001.jpg"));
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

	// ���Ԑ؂�Ȃ�
	if (m_pTime->CTime::GetTimeOver() == true)
	{
		m_bFinish = true;
	}

	if (m_bFinish == true)
	{
		// �t���[���J�E���g
		m_nCntFinFream++;
	}

	if (m_nCntFinFream >= 60)
	{
		m_nCntFinFream = 0;

		// �t�F�[�h���擾
		CFade* fade = CManager::GetFade();

		// ���U���g�փV�[����ς���
		fade->Set(CScene::MODE_RESULT);
	}

	if (m_pNoteManager->GetNum() <= 0)
	{
		// �t���[���J�E���g
		m_nCntNoteSpan++;

		if (m_nCntNoteSpan >= NOTE_SPAWN)
		{
			// �����̌Ăяo��
			m_pNoteManager->Spawn();

			// �t���[���J�E���g���Z�b�g
			m_nCntNoteSpan = 0;
		}
	}
	if (m_pShockManager != NULL)
	{
		m_pShockManager->Update();
	}
	CDebugProc::Print("Num Note�F%d\n", m_pNoteManager->GetNum());

#ifdef _DEBUG

	if (CManager::GetKeyboard()->GetTrigger(DIK_RSHIFT) == true)
	{
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