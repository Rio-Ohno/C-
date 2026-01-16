//====================================================
//
// メッシュフィールド[meshfield.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "meshfield.h"
#include "manager.h"
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

	m_nTexIndx = -1;	// テクスチャインデックス
	m_nDiviX = 0;	// 分割数(x軸)
	m_nDiviZ = 0;	// 分割数(z軸)
	m_nWidth = 0;	// 幅
	m_nHeight = 0;	// 高さ
	m_nMaxVtx = 0;	// 最大頂点数
	m_nPolyNum = 0;	// ポリゴン数
	m_nCntFream = 0;// フレームカウンター
}

//====================================================
// デストラクタ
//====================================================
CMeshField::~CMeshField()
{
	// なし
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
	pMeshField->m_pos = pos;												// 位置
	pMeshField->m_rot = rot;												// 向き
	pMeshField->m_nTexIndx = textype;										// テクスチャインデックス
	pMeshField->m_nWidth = nWidth;											// 幅
	pMeshField->m_nHeight = nHeight;										// 高さ
	pMeshField->m_nDiviX = nDiviX;											// 分割数(x軸)
	pMeshField->m_nDiviZ = nDiviZ;											// 分割数(z軸)
	pMeshField->m_nMaxVtx = (nDiviX + 1) * (nDiviZ + 1);					// 最大頂点数
	pMeshField->m_nPolyNum = (2 * nDiviX * nDiviZ + (nDiviZ - 1) * 4);		// ポリゴン数

	// 初期化処理
	pMeshField->Init();

	return pMeshField;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CMeshField::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//インデックスへのポインタ
	WORD* pIdx = NULL;

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
			pIdx[0] = nCntX + (nCntZ + 1) * (m_nDiviX + 1);
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
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIndx));

	//メッシュ床を描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMaxVtx, 0, m_nPolyNum);
}

//====================================================
// 高さを渡す処理
//====================================================
float CMeshField::GetHeight(const D3DXVECTOR3 pos)
{
	float fHeight = 0.0f;// 返す用変数

	float centerX = m_nWidth * (m_nDiviX - 2) * 0.5f;
	float centerZ = m_nHeight * (m_nDiviZ - 2) * 0.5f;

	float localX = pos.x + centerX + (float)m_nWidth;// 1つのセルをposぶんずらすイメージ
	int cellX = (int)floorf(localX / m_nWidth);// X軸インデックス

	float localZ = pos.z + centerZ + (float)m_nHeight;// 1つのセルをposぶんずらすイメージ
	int cellZ = (int)floorf(localZ / m_nHeight);// Z軸インデックス

	// 特定したセルのインデックス算出
	int indx0 = cellX + cellZ * (m_nDiviX + 1);
	int indx1 = (cellX + 1) + cellZ * (m_nDiviX + 1);
	int indx2 = cellX + (cellZ + 1) * (m_nDiviX + 1);
	int indx3 = (cellX + 1) + (cellZ + 1) * (m_nDiviX + 1);

	// ローカルUV
	float u = (localX / (float)m_nWidth) - cellX;
	float v = (localZ / (float)m_nHeight) - cellZ;

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	D3DXVECTOR3 VecA, VecB, VecC, VecD,
		norA, norB, norC, nor, VecPos;

	// インデックス順
	// 01
	// 23

	if (u + v < 1.0f)// 下側三角形なら
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		D3DXVECTOR3 posA = pVtx[indx2].pos;
		D3DXVECTOR3 posB = pVtx[indx0].pos;
		D3DXVECTOR3 posC = pVtx[indx3].pos;

		//頂点バッファをアンロック　
		m_pVtxBuff->Unlock();

		// 全頂点のベクトル
		VecA = posB - posA;
		VecB = posC - posB;
		VecC = posA - posC;
		VecD = posC - posA;

		// 対象とのベクトル
		VecPos = pos - posA;

		D3DXVECTOR3 VecPosA = pos - posA;
		D3DXVECTOR3 VecPosB = pos - posB;
		D3DXVECTOR3 VecPosC = pos - posC;

		// 外積
		D3DXVec3Cross(&norA, &VecPosA, &VecA);
		D3DXVec3Cross(&norB, &VecPosB, &VecB);
		D3DXVec3Cross(&norC, &VecPosC, &VecC);

		// 法線を正規化
		D3DXVec3Normalize(&norA, &norA);
		D3DXVec3Normalize(&norB, &norB);
		D3DXVec3Normalize(&norC, &norC);
	}
	else// 上側三角形なら
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		D3DXVECTOR3 posA = pVtx[indx1].pos;
		D3DXVECTOR3 posB = pVtx[indx3].pos;
		D3DXVECTOR3 posC = pVtx[indx0].pos;

		//頂点バッファをアンロック　
		m_pVtxBuff->Unlock();

		// 全頂点のベクトル
		VecA = posB - posA;
		VecB = posC - posB;
		VecC = posA - posC;
		VecD = posC - posA;

		// 対象とのベクトル
		VecPos = pos - posA;

		D3DXVECTOR3 VecPosA = pos - posA;
		D3DXVECTOR3 VecPosB = pos - posB;
		D3DXVECTOR3 VecPosC = pos - posC;

		// 外積
		D3DXVec3Cross(&norA, &VecPosA, &VecA);
		D3DXVec3Cross(&norB, &VecPosB, &VecB);
		D3DXVec3Cross(&norC, &VecPosC, &VecC);

		// 法線を正規化
		D3DXVec3Normalize(&norA, &norA);
		D3DXVec3Normalize(&norB, &norB);
		D3DXVec3Normalize(&norC, &norC);
	}

	float dot = 0.0f;// 内積結果保存用

	// 2つのベクトルから法線を求める(外積)
	D3DXVec3Cross(&nor, &VecA, &VecD);

	// 法線を正規化
	D3DXVec3Normalize(&nor, &nor);

	// 内積
	dot = D3DXVec3Dot(&VecPos, &nor);

	if (nor.y != 0.0f)
	{
		// 高さを変える
		fHeight = -dot;
	}

	return fHeight;
}