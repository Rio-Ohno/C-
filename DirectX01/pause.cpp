//====================================================
//
//�|�[�Y[pause.cpp]
//Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"pause.h"
#include"manager.h"
#include"game.h"

// �ÓI�����o�ϐ�
CObject2D* CPause::m_apObject2D[NUM_POLY] = { NULL };

//====================================================
// �R���X�g���N�^
//====================================================
CPause::CPause()
{
	m_mode = MENU_CONTINUE;
	m_nCntMenu = 1;

	for (int nCnt = 0; nCnt < NUM_POLY; nCnt++)
	{
		m_apObject2D[nCnt] = { NULL };
	}
}

//====================================================
// �f�X�g���N�^
//====================================================
CPause::~CPause()
{
	// �Ȃ�
}

//====================================================
// ��������
//====================================================
CPause* CPause::Create(void)
{
	CPause* pPause = NULL;

	// �������̊m��
	pPause = new CPause;

	// ����������
	pPause->Init();

	return pPause;
}

//====================================================
// ����������
//====================================================
HRESULT CPause::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_POLY; nCnt++)
	{
		if (nCnt == 0)//�w�i
		{
			m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 1280.0f, 520.0f);
			m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_PAUSE);
			m_apObject2D[nCnt]->SetType(CObject::TYPE_PAUSE);
		}
		else
		{
			m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 225.0f + 100.0f * nCnt, 0.0f), 600.0f, 50.0f);
			m_apObject2D[nCnt]->SetType(CObject::TYPE_PAUSE);
		}
	}

	m_apObject2D[1]->BindTexIndx(CTexture::TYPE_CONTEINUE);
	m_apObject2D[2]->BindTexIndx(CTexture::TYPE_RETRY);
	m_apObject2D[3]->BindTexIndx(CTexture::TYPE_QUIT);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_POLY; nCnt++)
	{
		if (m_apObject2D[nCnt] != NULL)
		{
			m_apObject2D[nCnt]->Uninit();
		}
	}
}

//====================================================
// �X�V����
//====================================================
void CPause::Update(void)
{
	// �L�[�{�[�h�̎擾
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	if (m_nCntMenu >= 1 && m_nCntMenu < 4)
	{
		if (pKeyboard->GetTrigger(DIK_DOWN) == true || pKeyboard->GetTrigger(DIK_S) == true)//���L�[�������ꂽ
		{
			m_nCntMenu++;
		}

		if (pKeyboard->GetTrigger(DIK_UP) == true || pKeyboard->GetTrigger(DIK_W) == true)//��L�[�������ꂽ
		{
			m_nCntMenu--;
		}
	}

	switch (m_nCntMenu)
	{
	case 1:

		m_mode = MENU_CONTINUE;

		// �|���S���̃A���t�@�l�ݒ�
		for (int nCountPause = 0; nCountPause < NUM_POLY; nCountPause++)
		{
			// �F�̐ݒ�
			if (nCountPause == 0 || nCountPause == 1)
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}


		break;

	case 2:

		m_mode = MENU_RETRY;

		// �|���S���̃A���t�@�l�ݒ�
		for (int nCountPause = 0; nCountPause < NUM_POLY; nCountPause++)
		{
			// �F�̐ݒ�
			if (nCountPause == 0 || nCountPause == 2)
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}

		break;

	case 3:

		m_mode = MENU_QUIT;

		// �|���S���̃A���t�@�l�ݒ�
		for (int nCountPause = 0; nCountPause < NUM_POLY; nCountPause++)
		{
			// �F�̐ݒ�
			if (nCountPause == 0 || nCountPause == 3)
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}
		break;

	default:


		// �I�����𒴂����Ƃ�
		if (m_nCntMenu >= 4)
		{
			m_nCntMenu = 1;
			m_mode = MENU_CONTINUE;
		}
		else if (m_nCntMenu < 1)
		{
			m_nCntMenu = 3;
			m_mode = MENU_QUIT;
		}

		// �|���S���̃A���t�@�l�ݒ�
		for (int nCountPause = 0; nCountPause < NUM_POLY; nCountPause++)
		{
			// �F�̐ݒ�
			if (nCountPause == 0 || nCountPause == m_nCntMenu)
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}

		break;
	}

	//����L�[�������ꂽ�Ƃ�
	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		switch (m_mode)
		{
		case MENU_CONTINUE:

			CGame::SetPause(false);

			break;

		case MENU_RETRY:

			 // �Q�[���֑J��
			CManager::GetFade()->Set(CScene::MODE_GAME);

			break;

		case MENU_QUIT:

			// �^�C�g���֑J��
			CManager::GetFade()->Set(CScene::MODE_TITLE);

			break;
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CPause::Draw(void)
{
	// �Ȃ�
}