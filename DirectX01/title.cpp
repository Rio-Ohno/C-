//====================================================
//
// タイトルシーン処理 [title.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"title.h"
#include"object2D.h"
#include"manager.h"
#include"ranking.h"

// 静的メンバ変数
CPlayer* CTitle::m_pPlayer = NULL;
CObject3D* CTitle::m_pObjecct3D = NULL;
CNoteManager* CTitle::m_pNoteManager = NULL;
CShockManager* CTitle::m_pShockManager = NULL;
CMeshSphere* CTitle::m_pSphere = NULL;

//====================================================
// コンストラクタ
//====================================================
CTitle::CTitle() :CScene(CScene::MODE_TITLE)
{
	// オブジェクトの種類設定
	CObject::SetType(CObject::TYPE_SCENE);

	// カメラの設定
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);
}

//====================================================
// デストラクタ
//====================================================
CTitle::~CTitle()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// テクスチャの取得
	CTexture* pTexture = CManager::GetTexture();

	// カメラ位置の設定
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 575.0f, 525.0f), D3DXVECTOR3(0.0f, 200.0f, 0.0f));

	// 音符のマネージャー
	m_pNoteManager = new CNoteManager;
	m_pNoteManager->Init();

	// 衝撃波のマネージャー
	m_pShockManager = new CShockManager;
	m_pShockManager->Init();

	// ポリゴン
	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 600.0f);
	m_pObjecct3D->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.8f, 1.0f));
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);

	// テクスチャの割当
	if (pTexture != nullptr)
	{
		m_pObjecct3D->BindTexIndex(pTexture->TYPE_FILED);
		m_pSphere->BindTexIndex(pTexture->TYPE_SKY);
	}

	// 音符の生成
	m_pNoteManager->Spawn();

	// 衝撃波の生成
	m_pShockManager->Place(1, 0);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTitle::Uninit(void)
{
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
void CTitle::Update(void)
{
	// スペースを押したらゲームへ
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) == true)
	{
		CManager::GetFade()->Set(CScene::MODE_GAME);
	}

	// 今のカメラRotの取得
	D3DXVECTOR3 rotNow = CManager::GetCamera()->GetRot();

	rotNow.y += CAMERA_SPEED;

	// カメラの向き設定
	CManager::GetCamera()->SetRotation(rotNow);

	// フレームカウントアップ
	m_nCntFream++;

	if (m_nCntFream >= 1800)
	{
		CRanking::SetMode(CRanking::MODE::MODE_DISPLAY);

		// フレームリセット
		m_nCntFream = 0;

		// ランキングへ
		CManager::GetFade()->Set(CScene::MODE_RANKING);
	}
}

//====================================================
// 描画処理
//====================================================
void CTitle::Draw(void)
{
	// なし
}