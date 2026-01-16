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
	m_nCntFream = 0;
	m_nSpan = 0;
	m_bColorRandom = false;
}

//====================================================
// デストラクタ
//====================================================
CParticle3D::~CParticle3D()
{
	// なし
}

//====================================================
// 生成処理(設定処理)
//====================================================
CParticle3D* CParticle3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fSpeed, int nLife, int nLifeEffect, int NumEffect,int nSpan)
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
	pParticle->m_nSpan = nSpan;					// エフェクトを呼ぶ間隔

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

//====================================================
// 初期化処理
//====================================================
HRESULT CParticle3D::Init(void)
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

	if (m_nSpan > 0)// 間隔があるなら
	{
		// フレームカウントアップ
		m_nCntFream++;
	}

	if (m_nLife > 0)
	{
		if (m_nCntFream >= m_nSpan)
		{
			// フレームカウンタリセット
			m_nCntFream = 0;

			for (int nNumEffect = 0; nNumEffect < m_nNumEffect; nNumEffect++)
			{
				D3DXVECTOR3 Rot, tenRot, move;
				int nLife = 0;
				float fRadius = m_fRadius;

				tenRot = m_rot * 100.0f;

				// 角度の設定
				Rot.x = (float)(rand() % (int)tenRot.x) * 0.01f;
				Rot.y = (float)(rand() % (int)tenRot.y) * 0.01f;

				// 移動量の設定
				move.x = (float)sinf(Rot.x) * cosf(Rot.y) * m_fSpeed;
				move.y = (float)cosf(Rot.x) * m_fSpeed;
				move.z = (float)sinf(Rot.x) * sinf(Rot.y) * m_fSpeed;

				// サイズの設定
				fRadius = (float)(rand() % (int)m_fRadius + 1.0f);

				// 寿命の設定
				nLife = rand() % m_nLifeEffect + 1;

				// エフェクトの生成
				CEffect3D* pEffect = CEffect3D::Create(m_pos, move, fRadius, nLife, 0.0f);

				// 色の設定
				if (m_bColorRandom)// ランダムなら
				{
					int nR = (int)(m_col.r * 100.0f);
					int nG = (int)(m_col.g * 100.0f);
					int nB = (int)(m_col.b * 100.0f);
					int nA = (int)(m_col.a * 100.0f);

					float R = 0.0f, G = 0.0f, B = 0.0f, A = 0.0f;

					// 0より大きいならランダム
					if (nR > 0)
					{
						R = (float)(rand() % nR) * 0.01f;
					}
					if (nG > 0)
					{
						G = (float)(rand() % nG) * 0.01f;
					}
					if (nB > 0)
					{
						B = (float)(rand() % nB) * 0.01f;
					}
					if (nA > 0)
					{
						A = (float)(rand() % nA) * 0.01f;
					}

					// エフェクトの色の設定
					pEffect->SetColor(D3DXCOLOR(R, G, B, A));
				}
				else
				{
					// エフェクトの色の設定
					pEffect->SetColor(m_col);
				}
			}
		}
	}
	else
	{
		// 終了処理
		CParticle3D::Uninit();
	}
}

//====================================================
// 描画処理
//====================================================
void CParticle3D::Draw(void)
{
	// なし
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
// 色の設定(ランダム)
//====================================================
void CParticle3D::SetColorRandom(D3DXCOLOR Maxcol)
{
	m_bColorRandom = true;

	// 色の最大の設定
	m_col = Maxcol;
}