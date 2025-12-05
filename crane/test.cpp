//====================================================
// 
// テストシーン[test.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include "test.h"
#include"manager.h"
#include "fieldManager.h"

// 静的メンバ変数
CMeshField* CTest::m_pFiled = nullptr;
CFiledManager* CTest::m_FieldManager = nullptr;

//====================================================
// コンストラクタ
//====================================================
CTest::CTest()
{
	// 種類の設定
	CObject::SetType(CObject::TYPE_SCENE);

	m_pFiled = nullptr;
}

//====================================================
// デストラクタ
//====================================================
CTest::~CTest()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CTest::Init(void)
{
	// ポリゴン
	m_pFiled = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, 50, 50, 6, 6);
	//m_pFiled->BindTexIndex(CTexture::TYPE_FILED);

	m_FieldManager = new CFiledManager;
	m_FieldManager->Init();

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTest::Uninit(void)
{
	if (m_FieldManager != nullptr)
	{
		m_FieldManager->Uninit();
		m_FieldManager = nullptr;
	}

	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CTest::Update(void)
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		m_FieldManager->SetWave(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 25.0f, 0.2f, 1, 0.07f);
	}

	m_FieldManager->Update();
}

//====================================================
// 描画処理
//====================================================
void CTest::Draw(void)
{
	// なし
}
