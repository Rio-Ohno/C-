//====================================================
//
// �`���[�g���A���V�[������ [tutorial.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"tutorial.h"
#include"manager.h"
#include"shockwave.h"

// �ÓI�����o�ϐ�
CPlayer* CTutorial::m_pPlayer = NULL;
CScore* CTutorial::m_pScore = NULL;
CObject3D* CTutorial::m_pObject3D = NULL;
CNoteManager* CTutorial::m_pNoteManager = NULL;
CShockManager* CTutorial::m_pShockManager = NULL;
CMeshSphere* CTutorial::m_pSphere = NULL;

//====================================================
// �R���X�g���N�^
//====================================================
CTutorial::CTutorial()
{
	// �J�����̏���������
	CManager::GetCamera()->Init();

	// ��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_SCENE);

	// �|�[�Y���Ă��Ȃ���Ԃ�
	CObject::SetPause(false);

	// �e�ϐ��̏�����
	m_nCntFream = 0;
	m_nCntNoteSpan = 0;
	m_bMove = true;
}

//====================================================
// �f�X�g���N�^
//====================================================
CTutorial::~CTutorial()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{

	// �J�����̎�ސݒ�
	CManager::GetCamera()->SetType(CCamera::TYPE_ASSENT);

	//----------------------------------------------------
	// ��������
	//----------------------------------------------------

	// �����̃}�l�[�W���[
	m_pNoteManager = new CNoteManager;
	m_pNoteManager->Init();

	// 3D�|���S��
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 500.0f, false, false);
	m_pObject3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 600.0f);
	m_pObject3D->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.8f, 1.0f));

	// ��
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 100.0f, false, true);
			break;

		case 1:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 600.0f, 100.0f, false, true);
			break;

		case 2:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(300.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, false, true);
			break;

		case 3:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(-300.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, false, true);
			break;
		}

		m_apWall[nCnt]->SetColor(D3DXCOLOR(0.4f, 0.9f, 0.7f, 1.0f));
		m_apWall[nCnt]->BindTexIndex(CTexture::TYPE_FILED);
		m_apWall[nCnt]->SetTexUV(0.0f, 1.0f, 0.0f, 0.25f);
	}

	for (int nCnt = 4; nCnt < 8; nCnt++)
	{
		switch (nCnt)
		{
		case 4:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 600.0f, 100.0f, true, false);
			break;

		case 5:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 100.0f, true, false);
			break;

		case 6:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, true, false);
			break;

		case 7:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, true, false);
			break;
		}
	}

	// �X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(1250.0f, 50.0f, 0.0f), 7, 50.0f, 100.0f);

	// �v���C���[
	m_pPlayer->SetMotion("data/MODEL/player/motion.txt");
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �v���C���[

	// �e�N�X�`���̊���
	m_pObject3D->BindTexIndex(CTexture::TYPE_FILED);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);

	// 2D�|���S��
	CObject2D* pBack = CObject2D::Create(D3DXVECTOR3(1220.0f, 150.0f, 0.0f), 100.0f, 100.0f);
	pBack->BindTexIndx(CTexture::TYPE_BACK_X);
	pBack->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f));

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CTutorial::Uninit(void)
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
void CTutorial::Update(void)
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_X) == true)
	{
		// �t�F�[�h���擾
		CFade* fade = CManager::GetFade();

		// �^�C�g���փV�[����ς���
		fade->Set(CScene::MODE_TITLE);
	}

	if (m_bMove == true)
	{
		// �t���[���J�E���g�A�b�v
		m_nCntFream++;

		if (m_nCntFream >= FREAM_MOVE)
		{
			m_bMove = false;

			//// �Ռ��g�̃}�l�[�W���[�̐���
			m_pShockManager = new CShockManager;
			m_pShockManager->Init();

			// �p�^�[���̎w��
			m_pShockManager->Place(1,0);

			// �t���[���J�E���g���Z�b�g
			m_nCntFream = 0;
		}
	}
	else
	{
		if (m_pShockManager != NULL)
		{
			m_pShockManager->Update();
		}
	}

	// �����̃}�l�[�W���[�̍X�V����
	if (m_pNoteManager->GetNum() <= 0)// �������S�ĂƂ�ꂽ�Ȃ�
	{
		// �t���[���J�E���g
		m_nCntNoteSpan++;

		if (m_nCntNoteSpan >= 90)// 90�t���[���o������
		{
			// �����̌Ăяo��(����)
			m_pNoteManager->Spawn();

			// �t���[���J�E���g���Z�b�g
			m_nCntNoteSpan = 0;
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CTutorial::Draw(void)
{
	// �Ȃ�
}