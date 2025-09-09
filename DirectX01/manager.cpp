//====================================================
// 
// �}�l�W���[[manager.cpp]
// Author:RioOhno
// 
//====================================================

//�C���N���[�h
#include"manager.h"
#include<time.h>
#include"object.h"
#include"objectX.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"

//�ÓI�����o�ϐ�
CRenderer* CManager::m_pRenderer = NULL;
CKeyboard* CManager::m_pKeyboard = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CTexture* CManager::m_pTexture = NULL;
CSound* CManager::m_pSound = { NULL };
CScene* CManager::m_pScene = { NULL };
CFade* CManager::m_pFade = { NULL };
CDebugProc* CManager::m_pDebug = { NULL };

//�ÓI�����o�֐�
CRenderer* CManager::GetRenderer(void) { return m_pRenderer; };
CKeyboard* CManager::GetKeyboard(void) { return m_pKeyboard; };
CSound* CManager::GetSound(void) { return m_pSound; };
CCamera* CManager::GetCamera(void) { return m_pCamera; };
CLight* CManager::GetLight(void) { return m_pLight; };
CTexture* CManager::GetTexture(void) { return m_pTexture; };
CFade* CManager::GetFade(void) { return m_pFade; };
CDebugProc* CManager::GetDebug(void) { return m_pDebug; };

//====================================================
// �R���X�g���N�^
//====================================================
CManager::CManager()
{
	// �Ȃ�
}

//====================================================
// �f�X�g���N�^
//====================================================
CManager::~CManager()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	srand((int)time(0));//�V�[�h�l

	//�����_���[�̐���
	m_pRenderer = new CRenderer;

	//�����_���[�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		//���������������s������
		return -1;
	}

	//�L�[�{�[�h�̐���
	m_pKeyboard = new CKeyboard;

	// �L�[�{�[�h�̏���������
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		//���������������s������
		return -1;
	}

	// �J�����̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ���C�g�̐���
	m_pLight = new CLight;
	m_pLight->Init();

	// �T�E���h�̐���
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// �t�F�[�h�̐���
	m_pFade = new CFade;
	m_pFade->Init();

	// �f�o�b�N�\���̐���
	m_pDebug = new CDebugProc;
	m_pDebug->Init();

	//---------------------------------
	// �e�N�X�`���̓Ǎ�
	//---------------------------------
	CBullet::Load();		// �e
	CExplosion::Load();		// ����
	CEffect::Load();		// �G�t�F�N�g

	m_pTexture = new CTexture;
	m_pTexture->Load();

	//---------------------------------
	// �V�[���̐���
	//---------------------------------
	m_pScene = CScene::Create(CScene::MODE_TITLE);


	return S_OK;
}

//====================================================
// �I������
//====================================================
void CManager::Uninit(void)
{
	// ���ׂẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	//---------------------------------
	// �e�N�X�`���̔j��
	//---------------------------------
	CBullet::UnLoad();		// �e
	CExplosion::UnLoad();	// ����
	CEffect::UnLoad();		// �G�t�F�N�g

	if (m_pTexture != NULL)
	{
		// �e�N�X�`���̔j��
		m_pTexture->UnLoad();

		// �������̔j��
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// �J�����̔j��
	if (m_pCamera != NULL)
	{
		// �J�����̏I������
		m_pCamera->Uninit();

		// �������̔j��
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ���C�g�̔j��
	if (m_pLight != NULL)
	{
		// ���C�g�̏I������
		m_pLight->Uninit();

		// �������̔j��
		delete m_pLight;
		m_pLight = NULL;
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		// �T�E���h�̏I������
		m_pSound->Uninit();

		// �������̊J��
		delete m_pSound;
		m_pSound = NULL;
	}

	// �L�[�{�[�h�̔j��
	if (m_pKeyboard != NULL)
	{
		// �L�[�{�[�h�̏I������
		m_pKeyboard->Uninit();

		// �������̊J��
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	// �V�[���̔j��
	if (m_pFade != NULL)
	{
		// �V�[���̏I������
		m_pFade->Uninit();

		// �������̊J��
		delete m_pFade;
		m_pFade = NULL;
	}

	// �f�o�b�N�\���̔j��
	if (m_pDebug != NULL)
	{
		// �f�o�b�N�\���̏I������
		m_pDebug->Uninit();

		// �������̊J��
		delete m_pDebug;
		m_pDebug = NULL;
	}

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		//�����_���[�̏I������
		m_pRenderer->Uninit();

		// �������̊J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//====================================================
// �X�V����
//====================================================
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V����
	m_pKeyboard->Update();

	// �J�����̍X�V
	m_pCamera->Update();

	// ���C�g�̍X�V
	m_pLight->Update();

	// �f�o�b�N�\���̍X�V
	m_pDebug->Print("�I�u�W�F�N�g���F%d\n", CObject::GetNumAll());
	m_pDebug->Update();

	//�����_���[�̍X�V����
	m_pRenderer->Update();

#ifdef _DEBUG

	// �V�[����؂�ւ���
	if (m_pKeyboard->GetTrigger(DIK_F4) == true)
	{// �Q�[��
		//SetMode(CScene::MODE_GAME);
		m_pFade->Set(CScene::MODE_GAME);
	}
	else if (m_pKeyboard->GetTrigger(DIK_F5) == true)
	{// �^�C�g��
		//SetMode(CScene::MODE_TITLE);
		m_pFade->Set(CScene::MODE_TITLE);
	}
	else if (m_pKeyboard->GetTrigger(DIK_F6) == true)
	{// ����
		m_pFade->Set(CScene::MODE_RESULT);
	}

	// �z�u�G�f�B�^�[�ɐ؂�ւ���
	if (m_pKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		if (m_pKeyboard->GetTrigger(DIK_1) == true)
		{
			m_pFade->Set(CScene::MODE_EDIT_DISPOSITION);
		}
	}

#endif // _DEBUG

	// �t�F�[�h�̍X�V
	m_pFade->Update();
}

//====================================================
// �`�揈��
//====================================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//====================================================
// �Q�[�����[�h�̐ݒ菈��
//====================================================
void CManager::SetMode(CScene::MODE mode)
{
	// �T�E���h�̒�~
	m_pSound->StopAll();

	// ���݂̃��[�h�̔j��
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
	}

	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	// �V�������[�h�̐���
	m_pScene = CScene::Create(mode);
}

//====================================================
// ���݂̃Q�[�����[�h�̎擾
//====================================================
CScene::MODE CManager::GetMode(void)
{
	return m_pScene->GetMode();
}