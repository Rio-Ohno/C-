//====================================================
//
// ホール　[hole.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "hole.h"
#include "collider.h"

//====================================================
// デストラクタ
//====================================================
CHole::~CHole()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CHole* CHole::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY, float fHeight, float fRadius)
{
	CHole* pHole = nullptr;

	// メモリの確保
	pHole = new CHole;

	// 各要素の設定
	pHole->CMeshCylinder::SetPos(pos);					// 位置
	pHole->CMeshCylinder::SetRot(rot);					// 向き
	pHole->CMeshCylinder::SetRadius(fRadius);			// 半径
	pHole->CMeshCylinder::SetHeight(fHeight);			// 高さ
	pHole->CMeshCylinder::SetParameter(DiviX, DiviY);	// 分割数

	// 初期化処理
	pHole->Init();

	return pHole;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CHole::Init(void)
{
	// カリングを切る
	CMeshCylinder::SetCulling(false);

	// 親クラスの初期化処理
	if (FAILED(CMeshCylinder::Init()))
	{
		return 0;
	}

	// 色の設定
	CMeshCylinder::SetColor(D3DXCOLOR(0.5f, 1.0f, 0.9f, 0.7f));

	// コライダーの生成
	m_collider = new CColliderCylinder;
	m_collider->Init();

	// コライダーの設定
	m_collider->SetParameter(CMeshCylinder::GetPos(), CMeshCylinder::GetRadius() * COLLIDER_SCALE_RADIUS, CMeshCylinder::GetHeight()* COLLIDER_SCALE_HEIGHT);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CHole::Uninit(void)
{
	// 親クラスの終了処理
	CMeshCylinder::Uninit();

	// コライダーの破棄
	if (m_collider != nullptr)
	{
		// 終了処理
		m_collider->Uninit();
		m_collider = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CHole::Update(void)
{
	// 親クラスの更新処理
	CMeshCylinder::Update();
}

//====================================================
// 描画処理
//====================================================
void CHole::Draw(void)
{
	// 親クラスの描画処理
	CMeshCylinder::Draw();
}