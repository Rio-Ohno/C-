//====================================================
// 
// リザルトシーン[result.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include "result.h"
#include "score.h"
#include "object2D.h"
#include "meshSphere.h"
#include "manager.h"

// 静的メンバ変数
CScore* CResult::m_pScore = nullptr;
CMeshSphere* CResult::m_pSphere = nullptr;

//====================================================
// コンストラクタ
//====================================================
CResult::CResult()
{
	// 種類の設定
	CObject::SetType(CObject::TYPE_SCENE);

	m_pObject2D = nullptr;
	m_pScore = nullptr;
	m_pSphere = nullptr;
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
	CObject2D* pObject2D = CObject2D::Create(D3DXVECTOR3(640.0f, 75.0f, 0.0f), 1280.0f, 150.0f);
	pObject2D->BindTexIndx(CTexture::TYPE_TITLE);

	m_pObject2D = CObject2D::Create(D3DXVECTOR3(640.0f, 60.0f, 0.0f), 600.0f, 120.0f);
	m_pObject2D->BindTexIndx(CTexture::TYPE_RESULT);

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(802.5f, 360.0f, 0.0f), 6, 45.0f, 65.0f);
	int score = CScore::Load();
	m_pScore->Add(score);

	// 球体(空)の生成処理
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);	// テクスチャ設定
	m_pSphere->SetTurn(0.0005f);					// 回転設定

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
	// キーボードの情報取得
	CKeyboard* pKeyborad = CManager::GetKeyboard();

	if (pKeyborad->GetTrigger(DIK_RETURN))
	{
		// タイトルシーンに切り替える
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