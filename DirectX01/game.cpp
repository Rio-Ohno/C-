//====================================================
//
// ゲームシーン処理 [game.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"game.h"
#include"manager.h"
#include"meshfield.h"
#include"meshSphere.h"
#include"Time.h"
#include"shockwave.h"
#include"particle3D.h"

// 静的メンバ変数
CPlayer* CGame::m_pPlayer = NULL;
CScore* CGame::m_pScore = NULL;
CObject3D* CGame::m_pObjecct3D = NULL;
CTime* CGame::m_pTime = NULL;
CPause* CGame::m_pPause = NULL;
CNoteManager* CGame::m_pNoteManager = NULL;
CShockManager* CGame::m_pShockManager = NULL;
bool CGame::m_bFinish = false;
bool CGame::m_bPause = false;

// 静的メンバ関数
CPlayer* CGame::GetPlayer(void) { return m_pPlayer; };
CScore* CGame::GetScore(void) { return m_pScore; };
CObject3D* CGame::GetObject3D(void) { return m_pObjecct3D; };
CTime* CGame::GetTime(void) { return m_pTime; };

//====================================================
// コンストラクタ
//====================================================
CGame::CGame() :CScene(MODE_GAME)
{
	m_nCntFinFream = 0;
	m_bFinish = false;
	m_bPause = false;

	// カメラの初期化処理
	CManager::GetCamera()->Init();

	// 種類の設定
	CObject::SetType(CObject::TYPE_SCENE);

	// ポーズしていない状態へ
	CObject::SetPause(false);
}

//====================================================
// デストラクタ
//====================================================
CGame::~CGame()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//----------------------------------------------------
	// 生成処理
	//----------------------------------------------------

	// 音符のマネージャー
	m_pNoteManager = new CNoteManager;
	m_pNoteManager->Init();

	// 衝撃波のマネージャー
	m_pShockManager = new CShockManager;
	m_pShockManager->Init();

	// ポリゴン
	CMeshSphere* pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 500.0f, false, false);
	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, 300.0f);

	// スコア
	m_pScore = CScore::Create(D3DXVECTOR3(1250.0f, 50.0f, 0.0f), 50.0f, 100.0f);

	// プレイヤー
	m_pPlayer->SetMotion("data/MODEL/player/motion.txt");
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// プレイヤー

	//CMeshField* pMesh = CMeshField:: Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 3, 3, 100, 100);

	// 音符の生成
	m_pNoteManager->Spawn();

	// 衝撃波の生成
	m_pShockManager->Place(0, 0);

	CShockwave* pWave = CShockwave::Create(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 1, 30, 0.0f, 5.0f, 30.0f, 0.5f, false, true);
	pWave->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), true);
	pWave->SetVanish(90);

#ifdef _DEBUG

	m_pTime = CTime::Create(CTime::TYPE_CNTDOWN, 300, 4, D3DXVECTOR3(740.0f, 50.0f, 0.0f), 40.0f, 80.0f);
#endif
#ifndef _DEBUG
	m_pTime = CTime::Create(CTime::TYPE_CNTDOWN, 90, 4, D3DXVECTOR3(740.0f, 50.0f, 0.0f), 40.0f, 80.0f);
#endif

	// テクスチャ割当
	m_pTime->BindTexIndx(CTexture::TYPE_SCORENUMBER);

	// テクスチャクラスの取得
	CTexture* pTexture = CManager::GetTexture();

	if (pTexture != nullptr)
	{
		m_pObjecct3D->BindTexIndex(pTexture->TYPE_FILED);
		pSphere->BindTexIndex(pTexture->Register("data/TEXTURE/BG001.jpg"));
	}

	// カメラの種類設定
	CManager::GetCamera()->SetType(CCamera::TYPE_ASSENT);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CGame::Uninit(void)
{
	// ポーズの破棄
	if (m_pPause != NULL)
	{
		// 終了処理
		m_pPause->Uninit();

		// メモリの破棄
		delete m_pPause;
		m_pPause = NULL;
	}

	// 音符マネージャーの破棄
	if (m_pNoteManager != NULL)
	{
		// 終了処理
		m_pNoteManager->Uninit();

		// メモリの破棄
		delete m_pNoteManager;
		m_pNoteManager = NULL;
	}

	// 衝撃波マネージャーの破棄
	if (m_pShockManager != NULL)
	{
		// 終了処理
		m_pShockManager->Uninit();

		// メモリの破棄
		delete m_pShockManager;
		m_pShockManager = NULL;
	}

	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CGame::Update(void)
{
	if (m_bFinish == false)
	{
		// ポーズするかどうか
		isPause();

		if (m_pPause != NULL && m_bPause == true)
		{
			// ポーズの更新処理
			m_pPause->Update();
		}
	}

	// 時間切れなら
	if (m_pTime->CTime::GetTimeOver() == true)
	{
		m_bFinish = true;
	}

	if (m_bFinish == true)
	{
		// フレームカウント
		m_nCntFinFream++;
	}

	if (m_nCntFinFream >= 60)
	{
		m_nCntFinFream = 0;

		// フェードを取得
		CFade* fade = CManager::GetFade();

		// リザルトへシーンを変える
		fade->Set(CScene::MODE_RESULT);
	}

	if (m_pNoteManager->GetNum() <= 0)
	{
		// フレームカウント
		m_nCntNoteSpan++;

		if (m_nCntNoteSpan >= NOTE_SPAWN)
		{
			// 音符の呼び出し
			m_pNoteManager->Spawn();

			// フレームカウントリセット
			m_nCntNoteSpan = 0;
		}
	}
	if (m_pShockManager != NULL)
	{
		m_pShockManager->Update();
	}
	CDebugProc::Print("Num Note：%d\n", m_pNoteManager->GetNum());

#ifdef _DEBUG

	if (CManager::GetKeyboard()->GetTrigger(DIK_RSHIFT) == true)
	{
		// フェードを取得
		CFade* fade = CManager::GetFade();

		// リザルトへシーンを変える
		fade->Set(CScene::MODE_RESULT);
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_C) == true)
	{
		m_pNoteManager->Spawn();
	}
#endif
}

//====================================================
// 描画処理
//====================================================
void CGame::Draw(void)
{
	if (m_bPause == true && m_pPause != NULL)
	{
		// ポーズの描画処理
		m_pPause->Draw();
	}
}

//====================================================
// ポーズするかどうか
//====================================================
bool CGame::isPause(void)
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_TAB) == true)
	{
		m_bPause = m_bPause ? false : true;

		// フラグ管理
		CObject::SetPause(m_bPause);

		if (m_bPause == true)
		{
			// メモリの確保
			m_pPause = CPause::Create();
		}
	}
	
	if (m_bPause == false)
	{
		if (m_pPause != NULL)
		{
			// 終了処理
			m_pPause->Uninit();

			// メモリの破棄
			delete m_pPause;
			m_pPause = NULL;
		}
	}

	return m_bPause;
}

//====================================================
// ポーズの設定処理
//====================================================
void CGame::SetPause(bool Use)
{
	m_bPause = Use;
	CObject::SetPause(Use);
}