//====================================================
//
// タイトルシーン　[title.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "title.h"
#include "object2D.h"
#include "meshfield.h"
#include "manager.h"

//====================================================
// コンストラクタ
//====================================================
CTitle::CTitle()
{
	// 種類の設定
	CObject::SetType(CObject::TYPE_SCENE);

	m_pObject2D = nullptr;
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
	// ポリゴン
	CMeshField* pFiled = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, 50, 50, 7, 6);
	pFiled->BindTexIndex(CTexture::TYPE_FILED);

	m_pObject2D = CObject2D::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), 1280.0f, 200.0f);
	m_pObject2D->BindTexIndx(CTexture::TYPE_TITLE);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTitle::Uninit(void)
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();

		m_pObject2D = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CTitle::Update(void)
{
//#ifdef _DEBUG
	// キーボードの情報取得
	CKeyboard* pKeyborad = CManager::GetKeyboard();

	if (pKeyborad->GetTrigger(DIK_RETURN))
	{
		// ゲームシーンに切り替える
		CManager::GetFade()->Set(CScene::MODE_GAME);
	}
//#endif // _DEBUG

}

//====================================================
// 描画処理
//====================================================
void CTitle::Draw(void)
{
	// なし
}