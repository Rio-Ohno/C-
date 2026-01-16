//====================================================
//
//ポーズ[pause.cpp]
//Author:Rio Ohno
//
//====================================================

// インクルード
#include"pause.h"
#include"manager.h"
#include"game.h"

// 静的メンバ変数
CObject2D* CPause::m_apObject2D[NUM_POLY] = { NULL };

//====================================================
// コンストラクタ
//====================================================
CPause::CPause()
{
	m_mode = MENU_CONTINUE;
	m_nCntMenu = 1;

	for (int nCnt = 0; nCnt < NUM_POLY; nCnt++)
	{
		m_apObject2D[nCnt] = { NULL };
	}
}

//====================================================
// デストラクタ
//====================================================
CPause::~CPause()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CPause* CPause::Create(void)
{
	CPause* pPause = NULL;

	// メモリの確保
	pPause = new CPause;

	// 初期化処理
	pPause->Init();

	return pPause;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CPause::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_POLY; nCnt++)
	{
		if (nCnt == 0)//背景
		{
			m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 1280.0f, 520.0f);
			m_apObject2D[nCnt]->BindTexIndx(CTexture::TYPE_PAUSE);
			m_apObject2D[nCnt]->SetType(CObject::TYPE_PAUSE);
		}
		else
		{
			m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 225.0f + 100.0f * nCnt, 0.0f), 600.0f, 50.0f);
			m_apObject2D[nCnt]->SetType(CObject::TYPE_PAUSE);
		}
	}

	m_apObject2D[1]->BindTexIndx(CTexture::TYPE_CONTEINUE);
	m_apObject2D[2]->BindTexIndx(CTexture::TYPE_RETRY);
	m_apObject2D[3]->BindTexIndx(CTexture::TYPE_QUIT);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_POLY; nCnt++)
	{
		if (m_apObject2D[nCnt] != NULL)
		{
			m_apObject2D[nCnt]->Uninit();
		}
	}
}

//====================================================
// 更新処理
//====================================================
void CPause::Update(void)
{
	// キーボードの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	if (m_nCntMenu >= 1 && m_nCntMenu < 4)
	{
		if (pKeyboard->GetTrigger(DIK_DOWN) == true || pKeyboard->GetTrigger(DIK_S) == true)//下キーを押された
		{
			m_nCntMenu++;
		}

		if (pKeyboard->GetTrigger(DIK_UP) == true || pKeyboard->GetTrigger(DIK_W) == true)//上キーを押された
		{
			m_nCntMenu--;
		}
	}

	switch (m_nCntMenu)
	{
	case 1:

		m_mode = MENU_CONTINUE;

		// ポリゴンのアルファ値設定
		for (int nCountPause = 0; nCountPause < NUM_POLY; nCountPause++)
		{
			// 色の設定
			if (nCountPause == 0 || nCountPause == 1)
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}


		break;

	case 2:

		m_mode = MENU_RETRY;

		// ポリゴンのアルファ値設定
		for (int nCountPause = 0; nCountPause < NUM_POLY; nCountPause++)
		{
			// 色の設定
			if (nCountPause == 0 || nCountPause == 2)
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}

		break;

	case 3:

		m_mode = MENU_QUIT;

		// ポリゴンのアルファ値設定
		for (int nCountPause = 0; nCountPause < NUM_POLY; nCountPause++)
		{
			// 色の設定
			if (nCountPause == 0 || nCountPause == 3)
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}
		break;

	default:


		// 選択肢を超えたとき
		if (m_nCntMenu >= 4)
		{
			m_nCntMenu = 1;
			m_mode = MENU_CONTINUE;
		}
		else if (m_nCntMenu < 1)
		{
			m_nCntMenu = 3;
			m_mode = MENU_QUIT;
		}

		// ポリゴンのアルファ値設定
		for (int nCountPause = 0; nCountPause < NUM_POLY; nCountPause++)
		{
			// 色の設定
			if (nCountPause == 0 || nCountPause == m_nCntMenu)
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_apObject2D[nCountPause]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}

		break;
	}

	//決定キーを押されたとき
	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		switch (m_mode)
		{
		case MENU_CONTINUE:

			CGame::SetPause(false);

			break;

		case MENU_RETRY:

			 // ゲームへ遷移
			CManager::GetFade()->Set(CScene::MODE_GAME);

			break;

		case MENU_QUIT:

			// タイトルへ遷移
			CManager::GetFade()->Set(CScene::MODE_TITLE);

			break;
		}
	}
}

//====================================================
// 描画処理
//====================================================
void CPause::Draw(void)
{
	// なし
}