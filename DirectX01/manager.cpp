//====================================================
// 
// マネジャー[manager.cpp]
// Author:RioOhno
// 
//====================================================

//インクルード
#include"manager.h"
#include<time.h>
#include"object.h"
#include"objectX.h"
#include"objectBillboard.h"
#include"meshfield.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"note.h"

//静的メンバ変数
CRenderer* CManager::m_pRenderer = NULL;
CKeyboard* CManager::m_pKeyboard = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CEnemy* CManager::m_pEnemy[MAX_ENEMY] = { NULL };
CBGManager* CManager::m_BGManager = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CTexture* CManager::m_pTexture = NULL;
CLoadMotion* CManager::m_pLoadMotion = NULL;
CScore* CManager::m_pScore = NULL;
CObject3D* CManager::m_pObjecct3D = NULL;

//静的メンバ関数
CRenderer* CManager::GetRenderer(void) { return m_pRenderer; };
CKeyboard* CManager::GetKeyboard(void) { return m_pKeyboard; };
CPlayer* CManager::GetPlayer(void) { return m_pPlayer; };
CCamera* CManager::GetCamera(void) { return m_pCamera; };
CLight* CManager::GetLight(void) { return m_pLight; };
CTexture* CManager::GetTexture(void) { return m_pTexture; };
CLoadMotion* CManager::GetLoadMotion(void) { return m_pLoadMotion; };
CScore* CManager::GetScore(void) { return m_pScore; };
CObject3D* CManager::GetObject3D(void) { return m_pObjecct3D; };

CNote* g_Item = { NULL };

//====================================================
// コンストラクタ
//====================================================
CManager::CManager()
{
	// なし
}

//====================================================
// デストラクタ
//====================================================
CManager::~CManager()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	srand((int)time(0));//シード値

	//レンダラーの生成
	m_pRenderer = new CRenderer;

	//レンダラーの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		//初期化処理が失敗したら
		return -1;
	}

	//キーボードの生成
	m_pKeyboard = new CKeyboard;

	// キーボードの初期化処理
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		//初期化処理が失敗したら
		return -1;
	}

	// カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ライトの設定
	m_pLight = new CLight;
	m_pLight->Init();

	//---------------------------------
	// テクスチャの読込
	//---------------------------------
	CBullet::Load();		// 弾
	CExplosion::Load();		// 爆発
	CEffect::Load();		// エフェクト

	m_pTexture = new CTexture;
	m_pTexture->Load();

	//---------------------------------
	// オブジェクトの生成
	//---------------------------------
	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f);
	m_pObjecct3D->BindTexIndex(m_pTexture->TYPE_FILED);
	//CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 3, 3, 100, 100);

	m_pScore = CScore::Create(D3DXVECTOR3(1250.0f, 50.0f, 0.0f), 50.0f, 100.0f);
	g_Item = CNote::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer->SetMotion("data/MODEL/player/motion.txt");
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// プレイヤー

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CManager::Uninit(void)
{
	// すべてのオブジェクトの破棄
	CObject::ReleaseAll();

	//---------------------------------
	// テクスチャの破棄
	//---------------------------------
	CBullet::UnLoad();		// 弾
	CExplosion::UnLoad();	// 爆発
	CEffect::UnLoad();		// エフェクト

	if (m_pTexture != NULL)
	{
		// テクスチャの破棄
		m_pTexture->UnLoad();

		// メモリの破棄
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// カメラの破棄
	if (m_pCamera != NULL)
	{
		// カメラの終了処理
		m_pCamera->Uninit();

		// メモリの破棄
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ライトの破棄
	if (m_pLight != NULL)
	{
		// ライトの終了処理
		m_pLight->Uninit();

		// メモリの破棄
		delete m_pLight;
		m_pLight = NULL;
	}

	// キーボードの破棄
	if (m_pKeyboard != NULL)
	{
		// キーボードの終了処理
		m_pKeyboard->Uninit();

		// メモリの開放
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		//レンダラーの終了処理
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//====================================================
// 更新処理
//====================================================
void CManager::Update(void)
{
	// キーボードの更新処理
	m_pKeyboard->Update();

	// カメラの更新
	m_pCamera->Update();

	// ライトの更新
	m_pLight->Update();

	//レンダラーの更新処理
	m_pRenderer->Update();
}

//====================================================
// 描画処理
//====================================================
void CManager::Draw(void)
{
	//レンダラーの描画処理
	m_pRenderer->Draw();
}