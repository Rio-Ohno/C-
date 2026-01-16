//====================================================
// 
// リザルトシーン[result.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include "result.h"
#include "object2D.h"
#include "manager.h"

//====================================================
// コンストラクタ
//====================================================
CResult::CResult()
{
	// 種類の設定
	CObject::SetType(CObject::TYPE_SCENE);

	m_pObject2D = nullptr;
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
HRESULT CResult::Init(void)
{
	m_pObject2D = CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 600.0f, 600.0f);
	m_pObject2D->BindTexIndx(CTexture::TYPE_RESULT);
	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CResult::Uninit(void)
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
void CResult::Update(void)
{
#ifdef _DEBUG
	// キーボードの情報取得
	CKeyboard* pKeyborad = CManager::GetKeyboard();

	if (pKeyborad->GetTrigger(DIK_RETURN))
	{
		// タイトルシーンに切り替える
		CManager::GetFade()->Set(CScene::MODE_TITLE);
	}
#endif // _DEBUG
}

//====================================================
// 描画処理
//====================================================
void CResult::Draw(void)
{
	// なし
}