//====================================================
// 
// ���͏���[input.h]
// Author:Rio Ohno
// 
//==================================================== 

#ifndef _INPUT_H_
#define _INPUT_H_

// �C���N���[�h
#include"main.h"

//�}�N����`
#define NUM_KEY_MAX (256)							//�L�[�̍ő吔

// ���̓N���X
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

// �L�[�{�[�h�N���X
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

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aOldKeyState[NUM_KEY_MAX];
};

// �}�E�X(�{�^��)�N���X
class CMouse :public CInput
{
public:
	CMouse();
	~CMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool ButtonPress(int nButton);
	bool OnButtonDown(int nButton);
	bool OnButtonUp(int nButton);
	bool GetRepeat(int nButton);

private:
	DIMOUSESTATE m_MouseState;
	DIMOUSESTATE m_oldMouseState;
};

//// �W���C�p�b�h�N���X
//class CJoypad :public CInput
//{
//public:
//
//	//�L�[���͂̎��
//	typedef enum
//	{
//		JOYKEY_UP = 0,
//		JOYKEY_DOWN,
//		JOYKEY_LEFT,
//		JOYKEY_RIGHT,
//		JOYKEY_START,
//		JOYKEY_BACK,
//		JOYKEY_L3,
//		JOYKEY_R3,
//		JOYKEY_L1,
//		JOYKEY_R1,
//		JOYKEY_L2,	// ������Ŏg���Ȃ�
//		JOYKEY_R2,	// ������Ŏg���Ȃ�
//		JOYKEY_A,
//		JOYKEY_B,
//		JOYKEY_X,
//		JOYKEY_Y,
//		JOYKEY_MAX
//	}JOYKEY;
//
//	CJoypad();
//	~CJoypad();
//
//	HRESULT Init(void);
//	void Uninit(void);
//	void Update(void);
//
//	bool GetPress(JOYKEY Key);
//	bool GetTrigger(JOYKEY Key);
//	bool GetRelease(JOYKEY Key);
//	bool GetRepeat(JOYKEY Key);
//
//private:
//	XINPUT_STATE m_joyKeyState;
//	WORD m_Button;
//	WORD m_OldButton;
//
//};
#endif