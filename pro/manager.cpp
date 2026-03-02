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
CRenderer* CManager::m_pRenderer = nullptr;
CKeyboard* CManager::m_pKeyboard = nullptr;
CJoypad* CManager::m_pJoypad = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CTexture* CManager::m_pTexture = nullptr;
CSound* CManager::m_pSound = { nullptr };
CScene* CManager::m_pScene = { nullptr };
CFade* CManager::m_pFade = { nullptr };
CDebugProc* CManager::m_pDebug = { nullptr };

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
	srand((int)time(0));//シード値(ランダムの)

	//レンダラーの生成
	m_pRenderer = new CRenderer;

	//レンダラーの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
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

	// ジョイパッドの生成
	m_pJoypad = new CJoypad;

	// ジョイパッドの初期化処理
	if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
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
	m_pScene = CScene::Create(CScene::MODE_TITLE);

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

	if (m_pTexture != nullptr)
	{
		// テクスチャの破棄
		m_pTexture->UnLoad();

		// メモリの破棄
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// カメラの破棄
	if (m_pCamera != nullptr)
	{
		// カメラの終了処理
		m_pCamera->Uninit();

		// メモリの破棄
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// ライトの破棄
	if (m_pLight != nullptr)
	{
		// ライトの終了処理
		m_pLight->Uninit();

		// メモリの破棄
		delete m_pLight;
		m_pLight = nullptr;
	}

	// サウンドの破棄
	if (m_pSound != nullptr)
	{
		// サウンドの終了処理
		m_pSound->Uninit();

		// メモリの開放
		delete m_pSound;
		m_pSound = nullptr;
	}

	// キーボードの破棄
	if (m_pKeyboard != nullptr)
	{
		// キーボードの終了処理
		m_pKeyboard->Uninit();

		// メモリの開放
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	// ジョイパッドの破棄
	if (m_pJoypad != nullptr)
	{
		// ジョイパッドの終了処理
		m_pJoypad->Uninit();

		// メモリの開放
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	// シーンの破棄
	if (m_pFade != nullptr)
	{
		// シーンの終了処理
		m_pFade->Uninit();

		// メモリの開放
		delete m_pFade;
		m_pFade = nullptr;
	}

	// デバック表示の破棄
	if (m_pDebug != nullptr)
	{
		// デバック表示の終了処理
		m_pDebug->Uninit();

		// メモリの開放
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	//レンダラーの破棄
	if (m_pRenderer != nullptr)
	{
		//レンダラーの終了処理
		m_pRenderer->Uninit();

		// メモリの開放
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//====================================================
// 更新処理
//====================================================
void CManager::Update(void)
{
	// キーボードの更新処理
	m_pKeyboard->Update();

	// ジョイパッドの更新処理
	m_pJoypad->Update();

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
	if (m_pScene != nullptr)
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