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
#include"Time.h"
#include"shockwave.h"
#include"particle3D.h"

// 静的メンバ変数
CPlayer* CGame::m_pPlayer = NULL;
CObject3D* CGame::m_pObjecct3D = NULL;
CScore* CGame::m_pScore = NULL;
CTime* CGame::m_pTime = NULL;
CTime* CGame::m_pStartTime = NULL;
CPause* CGame::m_pPause = NULL;
CNoteManager* CGame::m_pNoteManager = NULL;
CShockManager* CGame::m_pShockManager = NULL;
bool CGame::m_bFinish = false;
bool CGame::m_bStart = false;
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
	m_nCntFreamFin = 0;
	m_nCntWaveSpan = 0;
	m_nCntNoteSpan = 0;
	m_bFinish = false;
	m_bStart = false;
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
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 500.0f, false, false);// 空
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);

	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 600.0f);// 床
	m_pObjecct3D->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.8f, 1.0f));
	m_pObjecct3D->BindTexIndex(CTexture::TYPE_FILED);

	// 壁
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 100.0f, false, true);
			break;

		case 1:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 600.0f, 100.0f, false, true);
			break;

		case 2:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(300.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, false, true);
			break;

		case 3:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(-300.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, false, true);
			break;
		}

		m_apWall[nCnt]->SetColor(D3DXCOLOR(0.4f, 0.9f, 0.7f, 1.0f));
		m_apWall[nCnt]->BindTexIndex(CTexture::TYPE_FILED);
		m_apWall[nCnt]->SetTexUV(0.0f, 1.0f, 0.0f, 0.25f);
	}

	for (int nCnt = 4; nCnt < 8; nCnt++)
	{
		switch (nCnt)
		{
		case 4:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 600.0f, 300.0f, true, false);
			break;

		case 5:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, true, false);
			break;

		case 6:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 600.0f, 300.0f, true, false);
			break;

		case 7:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 600.0f, 300.0f, true, false);
			break;
		}
	}

	// スコア
	m_pScore = CScore::Create(D3DXVECTOR3(1250.0f, 50.0f, 0.0f),7, 50.0f, 100.0f);

	// プレイヤー
	m_pPlayer->SetMotion("data/MODEL/player/motion.txt");
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -75.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// プレイヤー

	// 時間
	m_pStartTime = CTime::Create(CTime::TYPE_CNTDOWN, 3, 1, D3DXVECTOR3(740.0f, 310.0f, 0.0f), 100.0f, 100.0f);
	m_pStartTime->BindTexIndx(CTexture::TYPE_TIMENUMBER);

	// 衝撃波の生成
	m_pShockManager->Place(2, 0);

	// カメラの種類設定
	CManager::GetCamera()->SetType(CCamera::TYPE_ASSENT);

	// BGMの再生
	CManager::GetSound()->Play(CSound::SOUND_LABEL_GAME);

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
	
	// ゲーム開始処理
	CGame::Start();

	// ゲーム終了処理
	CGame::Finish();

	// 時間切れなら
	if (m_pTime != NULL && m_pTime->CTime::GetTimeOver() == true)
	{
		m_bFinish = true;

		// スコアの記録処理(セーブ)
		m_pScore->Save(SAVEFILE_SCORE);
	}

	if (m_bStart == true && m_bFinish == false)
	{
		if (m_bPause == false)
		{
			// 音符の生成処理関係
			NoteSpawm();

			// 衝撃波の生成処理関係と更新処理
			WaveSpawn();
		}
	}

	// デバック表示
	CDebugProc::Print("Num Note：%d\n", m_pNoteManager->GetNum());// 音符の数
	float haku = CManager::GetSound()->GetPlaybackTempo(CSound::SOUND_LABEL_GAME);
	CDebugProc::Print("BGM：%f\n", haku);// BGMの拍

#ifdef _DEBUG

	if (CManager::GetSound()->isBeatTrigger(CSound::SOUND_LABEL_GAME, 4.0f))// 1小節の4拍目になら
	{
		CManager::GetSound()->Play(CSound::SOUND_LABEL_DEBUG);
	}


	if (CManager::GetKeyboard()->GetTrigger(DIK_RSHIFT) == true)
	{
		// スコアの記録処理(セーブ)
		m_pScore->Save(SAVEFILE_SCORE);

		// フェードを取得
		CFade* fade = CManager::GetFade();

		// リザルトへシーンを変える
		fade->Set(CScene::MODE_RESULT);
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_C) == true)
	{
		// 音符生成処理
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

//====================================================
// ゲーム開始処理
//====================================================
void CGame::Start(void)
{
	if (m_pStartTime != NULL)
	{
		if (m_pStartTime->GetTimeOver() == true)
		{
			m_bStart = true;

#ifdef _DEBUG

			// タイムの生成
			m_pTime = CTime::Create(CTime::TYPE_CNTDOWN, 90, 4, D3DXVECTOR3(740.0f, 50.0f, 0.0f), 40.0f, 80.0f);
#endif
#ifndef _DEBUG
			// タイムの生成
			m_pTime = CTime::Create(CTime::TYPE_CNTDOWN, 90, 4, D3DXVECTOR3(740.0f, 50.0f, 0.0f), 40.0f, 80.0f);
#endif // 

			// タイムのテクスチャ割当
			//m_pTime->BindTexIndx(CTexture::TYPE_SCORENUMBER);
			m_pTime->BindTexIndx(CTexture::TYPE_TIMENUMBER);

			// 音符の生成
			m_pNoteManager->Spawn();

			// 終了処理
			m_pStartTime->Uninit();
			m_pStartTime = { NULL };

		}
	}
}

//====================================================
// ゲーム終了処理
//====================================================
void CGame::Finish(void)
{
	if (m_bFinish == true)
	{
		// フレームカウント
		m_nCntFreamFin++;

		if (m_nCntFreamFin >= FINISH_REAM)
		{
			m_nCntFreamFin = 0;

			// フェードを取得
			CFade* fade = CManager::GetFade();

			// リザルトへシーンを変える
			fade->Set(CScene::MODE_RESULT);
		}
	}
}

//====================================================
// 音符生成処理
//====================================================
void CGame::NoteSpawm(void)
{
	// 音符のマネージャーの更新処理
	if (m_pNoteManager->GetNum() <= 0)// 音符が全てとられたなら
	{
		// フレームカウント
		m_nCntNoteSpan++;

		if (m_nCntNoteSpan >= NOTE_SPAWN)// 90フレーム経ったら
		{
			// 音符の呼び出し(生成)
			m_pNoteManager->Spawn();

			// フレームカウントリセット
			m_nCntNoteSpan = 0;
		}
	}
}

//====================================================
// 衝撃破の生成処理と更新処理
//====================================================
void CGame::WaveSpawn(void)
{
	if (m_pShockManager != NULL)
	{
		// フレームカウント
		++m_nCntWaveSpan;

		if ((m_nCntWaveSpan % WAVE_SPAWN) == 0)
		{
			if ((m_nCntWaveSpan / WAVE_SPAWN) == 1)
			{
				// 衝撃波の生成
				m_pShockManager->Place(2, 1);
			}
			else if ((m_nCntWaveSpan / WAVE_SPAWN) == 2)
			{
				// 衝撃波の生成
				m_pShockManager->Place(2, 2);
			}
			else if ((m_nCntWaveSpan / WAVE_SPAWN) >= 3)
			{
				// カウンタリセット(念のため)
				m_nCntWaveSpan = WAVE_SPAWN * 3;
			}
		}

		// 衝撃波のマネージャーの更新処理
		m_pShockManager->Update();
	}
}