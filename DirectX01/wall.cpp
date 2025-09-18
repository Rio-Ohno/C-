//====================================================
//
// 壁[wall.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"wall.h"
#include"manager.h"
#include"tutorial.h"
#include"game.h"

//====================================================
// コンストラクタ
//====================================================
CWall::CWall()
{
	// 各変数の初期化
	m_pVtxBuff = { NULL };
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTexindx = -1;
	m_fLength = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_bCollision = false;
	m_bDisp = true;
}

//====================================================
// デストラクタ
//====================================================
CWall::~CWall()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight,bool bCollision,bool bDisp)
{
	CWall* pWall = NULL;

	// メモリの確保
	pWall = new CWall;

	pWall->m_pos = pos;
	pWall->m_rot = rot;
	pWall->m_fWidth = fWidth;
	pWall->m_fHeight = fHeight;
	pWall->m_bCollision = bCollision;
	pWall->m_bDisp = bDisp;

	// 初期化処理
	pWall->Init(pos, fWidth, fHeight);

	return pWall;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CWall::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//デバイスへのポインタと取得
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
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth * 0.5f, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth * 0.5f, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth * 0.5f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, 0.0f);

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
void CWall::Uninit(void)
{
	// 頂点バッファの破棄
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
void CWall::Update(void)
{
	if (m_bCollision == true)// 当たり判定をとるなら
	{
		// プレイヤーポインタ
		CPlayer* pPlayer = NULL;

		if (CManager::GetMode() == CScene::MODE_TUTORIAL)
		{
			// チュートリアルのプレイヤー取得
			pPlayer = CTutorial::GetPlayer();
		}
		else if (CManager::GetMode() == CScene::MODE_GAME)
		{
			// ゲームのプレイヤー取得
			pPlayer = CGame::GetPlayer();
		}

		if (pPlayer != NULL)
		{
			D3DXVECTOR3 pos = pPlayer->GetPos();
			if (isColision(pos) == true)// もし当たっていたら
			{

				// 前の位置の取得
				D3DXVECTOR3 oldpos = pPlayer->GetOldPos();

				// 前の位置に戻す(ｙ軸以外)
				pPlayer->SetPos(D3DXVECTOR3(oldpos.x, pos.y, oldpos.z));

				// 移動量のリセット
				pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
	}
}

//====================================================
// 描画処理
//====================================================
void CWall::Draw(void)
{
		//デバイスへのポインタと取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャポインタの取得
		CTexture* pTexture = CManager::GetTexture();

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

		if (m_bDisp == true)// 表示するなら
		{
			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

			//テクスチャ座標の設定
			pDevice->SetTexture(0, pTexture->GetAddress(m_nTexindx));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
}

//====================================================
// 当たり判定処理
//====================================================
bool CWall::isColision(D3DXVECTOR3 pos)
{
	if (m_pos.x + m_fWidth * 0.5f >= pos.x && m_pos.x - m_fWidth * 0.5f <= pos.x && m_pos.y + m_fHeight * 0.5f >= pos.y && m_pos.y <= pos.y)
	{
		D3DXVECTOR3 VecWall, VecTarget, cross;
		D3DXVECTOR3 pos1, pos2;

		pos1.x = m_pos.x - cosf(m_rot.y) * (m_fWidth * 0.5f);
		pos1.y = 0.0f;
		pos1.z = m_pos.z + sinf(m_rot.y) * (m_fWidth * 0.5f);

		pos2.x = m_pos.x + cosf(m_rot.y) * (m_fWidth * 0.5f);
		pos2.y = 0.0f;
		pos2.z = m_pos.z - sinf(m_rot.y) * (m_fWidth * 0.5f);

		VecWall = pos2 - pos1;
		VecTarget = pos - pos1;

		// 外積
		D3DXVec3Cross(&cross, &VecWall, &VecTarget);

		if (cross.y < 0.0f)
		{
			return true;
		}
	}

	return false;
}

//====================================================
// 反射処理
//====================================================
D3DXVECTOR3 CWall::Reflect(D3DXVECTOR3 pos, D3DXVECTOR3 posOld)
{
	D3DXVECTOR3 VecWall, VecTarget, cross;
	D3DXVECTOR3 pos1, pos2;
	D3DXVECTOR3 nor,reflect;
	float Dot;

	pos1.x = m_pos.x - cosf(m_rot.y) * (m_fWidth * 0.5f);
	pos1.y = 0.0f;
	pos1.z = m_pos.z + sinf(m_rot.y) * (m_fWidth * 0.5f);

	pos2.x = m_pos.x + cosf(m_rot.y) * (m_fWidth * 0.5f);
	pos2.y = 0.0f;
	pos2.z = m_pos.z - sinf(m_rot.y) * (m_fWidth * 0.5f);

	VecWall = pos2 - pos1;
	VecTarget = pos - posOld;

	// 外積
	D3DXVec3Cross(&nor, &VecWall, &VecTarget);

	// 逆ベクトルにする
	VecTarget *= -1.0f;

	// 内積
	Dot = D3DXVec3Dot(&VecTarget, &nor);
	reflect = VecTarget + 2.0f * Dot * nor;

	return reflect;
}

//====================================================
// 色の設定
//====================================================
void CWall::SetColor(D3DCOLOR col)
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
// テクスチャ座標の設定
//====================================================
void CWall::SetTexUV(float minU, float maxU, float minV, float maxV)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].tex = D3DXVECTOR2(minU,minV);
	pVtx[1].tex = D3DXVECTOR2(maxU,minV);
	pVtx[2].tex = D3DXVECTOR2(minU,maxV);
	pVtx[3].tex = D3DXVECTOR2(maxU,maxV);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
