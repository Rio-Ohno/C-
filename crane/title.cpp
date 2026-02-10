//====================================================
//
// タイトルシーン　[title.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "title.h"
#include "manager.h"
#include "object2D.h"
#include "meshfield.h"
#include "meshSphere.h"
#include "wall.h"
#include "player.h"
#include "PrizeManager.h"
#include "funcEnemyGravityforTitle.h"

// 静的メンバ変数
CMeshSphere* CTitle::m_pSphere = nullptr;
CMeshField* CTitle::m_pField = nullptr;
CPrizemanager* CTitle::m_pPrizeManager = nullptr;
CPlayer* CTitle::m_pPlayer = nullptr;
std::vector<std::unique_ptr<CFunctionBase>> CTitle::m_apFunction;

//====================================================
// コンストラクタ
//====================================================
CTitle::CTitle()
{
	// 種類の設定
	CObject::SetType(CObject::TYPE_SCENE);

	// 各種メンバ変数の初期化
	for (int nCnt = 0; nCnt < NUM_POLY; ++nCnt)
	{
		m_pObject2D[nCnt] = nullptr;	// UIポリゴン
	}
	m_pSphere = nullptr;				// 球体メッシュ
	m_pField = nullptr;					// メッシュフィールド
	m_pPrizeManager = nullptr;			// プライズマネージャー
	m_pPlayer = nullptr;				// プレイヤー

	m_nCntFream = 0;					// フレームカウンタ
}

//====================================================
// デストラクタ
//====================================================
CTitle::~CTitle()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CTitle::Init(void)
{
	// カメラの設定
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 340.0f, 0.0f), D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	CManager::GetCamera()->SetRotation(D3DXVECTOR3(1.6f, 0.0f, 0.0f));

	// 空
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);	// テクスチャ設定
	m_pSphere->SetTurn(0.0005f);					// 回転設定

	// 壁
	CWall* pWall00 = CWall::Create(D3DXVECTOR3(0.0f, -120.0f, 120.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 280.0f, 120.0f, false, true);
	CWall* pWall01 = CWall::Create(D3DXVECTOR3(0.0f, -120.0f, -120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 280.0f, 120.0f, false, true);
	CWall* pWall02 = CWall::Create(D3DXVECTOR3(-140.0f, -120.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 240.0f, 120.0f, false, true);
	CWall* pWall03 = CWall::Create(D3DXVECTOR3(140.0f, -120.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 240.0f, 120.0f, false, true);

	// テクスチャの設定
	pWall00->BindTexIndex(CTexture::TYPE_FILED);
	pWall01->BindTexIndex(CTexture::TYPE_FILED);
	pWall02->BindTexIndex(CTexture::TYPE_FILED);
	pWall03->BindTexIndex(CTexture::TYPE_FILED);

	// ポリゴン
	m_pField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, 40, 40, 7, 6);// 280×240;
	m_pField->BindTexIndex(CTexture::TYPE_FILED);

	// プライズマネージャー
	m_pPrizeManager = new CPrizemanager;
	m_pPrizeManager->Init();
	m_pPrizeManager->Spawn();

	// プレイヤー
	m_pPlayer= CPlayer::Create(D3DXVECTOR3(95.0f, 85.0f, 70.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// UIポリゴン
	m_pObject2D[UI_POP] = CObject2D::Create(D3DXVECTOR3(640.0f, 75.0f, 0.0f), 1280.0f, 150.0f);
	m_pObject2D[UI_POP]->BindTexIndx(CTexture::TYPE_POP);

	m_pObject2D[UI_TITLE] = CObject2D::Create(D3DXVECTOR3(640.0f, 80.0f, 0.0f), 550.0f, 175.0f);
	m_pObject2D[UI_TITLE]->BindTexIndx(CTexture::TYPE_TITLE);

	m_pObject2D[UI_ENTER] = CObject2D::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), 600.0f, 120.0f);
	m_pObject2D[UI_ENTER]->BindTexIndx(CTexture::TYPE_PRESS);

	// ファンクションの追加 & 生成
	AddFunction(std::make_unique<CFuncTitleEnemyGravity>());	// 敵の重力

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTitle::Uninit(void)
{
	// UIポリゴンの破棄
	for (int nCnt = 0; nCnt < NUM_POLY; ++nCnt)
	{
		if (m_pObject2D[nCnt] != nullptr)
		{
			m_pObject2D[nCnt]->Uninit();

			m_pObject2D[nCnt] = nullptr;
		}
	}

	// 球体メッシュの破棄
	if (m_pSphere != nullptr)
	{
		m_pSphere->Uninit();
		m_pSphere = nullptr;
	}

	// メッシュフィールドの破棄
	if(m_pField!=nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	// プライズマネージャーの破棄
	if (m_pPrizeManager != nullptr)
	{
		m_pPrizeManager->Uninit();
		delete m_pPrizeManager;
		m_pPrizeManager = nullptr;
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

	// 自身の破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CTitle::Update(void)
{
	// カメラの向きの取得
	D3DXVECTOR3 CameraRot = CManager::GetCamera()->GetRot();

	// カメラを回転させる
	CManager::GetCamera()->SetRotation(D3DXVECTOR3(CameraRot.x, CameraRot.y + CAMERA_TURN, CameraRot.z));

	// プライズマネージャーの更新処理
	m_pPrizeManager->Update();

	// UI_ENTERの更新処理
	UpdateUI_ENTER();

	// ファンクションの更新処理
	for (auto& func : m_apFunction)
	{
		func->Update();
	}

	// キーボードの情報取得
	CKeyboard* pKeyborad = CManager::GetKeyboard();

	// ジョイパッドの情報取得
	CJoypad* pJoypad = CManager::GetJoypad();

	if (pKeyborad->GetTrigger(DIK_RETURN)||
		pKeyborad->GetTrigger(DIK_A) ||
		pJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		// ゲームシーンに切り替える
		CManager::GetFade()->Set(CScene::MODE_GAME);
		return;
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
// UI_ENTERの更新処理
//====================================================
void CTitle::UpdateUI_ENTER(void)
{
	// フレームカウントアップ
	++m_nCntFream;

	// フレーム割合算出
	float fRatio = (float)m_nCntFream / BLINKING_FREAM;
	float fMinAlpha = 0.2f;
	float fMaxSin = 1.0f - fMinAlpha;

	// アルファ値の算出
	float fAlpha = fMaxSin * sinf(fRatio * D3DX_PI) + fMinAlpha;

	if (fAlpha >= 1.0f)fAlpha = 1.0f;
	else if (fAlpha <= 0.0f)fAlpha *= -1.0f;

	// 色の更新
	m_pObject2D[UI_ENTER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha));

	if (m_nCntFream > BLINKING_FREAM)
	{
		// フレームカウンタリセット
		m_nCntFream = 0;
	}
}