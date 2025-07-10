//====================================================
//
// 爆発[explosion.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"explosion.h"
#include"manager.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

////====================================================
//// コンストラクタ
////====================================================
//CExplosion::CExplosion()
//{
//	// 値をクリア
//	m_nCntAnime = 0;
//	m_nPatternAnime = 0;
//}

//====================================================
// コンストラクタ
//====================================================
CExplosion::CExplosion(int nPriority) :CObject2D(nPriority)
{
	// 値をクリア
	m_nCntAnime = 0;
	m_nPatternAnime = 0;
}

//====================================================
// デストラクタ
//====================================================
CExplosion::~CExplosion()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ポリゴンの初期化処理
	CObject2D::Init(pos, fWidth, fHeight);

	// テクスチャ座標の設定
	SetTexUV(8.0f, 1.0f);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CExplosion::Uninit(void)
{
	// ポリゴンの終了処理
	CObject2D::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CExplosion::Update(void)
{
	// アニメーション
	Anime(8, 1);
}

//====================================================
// 描画処理
//====================================================
void CExplosion::Draw(void)
{
	// ポリゴンの描画処理
	CObject2D::Draw();
}

//====================================================
// アニメーション処理
//====================================================
void CExplosion::Anime(int nDiviX, int nDiviY)
{
	//カウントアップ
	m_nCntAnime++;

	if (((m_nCntAnime + 1) % EXPLOSION_ANIME_SPAN) == 0)
	{
		// 0に戻す
		m_nCntAnime = 0;

		// アニメカウンターカウントアップ
		m_nPatternAnime = (m_nPatternAnime + 1) % nDiviX * nDiviY;

		// バッファーの取得
		LPDIRECT3DVERTEXBUFFER9 pBuff = GetBuffer();

		//頂点情報へのポインタ
		VERTEX_2D* pVtx = NULL;

		//頂点バッファをロック
		pBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((1.0f / nDiviX) * m_nPatternAnime, (1.0f / nDiviY) * (m_nPatternAnime / nDiviX));
		pVtx[1].tex = D3DXVECTOR2((1.0f / nDiviX) * (m_nPatternAnime + 1), (1.0f / nDiviY) * (m_nPatternAnime / nDiviX));
		pVtx[2].tex = D3DXVECTOR2((1.0f / nDiviX) * m_nPatternAnime, (1.0f / nDiviY) * ((m_nPatternAnime / nDiviX) + 1));
		pVtx[3].tex = D3DXVECTOR2((1.0f / nDiviX) * (m_nPatternAnime + 1), (1.0f / nDiviY) * ((m_nPatternAnime / nDiviX) + 1));

		//頂点バッファのアンロック
		pBuff->Unlock();

		if (m_nPatternAnime >= nDiviX * nDiviY - 1)
		{
			// 終了処理
			Uninit();
		}
	}
}

//====================================================
// テクスチャの読み込み処理
//====================================================
HRESULT CExplosion::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読込
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;

}

//====================================================
// テクスチャの破棄
//====================================================
void CExplosion::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//====================================================
// 生成処理
//====================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, float fRadius)
{
	CExplosion* pExplosion = NULL;

	// メモリの確保
	pExplosion = new CExplosion;

	// 初期化処理
	pExplosion->Init(pos, fRadius, fRadius);

	//テクスチャの割当
	pExplosion->BindTex(m_pTexture);

	// 種類の設定
	pExplosion->SetType(CObject::TYPE_EXPLOSION);

	return pExplosion;
}
