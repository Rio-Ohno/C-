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

//====================================================
// コンストラクタ
//====================================================
CTitle::CTitle() :CScene(CScene::MODE_TITLE)
{
	CObject::SetType(CObject::TYPE_SCENE);
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

	CObject2D* poly = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	poly->BindTexIndx(pTexture->Register("data\\TEXTURE\\Title000.png"));

	// カメラの設定
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTitle::Uninit(void)
{
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
}

//====================================================
// 描画処理
//====================================================
void CTitle::Draw(void)
{
	// なし
}