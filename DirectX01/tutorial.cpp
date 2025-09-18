//====================================================
//
// チュートリアルシーン処理 [tutorial.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"tutorial.h"
#include"manager.h"
#include"shockwave.h"

// 静的メンバ変数
CPlayer* CTutorial::m_pPlayer = NULL;
CScore* CTutorial::m_pScore = NULL;
CObject3D* CTutorial::m_pObject3D = NULL;
CNoteManager* CTutorial::m_pNoteManager = NULL;
CShockManager* CTutorial::m_pShockManager = NULL;
CMeshSphere* CTutorial::m_pSphere = NULL;

//====================================================
// コンストラクタ
//====================================================
CTutorial::CTutorial()
{
	// カメラの初期化処理
	CManager::GetCamera()->Init();

	// 種類の設定
	CObject::SetType(CObject::TYPE_SCENE);

	// ポーズしていない状態へ
	CObject::SetPause(false);

	// 各変数の初期化
	m_nCntFream = 0;
	m_nCntNoteSpan = 0;
	m_bMove = true;
}

//====================================================
// デストラクタ
//====================================================
CTutorial::~CTutorial()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{

	// カメラの種類設定
	CManager::GetCamera()->SetType(CCamera::TYPE_ASSENT);

	//----------------------------------------------------
	// 生成処理
	//----------------------------------------------------

	// 音符のマネージャー
	m_pNoteManager = new CNoteManager;
	m_pNoteManager->Init();

	// 3Dポリゴン
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 500.0f, false, false);
	m_pObject3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 600.0f);
	m_pObject3D->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.8f, 1.0f));

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
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 600.0f, 100.0f, true, false);
			break;

		case 5:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 100.0f, true, false);
			break;

		case 6:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, true, false);
			break;

		case 7:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, true, false);
			break;
		}
	}

	// スコア
	m_pScore = CScore::Create(D3DXVECTOR3(1250.0f, 50.0f, 0.0f), 7, 50.0f, 100.0f);

	// プレイヤー
	m_pPlayer->SetMotion("data/MODEL/player/motion.txt");
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// プレイヤー

	// テクスチャの割当
	m_pObject3D->BindTexIndex(CTexture::TYPE_FILED);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);

	// 2Dポリゴン
	CObject2D* pBack = CObject2D::Create(D3DXVECTOR3(1220.0f, 150.0f, 0.0f), 100.0f, 100.0f);
	pBack->BindTexIndx(CTexture::TYPE_BACK_X);
	pBack->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f));

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTutorial::Uninit(void)
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
void CTutorial::Update(void)
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_X) == true)
	{
		// フェードを取得
		CFade* fade = CManager::GetFade();

		// タイトルへシーンを変える
		fade->Set(CScene::MODE_TITLE);
	}

	if (m_bMove == true)
	{
		// フレームカウントアップ
		m_nCntFream++;

		if (m_nCntFream >= FREAM_MOVE)
		{
			m_bMove = false;

			//// 衝撃波のマネージャーの生成
			m_pShockManager = new CShockManager;
			m_pShockManager->Init();

			// パターンの指定
			m_pShockManager->Place(1,0);

			// フレームカウントリセット
			m_nCntFream = 0;
		}
	}
	else
	{
		if (m_pShockManager != NULL)
		{
			m_pShockManager->Update();
		}
	}

	// 音符のマネージャーの更新処理
	if (m_pNoteManager->GetNum() <= 0)// 音符が全てとられたなら
	{
		// フレームカウント
		m_nCntNoteSpan++;

		if (m_nCntNoteSpan >= 90)// 90フレーム経ったら
		{
			// 音符の呼び出し(生成)
			m_pNoteManager->Spawn();

			// フレームカウントリセット
			m_nCntNoteSpan = 0;
		}
	}
}

//====================================================
// 描画処理
//====================================================
void CTutorial::Draw(void)
{
	// なし
}