//====================================================
// 
// ビルボードオブジェクト [objectBillboard.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include"objectBillboard.h"
#include"manager.h"

//====================================================
// コンストラクタ
//====================================================
CObjectBillboard::CObjectBillboard()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_indxTexture = -1;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
}

//====================================================
// デストラクタ
//====================================================
CObjectBillboard::~CObjectBillboard()
{
	// なし
}

//============================================================
// 生成処理
//============================================================
CObjectBillboard* CObjectBillboard::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXVECTOR3 origin)
{
	CObjectBillboard* pBillboard = NULL;

	pBillboard = new CObjectBillboard;

	// 各メンバ変数の設定
	pBillboard->m_pos = pos;
	pBillboard->m_fWidth = fWidth;
	pBillboard->m_fHeight = fHeight;
	pBillboard->m_origin = origin;

	// 初期化処理
	pBillboard->Init();

	return pBillboard;
}

//====================================================
// ビルボードの初期化処理
//====================================================
HRESULT CObjectBillboard::Init(void)
{
	//デバイスへのポインタと取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 向きの初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-(m_origin.x), (m_fHeight - m_origin.y), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(m_fWidth - m_origin.x), (m_fHeight - m_origin.y), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_origin.x), (-m_origin.y), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(m_fWidth - m_origin.x), (-m_origin.y), 0.0f);

	//各頂点の法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================================
// ビルボードの終了処理
//============================================================
void CObjectBillboard::Uninit(void)
{
	//頂点バッファの解放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの破棄
	CObject::Release();
}

//============================================================
// ビルボードの更新処理
//============================================================
void CObjectBillboard::Update(void)
{

}

//============================================================
// ビルボードの描画処理
//============================================================
void CObjectBillboard::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// テクスチャクラスへのポインタの取得
	CTexture* pTexture = CManager::GetTexture();

	//ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMATRIX mtxView;//ビューマトリックス

	//ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ座標の設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_indxTexture));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================================
// サイズの設定
//============================================================
void CObjectBillboard::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
}

//============================================================
// 色の設定
//============================================================
void CObjectBillboard::SetColor(D3DXCOLOR col)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}