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
CObject3D* CTitle::m_pObjecct3D = NULL;
CNoteManager* CTitle::m_pNoteManager = NULL;
CShockManager* CTitle::m_pShockManager = NULL;
CObject2D* CTitle::m_apObject2D[NUM_POLYGON] = { NULL };

//====================================================
// �R���X�g���N�^
//====================================================
CTitle::CTitle() :CScene(CScene::MODE_TITLE)
{
	// �I�u�W�F�N�g�̎�ސݒ�
	CObject::SetType(CObject::TYPE_SCENE);

	// �J�����̐ݒ�
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);

	// �e�ϐ��̏�����
	m_nCntMenu = 0;// ���j���[�J�E���^
	m_nCntFream = 0;// �t���[���J�E���^
	m_Menu = MENU_GAME;
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
	// �J�����ʒu�̐ݒ�
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 575.0f, 525.0f), D3DXVECTOR3(0.0f, 200.0f, 0.0f));

	// �����̃}�l�[�W���[�̐���
	m_pNoteManager = new CNoteManager;
	m_pNoteManager->Init();

	// �Ռ��g�̃}�l�[�W���[�̐���
	m_pShockManager = new CShockManager;
	m_pShockManager->Init();

	// 3D�|���S���̐���
	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 600.0f);
	m_pObjecct3D->BindTexIndex(CTexture::TYPE_FILED);// �e�N�X�`���̊���
	m_pObjecct3D->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.8f, 1.0f));// �F�̐ݒ�

	// ��
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 100.0f, true, true);
			break;

		case 1:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 600.0f, 100.0f, true, true);
			break;

		case 2:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(300.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, true, true);
			break;

		case 3:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(-300.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, true, true);
			break;
		}

		m_apWall[nCnt]->SetColor(D3DXCOLOR(0.4f, 0.9f, 0.7f, 1.0f));
		m_apWall[nCnt]->BindTexIndex(CTexture::TYPE_FILED);
		m_apWall[nCnt]->SetTexUV(0.0f, 1.0f, 0.0f, 0.25f);
	}


	// ����(��)�̐���
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);// �e�N�X�`���̊���

	// 2D�|���S���̐���
	for (int nCnt = 0; nCnt < NUM_POLYGON; nCnt++)
	{
		if (nCnt == 0)// �^�C�g��
		{
			m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 200.0f, 0.0f), 800.0f, 150.0f);
			m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_TITLE);
		}
		else if (nCnt == 3)// �X�y�[�X�L�[
		{
			m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(950.0f, 490.0f, 0.0f), 200.0f, 200.0f);
			m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_SPACE);
			// memo  GAME:490  TUTORIAL:610
		}
		else// �I����
		{

			// �e�N�X�`���̊���
			if (nCnt == 1)
			{
				m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 300.0f + 120.0f * nCnt, 0.0f), 600.0f, 90.0f);
				m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_GAME);
			}
			else
			{
				m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 300.0f + 120.0f * nCnt, 0.0f), 450.0f, 90.0f);
				m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_TUTORIAL);
			}
		}
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

	// ���[�h�̑I��
	CTitle::SelectMode();

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
	else if ((m_nCntFream % 30) == 0)
	{
		// �_�ŏ���
		if ((m_nCntFream % 60) == 0)
		{
			// �F�̐ݒ�
			m_apObject2D[3]->CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			// �F�̐ݒ�
			m_apObject2D[3]->CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.8f, 1.0f));
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CTitle::Draw(void)
{
	// �Ȃ�
}

//====================================================
// ���[�h�I������
//====================================================
void CTitle::SelectMode(void)
{
	// �L�[�{�[�h�̎擾
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	if (m_nCntMenu >= 0 && m_nCntMenu < MENU_MAX)
	{
		if (pKeyboard->GetTrigger(DIK_DOWN) == true || pKeyboard->GetTrigger(DIK_S) == true)//���L�[�������ꂽ
		{
			m_nCntMenu++;
		}

		if (pKeyboard->GetTrigger(DIK_UP) == true || pKeyboard->GetTrigger(DIK_W) == true)//��L�[�������ꂽ
		{
			m_nCntMenu--;
		}

		switch (m_nCntMenu)
		{
		case 0:

			m_Menu = MENU_GAME;

			// �|���S���̃A���t�@�l�ݒ�
			for (int nCount = 0; nCount < NUM_POLYGON; nCount++)
			{
				// �ʒu�̐ݒ�
				if (nCount == 3)
				{
					m_apObject2D[nCount]->SetPos(D3DXVECTOR3(950.0f, 490.0f, 0.0f));
				}

				// �F�̐ݒ�
				if (nCount == 2)
				{
					m_apObject2D[nCount]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
				}
				else if (nCount == 3)
				{
					// �Ȃ�(�F�������Ȃ�����)
				}
				else
				{
					m_apObject2D[nCount]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}


			break;

		case 1:

			m_Menu = MENU_TUTORIAL;

			// �|���S���̃A���t�@�l�ݒ�
			for (int nCount = 0; nCount < NUM_POLYGON; nCount++)
			{
				// �ʒu�̐ݒ�
				if (nCount == 3)
				{
					m_apObject2D[nCount]->SetPos(D3DXVECTOR3(950.0f, 610.0f, 0.0f));
				}

				// �F�̐ݒ�
				if (nCount == 1)
				{
					m_apObject2D[nCount]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
				}
				else if (nCount == 3)
				{
					// �Ȃ�(�F�������Ȃ�����)
				}
				else
				{
					m_apObject2D[nCount]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}

			break;

		default:


			// �I�����𒴂����Ƃ�
			if (m_nCntMenu >= MENU_MAX)
			{
				m_nCntMenu = 0;
				m_Menu = MENU_GAME;
			}
			else if (m_nCntMenu < 0)
			{
				m_nCntMenu = 1;
				m_Menu = MENU_TUTORIAL;
			}

			break;
		}

	}

	//����L�[�������ꂽ�Ƃ�
	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		switch (m_Menu)
		{
		case MENU_GAME:

			// �Q�[���֑J��
			CManager::GetFade()->Set(CScene::MODE_GAME);

			break;

		case MENU_TUTORIAL:

			// �Q�[���֑J��
			CManager::GetFade()->Set(CScene::MODE_TUTORIAL);

			break;

		}
	}
}