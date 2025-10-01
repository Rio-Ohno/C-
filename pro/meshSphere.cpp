//====================================================
//
//メッシュスフィア[meshSphere.cpp]
//Author:Rio Ohno
//
//====================================================

// インクルード
#include "meshSphere.h"
#include "manager.h"
#include <cassert>

//====================================================
// コンストラクタ
//====================================================
CMeshSphere::CMeshSphere()
{
	// 各変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	//D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックス
	m_pVtxBuff = { NULL };					// 頂点バッファへのポインタ
	m_pIndxBuff = { NULL };					// インデックスバッファへのポインタ
	m_nTexindx = -1;						// テクスチャインデックス
	m_nDiviX = 0;							// 分割数
	m_nDiviY = 0;							// 分割数
	m_nMaxVtx = 0;							// 頂点数
	m_nPolyNum = 0;							// ポリゴン数
	m_fRadius = 0.0f;						// 半径
	m_bFront = true;
	m_bHalf = true;							// 半球かどうか(半球の状態へ)
}

//====================================================
// デストラクタ
//====================================================
CMeshSphere::~CMeshSphere()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CMeshSphere* CMeshSphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDiviX, int nDiviY, float fRadius, bool bHalf, bool bFront)
{
	CMeshSphere* pSphere = NULL;

	// メモリの確保
	pSphere = new CMeshSphere;

	// 各変数の設定
	pSphere->m_nDiviX = nDiviX;
	pSphere->m_nDiviY = nDiviY;
	pSphere->m_fRadius = fRadius;
	pSphere->m_nMaxVtx = (nDiviX + 1) * nDiviY + 1;// 頂点数
	pSphere->m_bHalf = bHalf;
	pSphere->m_bFront = bFront;

	// 初期化処理
	pSphere->Init(pos, fRadius, fRadius);

	return pSphere;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CMeshSphere::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D* pVtx = NULL;
	int indx = 0;//頂点インデックス
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ベクトルの保存用

	//頂点バッファの生成
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
			int i = nCntX;

			if (m_bFront == false)
			{
				i = m_nDiviX - nCntX;
			}

			//角度格納
			float fAngle = ((D3DX_PI * 2 / m_nDiviX) * i);						//y軸
			float fAngle2 = (D3DX_PI / m_nDiviY) * nCntY;		//z軸

			//半球なら
			if (m_bHalf == true)
			{
				fAngle2 = (((D3DX_PI * 0.5f) / m_nDiviY) * nCntY);
			}

			//頂点の位置の設定
			pVtx[indx].pos.x = (float)m_fRadius * sinf(fAngle2) * sinf(fAngle);
			pVtx[indx].pos.y = (float)m_fRadius * cosf(fAngle2);
			pVtx[indx].pos.z = (float)m_fRadius * sinf(fAngle2) * cosf(fAngle);

			//外側へのベクトル
			vec = pVtx[indx].pos - m_pos;

			//ベクトルの正規化,各頂点の法線の設定
			D3DXVec3Normalize(&pVtx[indx].nor, &vec);

			//頂点カラーの設定
			pVtx[indx].col = m_col;

			//テクスチャ座標の設定
			if (indx == 0)
			{
				pVtx[indx].tex = D3DXVECTOR2(0.5f, 0.0f);
			}
			else if (indx >= 1 && indx <= (m_nDiviX + 1))
			{
				pVtx[indx].tex = D3DXVECTOR2(1.0f - (float)nCntX / m_nDiviX, 1.0f / m_nDiviY);
			}
			else
			{
				pVtx[indx].tex = D3DXVECTOR2(1.0f - (float)nCntX / m_nDiviX, (float)nCntY / m_nDiviY);
			}

			//頂点インデックスを進める
			indx++;
			assert(indx >= 0 && indx <= m_nMaxVtx);

			if ((indx - 1) == 0)
			{// 1頂点目なら
				break;
			}
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	//インデックスへのポインタ
	WORD* pIdx = NULL;
	int indexNum = (2 * ((m_nDiviY /*- 1*/) * (2 + m_nDiviX) - 1));													// インデックス
	m_nPolyNum = (2 * m_nDiviX * (m_nDiviY-1) + (m_nDiviY-2) * 4);					// ポリゴン数

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * indexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndxBuff,
		NULL);

	//インデックスバッファをロック
	m_pIndxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nCntX = 0;
	int Indx = 0;

	for (int nCntY = 0; nCntY < m_nDiviY; nCntY++)
	{
		for (nCntX = m_nDiviX; nCntX >= 0; nCntX--)
		{
			//インデックスの設定
			pIdx[0] = (m_nDiviX + 1) * (nCntY + 1) + nCntX;
			pIdx[1] = nCntX + (nCntY * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}

		//衰退ポリゴン分
		if (nCntY < m_nDiviY - 2)
		{
			//インデックスの設定
			pIdx[0] = (nCntX + 1) + (nCntY * (m_nDiviX + 1));
			pIdx[1] = (m_nDiviX + 1) * (nCntY + 2) + m_nDiviX;

			pIdx += 2;
			Indx += 2;
		}

		assert(Indx <= indexNum);
		assert(nCntY >= 0 && nCntY <= m_nDiviY);
	}

	//インデックスバッファをアンロック
	m_pIndxBuff->Unlock();

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CMeshSphere::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの破棄
	if (m_pIndxBuff != NULL)
	{
		m_pIndxBuff->Release();
		m_pIndxBuff = NULL;
	}

	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CMeshSphere::Update(void)
{
	// なし

		// 角度の近道
	if ((m_rot.y + 0.0005f) >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if ((m_rot.y + 0.0005f) <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_rot.y += 0.0005f;
}

//====================================================
// 描画処理
//====================================================
void CMeshSphere::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャクラスへのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを切る
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);   // 横方向：繰り返し
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);  // 縦方向：端止め

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexindx));

	// ポリゴンを描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_nDiviX);

	if (m_nDiviY >= 2)
	{
		// インデックスバッファをデータストリームに設定
		pDevice->SetIndices(m_pIndxBuff);

		// メッシュ壁を描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 1, 0, m_nMaxVtx, 0, m_nPolyNum);
	}

	//ライトをつける
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//====================================================
// 色の設定
//====================================================
void CMeshSphere::SetColor(D3DXCOLOR col)
{
	VERTEX_3D* pVtx = NULL;
	int indx = 0;//頂点インデックス

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntY = 0; nCntY <= m_nDiviY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			// 色の設定
			pVtx[indx].col = col;
			m_col = col;

			//頂点インデックスを進める
			indx++;
			assert(indx >= 0 && indx <= m_nMaxVtx);

			if ((indx - 1) == 0)
			{// 1頂点目なら
				break;
			}
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}