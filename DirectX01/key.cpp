//====================================================
//
// モーションのキー[key.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"key.h"
#include<string.h>

//====================================================
// パーツのコンストラクタ
//====================================================
CKEY::CKEY()
{
	// 各変数をクリア
	m_fposX = 0;
	m_fposY = 0;
	m_fposZ = 0;

	m_frotX = 0;
	m_frotY = 0;
	m_frotZ = 0;
}

//====================================================
// パーツのデストラクタ
//====================================================
CKEY::~CKEY()
{
	// なし
}

//====================================================
// パーツの生成処理
//====================================================
CKEY* CKEY::Create(float fposX, float fposY, float fposZ, float frotX, float frotY, float frotZ)
{
	CKEY* pKey = NULL;

	// メモリの確保
	pKey = new CKEY;

	// 各変数の設定
	pKey->m_fposX = fposX;
	pKey->m_fposY = fposY;
	pKey->m_fposZ = fposZ;

	pKey->m_frotX = frotX;
	pKey->m_frotY = frotY;
	pKey->m_frotZ = frotZ;

	return pKey;
}

//====================================================
// パーツの位置の取得処理
//====================================================
float CKEY::GetPos(const char* Axis)
{
	float pos = 0.0f;

	if (strcmp(Axis, "X") == 0 || strcmp(Axis, "x") == 0)// Xなら
	{
		// 位置(X軸)を代入
		pos = this->m_fposX;
	}
	else if (strcmp(Axis, "Y") == 0 || strcmp(Axis, "y") == 0)// Yなら
	{
		// 位置(Y軸)を代入
		pos = this->m_fposY;
	}
	else if (strcmp(Axis, "Z") == 0 || strcmp(Axis, "z") == 0)// Zなら
	{
		// 位置(Z軸)を代入
		pos = this->m_fposZ;
	}

	return pos;
}

//====================================================
// パーツの向きの取得処理
//====================================================
float CKEY::GetRot(const char* Axis)
{
	float rot = 0.0f;

	if (strcmp(Axis, "X") == 0 || strcmp(Axis, "x") == 0)// Xなら
	{
		// 位置(X軸)を代入
		rot = this->m_frotX;
	}
	else if (strcmp(Axis, "Y") == 0 || strcmp(Axis, "y") == 0)// Yなら
	{
		// 位置(Y軸)を代入
		rot = this->m_frotY;
	}
	else if (strcmp(Axis, "Z") == 0 || strcmp(Axis, "z") == 0)// Zなら
	{
		// 位置(Z軸)を代入
		rot = this->m_frotZ;
	}

	return rot;
}

//====================================================
// キーのコンストラクタ
//====================================================
CKeyInfo::CKeyInfo()
{
	// 値をクリア
	for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
	{
		m_apKey[nCnt] = { NULL };
	}
	m_nFream = 0;
}

//====================================================
// キーのデストラクタ
//====================================================
CKeyInfo::~CKeyInfo()
{
	// なし
}

//====================================================
// キーの生成処理
//====================================================
CKeyInfo* CKeyInfo::Create(int nFream)
{
	CKeyInfo* pKeyInfo = NULL;

	// メモリの確保
	pKeyInfo = new CKeyInfo;

	// 変数の設定
	pKeyInfo->m_nFream = nFream;

	return pKeyInfo;
}

//====================================================
// パーツの設定処理
//====================================================
void CKeyInfo::SetKey(CKEY** pKey)
{
	for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
	{
		if (pKey[nCnt] != NULL)
		{
			m_apKey[nCnt] = pKey[nCnt];
		}
	}
}

//====================================================
// キーの生成処理
//====================================================
void CKeyInfo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
	{
		if (m_apKey[nCnt] != NULL)
		{
			delete m_apKey[nCnt];
			m_apKey[nCnt] = NULL;
		}
	}
}

//====================================================
// モーション情報のコンストラクタ
//====================================================
CInfo::CInfo()
{
	// 値をクリアにする
	for (int nCnt = 0; nCnt < MAX_KEY_INFO; nCnt++)
	{
		m_apKeyInfo[nCnt] = { NULL };
	}
	m_bLoop = 0;
	m_nNumKey = 0;
}

//====================================================
// モーション情報のデストラクタ
//====================================================
CInfo::~CInfo()
{
	// なし
}

//====================================================
// モーション情報の生成処理
//====================================================
CInfo* CInfo::Create(bool Loop, int nNumKey)
{
	CInfo* pInfo = NULL;

	// メモリの確保
	pInfo = new CInfo;

	// 各変数の設定
	pInfo->m_bLoop = Loop;
	pInfo->m_nNumKey = nNumKey;

	return pInfo;
}

//====================================================
// キー情報を設定する処理
//====================================================
void CInfo::SetKeyInfo(CKeyInfo** pKeyInfo)
{
	for (int nCnt = 0; nCnt < MAX_KEY_INFO; nCnt++)
	{
		// キー情報の生成処理
		m_apKeyInfo[nCnt] = pKeyInfo[nCnt];
	}
}

//====================================================
// モーション情報の終了処理
//====================================================
void CInfo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_KEY_INFO; nCnt++)
	{
		if (m_apKeyInfo[nCnt] != NULL)
		{
			m_apKeyInfo[nCnt]->Uninit();

			// メモリの開放
			delete m_apKeyInfo[nCnt];
			m_apKeyInfo[nCnt] = NULL;
		}
	}
}