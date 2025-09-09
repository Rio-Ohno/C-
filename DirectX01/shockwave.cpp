//====================================================
// 
// 衝撃波[shockwave.cpp]
// Author:Rio Ohno
// 
//==================================================== 

// インクルード
#include"shockwave.h"
#include"manager.h"
#include"game.h"
#include <cassert>

//==================================================== 
// コンストラクタ
//==================================================== 
CShockwave::CShockwave()
{
	// 各変数初期化
	m_pVtxBuff = { NULL };					// 頂点バッファへのポインタ
	m_pIdxBuff = { NULL };					// インデックスバッファへのポインタ
	m_mtxWorld = {};						// ワールドマトリックス

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き

	m_nTexindx = -1;						// テクスチャインデックス
	m_nDiviX = 0;							// 横軸分割数
	m_nDiviY = 0;							// 縦軸分割数
	m_nMaxVtx = 0;							// 最大頂点数
	m_nPolyNum = 0;							// ポリゴン数
	m_nLife = 0;							// 寿命
	m_nVanishFream = 0;						// 消えるフレーム数
	m_nVanishCnt = 0;						// 消えるフレームカウンター
	m_fHeight = 0.0f;						// 高さ
	m_fWidth = 0.0f;						// 幅
	m_fRadius = 0.0f;						// 半径
	m_fSpeed = 0.0f;						// 広がるスピード
	m_bCulling = true;						// カリングするかどうか
	m_bCollision = false;					// 当たり判定をとるかどうか
	m_bVanish = false;						// 消える演出をいれるかどうか
}

//==================================================== 
// デストラクタ
//==================================================== 
CShockwave::~CShockwave()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CShockwave* CShockwave::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY,int nLife, float fWidth, float fHeight, float fRadius, float fSpeed, bool bCulling, bool bCollision)
{
	CShockwave* pwave = NULL;

	// メモリの確保
	pwave = new CShockwave;

	//各変数の設定
	pwave->m_pos = pos;												// 位置
	pwave->m_rot = rot;												// 向き
	pwave->m_nDiviX = DiviX;										// 分割数(x軸)
	pwave->m_nDiviY = DiviY;										// 分割数(y軸)
	pwave->m_nLife = nLife;											// 寿命
	pwave->m_fHeight = fHeight;										// 高さ
	pwave->m_fWidth = fWidth;										// 幅
	pwave->m_fRadius = fRadius;										// 半径
	pwave->m_fSpeed = fSpeed;										// 広がるスピード
	pwave->m_nMaxVtx = (DiviX + 1) * (DiviY + 1);					// 最大頂点数
	pwave->m_nPolyNum = (2 * DiviX * DiviY + (DiviY - 1) * 4);		// ポリゴン数
	pwave->m_bCulling = bCulling;
	pwave->m_bCollision = bCollision;

	// 初期化処理
	pwave->Init(pos, fWidth, fHeight);

	return pwave;
}

//==================================================== 
// 初期化処理
//==================================================== 
HRESULT CShockwave::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
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
			float fAngle = ((D3DX_PI * 2.0f / m_nDiviX) * (m_nDiviX - nCntX));

			//高さの格納
			float fHeight = (m_fHeight / m_nDiviY) * (m_nDiviY - nCntY);

			// 幅の算出
			float fWidth = (m_fWidth / m_nDiviY) * nCntY;

			//頂点の設定
			pVtx[indx].pos = D3DXVECTOR3((m_fRadius+fWidth) * sinf(fAngle), fHeight, (m_fRadius + fWidth) * cosf(fAngle));

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
	int Indx = 0;	// インデックスカウンタ

	for (int nCntY = 0; nCntY < m_nDiviY; nCntY++)
	{
		for (nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//インデックスの設定
			pIdx[0] = (m_nDiviX + 1) * (nCntY + 1) + nCntX;
			pIdx[1] = nCntX + (nCntY * (m_nDiviX + 1));

			// ポインタとインデックスカウンタを進める
			pIdx += 2;
			Indx += 2;
		}

		//衰退ポリゴン分
		if (nCntY < m_nDiviY - 1)
		{
			//インデックスの設定
			pIdx[0] = (nCntX - 1) + (nCntY * (m_nDiviX + 1));
			pIdx[1] = nCntX + ((nCntY + 1) * (m_nDiviX + 1));

			// ポインタとインデックスカウンタを進める
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
void CShockwave::Uninit(void)
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
void CShockwave::Update(void)
{
	// 寿命を減らす
	--m_nLife;

	// 寿命が残ってるなら
	if (m_nLife > 0)
	{
		// 当たり判定をとるなら
		if (m_bCollision)
		{
			// プレイヤーの情報取得
			CPlayer* pPlayer = CGame::GetPlayer();

			// プレイヤーの情報があるなら
			if (pPlayer != NULL)
			{
				// プレイヤーとの当たり判定
				if (isCollision(pPlayer->GetPos(), 6.0f,0.0f,pPlayer->GetSize().y) == true)
				{
					// プレイヤー被弾処理
					pPlayer->Hit();
				}
			}
		}

		// 広げる処理
		Spread();
	}
	// 寿命が尽きたなら
	else
	{
		// 消える演出をしないなら
		if (m_bVanish == false)
		{
			// 終了処理
			Uninit();
		}
		// 消える演出をするなら
		else
		{
			// 広げる処理
			Spread();

			// 消える演出
			Vanish();
		}
	}
}

//==================================================== 
// 描画処理
//==================================================== 
void CShockwave::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャクラスへのポインタの取得
	CTexture* pTexture = CManager::GetTexture();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	//ライトを切る
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// カリングをしないなら
	if (m_bCulling == false)
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
// 色の設定
//==================================================== 
void CShockwave::SetColor(D3DXCOLOR col, bool bTransparent)
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
			if (bTransparent == true)
			{
				float a = col.a;

				float alpha = ((a+0.1f) / m_nDiviY) * (m_nDiviY - nCntY);

				col.a = alpha;
			}

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

//==================================================== 
// 当たり判定
//==================================================== 
bool CShockwave::isCollision(D3DXVECTOR3 pos, float fRadius, float fUnder, float fTop)
{
	// 高さが範囲なら
	if (pos.y - fUnder <= m_pos.y + m_fHeight && pos.y + fTop >= m_pos.y)
	{
		float fDistance = (pos.x - m_pos.x) * (pos.x - m_pos.x) +
			(pos.z - m_pos.z) * (pos.z - m_pos.z);	// 距離(2D上)

		// 平方根
		fDistance = sqrtf(fDistance);

		if (fDistance <= (m_fRadius + m_fWidth + fRadius) && fDistance >= m_fRadius)
		{
			return true;
		}
	}
	return false;
}

//==================================================== 
// 消える演出の設定処理
//==================================================== 
void CShockwave::SetVanish(int nFream)
{
	if (nFream > 0)
	{
		// 消える演出のフラグを立てる
		m_bVanish = true;

		// 演出のフレーム設定(保存)
		m_nVanishFream = nFream;

		// フレームカウンタの初期化
		m_nVanishCnt = nFream;
	}
}

//==================================================== 
// 広げる処理
//==================================================== 
void CShockwave::Spread(void)
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
			//角度算出
			float fAngle = ((D3DX_PI * 2.0f / m_nDiviX) * (m_nDiviX - nCntX));

			// 移動量算出
			D3DXVECTOR3 move = D3DXVECTOR3(m_fSpeed * sinf(fAngle), 0.0f, m_fSpeed * cosf(fAngle));

			// 頂点の位置設定
			pVtx[indx].pos += move;

			// カウントアップ
			indx++;
		}
	}
	assert(indx <= m_nMaxVtx);

	// 半径に加算
	m_fRadius += m_fSpeed;

	//頂点バッファをアンロック　
	m_pVtxBuff->Unlock();
}

//====================================================
// 消える演出処理 
//==================================================== 
void CShockwave::Vanish(void)
{
	// カウンターを減らす
	--m_nVanishCnt;

	// カウンターが減り切ったら
	if (m_nVanishCnt < 0)
	{
		// 終了処理
		Uninit();

		return;
	}

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
			D3DXCOLOR col = pVtx[indx].col;

			float alpha = (((col.a + 0.1f) / m_nDiviY) / m_nVanishFream) * (m_nDiviY - nCntY) * m_nVanishCnt;

			col.a = alpha;

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