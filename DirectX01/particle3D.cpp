//====================================================
//
// パーティクル[particle.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"particle3D.h"
#include"effect3D.h"
#include"manager.h"

//====================================================
// コンストラクタ
//====================================================
CParticle3D::CParticle3D(int nPriority) :CObject(nPriority)
{
	// 値をクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fRadius = 0;
	m_fSpeed = 0;
	m_nLife = 0;
	m_nLifeEffect = 0;
	m_nNumEffect = 0;
}

//====================================================
// デストラクタ
//====================================================
CParticle3D::~CParticle3D()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CParticle3D::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CParticle3D::Uninit(void)
{
	// 自分自身の破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CParticle3D::Update(void)
{
	// 寿命(パーティクル)を減らす
	m_nLife--;

	if (m_nLife > 0)
	{
		for (int nNumEffect = 0; nNumEffect < m_nNumEffect; nNumEffect++)
		{
			D3DXVECTOR3 Rot, tenRot, move;
			int nLife = 0;
			float fRadius = m_fRadius;

			tenRot = m_rot * 100.0f;

			// 角度の設定
			Rot.x = (float)(rand() % (int)tenRot.x - 314) * 0.01f;
			Rot.y = (float)(rand() % (int)tenRot.y - 314) * 0.01f;

			// 移動量の設定
			move.x = (float)sinf(Rot.x) * cosf(Rot.y) * m_fSpeed;
			move.y = (float)sinf(Rot.x) * sinf(Rot.y) * m_fSpeed;
			move.z = (float)cosf(Rot.x) * m_fSpeed;

			// サイズの設定
			fRadius = (float)(rand() % (int)m_fRadius + 1.0f);

			// 寿命の設定
			nLife = rand() % m_nLifeEffect + 1;

			// エフェクトの生成
			CEffect3D* pEffect = CEffect3D::Create(m_pos, move, fRadius, nLife, 0.0f);
			pEffect->SetColor(m_col);
		}
	}
	else
	{
		CParticle3D::Uninit();
	}
}

//====================================================
// 描画処理
//====================================================
void CParticle3D::Draw(void)
{

}

//====================================================
// 位置の設定
//====================================================
void CParticle3D::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//====================================================
// 色の設定
//====================================================
void CParticle3D::SetColor(D3DXCOLOR col)
{
	this->m_col = col;
}

//====================================================
// 生成処理(設定処理)
//====================================================
CParticle3D* CParticle3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fSpeed, int nLife, int nLifeEffect, int NumEffect)
{
	CParticle3D* pParticle = NULL;

	pParticle = new CParticle3D;

	// 各変数の設定
	pParticle->m_pos = pos;						// 位置
	pParticle->m_rot = rot;						// 向き
	pParticle->m_fRadius = fRadius;				// 半径
	pParticle->m_fSpeed = fSpeed;				// スピード
	pParticle->m_nLife = nLife;					// 寿命(パーティクル)
	pParticle->m_nLifeEffect = nLifeEffect;		// 寿命(エフェクト)

	// 1Fに呼ぶエフェクトの数
	if (NumEffect <= MAX_EFFECT)
	{
		pParticle->m_nNumEffect = NumEffect;
	}
	else
	{
		pParticle->m_nNumEffect = MAX_EFFECT;
	}

	return pParticle;
}