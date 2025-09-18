//====================================================
//
//�J����[camera.cpp]
//Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"camera.h"
#include"manager.h"
#include"game.h"
#include"tutorial.h"
#include"input.h"

//====================================================
// �R���X�g���N�^
//====================================================
CCamera::CCamera()
{
	// �e�l�̏�����
	m_posV = D3DXVECTOR3(0.0f, 70.0f, -200.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NOMAL;
	m_fDistance = 0;
	m_bAssent = false;
}

//====================================================
// �f�X�g���N�^
//====================================================
CCamera::~CCamera()
{
	// �Ȃ�
}

//====================================================
// �J�����̏���������
//====================================================
HRESULT CCamera::Init(void)
{
	//�e�평����
	m_posV = D3DXVECTOR3(0.0f, 175.0f,-300.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bAssent = false;
	m_type = TYPE_NOMAL;

	////�r���[�|�[�g�̐ݒ�
	//m_viewport.X = (DWORD)0.0f;
	//m_viewport.Y = (DWORD)0.0f;
	//m_viewport.Width = 1280;
	//m_viewport.Height = 720;

	//���_���璍���_�̋����v�Z
	float fDisX = m_posR.x - m_posV.x;
	float fDisY = m_posR.y - m_posV.y;
	float fDisZ = m_posR.z - m_posV.z;

	// �p�x�����߂�
	float fRotX = atan2f(-fDisZ, -fDisY);

	//�Ίp���̒������Z�o����
	m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

	// �p�x�̐ݒ�
	m_rot.x = (float)fRotX + D3DX_PI;

	return S_OK;
}

//====================================================
// �J�����̏I������
//====================================================
void CCamera::Uninit(void)
{

}

//====================================================
//�J�����̍X�V����
//====================================================
void CCamera::Update(void)
{
	CDebugProc::Print("Camera PosR�F{%f, %f, %f}\n", m_posR.x, m_posR.y, m_posR.z);
	CDebugProc::Print("Camera PosV�F{%f, %f, %f}\n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("Camera rot�F{%f, %f, %f}\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("Camera Distance�F%f\n", m_fDistance);

	//�L�[�{�[�h�̎擾
	CKeyboard* pKeyboard = CManager::GetKeyboard();

#ifdef _DEBUG 
	//���Z�b�g================================================================================
	if (pKeyboard->GetTrigger(DIK_R) == true)
	{
		// ����������
		CCamera::Init();
	}

	//�Ǐ]�̃I���I�t
	if (pKeyboard->GetTrigger(DIK_F) == true)
	{
		m_bAssent = m_bAssent ? false : true;
	}
#endif

	if (CManager::GetMode() == CScene::MODE_GAME || CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		if (m_bAssent == false)
		{
			m_type = TYPE_NOMAL;
		}
		else if (m_bAssent == true)
		{
			m_type = TYPE_ASSENT;
		}
	}

#ifdef _DEBUG

	if (m_type == TYPE_NOMAL)
	{
		//�����_�̐���============================================================================
		if (pKeyboard->GetPress(DIK_LEFT) == true)
		{
			m_rot.y -= 0.01f;

			//�ڕW�̈ړ������i�p�x�j�̕␳
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
		}
		else if (pKeyboard->GetPress(DIK_RIGHT) == true)
		{
			m_rot.y += 0.01f;

			//�ڕW�̈ړ������i�p�x�j�̕␳
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
		}

		//�J�����̈ړ�============================================================================
		if (pKeyboard->GetPress(DIK_I) == true)
		{
			m_posV.x += (float)(sinf(m_rot.x) * sinf(m_rot.y) * 1.0f);
			m_posV.z += (float)(sinf(m_rot.x) * cosf(m_rot.y) * 1.0f);

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
		}
		else if (pKeyboard->GetPress(DIK_K) == true)
		{
			m_posV.x -= (float)(sinf(m_rot.x) * sinf(m_rot.y) * 1.0f);
			m_posV.z -= (float)(sinf(m_rot.x) * cosf(m_rot.y) * 1.0f);

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

		}
		else if (pKeyboard->GetPress(DIK_J) == true)
		{

			m_posV.x -= (float)(sinf(m_rot.x) * sinf(m_rot.y + D3DX_PI / 2.0f) * 1.0f);
			m_posV.z -= (float)(sinf(m_rot.x) * cosf(m_rot.y + D3DX_PI / 2.0f) * 1.0f);

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

		}
		else if (pKeyboard->GetPress(DIK_L) == true)
		{

			m_posV.x += (float)(sinf(m_rot.x) * sinf(m_rot.y + D3DX_PI / 2.0f) * 1.0f);
			m_posV.z += (float)(sinf(m_rot.x) * cosf(m_rot.y + D3DX_PI / 2.0f) * 1.0f);

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

		}
		//else if (GetKeyboardPress(DIK_T) == true)
		//{
		//	m_.posV.y += 0.05f;
		//	m_.posR.y = m_.posV.y;
		//}
		//else if (GetKeyboardPress(DIK_G) == true)
		//{
		//	m_.posV.y -= 0.05f;
		//	m_.posR.y = m_.posV.y;
		//}
	}
#endif // DEBUG
	//�Ǐ]====================================================================================
	
	if (m_type == TYPE_ASSENT)
	{
		// �v���C���[�|�C���^
		CPlayer* pPlayer = NULL;

		// �v���C���[�̏��擾
		if (CManager::GetMode() == CScene::MODE_TUTORIAL)
		{
			pPlayer = CTutorial::GetPlayer();
		}
		else if (CManager::GetMode() == CScene::MODE_GAME)
		{
			pPlayer = CGame::GetPlayer();
		}

		if (pPlayer != nullptr)
		{
			//�ړI�̒l
			m_posRDest.x = pPlayer->GetPos().x + sinf(pPlayer->GetRot().y);
			m_posRDest.y = pPlayer->GetPos().y * 0.5f;
			m_posRDest.z = pPlayer->GetPos().z + cosf(pPlayer->GetRot().y);

			m_posVDest.x = pPlayer->GetPos().x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posVDest.y = pPlayer->GetPos().y * 0.5f - (float)(cosf(m_rot.x) * m_fDistance);
			m_posVDest.z = pPlayer->GetPos().z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

			//
			m_posR.x += (m_posRDest.x - m_posR.x) * 0.09f;
			m_posR.y += (m_posRDest.y - m_posR.y) * 0.09f;
			m_posR.z += (m_posRDest.z - m_posR.z) * 0.09f;

			m_posV.x += (m_posVDest.x - m_posV.x) * 0.09f;
			m_posV.y += (m_posVDest.y - m_posV.y) * 0.09f;
			m_posV.z += (m_posVDest.z - m_posV.z) * 0.09f;
		}

	}

	//���_�̐���============================================================================
	if (pKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y -= 0.01f;

		//�ڕW�̈ړ������i�p�x�j�̕␳
		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}

		m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
		m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
		m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

	}
	else if (pKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y += 0.01f;

		//�ڕW�̈ړ������i�p�x�j�̕␳
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}

		m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
		m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
		m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
	}

#ifdef _DEBUG
	if (pKeyboard->GetPress(DIK_Y) == true)
	{

		if (m_rot.x + 0.01f <= D3DX_PI)
		{
			m_rot.x += 0.01f;
		}

		m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
		m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
		m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
	}
	else if (pKeyboard->GetPress(DIK_H) == true)
	{
		if (m_rot.x - 0.01f >= 0.0f)
		{
			m_rot.x -= 0.01f;
		}

		m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
		m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
		m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
	}

	//���_��Y���ړ�============================================================================
	if (pKeyboard->GetPress(DIK_T) == true)
	{
		m_posV.y += 0.5f;

		//���_���璍���_�̋����v�Z
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//�Ίp���̒������Z�o����
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// �p�x�����߂�
		float fRotX = atan2f(-fDisZ, -fDisY);

		// �p�x�̐ݒ�
		m_rot.x = (float)fRotX + D3DX_PI;
	}
	else if (pKeyboard->GetPress(DIK_G) == true)
	{
		m_posV.y -= 0.5f;

		//���_���璍���_�̋����v�Z
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//�Ίp���̒������Z�o����
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// �p�x�����߂�
		float fRotX = atan2f(-fDisZ, -fDisY);

		// �p�x�̐ݒ�
		m_rot.x = (float)fRotX + D3DX_PI;
	}

	//���_��Z���ړ�============================================================================
	if (pKeyboard->GetPress(DIK_0) == true)
	{
		m_posV.z += 0.5f;

		//���_���璍���_�̋����v�Z
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//�Ίp���̒������Z�o����
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// �p�x�����߂�
		float fRotX = atan2f(-fDisZ, -fDisY);

		// �p�x�̐ݒ�
		m_rot.x = (float)fRotX + D3DX_PI;
	}
	else if(pKeyboard->GetPress(DIK_P) == true)
	{
		m_posV.z -= 0.5f;

		//���_���璍���_�̋����v�Z
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//�Ίp���̒������Z�o����
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// �p�x�����߂�
		float fRotX = atan2f(-fDisZ, -fDisY);

		// �p�x�̐ݒ�
		m_rot.x = (float)fRotX + D3DX_PI;
	}

	//�����_��Y���ړ�============================================================================
	if (pKeyboard->GetPress(DIK_7) == true)
	{
		m_posR.y += 0.5f;

		//���_���璍���_�̋����v�Z
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//�Ίp���̒������Z�o����
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// �p�x�����߂�
		float fRotX = atan2f(-fDisZ, -fDisY);

		// �p�x�̐ݒ�
		m_rot.x = (float)fRotX + D3DX_PI;
	}
	else if (pKeyboard->GetPress(DIK_U) == true)
	{
		m_posR.y -= 0.5f;

		//���_���璍���_�̋����v�Z
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//�Ίp���̒������Z�o����
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// �p�x�����߂�
		float fRotX = atan2f(-fDisZ, -fDisY);

		// �p�x�̐ݒ�
		m_rot.x = (float)fRotX + D3DX_PI;
	}
#endif
}

//====================================================
// �J�����̐ݒ菈��
//====================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(40.0f),
														(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
														10.0f,
														2000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//====================================================
// �J�����̎�ސݒ�
//====================================================
void CCamera::SetType(TYPE type)
{
	m_type = type;

	if (type == TYPE_ASSENT)
	{
		m_bAssent = true;
	}
	else
	{
		m_bAssent = false;
	}
}

//====================================================
// �J������Pos�ݒ�
//====================================================
void CCamera::SetCameraPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	//���_���璍���_�̋����v�Z
	float fDisX = posR.x - posV.x;
	float fDisY = posR.y - posV.y;
	float fDisZ = posR.z - posV.z;

	//�Ίp���̒������Z�o����
	m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

	// �p�x�����߂�
	float fRotX = atan2f(-fDisZ, -fDisY);

	// �p�x�̐ݒ�
	m_rot.x = (float)fRotX + D3DX_PI;

	m_posR = posR;

	m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
	m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
	m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
}

//====================================================
// �J������Rot�ݒ�
//====================================================
void CCamera::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;

	//�ڕW�̈ړ������i�p�x�j�̕␳
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
	m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
	m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
}