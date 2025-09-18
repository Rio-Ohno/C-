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
CObject3D* CTitle::m_pObjecct3D = NULL;
CNoteManager* CTitle::m_pNoteManager = NULL;
CShockManager* CTitle::m_pShockManager = NULL;
CObject2D* CTitle::m_apObject2D[NUM_POLYGON] = { NULL };

//====================================================
// コンストラクタ
//====================================================
CTitle::CTitle() :CScene(CScene::MODE_TITLE)
{
	// オブジェクトの種類設定
	CObject::SetType(CObject::TYPE_SCENE);

	// カメラの設定
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);

	// 各変数の初期化
	m_nCntMenu = 0;// メニューカウンタ
	m_nCntFream = 0;// フレームカウンタ
	m_Menu = MENU_GAME;
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
	// カメラ位置の設定
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 575.0f, 525.0f), D3DXVECTOR3(0.0f, 200.0f, 0.0f));

	// 音符のマネージャーの生成
	m_pNoteManager = new CNoteManager;
	m_pNoteManager->Init();

	// 衝撃波のマネージャーの生成
	m_pShockManager = new CShockManager;
	m_pShockManager->Init();

	// 3Dポリゴンの生成
	m_pObjecct3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 600.0f);
	m_pObjecct3D->BindTexIndex(CTexture::TYPE_FILED);// テクスチャの割当
	m_pObjecct3D->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.8f, 1.0f));// 色の設定

	// 壁
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 100.0f, true, true);
			break;

		case 1:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 600.0f, 100.0f, true, true);
			break;

		case 2:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(300.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, true, true);
			break;

		case 3:
			m_apWall[nCnt] = CWall::Create(D3DXVECTOR3(-300.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 600.0f, 100.0f, true, true);
			break;
		}

		m_apWall[nCnt]->SetColor(D3DXCOLOR(0.4f, 0.9f, 0.7f, 1.0f));
		m_apWall[nCnt]->BindTexIndex(CTexture::TYPE_FILED);
		m_apWall[nCnt]->SetTexUV(0.0f, 1.0f, 0.0f, 0.25f);
	}


	// 球体(空)の生成
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);// テクスチャの割当

	// 2Dポリゴンの生成
	for (int nCnt = 0; nCnt < NUM_POLYGON; nCnt++)
	{
		if (nCnt == 0)// タイトル
		{
			m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 200.0f, 0.0f), 800.0f, 150.0f);
			m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_TITLE);
		}
		else if (nCnt == 3)// スペースキー
		{
			m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(950.0f, 490.0f, 0.0f), 200.0f, 200.0f);
			m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_SPACE);
			// memo  GAME:490  TUTORIAL:610
		}
		else// 選択肢
		{

			// テクスチャの割当
			if (nCnt == 1)
			{
				m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 300.0f + 120.0f * nCnt, 0.0f), 600.0f, 90.0f);
				m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_GAME);
			}
			else
			{
				m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 300.0f + 120.0f * nCnt, 0.0f), 450.0f, 90.0f);
				m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_TUTORIAL);
			}
		}
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

	// モードの選択
	CTitle::SelectMode();

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
	else if ((m_nCntFream % 30) == 0)
	{
		// 点滅処理
		if ((m_nCntFream % 60) == 0)
		{
			// 色の設定
			m_apObject2D[3]->CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			// 色の設定
			m_apObject2D[3]->CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.8f, 1.0f));
		}
	}
}

//====================================================
// 描画処理
//====================================================
void CTitle::Draw(void)
{
	// なし
}

//====================================================
// モード選択処理
//====================================================
void CTitle::SelectMode(void)
{
	// キーボードの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	if (m_nCntMenu >= 0 && m_nCntMenu < MENU_MAX)
	{
		if (pKeyboard->GetTrigger(DIK_DOWN) == true || pKeyboard->GetTrigger(DIK_S) == true)//下キーを押された
		{
			m_nCntMenu++;
		}

		if (pKeyboard->GetTrigger(DIK_UP) == true || pKeyboard->GetTrigger(DIK_W) == true)//上キーを押された
		{
			m_nCntMenu--;
		}

		switch (m_nCntMenu)
		{
		case 0:

			m_Menu = MENU_GAME;

			// ポリゴンのアルファ値設定
			for (int nCount = 0; nCount < NUM_POLYGON; nCount++)
			{
				// 位置の設定
				if (nCount == 3)
				{
					m_apObject2D[nCount]->SetPos(D3DXVECTOR3(950.0f, 490.0f, 0.0f));
				}

				// 色の設定
				if (nCount == 2)
				{
					m_apObject2D[nCount]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
				}
				else if (nCount == 3)
				{
					// なし(色をかえないため)
				}
				else
				{
					m_apObject2D[nCount]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}


			break;

		case 1:

			m_Menu = MENU_TUTORIAL;

			// ポリゴンのアルファ値設定
			for (int nCount = 0; nCount < NUM_POLYGON; nCount++)
			{
				// 位置の設定
				if (nCount == 3)
				{
					m_apObject2D[nCount]->SetPos(D3DXVECTOR3(950.0f, 610.0f, 0.0f));
				}

				// 色の設定
				if (nCount == 1)
				{
					m_apObject2D[nCount]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
				}
				else if (nCount == 3)
				{
					// なし(色をかえないため)
				}
				else
				{
					m_apObject2D[nCount]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}

			break;

		default:


			// 選択肢を超えたとき
			if (m_nCntMenu >= MENU_MAX)
			{
				m_nCntMenu = 0;
				m_Menu = MENU_GAME;
			}
			else if (m_nCntMenu < 0)
			{
				m_nCntMenu = 1;
				m_Menu = MENU_TUTORIAL;
			}

			break;
		}

	}

	//決定キーを押されたとき
	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		switch (m_Menu)
		{
		case MENU_GAME:

			// ゲームへ遷移
			CManager::GetFade()->Set(CScene::MODE_GAME);

			break;

		case MENU_TUTORIAL:

			// ゲームへ遷移
			CManager::GetFade()->Set(CScene::MODE_TUTORIAL);

			break;

		}
	}
}