//====================================================
//
// タイトルシーン　[title.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "title.h"
#include "titleInfo.h"
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
	CManager::GetCamera()->SetCameraPos(TitleInfo::Camera::POS, TitleInfo::Camera::TARGET);
	CManager::GetCamera()->SetRotation(TitleInfo::Camera::ROT);

	// 空
	m_pSphere = CMeshSphere::Create(
		TitleInfo::Sky::POS, 
		TitleInfo::Sky::ROT, 
		TitleInfo::Sky::DIVISION_X,
		TitleInfo::Sky::DIVISION_Y,
		TitleInfo::Sky::RADIUS,
		TitleInfo::Sky::IS_HALF_SPHERE,
		TitleInfo::Sky::FRONT_FACE);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);	// テクスチャ設定
	m_pSphere->SetTurn(TitleInfo::Sky::ROT_SPEED);	// 回転設定

	// 壁
	CWall* pWall00 = CWall::Create(
		TitleInfo::Wall::POS_FRONT, 
		TitleInfo::Wall::ROT_FRONT, 
		TitleInfo::Wall::WIDTH_FRONT, 
		TitleInfo::Wall::HEIGHT, 
		TitleInfo::Wall::IS_COLLISION, 
		TitleInfo::Wall::IS_DISPLAY);

	CWall* pWall01 = CWall::Create(
		TitleInfo::Wall::POS_BACK, 
		TitleInfo::Wall::ROT_BACK, 
		TitleInfo::Wall::WIDTH_BACK, 
		TitleInfo::Wall::HEIGHT,
		TitleInfo::Wall::IS_COLLISION,
		TitleInfo::Wall::IS_DISPLAY);

	CWall* pWall02 = CWall::Create(
		TitleInfo::Wall::POS_LEFT, 
		TitleInfo::Wall::ROT_LEFT,
		TitleInfo::Wall::WIDTH_LEFT, 
		TitleInfo::Wall::HEIGHT,
		TitleInfo::Wall::IS_COLLISION,
		TitleInfo::Wall::IS_DISPLAY);

	CWall* pWall03 = CWall::Create(
		TitleInfo::Wall::POS_RIGHT,
		TitleInfo::Wall::ROT_RIGHT, 
		TitleInfo::Wall::WIDTH_RIGHT, 
		TitleInfo::Wall::HEIGHT,
		TitleInfo::Wall::IS_COLLISION,
		TitleInfo::Wall::IS_DISPLAY);

	// テクスチャの設定
	pWall00->BindTexIndex(CTexture::TYPE_FILED);
	pWall01->BindTexIndex(CTexture::TYPE_FILED);
	pWall02->BindTexIndex(CTexture::TYPE_FILED);
	pWall03->BindTexIndex(CTexture::TYPE_FILED);

	// ポリゴン
	m_pField = CMeshField::Create(
		TitleInfo::Field::POS, 
		TitleInfo::Field::ROT, 
		TitleInfo::Field::DIVISION_X,
		TitleInfo::Field::DIVISION_Z,
		TitleInfo::Field::WIDTH,
		TitleInfo::Field::HEIGHT);// 280×240;
	m_pField->BindTexIndex(CTexture::TYPE_FILED);

	// プライズマネージャー
	m_pPrizeManager = new CPrizemanager;
	m_pPrizeManager->Init();
	//m_pPrizeManager->Spawn();

	// プレイヤー
	m_pPlayer= CPlayer::Create(TitleInfo::Player::POS, TitleInfo::Player::ROT);

	// UIポリゴン
	m_pObject2D[UI_POP] = CObject2D::Create(
		TitleInfo::UI::POP::POS, 
		TitleInfo::UI::POP::WIDTH,
		TitleInfo::UI::POP::HEIGHT);
	m_pObject2D[UI_POP]->BindTexIndx(CTexture::TYPE_POP);

	m_pObject2D[UI_TITLE] = CObject2D::Create(
		TitleInfo::UI::TITLE::POS, 
		TitleInfo::UI::TITLE::WIDTH, 
		TitleInfo::UI::TITLE::HEIGHT);
	m_pObject2D[UI_TITLE]->BindTexIndx(CTexture::TYPE_TITLE);

	m_pObject2D[UI_ENTER] = CObject2D::Create(
		TitleInfo::UI::ENTER::POS,
		TitleInfo::UI::ENTER::WIDTH,
		TitleInfo::UI::ENTER::HEIGHT);
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