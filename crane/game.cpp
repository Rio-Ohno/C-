//====================================================
// 
// テストシーン[game.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include "game.h"
#include "manager.h"
#include "player.h"
#include "fieldManager.h"

// 静的メンバ変数
CPlayer* CGame::m_pPlayer = nullptr;
CMeshField* CGame::m_pFiled = nullptr;
CFiledManager* CGame::m_FieldManager = nullptr;

//====================================================
// コンストラクタ
//====================================================
CGame::CGame()
{
	// 種類の設定
	CObject::SetType(CObject::TYPE_SCENE);

	m_pPlayer = nullptr;
	m_pFiled = nullptr;
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
	// ポリゴン
	m_pFiled = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, 50, 50, 7, 6);
	m_pFiled->BindTexIndex(CTexture::TYPE_FILED);

	m_FieldManager = new CFiledManager;
	m_FieldManager->BindFiled(m_pFiled);
	m_FieldManager->Init();

	// プレイヤー
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CGame::Update(void)
{
#ifdef _DEBUG

	//if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	//{
	//	m_FieldManager->SetWave(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 25.0f, 0.2f, 1, 0.1f);
	//}

#endif // _DEBUG

	// フィールドマネージャーの更新
	m_FieldManager->Update();
}

//====================================================
// 描画処理
//====================================================
void CGame::Draw(void)
{
	// なし
}