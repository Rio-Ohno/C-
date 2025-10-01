//====================================================
//
// エフェクト[effect.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"effect.h"
#include"manager.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//====================================================
// コンストラクタ
//====================================================
CEffect::CEffect(int nPriority):CObject2D(nPriority)
{
	// 値をクリア
	m_nLife = 0;
	m_fDelSize = 0;
}

//====================================================
// デストラクタ
//====================================================
CEffect::~CEffect()
{

}

//====================================================
// 生成処理
//====================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius, int nLife, float fDelSize)
{
	// 現在のオブジェクト数を取得
	int nNumAll = CObject::GetNumAll();

	if (nNumAll >= MAX_OBJECT || nLife <= 0)
	{// 上限以上なら
		return NULL;
	}

	// エフェクトへのポインタ
	CEffect* pEffect = NULL;

	// メモリの確保
	pEffect = new CEffect;

	// エフェクトの初期化処理
	pEffect->Init(pos, fRadius, fRadius);

	//テクスチャの割当
	pEffect->BindTex(m_pTexture);

	// メンバ変数の設定
	pEffect->m_nLife = nLife;
	pEffect->m_move = move;

	// サイズを小さくする係数の設定
	pEffect->m_fDelSize = fDelSize;

	return pEffect;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ポリゴンの初期化処理
	CObject2D::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CEffect::Uninit(void)
{
	// ポリゴンの終了処理
	CObject2D::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CEffect::Update(void)
{
	// 寿命を減らす
	m_nLife--;

	// 位置の取得
	D3DXVECTOR3 pos = CObject2D::GetPos();

	if (m_nLife <= 0)
	{
		// エフェクトの終了処理
		CEffect::Uninit();
	}
	else if (pos.x <= 0.0f ||
		pos.x >= SCREEN_WIDTH ||
		pos.y <= 0.0f ||
		pos.y >= SCREEN_HEIGHT)
	{// 画面外に出たら

		// エフェクトの終了処理
		CEffect::Uninit();
	}
	else
	{
		if (m_fDelSize != 0)
		{// サイズを小さくする係数があるなら
			// 半径の取得
			float fRadius = CObject2D::GetWidth();

			// 半径を小さくする
			fRadius *= m_fDelSize;

			// サイズの設定
			CObject2D::SetSize(fRadius, fRadius);
		}

		// 位置の更新
		pos += m_move;
		CObject2D::SetPos(pos);
	}
}

//====================================================
// 描画処理
//====================================================
void CEffect::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ポリゴンの描画処理
	CObject2D::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//====================================================
// テクスチャの読込
//====================================================
HRESULT CEffect::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読込
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;
}

//====================================================
// テクスチャの破棄
//====================================================
void CEffect::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}