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
#include"objectBillboard.h"
#include"meshfield.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"note.h"

//�ÓI�����o�ϐ�
CRenderer* CManager::m_pRenderer = NULL;
CKeyboard* CManager::m_pKeyboard = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CEnemy* CManager::m_pEnemy[MAX_ENEMY] = { NULL };
CBGManager* CManager::m_BGManager = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CTexture* CManager::m_pTexture = NULL;
CLoadMotion* CManager::m_pLoadMotion = NULL;
CScore* CManager::m_pScore = NULL;
CObject3D* CManager::m_pObjecct3D = NULL;

//�ÓI�����o�֐�
CRenderer* CManager::GetRenderer(void) { return m_pRenderer; };
CKeyboard* CManager::GetKeyboard(void) { return m_pKeyboard; };
CPlayer* CManager::GetPlayer(void) { return m_pPlayer; };
CCamera* CManager::GetCamera(void) { return m_pCamera; };
CLight* CManager::GetLight(void) { return m_pLight; };
CTexture* CManager::GetTexture(void) { return m_pTexture; };
CLoadMotion* CManager::GetLoadMotion(void) { return m_pLoadMotion; };
CScore* CManager::GetScore(void) { return m_pScore; };
CObject3D* CManager::GetObject3D(void) { return m_pObjecct3D; };

CNote* g_Item = { NULL };

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

	// ���C�g�̐ݒ�
	m_pLight = new CLight;
	m_pLight->Init();

	//---------------------------------
	// �e�N�X�`���̓Ǎ�
	//---------------------------------
	CBullet::Load();		// �e
	CExplosion::Load();		// ����
	CEffect::Load();		// �G�t�F�N�g

	m_pTexture = new CTexture;
	m_pTexture->Load();

	//---------------------------------
	// �I�u�W�F�N�g�̐���
	//---------------------------------
	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f);
	m_pObjecct3D->BindTexIndex(m_pTexture->TYPE_FILED);
	//CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 3, 3, 100, 100);

	m_pScore = CScore::Create(D3DXVECTOR3(1250.0f, 50.0f, 0.0f), 50.0f, 100.0f);
	g_Item = CNote::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer->SetMotion("data/MODEL/player/motion.txt");
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �v���C���[

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

	// �L�[�{�[�h�̔j��
	if (m_pKeyboard != NULL)
	{
		// �L�[�{�[�h�̏I������
		m_pKeyboard->Uninit();

		// �������̊J��
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		//�����_���[�̏I������
		m_pRenderer->Uninit();

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

	//�����_���[�̍X�V����
	m_pRenderer->Update();
}

//====================================================
// �`�揈��
//====================================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}