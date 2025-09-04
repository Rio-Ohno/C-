//====================================================
//
// エフェクト[effect3D.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"effect3D.h"
#include"manager.h"

// 静的メンバ変数
int CEffect3D::m_Texindx = -1;

//====================================================
// コンストラクタ
//====================================================
CEffect3D::CEffect3D()
{
	m_nLife = 0;
	m_fDelSize = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================================
// デストラクタ
//====================================================
CEffect3D::~CEffect3D()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CEffect3D* CEffect3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius, int nLife, float fDelSize)
{
	CEffect3D* pEffect = NULL;

	// メモリの確保
	pEffect = new CEffect3D;

	pEffect->m_nLife = nLife;
	pEffect->m_fDelSize = fDelSize;
	pEffect->m_move = move;
	pEffect->m_Texindx = CTexture::TYPE_EFFECT;

	// 回転軸の設定
	pEffect->SetOriogin(D3DXVECTOR3(fRadius * 0.5f, fRadius * 0.5f, 0.0f));

	// 初期化処理
	pEffect->Init(pos, fRadius, fRadius);

	// テクスチャの割当
	pEffect->BindTexindx(m_Texindx);

	return pEffect;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CEffect3D::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// 初期化処理
	CObjectBillboard::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CEffect3D::Uninit(void)
{
	// 終了処理
	CObjectBillboard::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CEffect3D::Update(void)
{
	// 寿命を減らす
	m_nLife--;

	// 位置の取得
	D3DXVECTOR3 pos = CObjectBillboard::GetPos();

	if (m_nLife <= 0)
	{
		// エフェクトの終了処理
		CEffect3D::Uninit();
	}
	else
	{
		if (m_fDelSize != 0.0f)
		{// サイズを小さくする係数があるなら
			// 半径の取得
			float fRadius = CObjectBillboard::GetWidth();

			// 半径を小さくする
			fRadius *= m_fDelSize;

			// サイズの設定
			CObjectBillboard::SetSize(fRadius, fRadius);
		}

		// 位置の更新
		pos += m_move;
		CObjectBillboard::SetPos(pos);
	}
}

//====================================================
// 描画処理
//====================================================
void CEffect3D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zテストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Zの比較方法
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// Zバッファには書き込まない

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画処理
	CObjectBillboard::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Zテストを元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}