//====================================================
//
// リザルトシーン処理 [result.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"result.h"
#include"manager.h"

//====================================================
// コンストラクタ
//====================================================
CResult::CResult() :CScene(CScene::MODE_TITLE)
{
	CObject::SetType(CObject::TYPE_SCENE);
}

//====================================================
// デストラクタ
//====================================================
CResult::~CResult()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// テクスチャの取得
	CTexture* pTexture = CManager::GetTexture();

	CObject2D* poly = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	poly->BindTexIndx(pTexture->Register("data\\TEXTURE\\Result000.png"));

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CResult::Uninit(void)
{
	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CResult::Update(void)
{
	// スペースを押したらタイトルへ
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) == true)
	{
		CManager::GetFade()->Set(CScene::MODE_TITLE);
	}
}

//====================================================
// 描画処理
//====================================================
void CResult::Draw(void)
{
	// なし
}