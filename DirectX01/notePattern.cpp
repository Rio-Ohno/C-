//====================================================
//
// 音符の出現パターン情報[notePattern.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"notePattern.h"

// 静的メンバ変数
int CNotePattern::m_nMaxNum = 0;
int CNotePattern::m_nNumInfo = 0;

//====================================================
// 音符の位置情報のコンストラクタ
//====================================================
CNotePos::CNotePos()
{
	// 各変数の初期化処理
	m_PosX = 0.0f;
	m_PosY = 0.0f;
	m_PosZ = 0.0f;
}

//====================================================
// 音符の位置情報のデストラクタ
//====================================================
CNotePos::~CNotePos()
{
	// なし
}

//====================================================
// 音符の位置情報の位置取得処理
//====================================================
D3DXVECTOR3 CNotePos::GetPos(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(m_PosX, m_PosY, m_PosZ);

	return pos;
}

//====================================================
// 音符の位置情報の生成処理
//====================================================
CNotePos* CNotePos::Create(float posX, float posY, float posZ)
{
	CNotePos* pPos = NULL;

	// メモリの確保
	pPos = new CNotePos;

	// 各変数の設定
	pPos->m_PosX = posX;
	pPos->m_PosY = posY;
	pPos->m_PosZ = posZ;

	return pPos;
}

//====================================================
// 音符のパターン情報のコンストラクタ
//====================================================
CNoteInfo::CNoteInfo()
{
	// 各変数の初期化
	m_nNum = 0;

	for (int nCnt = 0; nCnt < NUM_NOTE; nCnt++)
	{
		m_apPos[nCnt] = { NULL };
	}
}

//====================================================
// 音符のパターン情報のデストラクタ
//====================================================
CNoteInfo::~CNoteInfo()
{
	// なし
}

//====================================================
// 音符のパターン情報の終了処理
//====================================================
void CNoteInfo::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_NOTE; nCnt++)
	{
		if (m_apPos[nCnt] != NULL)
		{
			// メモリの破棄
			delete m_apPos[nCnt];
			m_apPos[nCnt] = { NULL };
		}
	}
}

//====================================================
// 音符の位置情報の設定処理
//====================================================
void CNoteInfo::SetNotePos(CNotePos** pNotePos)
{
	for (int nCnt = 0; nCnt < NUM_NOTE; nCnt++)
	{
		if (pNotePos[nCnt] != NULL)
		{
			m_apPos[nCnt] = pNotePos[nCnt];
		}
	}
}

//====================================================
// 音符のパターン情報の生成処理
//====================================================
CNoteInfo* CNoteInfo::Create(int nNum)
{
	CNoteInfo* pInfo = NULL;

	// メモリの確保
	pInfo = new CNoteInfo;

	// 各変数の設定
	pInfo->m_nNum = nNum;

	return pInfo;
}

//====================================================
// パターン情報のコンストラクタ
//====================================================
CNotePattern::CNotePattern()
{
	// 各変数の初期化
	m_nMaxNum = 0;
	m_nNumInfo = 0;

	for (int nCnt = 0; nCnt < NUM_PATTERN_NOTE; nCnt++)
	{
		m_apInfo[nCnt] = { NULL };
	}
}

//====================================================
// パターン情報のデストラクタ
//====================================================
CNotePattern::~CNotePattern()
{
	// なし
}

//====================================================
// パターン情報の終了処理
//====================================================
void CNotePattern::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PATTERN_NOTE; nCnt++)
	{
		if (m_apInfo[nCnt] != NULL)
		{
			// 終了処理
			m_apInfo[nCnt]->Uninit();

			// メモリの破棄
			delete m_apInfo[nCnt];
			m_apInfo[nCnt] = NULL;
		}
	}
}

//====================================================
// 音符のパターン情報の設定処理
//====================================================
void CNotePattern::SetNoteInfo(CNoteInfo** pNoteInfo)
{
	for (int nCnt = 0; nCnt < NUM_PATTERN_NOTE; nCnt++)
	{
		if (pNoteInfo[nCnt] != NULL)
		{
			m_apInfo[nCnt] = pNoteInfo[nCnt];
		}
	}
}

//====================================================
// パターン情報の生成処理
//====================================================
CNotePattern* CNotePattern::Create(const int nMaxNum)
{
	CNotePattern* pPattern = NULL;

	// メモリの確保
	pPattern->m_nMaxNum = nMaxNum;

	return pPattern;
}