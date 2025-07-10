//====================================================
//
// メッシュフィールド[meshfield.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "meshfield.h"
#include "manager.h"
#include "texture.h"
#include <cassert>

//====================================================
// コンストラクタ
//====================================================
CMeshField::CMeshField()
{
	// 各メンバ変数の初期化
	m_IdxBuff = { NULL };
	m_pVtxBuff = { NULL };

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 向き

	m_TexIndx = -1;	// テクスチャインデックス
	m_nDiviX = 0;	// 分割数(x軸)
	m_nDiviZ = 0;	// 分割数(z軸)
	m_nWidth = 0;	// 幅
	m_nHeight = 0;	// 高さ
	m_nMaxVtx = 0;	// 最大頂点数
	m_nPolyNum = 0;	// ポリゴン数
}

//====================================================
// デストラクタ
//====================================================
CMeshField::~CMeshField()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//インデックスへのポインタ
	WORD* pIdx = NULL;

	// 各メンバ変数の設定
	m_pos = pos;				// 位置
	m_nWidth = (int)fWidth;		// 幅
	m_nHeight = (int)fHeight;	// 高さ

	// インデックス数
	int flindexNum = (2 * (m_nDiviZ * (2 + m_nDiviX) - 1));

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nMaxVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;

	//中央へずらす
	float centerX = m_nWidth * (m_nDiviX - 2) * 0.5f;
	float centerY = m_nHeight * (m_nDiviZ - 2) * 0.5f;

	//頂点情報の設定
	for (int nCntZ = 0; nCntZ <= m_nDiviZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//頂点座標の設定
			pVtx[nCntVtx].pos = D3DXVECTOR3((float)(-m_nWidth + (m_nWidth * nCntX) - centerX), 0.0f, (float)(m_nHeight - (m_nHeight * nCntZ) + centerY));

			//法線ベクトルの設定
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);

			nCntVtx++;
		}
	}

	// maxを超えたときに強制終了
	assert(nCntVtx <= m_nMaxVtx);

	//頂点バッファをアンロック　
	m_pVtxBuff->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * flindexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_IdxBuff,
		NULL);

	//インデックスバッファをロック
	m_IdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nCntX;
	int Indx = 0;
	for (int nCntZ = 0; nCntZ < m_nDiviZ; nCntZ++)
	{
		for (nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//インデックスの設定
			pIdx[0] = (m_nDiviX + 1) * (nCntZ + 1) + nCntX;
			pIdx[1] = nCntX + (nCntZ * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}

		if (nCntZ < m_nDiviZ - 1)
		{
			pIdx[0] = (nCntX - 1) + (nCntZ * (m_nDiviX + 1));
			pIdx[1] = nCntX + ((nCntZ + 1) * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}
	}
	assert(Indx <= flindexNum);

	//インデックスバッファのアンロック
	m_IdxBuff->Unlock();

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CMeshField::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの破棄
	if (m_IdxBuff != NULL)
	{
		m_IdxBuff->Release();
		m_IdxBuff = NULL;
	}

	// 自身の破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CMeshField::Update(void)
{
	// なし
}

//====================================================
// 描画処理
//====================================================
void CMeshField::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャポインタの取得
	CTexture* pTexture = CManager::GetTexture();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_IdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_TexIndx));

	//メッシュ床を描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMaxVtx, 0, m_nPolyNum);
}

//====================================================
// 生成処理
//====================================================
CMeshField* CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int textype, int nDiviX, int nDiviZ, int nWidth, int nHeight)
{
	CMeshField* pMeshField = NULL;

	// メモリの確保
	pMeshField = new CMeshField;

	// 各メンバ変数の設定
	pMeshField->m_rot = rot;												// 向き
	pMeshField->m_TexIndx = textype;										// テクスチャインデックス
	pMeshField->m_nDiviX = nDiviX;											// 分割数(x軸)
	pMeshField->m_nDiviZ = nDiviZ;											// 分割数(z軸)
	pMeshField->m_nMaxVtx = (nDiviX + 1) * (nDiviZ + 1);					// 最大頂点数
	pMeshField->m_nPolyNum = (2 * nDiviX * nDiviZ + (nDiviZ - 1) * 4);		// ポリゴン数

	// 初期化処理
	pMeshField->Init(pos, (float)nWidth, (float)nHeight);

	return pMeshField;
}