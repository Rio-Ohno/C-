//====================================================
// 
// �f�o�b�N�\�� [DebugProc.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

// �C���N���[�h
#include"main.h"

// �}�N����`
#define MAX_STRING (1024)
#define MAX_FLOATNUM (2)	// �����_�ȉ��̕\������

class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init(void);
	void Uninit(void);
	void Update(void);

	static void Print(const char* fmt, ...);
	static void Draw(void);

private:
	static LPD3DXFONT m_pFont;// �t�H���g�ւ̃|�C���^
	static char m_aStr[MAX_STRING];// ��������i�[����o�b�t�@
	static bool m_bDisp;
};
#endif // !_DEBUGPROC_H_
