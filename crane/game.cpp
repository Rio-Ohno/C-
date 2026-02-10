//====================================================
// 
// ゲームシーン[game.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include "game.h"
#include "manager.h"
#include "player.h"
#include "hole.h"
#include "Time.h"
#include "score.h"
#include "wall.h"
#include "pause.h"
#include "meshSphere.h"
#include "fieldManager.h"
#include "PrizeManager.h"
#include "funcCollisionPlayer_to_Enemy.h"
#include "funcCollisionPlayer_to_Wall.h"
#include "funcCollisionHole_to_Enemy.h"
#include "funcEnemyGravityforGame.h"

// 静的メンバ変数
CWall* CGame::m_apWall[NUM_WALL] = { nullptr };
CMeshSphere* CGame::m_pSphere = nullptr;
CPlayer* CGame::m_pPlayer = nullptr;
CMeshField* CGame::m_pFiled = nullptr;
CFiledManager* CGame::m_FieldManager = nullptr;
CTimeManager* CGame::m_pTimeM = nullptr;
CScore* CGame::m_pScore = nullptr;
CPrizemanager* CGame::m_PrizeManager = nullptr;
CHole* CGame::m_pHole = nullptr;
CPauseManager* CGame::m_pPause = nullptr;
std::vector<std::unique_ptr<CFunctionBase>> CGame::m_apFunction;

//====================================================
// コンストラクタ
//====================================================
CGame::CGame()
{
	// 種類の設定
	CObject::SetType(CObject::TYPE_SCENE);

	// 各メンバ変数の初期化処理
	m_pPlayer = nullptr;		// プレイヤー
	m_pFiled = nullptr;			// フィールド
	m_FieldManager = nullptr;	// フィールドマネージャー
	m_PrizeManager = nullptr;	// プライズマネージャー
	m_pHole = nullptr;			// ゲットホール
	m_pTimeM = nullptr;			// タイム
	m_pScore = nullptr;			// スコア
	m_pPause = nullptr;			// ポーズマネージャー

	for (int nCnt = 0; nCnt < NUM_WALL; ++nCnt)// 壁
	{
		m_apWall[nCnt] = nullptr;
	}
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
HRESULT CGame::Init(void)
{
	// カメラの設定
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 175.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CManager::GetCamera()->SetRotation(D3DXVECTOR3(2.3f, 0.0f, 0.0f));

	//----------------------------------------------
	// 生成処理
	//----------------------------------------------

	// 空
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);	// テクスチャ設定
	m_pSphere->SetTurn(0.0005f);					// 回転設定

	// 壁
	m_apWall[0] = CWall::Create(D3DXVECTOR3(0.0f, -120.0f, -120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 280.0f, 120.0f, false, true);
	m_apWall[0]->BindTexIndex(CTexture::TYPE_FILED);

	// 当たり判定用の壁
	m_apWall[1] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -120.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 280.0f, 120.0f, true, false);
	m_apWall[2] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 280.0f, 120.0f, true, false);
	m_apWall[3] = CWall::Create(D3DXVECTOR3(140.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 240.0f, 120.0f, true, false);
	m_apWall[4] = CWall::Create(D3DXVECTOR3(-140.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 240.0f, 120.0f, true, false);

	// フィールド
	m_pFiled = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, 40, 40, 7, 6);// 280×240
	m_pFiled->BindTexIndex(CTexture::TYPE_FILED);

	// フィールドマネージャー
	m_FieldManager = new CFiledManager;
	m_FieldManager->BindFiled(m_pFiled);
	m_FieldManager->Init();

	// ゲットホール
	m_pHole = CHole::Create(D3DXVECTOR3(95.0f, 0.0f, 70.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 16, 1, 10.0f, 40.0f);

	// プライズマネージャー
	m_PrizeManager = new CPrizemanager;
	m_PrizeManager->Init();

	// ポーズマネージャー
	m_pPause = new CPauseManager;
	m_pPause->Init();

	// プレイヤー
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(95.0f, 65.0f, 70.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// -----------------------------------------------------
	// UIの生成
	// -----------------------------------------------------

	// タイム
	m_pTimeM = CTimeManager::Create(CTimeManager::CNT_DOWN, CTimeManager::DISPLAY_MINSEC, 5400, 3, D3DXVECTOR3(740.0f, 60.0f, 0.0f), 40.0f, 60.0f);
	m_pTimeM->BindNumTextere(CTexture::TYPE_TIMENUMBER);
	m_pTimeM->BindColonTexture(CTexture::TYPE_COLON);

	// スコア
	m_pScore = CScore::Create(D3DXVECTOR3(360.0f, 60.0f, 0.0f), 6, 45.0f, 65.0f);

	// ファンクションの追加 & 生成
	AddFunction(std::make_unique<CFuncCollisionPlayerToEnemy>());	// 敵とプレイヤーの当たり判定
	AddFunction(std::make_unique<CFuncCollisionPlayerToWall>());	// 壁とプレイヤーの当たり判定
	AddFunction(std::make_unique<CFuncCollisionHoleToEnemy>());		// 敵とゲットホールの当たり判定
	AddFunction(std::make_unique<CFuncGameEnemyGaravity>());		// 敵の重力

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CGame::Uninit(void)
{
	// フィールドマネージャーの破棄
	if (m_FieldManager != nullptr)
	{
		// 終了処理
		m_FieldManager->Uninit();
		m_FieldManager = nullptr;
	}

	// 球体の破棄
	if (m_pSphere != nullptr)
	{
		m_pSphere->Uninit();
		m_pSphere = nullptr;
	}

	// プレイヤーの破棄
	if (m_pPlayer != nullptr)
	{
		// 終了処理
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	// ゲットホールの破棄
	if (m_pHole != nullptr)
	{
		// 終了処理
		m_pHole->Uninit();
		m_pHole = nullptr;
	}

	// タイムの破棄
	if (m_pTimeM != nullptr)
	{
		// 終了処理
		m_pTimeM->Uninit();
		m_pTimeM = nullptr;
	}

	// プライズマネージャーの破棄
	if (m_PrizeManager != nullptr)
	{
		// 終了処理
		m_PrizeManager->Uninit();

		// メモリの破棄
		delete m_PrizeManager;
		m_PrizeManager = nullptr;
	}

	// ポーズマネージャーの破棄
	if (m_pPause != nullptr)
	{
		// 終了処理
		m_pPause->Uninit();

		// メモリの破棄
		delete m_pPause;
		m_pPause = nullptr;
	}

	// 壁の破棄
	for (int nCnt = 0; nCnt < NUM_WALL; ++nCnt)
	{
		if (m_apWall[nCnt] != nullptr)
		{
			// 終了処理
			m_apWall[nCnt]->Uninit();
			m_apWall[nCnt] = nullptr;
		}
	}

	// ファンクションの破棄
	for (auto& func : m_apFunction)
	{
		// 終了処理
		func->Uninit();

		// メモリの開放
		func.reset();
		func = nullptr;
	}

	// ファンクションの全消去
	m_apFunction.clear();			// vectorから消す

	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CGame::Update(void)
{
	// デバックコマンド
	DebugKey();

	// ポーズするかどうか
	m_pPause->isPause();

	// ポーズの更新処理
	m_pPause->Update();

	// ポーズ状態じゃないなら
	if (m_pPause->GetPause())
	{
		return;
	}

	if (m_pTimeM->GetFinish())// タイムアウトしたなら
	{
		// スコアの保存
		m_pScore->Save();

		// リザルトシーンに切り替える
		CManager::GetFade()->Set(CScene::MODE_RESULT);
	}

	if (m_pTimeM->GetFream() <= 3000)
	{
		// フレームによるスポーン処理
		m_PrizeManager->SpawnByFream();
	}
	if (m_pTimeM->GetFream() <= 1500)
	{
		// フレームによるスポーン処理
		m_PrizeManager->SpawnByFream();
	}

	// フェードし終わっていたら
	if (CManager::GetFade()->isFininsh())
	{
		// フレームによるスポーン処理
		m_PrizeManager->SpawnByFream();

		// プライズマネージャーの更新処理
		m_PrizeManager->Update();
	}

	// フィールドマネージャーの更新
	m_FieldManager->Update();

	// ファンクションの更新処理
	for (auto& func : m_apFunction)
	{
		func->Update();
	}
}

//====================================================
// 描画処理
//====================================================
void CGame::Draw(void)
{
	// なし
}

//====================================================
// デバックキー処理
//====================================================
void CGame::DebugKey(void)
{
	// デバックコマンド
#ifdef _DEBUG
	// キーボードの情報取得
	CKeyboard* pKeyborad = CManager::GetKeyboard();

	if (pKeyborad->GetPress(DIK_LSHIFT))
	{
		if (pKeyborad->GetTrigger(DIK_RETURN))
		{
			// スコアの保存
			m_pScore->Save();

			// リザルトシーンに切り替える
			CManager::GetFade()->Set(CScene::MODE_RESULT);
		}
		else if (pKeyborad->GetTrigger(DIK_1))
		{
			// タイムを止める
			m_pTimeM->Stop();
		}
		else if (pKeyborad->GetTrigger(DIK_2))
		{
			// タイムを動かす
			m_pTimeM->Play();
		}
		else if (pKeyborad->GetTrigger(DIK_0))
		{
			// 熊の生成処理
			m_PrizeManager->Create(CEnemyBase::PRIZE_BEAR, D3DXVECTOR3(m_pPlayer->GetPosition().x, 0.0f, m_pPlayer->GetPosition().z));
		}
		else if (pKeyborad->GetTrigger(DIK_D))
		{
			// 全ての敵を消す
			m_PrizeManager->DeleteAll();
		}
	}
#endif // _DEBUG
}