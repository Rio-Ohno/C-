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
CObjectX::CObjectX()
{
	// 変数を初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
// 初期化処理
//====================================================
HRESULT CObjectX::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL* pMat;			// マテリアルデータへのポインタ

	// 位置の代入
	m_pos = pos;

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
// 生成処理
//====================================================
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObjectX* pObjectX = NULL;

	// メモリの確保
	pObjectX = new CObjectX;

	// 初期化処理
	pObjectX->Init(pos, 0.0f, 0.0f);

	pObjectX->m_rot = rot;

	return pObjectX;
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
