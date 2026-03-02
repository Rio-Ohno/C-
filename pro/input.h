//====================================================
// 
// 入力処理[input.h]
// Author:Rio Ohno
// 
//==================================================== 

#ifndef _INPUT_H_
#define _INPUT_H_

// インクルード
#include"main.h"

// 入力クラス
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

// キーボードクラス
class CKeyboard :public CInput
{
public:
	CKeyboard();
	~CKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

	bool GetPressAnyBotton(void);
	int GetLastFream(void) { return m_nCntLastFream; }

private:

	// constexpr
	static constexpr int NUM_KEY_MAX = 256;//キーの最大数

	int m_nCntLastFream;		// 最後の入力からのフレーム
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aOldKeyState[NUM_KEY_MAX];
};

// マウス(ボタン)クラス
class CMouse :public CInput
{
public:

	// マウスボタンの種類
	typedef enum
	{
		BOTTON_LEFT = 0,
		BOTTON_RIGHT,
		BOTTON_WHEEL,
		BOTTON_MAX
	}BOTTON;

	CMouse();
	~CMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool ButtonPress(int nButton);
	bool OnButtonDown(int nButton);
	bool OnButtonUp(int nButton);
	bool GetRepeat(int nButton);
	D3DXVECTOR3 GetScreenCursorPosition(void);

private:
	DIMOUSESTATE m_MouseState;
	DIMOUSESTATE m_oldMouseState;
	HWND m_hWnd;
};

// ジョイパッドクラス
class CJoypad :public CInput
{
public:

	//キー入力の種類
	typedef enum
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_L1,
		JOYKEY_R1,
		JOYKEY_L2,
		JOYKEY_R2,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	}JOYKEY;

	CJoypad();
	~CJoypad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(JOYKEY Key);
	bool GetTrigger(JOYKEY Key);
	bool GetRelease(JOYKEY Key);
	bool GetRepeat(JOYKEY Key);
	bool GetPressAnyBotton(void);

	int GetLastFream(void) { return m_nCntLastFream; }

	bool GetL2Press(void);
	bool GetL2Trigger(void);
	bool GetL2Release(void);
	bool GetL2Repeat(void);

	bool GetR2Press(void);
	bool GetR2Trigger(void);
	bool GetR2Release(void);
	bool GetR2Repeat(void);

	float GetLStickRot(void);
	float GetLStick(void);

	float GetRStickRot(void);
	float GetRStick(void);

	void SetVib(int nRight, int nLeft/*, int nFream*/);

private:
	// constexpr
	static constexpr float THUMB_LIMIT = 32767.0f;

	static bool m_bVib;
	int m_nCntLastFream;		// 最後の入力からのフレーム
	XINPUT_STATE m_joyKeyState;
	XINPUT_STATE m_oldjoyKeyState;
};
#endif