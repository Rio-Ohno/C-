//====================================================
//
// フィールドマネージャー [fieldManager.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "fieldManager.h"
#include <vector>

// 静的メンバ変数
CMeshField* CFiledManager::m_pMeshField = nullptr;

//====================================================
// コンストラクタ
//====================================================
CFiledManager::CFiledManager()
{
	// メンバ変数の初期化
	m_pMeshField = nullptr;
	m_nCntFream = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 発生位置
	m_fHeight = 0.0f;						// 高さ
	m_fWidth = 0.0f;						// 幅
	m_fRadius = 0.0f;						// 半径
	m_fSpeed = 0.0f;						// 速さ
	m_nLifeFream = 0;						// 寿命（フレーム）
	m_fAttenuation = 0.0f;					// 減衰
	m_bFinish = true;						// 終わっているかどうか(終わってる状態へ)
}

//====================================================
// デストラクタ
//====================================================
CFiledManager::~CFiledManager()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CFiledManager::Init(void)
{
	if (m_pMeshField == nullptr)
	{
		m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, 50, 50, 6, 6);
	};

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CFiledManager::Uninit(void)
{
	if (m_pMeshField != nullptr)
	{
		m_pMeshField->Uninit();
		m_pMeshField = nullptr;
	}

	// 自身の破棄
	delete this;
}

//====================================================
// 更新処理
//====================================================
void CFiledManager::Update(void)
{
	if (m_nCntFream >= m_nLifeFream)
	{
		// フレームカウンターのリセット
		m_nCntFream = 0;

		// 各メンバ変数のリセット
		Reset();
	}
	else
	{
		// 波の更新処理
		UpdateWave();
	}
}

//====================================================
// 描画処理
//====================================================
void CFiledManager::Draw(void)
{
	// なし
}

//====================================================
// 波の設定＆発生処理
//====================================================
void CFiledManager::SetWave(D3DXVECTOR3 pos, float fWidth, float fHeight, float fRadius, float fSpeed, int nLifeSeccond, float fAttenuation)
{
	// 各要素の設定
	m_pos = pos;						// 位置
	m_fWidth = fWidth;					// 幅
	m_fHeight = fHeight;				// 高さ
	m_fRadius = fRadius;				// 半径
	m_fSpeed = fSpeed;					// はやさ
	m_nLifeFream = nLifeSeccond * 60;	// 寿命
	m_fAttenuation = fAttenuation;		// 減衰
	m_bFinish = false;					// 終わっているかどうか(終わってない状態へ)
}

//====================================================
// 波の更新処理
//====================================================
void CFiledManager::UpdateWave(void)
{
	if (m_bFinish)return;// 終了している状態ならこの先の処理をしない

	// フレームカウンタ
	++m_nCntFream;

	m_fRadius += m_fSpeed;

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pMeshField->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;// 頂点カウンター

	//// 頂点数の取得
	//int NumVtx = m_pMeshField->GetMaxVtx();

	//// 法線の合計保存
	//std::vector<D3DXVECTOR3> vertexNormals(NumVtx, D3DXVECTOR3(0, 0, 0));

	//頂点情報の設定
	for (int nCntZ = 0; nCntZ <= m_pMeshField->GetDivi().y; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_pMeshField->GetDivi().x; nCntX++)
		{
			float x = pVtx[nCntVtx].pos.x;
			float z = pVtx[nCntVtx].pos.z;

			// 発生源からの位置
			float fDistX = x - m_pos.x;
			float fDistZ = z - m_pos.z;
			float fDist = sqrtf(fDistX * fDistX + fDistZ * fDistZ);

			if (fDist <= m_fRadius)
			{
				float fFreq = 2.0f * D3DX_PI / m_fWidth;

				// 減衰
				float fDistAttenuation = 1.0f / (1.0f + fDist * m_fAttenuation);						// 距離によるもの
				float fLifeAttenuation = max(0.0f, 1.0f - (float)m_nCntFream / (float)m_nLifeFream);	// 寿命によるもの
				float fRangeAttenuation = max(0.0f, 1.0f - fDist / m_fRadius);							// 範囲によるもの

				//頂点座標の設定
				pVtx[nCntVtx].pos.y = sinf(fDist * fFreq - m_nCntFream * m_fSpeed) * m_fHeight * fDistAttenuation * fLifeAttenuation * fRangeAttenuation;
			}
			else
			{
				//頂点座標の設定
				pVtx[nCntVtx].pos.y = 0.0f;
			}

			// 法線の設定(影)
			if (nCntX > 0 && nCntX < (int)m_pMeshField->GetDivi().x&&
				nCntZ < (int)m_pMeshField->GetDivi().y)
			{
				D3DXVECTOR3 Vec[2] = {};
				D3DXVECTOR3 nor;

				if ((nCntZ % 2) == 0)
				{
					Vec[0] = pVtx[nCntVtx + (int)m_pMeshField->GetDivi().x].pos - pVtx[nCntVtx].pos;
					Vec[1] = pVtx[nCntVtx - 1].pos - pVtx[nCntVtx].pos;
				}
				else if ((nCntZ % 2) == 1)
				{
					Vec[0] = pVtx[nCntVtx - (int)m_pMeshField->GetDivi().x].pos - pVtx[nCntVtx].pos;
					Vec[1] = pVtx[nCntVtx + 1].pos - pVtx[nCntVtx].pos;
				}

				// 2つのベクトルから法線を求める(外積)
				D3DXVec3Cross(&nor, &Vec[0], &Vec[1]);

				// 法線を正規化
				D3DXVec3Normalize(&pVtx[nCntVtx].nor, &nor);
			}

			// 頂点カウンタを勧める
			nCntVtx++;
		}
	}

	//// ポリゴン数の取得
	//int NumPoly = m_pMeshField->GetNumPoly();

	////インデックスへのポインタ
	//WORD* pIdx = NULL;

	////インデックスバッファをロック
	//m_pMeshField->GetIdxBuff()->Lock(0, 0, (void**)&pIdx, 0);

	//// 各三角形の法線を計算して頂点に加算
	//for (int nCnt = 0; nCnt < NumPoly; ++nCnt)
	//{
	//	int idx0 = pIdx[nCnt * 3];
	//	int idx1 = pIdx[nCnt * 3 + 1];
	//	int idx2 = pIdx[nCnt * 3 + 2];

	//	D3DXVECTOR3 vtx0 = pVtx[idx0].pos;
	//	D3DXVECTOR3 vtx1 = pVtx[idx1].pos;
	//	D3DXVECTOR3 vtx2 = pVtx[idx2].pos;

	//	D3DXVECTOR3 edge1 = vtx1 - vtx0;
	//	D3DXVECTOR3 edge2 = vtx2 - vtx0;
	//	D3DXVECTOR3 faceNormal;

	//	// 外積
	//	D3DXVec3Cross(&faceNormal, &edge1, &edge2);

	//	// 正規化
	//	D3DXVec3Normalize(&faceNormal, &faceNormal);

	//	// 法線合算
	//	vertexNormals[idx0] += faceNormal;
	//	vertexNormals[idx1] += faceNormal;
	//	vertexNormals[idx2] += faceNormal;
	//}

	////インデックスバッファのアンロック
	//m_pMeshField->GetIdxBuff()->Unlock();

	//// 頂点ごとに正規化
	//for (int nCnt = 0; nCnt < NumVtx; ++nCnt)
	//{
	//	// 正規化
	//	D3DXVec3Normalize(&pVtx[nCnt].nor, &vertexNormals[nCnt]);
	//}

	// 頂点バッファをアンロック　
	m_pMeshField->GetVtxBuff()->Unlock();
}

//====================================================
// メンバ変数のリセット
//====================================================
void CFiledManager::Reset(void)
{
	m_nCntFream = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 発生位置
	m_fHeight = 0.0f;						// 高さ
	m_fWidth = 0.0f;						// 幅
	m_fRadius = 0.0f;						// 半径
	m_fSpeed = 0.0f;						// 速さ
	m_nLifeFream = 0;						// 寿命（フレーム）
	m_fAttenuation = 0.0f;					// 減衰
	m_bFinish = true;						// 終わっているかどうか(終わってる状態へ)
}