//====================================================
//
// モデル(階層構造前提)[model.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"model.h"
#include"manager.h"
#include <stdio.h>
#include <string.h>

//====================================================
// コンストラクタ
//====================================================
CModel::CModel()
{
	// 値を初期化
	m_pMesh = { NULL };
	m_pBuffMat = { NULL };
	m_dwNumMat = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = { NULL };
}

//====================================================
// デストラクタ
//====================================================
CModel::~CModel()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//D3DXMATERIAL* pMat;			// マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//Xファイルの読込
	if (FAILED(D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh)))
	{
		return -1;
	}

	// 各変数の設定
	m_pos = pos;		// 位置
	m_rot = rot;		// 向き

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CModel::Uninit(void)
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
}

//====================================================
// 描画処理
//====================================================
void CModel::Draw(void)
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

	D3DXMATRIX mtxParent;// 親モデルマトリックス

	if (m_pParent != NULL)
	{// 親があるなら
		// 親のマトリックス取得
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// 親がない
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// 親マトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
		pDevice->SetTexture(0, NULL/*apTextureModel[nCnt]*/);

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCnt);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================
// 生成処理
//====================================================
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	CModel* pModel = NULL;

	// メモリの確保
	pModel = new CModel;

	// 初期化処理
	if (FAILED(pModel->Init(pos, rot, pFilename)))
	{// 失敗したら

		// メモリ尾破棄
		delete pModel;
		pModel = NULL;

		return NULL;
	}

	return pModel;
}

//====================================================
// 親モデルの設定処理
//====================================================
void CModel::SetParent(CModel* pModel)
{
	// 親モデルの設定
	m_pParent = pModel;
}

//====================================================
// 位置の設定処理
//====================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	// 位置の設定
	m_pos = pos;
}


//====================================================
// 向きの設定処理
//====================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	// 位置の設定
	m_rot = rot;
}

//====================================================
// ワールドマトリックスの取得処理
//====================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}