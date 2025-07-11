//====================================================
// 
// 入力処理[input.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include"input.h"

//静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//====================================================
// 入力のコンストラクタ
//====================================================
CInput::CInput()
{
	// 値をクリアにする
	m_pDevice = NULL;
}

//====================================================
// 入力のデストラクタ
//====================================================
CInput::~CInput()
{

}

//====================================================
// 入力の初期化処理
//====================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}	

//====================================================
// 入力の終了処理
//====================================================
void CInput::Uninit()
{	
	//入力デバイス（キーボード）の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

}

//====================================================
// キーボードのコンストラクタ
//====================================================
CKeyboard::CKeyboard()
{
	// 値をクリアする
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = { NULL };
		m_aOldKeyState[nCnt] = { NULL };
	}
}

//====================================================
// キーボードのデストラクタ
//====================================================
CKeyboard::~CKeyboard()
{

}

//====================================================
//キーボードの初期化処理
//====================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 入力の初期化処理
	CInput::Init(hInstance, hWnd);

	//入力デバイス（キーボード）の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//====================================================
//キーボードの終了処理
//====================================================
void CKeyboard::Uninit()
{
	//入力の終了処理
	CInput::Uninit();
	
	//入力デバイス（キーボード）の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//====================================================
//キーボードの更新処理
//====================================================
void CKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aOldKeyState[nCntKey] = m_aKeyState[nCntKey];//一つ前の情報を取得
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードのプレス情報を取得
		}
	}
	else
	{
		//キーボードへのアクセス権を獲得
		m_pDevice->Acquire();
	}
}

//====================================================
//キーボードのプレス情報を取得
//====================================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//====================================================
//キーボードの押された瞬間
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
//キーボードを離した瞬間
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
//キーボード押してる時間
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
// マウスのコンストラクタ
//====================================================
CMouse::CMouse()
{

}

//====================================================
// マウスのデストラクタ
//====================================================
CMouse::~CMouse()
{

}

//====================================================
// マウスの初期化処理
//====================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//入力の初期化
	CInput::Init(hInstance, hWnd);

	if (FAILED(m_pInput->CreateDevice(
		GUID_SysMouse,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//マウスへのアクセス権を獲得
	if (FAILED(m_pDevice->Acquire()))
	{
		return E_FAIL;
	}

	// ポーリング(競合回避)
	if (FAILED(m_pDevice->Poll()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//====================================================
// マウスの終了処理
//====================================================
void CMouse::Uninit(void)
{
	//入力の初期化処理
	CInput::Uninit();

	//入力デバイス（マウス）の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//====================================================
// マウスの更新処理
//====================================================
void CMouse::Update(void)
{
	// 前の情報を保存
	m_oldMouseState = m_MouseState;

	//マウスの更新
	if (FAILED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState)))
	{
		// アクセス権の取得
		m_pDevice->Acquire();

		//マウスの更新
		m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState);
	}
}

//====================================================
// マウスのクリックの取得処理
//====================================================
bool CMouse::ButtonPress(int nButton)
{
	return (m_MouseState.rgbButtons[nButton] & 0x80) ? true : false;
}

//====================================================
// マウスのクリックした瞬間
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
// マウスのクリック離した瞬間
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
//マウスの押してる時間
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
////ジョイパッドの初期化処理
////=============================================================================================================
//HRESULT InitJoypad()
//{
//	//メモリのクリア
//	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));
//
//	//XInputのステートを設定(有効にする)
//	XInputEnable(true);
//
//	return S_OK;
//}
//
////=============================================================================================================
////ジョイパッドの終了処理
////=============================================================================================================
//void UninitJoypad()
//{
//	//XInputのステートを設定(無効にする)
//	XInputEnable(false);
//}
//
////=============================================================================================================
////ジョイパッドの更新処理
////=============================================================================================================
//void UpdateJoypad()
//{
//	XINPUT_STATE joykeyState;//ジョイパッドの入力情報
//
//	//ジョイパッドの状態を取得
//	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
//	{
//		g_joyKeyState = joykeyState;
//	}
//}
//
////=============================================================================================================
////ジョイパッドのプレス情報を取得
////=============================================================================================================
//bool GetJoypadPress(JOYKEY key)
//{
//	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
//}