//====================================================
//
// 音符（アイテム）管理処理 [noteManager.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"noteManager.h"
#include"DebugProc.h"
#include"loadnote.h"

// 静的メンバ変数
int CNoteManager::m_nNumNote = 0;
CNote* CNoteManager::m_apNote[NUM_NOTE] = { NULL };
CNotePattern* CNoteManager::m_pPattern = { NULL };

//====================================================
// コンストラクタ
//====================================================
CNoteManager::CNoteManager()
{
	// 各変数初期化
	m_nNumNote = 0;
	m_pPattern = { NULL };

	for (int nCnt = 0; nCnt < NUM_NOTE; nCnt++)
	{
		m_apNote[nCnt] = { NULL };
	}
}

//====================================================
// デストラクタ
//====================================================
CNoteManager::~CNoteManager()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CNoteManager::Init(void)
{
	// スクリプト読込
	CNoteManager::Load();

	if (m_pPattern == NULL)
	{
		return 0;
	}

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CNoteManager::Uninit(void)
{
	// パターンの破棄
	if (m_pPattern != NULL)
	{
		// 終了処理
		m_pPattern->Uninit();

		delete m_pPattern;
		m_pPattern = NULL;
	}

	// 音符は自動破棄
}

//====================================================
// 更新処理
//====================================================
void CNoteManager::Update(void)
{
	// なし
}

//====================================================
// 描画処理
//====================================================
void CNoteManager::Draw(void)
{
	// なし
}

//====================================================
// パターン読込処理の呼び出し処理
//====================================================
void CNoteManager::Load(void)
{
	// メモリの確保
	m_pPattern = new CNotePattern;

	if (m_pPattern != NULL)
	{
		// テキスト読込処理
		CLoadNote::Load("data/SCRIPT/NotePattern.txt", m_pPattern);
	}
}

//====================================================
// 音符の生成処理
//====================================================
void CNoteManager::Spawn()
{
	CNoteInfo* pInfo = { NULL };
	CNotePos* pPos[NUM_NOTE] = { NULL };
	int nPattern = rand() % m_pPattern->GetNumInfo();

	// 最大パターン数を超えていないなら
	if (nPattern <= NUM_PATTERN_NOTE && nPattern >= 0)
	{
		pInfo = m_pPattern->GetNoteInfo()[nPattern];
		
		for (int nCnt = 0; nCnt < pInfo->GetNum(); nCnt++)
		{
			pPos[nCnt] = pInfo->GetNotePos()[nCnt];
		}
	}
	else
	{
		return;
	}

	for (int nCnt = 0; nCnt < pInfo->GetNum(); nCnt++)
	{
		// 音符の生成
		m_apNote[nCnt] = CNote::Create(pPos[nCnt]->GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	int i = 0;
}

//====================================================
// 生成処理
//====================================================
CNoteManager* CNoteManager::Create(void)
{
	CNoteManager* pManager = NULL;

	// メモリの確保
	pManager = new CNoteManager;

	// 初期化処理
	pManager->Init();

	return pManager;
}