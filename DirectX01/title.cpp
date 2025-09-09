//====================================================
//
// �^�C�g���V�[������ [title.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"title.h"
#include"object2D.h"
#include"manager.h"
#include"ranking.h"

// �ÓI�����o�ϐ�
CPlayer* CTitle::m_pPlayer = NULL;
CObject3D* CTitle::m_pObjecct3D = NULL;
CNoteManager* CTitle::m_pNoteManager = NULL;
CShockManager* CTitle::m_pShockManager = NULL;
CMeshSphere* CTitle::m_pSphere = NULL;

//====================================================
// �R���X�g���N�^
//====================================================
CTitle::CTitle() :CScene(CScene::MODE_TITLE)
{
	// �I�u�W�F�N�g�̎�ސݒ�
	CObject::SetType(CObject::TYPE_SCENE);

	// �J�����̐ݒ�
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);
}

//====================================================
// �f�X�g���N�^
//====================================================
CTitle::~CTitle()
{

}

//====================================================
// ����������
//====================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �e�N�X�`���̎擾
	CTexture* pTexture = CManager::GetTexture();

	// �J�����ʒu�̐ݒ�
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 575.0f, 525.0f), D3DXVECTOR3(0.0f, 200.0f, 0.0f));

	// �����̃}�l�[�W���[
	m_pNoteManager = new CNoteManager;
	m_pNoteManager->Init();

	// �Ռ��g�̃}�l�[�W���[
	m_pShockManager = new CShockManager;
	m_pShockManager->Init();

	// �|���S��
	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 600.0f);
	m_pObjecct3D->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.8f, 1.0f));
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);

	// �e�N�X�`���̊���
	if (pTexture != nullptr)
	{
		m_pObjecct3D->BindTexIndex(pTexture->TYPE_FILED);
		m_pSphere->BindTexIndex(pTexture->TYPE_SKY);
	}

	// �����̐���
	m_pNoteManager->Spawn();

	// �Ռ��g�̐���
	m_pShockManager->Place(1, 0);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CTitle::Uninit(void)
{
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
void CTitle::Update(void)
{
	// �X�y�[�X����������Q�[����
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) == true)
	{
		CManager::GetFade()->Set(CScene::MODE_GAME);
	}

	// ���̃J����Rot�̎擾
	D3DXVECTOR3 rotNow = CManager::GetCamera()->GetRot();

	rotNow.y += CAMERA_SPEED;

	// �J�����̌����ݒ�
	CManager::GetCamera()->SetRotation(rotNow);

	// �t���[���J�E���g�A�b�v
	m_nCntFream++;

	if (m_nCntFream >= 1800)
	{
		CRanking::SetMode(CRanking::MODE::MODE_DISPLAY);

		// �t���[�����Z�b�g
		m_nCntFream = 0;

		// �����L���O��
		CManager::GetFade()->Set(CScene::MODE_RANKING);
	}
}

//====================================================
// �`�揈��
//====================================================
void CTitle::Draw(void)
{
	// �Ȃ�
}