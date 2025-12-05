//====================================================
// 
// 3Dオブジェクト [object3D.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include"object3D.h"
#include"manager.h"

//====================================================
// コンストラクタ
//====================================================
CObject3D::CObject3D()
{
	// 各変数の初期化
	m_pVtxBuff = { NULL };
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTexindx = -1;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fLength = 0.0f;
}

//====================================================
// デストラクタ
//====================================================
CObject3D::~CObject3D()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CObject3D::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth * 0.5f, 0.0f, m_fLength * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, m_fLength * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth * 0.5f, 0.0f, -m_fLength * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, -m_fLength * 0.5f);

	//各頂点の法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CObject3D::Uninit(void)
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

//====================================================
// 更新処理
//====================================================
void CObject3D::Update(void)
{ 
	// なし
}

//====================================================
// 描画処理
//====================================================
void CObject3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャクラスへのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	LPDIRECT3DTEXTURE9 pTexMT;// マルチターゲット用テクスチャ

	// マルチターゲット用テクスチャの取得
	pTexMT = CManager::GetRenderer()->GetTextureMT();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

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

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexindx));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//====================================================
// 生成処理
//====================================================
CObject3D* CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fLength)
{
	CObject3D* pObject3D = NULL;

	// メモリの確保
	pObject3D = new CObject3D;

	// 各メンバ変数の設定
	pObject3D->m_pos = pos;
	pObject3D->m_rot = rot;
	pObject3D->m_fWidth = fWidth;
	pObject3D->m_fLength = fLength;

	// 初期化処理
	pObject3D->Init();

	return pObject3D;
}

//====================================================
// 当たり判定
//====================================================
void CObject3D::isColision(void)
{
	// 頂点位置
	D3DXVECTOR3 pos[4] = {};
	D3DXVECTOR3 Vec[3], Vec1, Vec2;
	D3DXVECTOR3 nor[3];

	//// プレイヤーポインタ
	//CPlayer* pPlayer = NULL;

	//// プレイヤーの情報取得
	//if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	//{
	//	pPlayer = CTutorial::GetPlayer();
	//}
	//else if (CManager::GetMode() == CScene::MODE_GAME)
	//{
	//	pPlayer = CGame::GetPlayer();
	//}

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pos[nCnt] = pVtx[nCnt].pos;
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	for (int nCnt = 0; nCnt < 2; nCnt++)//012321
	{
		// ベクトル計算
		Vec[0] = pos[nCnt + 1] - pos[nCnt * 3];
		Vec[1] = pos[2 - nCnt] - pos[nCnt + 1];
		Vec[2] = pos[nCnt * 3] - pos[2 - nCnt];

		D3DXVECTOR3 vecPlayer;

		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{
			int VecIndx = 0;

			//// プレイヤーとのベクトル
			//vecPlayer = pPlayer->GetPos() - pos[nCntVtx + nCnt];

			if (nCnt == 1)
			{
				VecIndx = 2 - nCntVtx;
			}
			else
			{
				VecIndx = nCntVtx;
			}

			D3DXVec3Cross(&nor[nCntVtx], &vecPlayer, &Vec[VecIndx]);

			// 法線を正規化
			D3DXVec3Normalize(&nor[nCntVtx], &nor[nCntVtx]);
		}

		if (0.0f >= nor[0].y && 0.0f >= nor[1].y && 0.0f >= nor[2].y)
		{
			D3DXVECTOR3 nor;
			float dot = 0.0f;

			Vec1 = pos[nCnt + 1] - pos[nCnt * 3];
			Vec2 = pos[2 - nCnt] - pos[nCnt * 3];

			// 2つのベクトルから法線を求める(外積)
			D3DXVec3Cross(&nor, &Vec1, &Vec2);

			// 法線を正規化
			D3DXVec3Normalize(&nor, &nor);

			// 内積
			dot = D3DXVec3Dot(&vecPlayer, &nor);

			if (nor.y != 0.0f)
			{
				// 高さを変える
				m_fHeight = -dot;
				return;
			}
		}
	}
}

//====================================================
// 高さの取得
//====================================================
float CObject3D::GetHeight(void)
{
	// 衝突判定
	isColision();

	return m_fHeight;
}

//====================================================
// 色の設定
//====================================================
void CObject3D::SetColor(D3DCOLOR col)
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

//====================================================
// サイズの設定処理
//====================================================
void CObject3D::SetSize(D3DXVECTOR2 size)
{
	m_fWidth = size.x;
	m_fLength = size.y;
}