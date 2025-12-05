//====================================================
// 
// デバック表示 [DebugProc.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include"DebugProc.h"
#include"manager.h"
#include <stdio.h>

// 静的メンバ変数
LPD3DXFONT CDebugProc::m_pFont = { NULL };
char CDebugProc::m_aStr[MAX_STRING] = { NULL };
bool CDebugProc::m_bDisp = false;

//====================================================
// コンストラクタ
//====================================================
CDebugProc::CDebugProc()
{
	// なし
}

//====================================================
// デストラクタ
//====================================================
CDebugProc::~CDebugProc()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
void CDebugProc::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//デバック表示用フォントの生成
	D3DXCreateFont(pDevice,
		25, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"メイリオ",
		&m_pFont);

	//デバッグ表示情報のクリア
	memset(&m_aStr[0], NULL, sizeof(m_aStr));

// 初期表示設定
#if _DEBUG
	m_bDisp = true;
#else NDEBUG
	m_bDisp = false;
#endif
}

//====================================================
// 終了処理
//====================================================
void CDebugProc::Uninit(void)
{
	// フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//====================================================
// 更新処理
//====================================================
void CDebugProc::Update(void)
{
#ifdef _DEBUG

	// キーボードの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard != NULL)
	{
		// デバック表示の表示非表示
		if (pKeyboard->GetTrigger(DIK_1) == true)
		{
			m_bDisp = m_bDisp ? false : true;
		}
	}
#endif // DEBUG
}

//====================================================
// 描画処理
//====================================================
void CDebugProc::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	RECT rect = { 10,20,SCREEN_WIDTH,SCREEN_HEIGHT };

	if (m_bDisp == true)
	{
		//テキストの描画
		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 200, 125, 255));
	}

	//デバッグ表示情報のクリア
	memset(&m_aStr[0], NULL, sizeof(m_aStr));
}

//====================================================
// 出力処理
//====================================================
void CDebugProc::Print(const char* fmt, ...)
{
	va_list args;
	char aString[MAX_STRING];
	char aproStr[MAX_STRING];
	int nLength = 0;
	int nStopLength;

	// 文字列を代入
	strcpy(&aString[0], fmt);

	// 可変長引数リストの処理を開始
	va_start(args, fmt);

	for (char* s = &aString[0]; *s != '\0'; s++)
	{
		if (*s == '%')
		{
			// 型指定を見る
			s++;

			switch (*s)
			{
			case 'd':	// 整数

				// 文字列として変換
				sprintf(&aproStr[0], "%d", va_arg(args, int));

				// 文字列の長さを取得
				nLength = (int)strlen(&aproStr[0]);

				break;

			case 'f':

				// 文字列として変換
				sprintf(&aproStr[0], "%f", va_arg(args, double));

				// 文字列の長さを取得
				nLength = (int)strlen(&aproStr[0]);

				//小数点以下の文字目まで確認
				for (int nCntlength = 0; aproStr[nCntlength] != '\0'; nCntlength++)
				{
					if (aproStr[nCntlength] == '.')
					{//小数点があった場合

						//小数点以下の桁数を求める
						int nMin = (int)strlen(&aproStr[nCntlength + 1]);

						//小数点より先の文字数と指定した値までの差分を求める
						nMin -= MAX_FLOATNUM;

						//文字列の長さを小数点以下第二位までに補正
						nLength -= nMin;
					}
				}

				break;

			case 'c':

				// 文字列として変換
				sprintf(&aproStr[0], "%c", va_arg(args, char));

				// 文字列の長さを取得
				nLength = (int)strlen(&aproStr[0]);

				break;

			case 's':

				// 文字列として変換
				vsnprintf(&aproStr[0], sizeof(aproStr), "%s", args);

				//文字列の長さを取得
				nLength = (int)strlen(&aproStr[0]);

				break;

			default:
				break;
			}

			nStopLength = (int)strlen(s) + 1;

			//メモリ内の確認文字より後ろの文字列をずらす
			memmove(s + nLength - 2, s, nStopLength);

			s--;	//ポインタを%まで戻す

			//可変引数を指定された場所に挿入
			memcpy(s, &aproStr[0], nLength);

		}
	}

	va_end(args);

	//文字列を連結する
	strcat(&m_aStr[0], &aString[0]);
}