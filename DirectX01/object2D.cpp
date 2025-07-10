//====================================================
//
// オブジェクト[object.h]
// Author:Rio Ohno
//
//====================================================

//インクルード
#include"object2D.h"
#include"renderer.h"
#include"manager.h"

////====================================================
//// コンストラクタ
////====================================================
//CObject2D::CObject2D()
//{
//	//値をクリアする
//	m_pTexture = NULL;
//	m_pVtxBuff = NULL;
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_fWidth = 0;
//	m_fHeight = 0;
//}

//====================================================
// コンストラクタ
//====================================================
CObject2D::CObject2D(int nPriority) :CObject(nPriority)
{
	//値をクリアする
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0;
	m_fHeight = 0;
}

//====================================================
// デストラクタ
//====================================================
CObject2D::~CObject2D()
{
}

//====================================================
// 初期化処理
//====================================================
HRESULT CObject2D::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//レンダラーの取得
	CRenderer* pRenderer = CManager::GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 各変数の初期化
	m_pos = pos;// 位置
	m_fWidth = fWidth;// 幅
	m_fHeight = fHeight;// 高さ

	//ポリゴンの初期化処理

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, 
							  m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/,
							  m_pos.z);

	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/,
							  m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/,
							  m_pos.z);

	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/,
							  m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/,
		                      m_pos.z);

	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/,
							  m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/,
							  m_pos.z);

	//int i = 0;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//rhwの設定
		pVtx[nCnt].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CObject2D::Uninit(void)
{
	//ポリゴンの終了処理
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}

	//バッファーの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CObject2D::Update(void)
{
	//ポリゴンの更新処理
}

//====================================================
// 描画処理
//====================================================
void CObject2D::Draw(void)
{
	//レンダラーの取得
	CRenderer* pRenderer = CManager::GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ポリゴンの描画処理

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//====================================================
// 位置の設定
//====================================================
void CObject2D::SetPos(const D3DXVECTOR3 pos)
{
	CObject2D::m_pos = pos;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//====================================================
// 向きの設定
//====================================================
void CObject2D::SetRot(const D3DXVECTOR3 rot)
{
	CObject2D::m_rot = rot;
}

//====================================================
// サイズの設定
//====================================================
void CObject2D::SetSize(const float fWidth,const float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//====================================================
// テクスチャの設定処理
//====================================================
void CObject2D::BindTex(LPDIRECT3DTEXTURE9 pTexture)
{
	// テクスチャの設定
	m_pTexture = pTexture;
}

//====================================================
// テクスチャの設定処理
//====================================================
void CObject2D::BindTex2(int nTextureIndx)
{
	// テクスチャインデックスの設定
	m_nIndxTex = nTextureIndx;
}

//====================================================
// 生成処理
//====================================================
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CObject2D* pObject2D = NULL;

	//オブジェクトの生成
	pObject2D = new CObject2D;

	//初期化処理
	pObject2D->Init(pos, fWidth, fHeight);

	return pObject2D;
}

//====================================================
// テクスチャのUV設定処理
//====================================================
void CObject2D::SetTexUV(float fDiviX, float fDiviY)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
		//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((1.0f / fDiviX), (1.0f / fDiviY) - 1);
	pVtx[1].tex = D3DXVECTOR2((1.0f / fDiviX) * 2.0f, (1.0f / fDiviY) - 1);
	pVtx[2].tex = D3DXVECTOR2((1.0f / fDiviX), (1.0f / fDiviY));
	pVtx[3].tex = D3DXVECTOR2((1.0f / fDiviX) * 2.0f, (1.0f / fDiviY));

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//====================================================
// 頂点バッファの設定処理
//====================================================
void CObject2D::SetBuffer(LPDIRECT3DVERTEXBUFFER9 pVtxBuff)
{
	// 頂点バッファの設定
	m_pVtxBuff = pVtxBuff;
}

//====================================================
// 頂点カラーの設定処理
//====================================================
void CObject2D::SetColor(D3DXCOLOR col)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//頂点カラーの設定
		pVtx[nCnt].col = col;
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
