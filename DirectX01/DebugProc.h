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

// マクロ定義
#define MAX_STRING (1024)
#define MAX_FLOATNUM (2)	// 小数点以下の表示桁数

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
	static LPD3DXFONT m_pFont;// フォントへのポインタ
	static char m_aStr[MAX_STRING];// 文字列を格納するバッファ
	static bool m_bDisp;
};
#endif // !_DEBUGPROC_H_
