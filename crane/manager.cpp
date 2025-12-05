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
#include"effect.h"

//静的メンバ変数
CRenderer* CManager::m_pRenderer = NULL;
CKeyboard* CManager::m_pKeyboard = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CTexture* CManager::m_pTexture = NULL;
CSound* CManager::m_pSound = { NULL };
CScene* CManager::m_pScene = { NULL };
CFade* CManager::m_pFade = { NULL };
CDebugProc* CManager::m_pDebug = { NULL };

//静的メンバ関数
CRenderer* CManager::GetRenderer(void) { return m_pRenderer; };
CKeyboard* CManager::GetKeyboard(void) { return m_pKeyboard; };
CSound* CManager::GetSound(void) { return m_pSound; };
CCamera* CManager::GetCamera(void) { return m_pCamera; };
CLight* CManager::GetLight(void) { return m_pLight; };
CTexture* CManager::GetTexture(void) { return m_pTexture; };
CFade* CManager::GetFade(void) { return m_pFade; };
CDebugProc* CManager::GetDebug(void) { return m_pDebug; };

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

	// ライトの生成
	m_pLight = new CLight;
	m_pLight->Init();

	// サウンドの生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// フェードの生成
	m_pFade = new CFade;
	m_pFade->Init();

	// デバック表示の生成
	m_pDebug = new CDebugProc;
	m_pDebug->Init();

	//---------------------------------
	// テクスチャの読込
	//---------------------------------
	m_pTexture = new CTexture;
	m_pTexture->Load();

	//---------------------------------
	// シーンの生成
	//---------------------------------
	m_pScene = CScene::Create(CScene::MODE_GAME);

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

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		// サウンドの終了処理
		m_pSound->Uninit();

		// メモリの開放
		delete m_pSound;
		m_pSound = NULL;
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

	// シーンの破棄
	if (m_pFade != NULL)
	{
		// シーンの終了処理
		m_pFade->Uninit();

		// メモリの開放
		delete m_pFade;
		m_pFade = NULL;
	}

	// デバック表示の破棄
	if (m_pDebug != NULL)
	{
		// デバック表示の終了処理
		m_pDebug->Uninit();

		// メモリの開放
		delete m_pDebug;
		m_pDebug = NULL;
	}

	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		//レンダラーの終了処理
		m_pRenderer->Uninit();

		// メモリの開放
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

	// デバック表示の更新
	m_pDebug->Print("オブジェクト数：%d\n", CObject::GetNumAll());
	m_pDebug->Update();

	//レンダラーの更新処理
	m_pRenderer->Update();

	// フェードの更新
	m_pFade->Update();
}

//====================================================
// 描画処理
//====================================================
void CManager::Draw(void)
{
	//レンダラーの描画処理
	m_pRenderer->Draw();
}

//====================================================
// ゲームモードの設定処理
//====================================================
void CManager::SetMode(CScene::MODE mode)
{
	// サウンドの停止
	m_pSound->StopAll();

	// 現在のモードの破棄
	if (m_pScene != NULL)
	{
		// 終了処理
		m_pScene->Uninit();
	}

	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();

	// 新しいモードの生成
	m_pScene = CScene::Create(mode);
}

//====================================================
// 現在のゲームモードの取得
//====================================================
CScene::MODE CManager::GetMode(void)
{
	return m_pScene->GetMode();
}