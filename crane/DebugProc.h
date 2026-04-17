//====================================================
// 
// デバック表示 [DebugProc.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

// インクルード
#include"main.h"

// デバックプロッククラス
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

	static constexpr int MAX_STRING = 1024;
	static constexpr int MAX_FLOATNUM = 2;

	static LPD3DXFONT m_pFont;// フォントへのポインタ
	static char m_aStr[MAX_STRING];// 文字列を格納するバッファ
	static bool m_bDisp;
};
#endif // !_DEBUGPROC_H_
