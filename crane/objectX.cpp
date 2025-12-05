//====================================================
//
// Xファイル[objectX.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"objectX.h"
#include"manager.h"

//====================================================
// コンストラクタ
//====================================================
CObjectX::CObjectX(int nPriority):CObject(nPriority)
{
	// 変数を初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bExistence = false;

	for (int nCnt = 0; nCnt < MAX_MAT; nCnt++)
	{
		m_anTexIndx[nCnt] = { -1 };
	}
}

//====================================================
// デストラクタ
//====================================================
CObjectX::~CObjectX()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObjectX* pObjectX = NULL;

	// メモリの確保
	pObjectX = new CObjectX;

	// 各メンバ変数の設定
	pObjectX->m_pos = pos;		// 位置
	pObjectX->m_rot = rot;		// 向き

	// 初期化処理
	pObjectX->Init();


	return pObjectX;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CObjectX::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL* pMat;			// マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bExistence == false)
	{
		//Xファイルの読込
		D3DXLoadMeshFromX("data\\MODEL\\box000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
	{

		if (pMat[nCnt].pTextureFilename != NULL)
		{
			m_anTexIndx[nCnt] = CManager::GetTexture()->Register(pMat[nCnt].pTextureFilename);
		}
	}

	// 頂点数の取得
	int nNumVtx = m_pMesh->GetNumVertices();
	DWORD sizeFVF;			// 頂点フォーマットのサイズ
	BYTE* pVtxBUff;			// 頂点バッファへのポインタ

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

	for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

		//頂点座標を比較してモデルの最大最小を取得

		if (vtx.x > m_vtxMax.x)//x最大値
		{
			m_vtxMax.x = vtx.x;
		}
		else if (vtx.x < m_vtxMin.x)//x最小値
		{
			m_vtxMin.x = vtx.x;
		}

		if (vtx.y > m_vtxMax.y)//y最大値
		{
			m_vtxMax.y = vtx.y;
		}
		else if (vtx.y < m_vtxMin.y)//y最小値
		{
			m_vtxMin.y = vtx.y;
		}

		if (vtx.z > m_vtxMax.z)//z最大値
		{
			m_vtxMax.z = vtx.z;
		}
		else if (vtx.z < m_vtxMin.z)//z最小値
		{
			m_vtxMin.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBUff += sizeFVF;
	}

	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();

	//サイズの初期化
	m_size = m_vtxMax - m_vtxMin;

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CObjectX::Uninit(void)
{
	// メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CObjectX::Update(void)
{

}

//====================================================
// 描画処理
//====================================================
void CObjectX::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(m_anTexIndx[nCnt]));

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCnt);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================
// モデルの割当
//====================================================
void CObjectX::BindModel(const char* pFileName)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXLoadMeshFromX(pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh)))
	{
		m_bExistence = false;
	}
	else
	{
		m_bExistence = true;
	}
}
