//====================================================
//
// メッシュシリンダー [meshcylinder.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "meshcylinder.h"
#include"manager.h"
#include <cassert>

//====================================================
// コンストラクタ
//====================================================
CMeshCylinder::CMeshCylinder()
{
	// 各変数初期化
	m_pVtxBuff = { NULL };
	m_pIdxBuff = { NULL };
	m_mtxWorld = {};

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nTexindx = -1;
	m_nDiviX = 0;
	m_nDiviY = 0;
	m_nMaxVtx = 0;
	m_nPolyNum = 0;
	m_fHeight = 0.0f;
	m_fRadius = 0.0f;
	m_bCulling = true;
}

//====================================================
// デストラクタ
//====================================================
CMeshCylinder::~CMeshCylinder()
{
	// なし
}

//====================================================
//初期化処理
//====================================================
HRESULT CMeshCylinder::Init(D3DXVECTOR3 pos,float fWidth,float fHeight)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//インデックスへのポインタ
	WORD* pIdx = NULL;

	int flindexNum = (2 * (m_nDiviY * (2 + m_nDiviX) - 1));	//インデックス数

	//インデックスカウンター
	int indx = 0;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nMaxVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY <= m_nDiviY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//角度算出
			float fAngle = ((D3DX_PI * 2.0f / m_nDiviX) * nCntX);

			//高さの格納
			float fHeight = (m_fHeight / m_nDiviY) * (m_nDiviY - nCntY);

			//頂点の設定
			pVtx[indx].pos = D3DXVECTOR3(m_fRadius * sinf(fAngle), fHeight, m_fRadius * cosf(fAngle));

			//中心へのベクトル
			D3DXVECTOR3 vec = m_pos - pVtx[indx].pos;

			//ベクトルの正規化,各頂点の法線の設定
			D3DXVec3Normalize(&pVtx[indx].nor, &vec);

			//頂点カラーの設定
			pVtx[indx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[indx].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntY);
			indx++;
		}
	}
	assert(indx <= m_nMaxVtx);

	//頂点バッファをアンロック　
	m_pVtxBuff->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * flindexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nCntX = 0;
	int Indx = 0;
	for (int nCntY = 0; nCntY < m_nDiviY; nCntY++)
	{
		for (nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//インデックスの設定
			pIdx[0] = (m_nDiviX + 1) * (nCntY + 1) + nCntX;
			pIdx[1] = nCntX + (nCntY * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}

		//衰退ポリゴン分
		if (nCntY < m_nDiviY - 1)
		{
			//インデックスの設定
			pIdx[0] = (nCntX - 1) + (nCntY * (m_nDiviX + 1));
			pIdx[1] = nCntX + ((nCntY + 1) * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}
	}
	assert(indx <= m_nMaxVtx);

	//インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CMeshCylinder::Uninit(void)
{
	//バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CMeshCylinder::Update(void)
{
	// なし
}

//====================================================
// 描画処理
//====================================================
void CMeshCylinder::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャクラスへのポインタの取得
	CTexture* pTexture = CManager::GetTexture();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	//ライトを切る
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	if (m_bCulling == true)
	{
		//カリングをつける
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
	else
	{
		//カリングを切る
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデバイスからデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexindx));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMaxVtx, 0, m_nPolyNum);

	//ライトをつける
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//カリングをつける
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//====================================================
// 生成処理
//====================================================
CMeshCylinder* CMeshCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int DiviX, int DiviY, float fHeight, float fRadius)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//インデックスへのポインタ
	WORD* pIdx = NULL;

	CMeshCylinder* pCylinder = NULL;

	// メモリの確保
	pCylinder = new CMeshCylinder;

	//各変数の設定
	pCylinder->m_pos = pos;												// 位置
	pCylinder->m_rot = rot;												// 向き
	pCylinder->m_nDiviX = DiviX;										// 分割数(x軸)
	pCylinder->m_nDiviY = DiviY;										// 分割数(y軸)
	pCylinder->m_fHeight = fHeight;										// 高さ
	pCylinder->m_fRadius = fRadius;										// 半径
	pCylinder->m_nMaxVtx = (DiviX + 1) * (DiviY + 1);					// 最大頂点数
	pCylinder->m_nPolyNum = (2 * DiviX * DiviY + (DiviY - 1) * 4);		// ポリゴン数

	// 初期化処理
	pCylinder->Init(pos, 0.0f, fHeight);

	return pCylinder;
}

//====================================================
// 色の設定処理
//====================================================
void CMeshCylinder::SetColor(D3DXCOLOR col)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//インデックスカウンター
	int indx = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY <= m_nDiviY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//頂点カラーの設定
			pVtx[indx].col = col;

			// カウントアップ
			indx++;
		}
	}
	assert(indx <= m_nMaxVtx);

	//頂点バッファをアンロック　
	m_pVtxBuff->Unlock();
}