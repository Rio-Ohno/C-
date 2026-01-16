//====================================================
// 
//  当たり判定（コライダー）[collider.cpp]
// Author：Rio Ohno
// 
//====================================================

// インクルード
#include "collider.h"

//====================================================
// 球のコライダーのコンストラクタ
//====================================================
CColliderSphere::CColliderSphere()
{
	// メンバ変数の初期化
	m_fRadius = 0.0f;
}

//====================================================
// パラメーターの設定処理
//====================================================
void CColliderSphere::SetParameter(D3DXVECTOR3 pos, float fRadius)
{
	// 位置
	CColliderBase::SetPos(pos);

	// 半径
	m_fRadius = fRadius;
}

//====================================================
// 円柱のコライダーのコンストラクタ
//====================================================
CColliderCylinder::CColliderCylinder()
{
	// メンバ変数の初期化
	m_fRadius = 0.0f;
	m_fHeight = 0.0f;
}

//====================================================
// パラメーターの設定処理
//====================================================
void CColliderCylinder::SetParameter(D3DXVECTOR3 pos, float fRadius, float fHeight)
{
	// 位置
	CColliderBase::SetPos(pos);

	// 半径
	m_fRadius = fRadius;

	// 高さ
	m_fHeight = fHeight;
}