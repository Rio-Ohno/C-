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
	// なし
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
	pKey->m_pos.x = fposX;
	pKey->m_pos.y = fposY;
	pKey->m_pos.z = fposZ;

	pKey->m_rot.x = frotX;
	pKey->m_rot.y = frotY;
	pKey->m_rot.z = frotZ;

	return pKey;
}

//====================================================
// パーツの位置の取得処理
//====================================================
float CKEY::GetPos(int Axis)
{
	float pos = 0.0f;

	if (AXIS_X == Axis)// Xなら
	{
		// 位置(X軸)を代入
		pos = this->m_pos.x;
	}
	else if (AXIS_Y == Axis)// Yなら
	{
		// 位置(Y軸)を代入
		pos = this->m_pos.y;
	}
	else if (AXIS_Z == Axis)// Zなら
	{
		// 位置(Z軸)を代入
		pos = this->m_pos.z;
	}

	return pos;
}

//====================================================
// パーツの向きの取得処理
//====================================================
float CKEY::GetRot(int Axis)
{
	float rot = 0.0f;

	if (AXIS_X == Axis)// Xなら
	{
		// 位置(X軸)を代入
		rot = this->m_rot.x;
	}
	else if (AXIS_Y==Axis)// Yなら
	{
		// 位置(Y軸)を代入
		rot = this->m_rot.y;
	}
	else if (AXIS_Z==Axis)// Zなら
	{
		// 位置(Z軸)を代入
		rot = this->m_rot.z;
	}

	return rot;
}

//====================================================
// キーのコンストラクタ
//====================================================
CKeyInfo::CKeyInfo()
{
	// 値をクリア
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
void CKeyInfo::SetKey(std::vector<CKEY*> pKey)
{
	m_apKey = pKey;
}

//====================================================
// キーの生成処理
//====================================================
void CKeyInfo::Uninit(void)
{
	for (int nCnt = 0; nCnt < (int)m_apKey.size(); nCnt++)
	{
		if (m_apKey[nCnt] != nullptr)
		{
			delete m_apKey[nCnt];
			m_apKey[nCnt] = nullptr;
		}
	}
}

//====================================================
// モーション情報のコンストラクタ
//====================================================
CInfo::CInfo()
{
	// 値をクリアにする
	m_bLoop = 0;
	m_nNumKey = 0;
}

//====================================================
// コピーコンストラクタ
//====================================================
CInfo::CInfo(const CInfo& other)
{
	this->m_apKeyInfo = other.m_apKeyInfo;
	this->m_bLoop = other.m_bLoop;
	this->m_nNumKey = other.m_nNumKey;
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
	CInfo* pInfo = nullptr;

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
void CInfo::SetKeyInfo(std::vector<CKeyInfo*> pKeyInfo)
{
	// キー情報の生成処理
	m_apKeyInfo = pKeyInfo;
}

//====================================================
// モーション情報の終了処理
//====================================================
void CInfo::Uninit(void)
{
	for (int nCnt = 0; nCnt < (int)m_apKeyInfo.size(); nCnt++)
	{
		if (m_apKeyInfo[nCnt] != nullptr)
		{
			m_apKeyInfo[nCnt]->Uninit();

			// メモリの開放
			delete m_apKeyInfo[nCnt];
			m_apKeyInfo[nCnt] = nullptr;
		}
	}
}