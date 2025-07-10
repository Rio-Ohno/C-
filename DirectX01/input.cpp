//====================================================
// 
// ���͏���[input.cpp]
// Author:Rio Ohno
// 
//====================================================

// �C���N���[�h
#include"input.h"

//�ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//====================================================
// ���͂̃R���X�g���N�^
//====================================================
CInput::CInput()
{
	// �l���N���A�ɂ���
	m_pDevice = NULL;
}

//====================================================
// ���͂̃f�X�g���N�^
//====================================================
CInput::~CInput()
{

}

//====================================================
// ���͂̏���������
//====================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}	

//====================================================
// ���͂̏I������
//====================================================
void CInput::Uninit()
{	
	//���̓f�o�C�X�i�L�[�{�[�h�j�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

}

//====================================================
// �L�[�{�[�h�̃R���X�g���N�^
//====================================================
CKeyboard::CKeyboard()
{
	// �l���N���A����
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = { NULL };
		m_aOldKeyState[nCnt] = { NULL };
	}
}

//====================================================
// �L�[�{�[�h�̃f�X�g���N�^
//====================================================
CKeyboard::~CKeyboard()
{

}

//====================================================
//�L�[�{�[�h�̏���������
//====================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���͂̏���������
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//====================================================
//�L�[�{�[�h�̏I������
//====================================================
void CKeyboard::Uninit()
{
	//���͂̏I������
	CInput::Uninit();
	
	//���̓f�o�C�X�i�L�[�{�[�h�j�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//====================================================
//�L�[�{�[�h�̍X�V����
//====================================================
void CKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aOldKeyState[nCntKey] = m_aKeyState[nCntKey];//��O�̏����擾
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃v���X�����擾
		}
	}
	else
	{
		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
		m_pDevice->Acquire();
	}
}

//====================================================
//�L�[�{�[�h�̃v���X�����擾
//====================================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//====================================================
//�L�[�{�[�h�̉����ꂽ�u��
//====================================================
bool CKeyboard::GetTrigger(int nKey)
{
	bool Trigger = false;
	if (m_aKeyState[nKey] & 0x80 && !(m_aOldKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//====================================================
//�L�[�{�[�h�𗣂����u��
//====================================================
bool CKeyboard::GetRelease(int nKey)
{
	bool Trigger = false;
	if (m_aOldKeyState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//====================================================
//�L�[�{�[�h�����Ă鎞��
//====================================================
bool CKeyboard::GetRepeat(int nKey)
{
	bool Trigger = false;
	if (m_aOldKeyState[nKey] & 0x80 && (m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//====================================================
// �}�E�X�̃R���X�g���N�^
//====================================================
CMouse::CMouse()
{

}

//====================================================
// �}�E�X�̃f�X�g���N�^
//====================================================
CMouse::~CMouse()
{

}

//====================================================
// �}�E�X�̏���������
//====================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//���͂̏�����
	CInput::Init(hInstance, hWnd);

	if (FAILED(m_pInput->CreateDevice(
		GUID_SysMouse,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X�����l��
	if (FAILED(m_pDevice->Acquire()))
	{
		return E_FAIL;
	}

	// �|�[�����O(�������)
	if (FAILED(m_pDevice->Poll()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//====================================================
// �}�E�X�̏I������
//====================================================
void CMouse::Uninit(void)
{
	//���͂̏���������
	CInput::Uninit();

	//���̓f�o�C�X�i�}�E�X�j�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//====================================================
// �}�E�X�̍X�V����
//====================================================
void CMouse::Update(void)
{
	// �O�̏���ۑ�
	m_oldMouseState = m_MouseState;

	//�}�E�X�̍X�V
	if (FAILED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState)))
	{
		// �A�N�Z�X���̎擾
		m_pDevice->Acquire();

		//�}�E�X�̍X�V
		m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState);
	}
}

//====================================================
// �}�E�X�̃N���b�N�̎擾����
//====================================================
bool CMouse::ButtonPress(int nButton)
{
	return (m_MouseState.rgbButtons[nButton] & 0x80) ? true : false;
}

//====================================================
// �}�E�X�̃N���b�N�����u��
//====================================================
bool CMouse::OnButtonDown(int nButton)
{
	if (!(m_oldMouseState.rgbButtons[nButton] & (0x80)) && m_MouseState.rgbButtons[nButton] & (0x80))
	{
		return true;
	}
	return false;
}

//====================================================
// �}�E�X�̃N���b�N�������u��
//====================================================
bool CMouse::OnButtonUp(int nButton)
{
	if (m_oldMouseState.rgbButtons[nButton] & (0x80) &&
		!(m_MouseState.rgbButtons[nButton] & (0x80)))
	{
		return true;
	}
	return false;
}

//====================================================
//�}�E�X�̉����Ă鎞��
//====================================================
bool CMouse::GetRepeat(int nButton)
{
	if (m_oldMouseState.rgbButtons[nButton] & 0x80 && (m_MouseState.rgbButtons[nButton] & 0x80))
	{
		return true;
	}
	return false;
}

////=============================================================================================================
////�W���C�p�b�h�̏���������
////=============================================================================================================
//HRESULT InitJoypad()
//{
//	//�������̃N���A
//	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));
//
//	//XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
//	XInputEnable(true);
//
//	return S_OK;
//}
//
////=============================================================================================================
////�W���C�p�b�h�̏I������
////=============================================================================================================
//void UninitJoypad()
//{
//	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
//	XInputEnable(false);
//}
//
////=============================================================================================================
////�W���C�p�b�h�̍X�V����
////=============================================================================================================
//void UpdateJoypad()
//{
//	XINPUT_STATE joykeyState;//�W���C�p�b�h�̓��͏��
//
//	//�W���C�p�b�h�̏�Ԃ��擾
//	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
//	{
//		g_joyKeyState = joykeyState;
//	}
//}
//
////=============================================================================================================
////�W���C�p�b�h�̃v���X�����擾
////=============================================================================================================
//bool GetJoypadPress(JOYKEY key)
//{
//	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
//}