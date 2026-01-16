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
#include "fieldManager.h"
#include "hole.h"
#include "Time.h"
#include "box.h"
#include "PrizeManager.h"
#include "funcCollisionPlayer_to_Enemy.h"
#include "funcEnemyGravity.h"
#include "funcCollisionHole_to_Enemy.h"

// 静的メンバ変数
CPlayer* CGame::m_pPlayer = nullptr;
CMeshField* CGame::m_pFiled = nullptr;
CFiledManager* CGame::m_FieldManager = nullptr;
CTimeManager* CGame::m_pTimeM = nullptr;
CPrizemanager* CGame::m_PrizeManager = nullptr;
CHole* CGame::m_pHole = nullptr;
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
	CManager::GetCamera()->SetPosR(D3DXVECTOR3(0.0f,0.0f,0.0f));
	CManager::GetCamera()->SetRotation(D3DXVECTOR3(2.3f, 0.0f, 0.0f));

	//----------------------------------------------
	// 生成処理
	//----------------------------------------------

	// ポリゴン
	m_pFiled = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, 40, 40, 7, 6);
	m_pFiled->BindTexIndex(CTexture::TYPE_FILED);

	// フィールドマネージャー
	m_FieldManager = new CFiledManager;
	m_FieldManager->BindFiled(m_pFiled);
	m_FieldManager->Init();

	// ゲットホール
	m_pHole = CHole::Create(D3DXVECTOR3(95.0f, 0.0f, 70.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 16, 1, 10.0f, 40.0f);

	// タイム
	m_pTimeM = CTimeManager::Create(CTimeManager::CNT_DOWN, CTimeManager::DISPLAY_MINSEC, 5400, 3, D3DXVECTOR3(740.0f, 100.0f, 0.0f), 40.0f, 60.0f);
	m_pTimeM->BindNumTextere(CTexture::TYPE_TIMENUMBER);

	// プライズマネージャー
	m_PrizeManager = new CPrizemanager;
	m_PrizeManager->Init();
	m_PrizeManager->Create(CEnemyBase::PRIZE_BOX, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// プレイヤー
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(95.0f, 85.0f, 70.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ファンクションの追加 & 生成
	AddFunction(std::make_unique<CFuncCollisionPlayerToEnemy>());// 敵とプレイヤーの当たり判定
	AddFunction(std::make_unique<CFuncCollisionHoleToEnemy>());// 敵とゲットホールの当たり判定
	AddFunction(std::make_unique<CFuncEnemyGaravity>());// 敵の重力

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
		m_pTimeM->Uninit();
		m_pTimeM = nullptr;
	}

	// プライズマネージャーの破棄
	if (m_PrizeManager != nullptr)
	{
		m_PrizeManager->Uninit();
		delete m_PrizeManager;
		m_PrizeManager = nullptr;
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
#ifdef _DEBUG
	// キーボードの情報取得
	CKeyboard* pKeyborad = CManager::GetKeyboard();

	if (pKeyborad->GetPress(DIK_LSHIFT))
	{
		if (pKeyborad->GetTrigger(DIK_RETURN))
		{
			// リザルトシーンに切り替える
			CManager::GetFade()->Set(CScene::MODE_RESULT);
		}
		else if (pKeyborad->GetTrigger(DIK_1))
		{
			m_pTimeM->Stop();
		}
		else if (pKeyborad->GetTrigger(DIK_2))
		{
			m_pTimeM->Play();
		}
		else if (pKeyborad->GetTrigger(DIK_0))
		{
			m_PrizeManager->Create(CEnemyBase::PRIZE_BEAR, D3DXVECTOR3(m_pPlayer->GetPosition().x, 0.0f, m_pPlayer->GetPosition().z));
		}
		else if (pKeyborad->GetTrigger(DIK_D))
		{
			m_PrizeManager->DeleteAll();
		}

	}
#endif // _DEBUG

	// フィールドマネージャーの更新
	m_FieldManager->Update();

	if (m_pTimeM->GetFinish())// タイムアウト
	{
		// リザルトシーンに切り替える
		CManager::GetFade()->Set(CScene::MODE_RESULT);
	}

	// プライズマネージャーの更新処理
	m_PrizeManager->Update();

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