//====================================================
//
// アイテム[item.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"note.h"
#include"noteManager.h"
#include"manager.h"
#include"game.h"
#include"tutorial.h"
#include"particle3D.h"

//====================================================
// コンストラクタ
//====================================================
CNote::CNote(int nPriority):CObjectX(nPriority)
{
	// メンバ変数の初期化
	m_nCounter = 0;

	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = {};

	m_pShadow = { NULL };
}

//====================================================
// デストラクタ
//====================================================
CNote::~CNote()
{
	// 音符の総数を減らす
	CNoteManager::DefNum();
}

//====================================================
// 生成処理
//====================================================
CNote* CNote::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CNote* pItem = NULL;

	// メモリの確保
	pItem = new CNote;

	// 音符の総数を増やす
	CNoteManager::AddNum();

	// モデルの割当
	pItem->BindModel("data/MODEL/note001.x");

	// 初期化処理
	pItem->Init(pos, 0.0f, 0.0f);

	// 向きの設定
	pItem->CObjectX::SetRot(rot);

	return pItem;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CNote::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// オブジェクトの初期化
	if (FAILED(CObjectX::Init(pos, 0.0f, 0.0f)))
	{
		return -1;
	}

	int nNumVtx = CObjectX::GetMesh()->GetNumVertices();//最大頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBUff;//頂点バッファへのポインタ

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(CObjectX::GetMesh()->GetFVF());

	//頂点バッファのロック
	CObjectX::GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

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
	CObjectX::GetMesh()->UnlockVertexBuffer();

	//サイズの初期化
	m_size = m_vtxMax - m_vtxMin;

	// 影の生成
	m_pShadow = CShadow::Create(D3DXVECTOR3(pos.x, pos.y + 0.3f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CNote::Uninit(void)
{
	if (m_pShadow != NULL)
	{
		// 終了処理
		m_pShadow->Uninit();
	}

	// オブジェクトの終了処理
	CObjectX::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CNote::Update(void)
{
	// プレイヤーポインタ
	CPlayer* pPlayer = NULL;

	// スコアポインタ
	CScore* pScore = NULL;

	// プレイヤーの情報取得
	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		// プレイヤーの取得
		pPlayer = CTutorial::GetPlayer();

		// スコアの取得
		pScore = CTutorial::GetScore();
	}
	else if (CManager::GetMode() == CScene::MODE_GAME)
	{
		// プレイヤーの取得
		pPlayer = CGame::GetPlayer();

		// スコアの取得
		pScore = CGame::GetScore();
	}

	// プレイヤーとスコアがNULLじゃないなら
	if (pPlayer != NULL)
	{
		// プレイヤーと衝突したなら
		if (isColision(pPlayer->GetPos(), pPlayer->GetSize(), pPlayer->GetSize().x * 0.5f) == true)
		{
			if (pScore != NULL)
			{
				// スコア加算
				pScore->Add(1000);
			}

			// パーティクルの設定
			CParticle3D::Create(CObjectX::GetPos(), 
								D3DXVECTOR3(D3DX_PI * 0.25f, D3DX_PI * 2.0f, 0.0f),
								10.0f, 0.8f, 10, 60, 6);

			// 終了処理
			Uninit();
		}
	}
}

//====================================================
// 描画処理
//====================================================
void CNote::Draw(void)
{
	// オブジェクトの描画処理
	CObjectX::Draw();
}

//====================================================
// 当たり判定
//====================================================
bool CNote::isColision(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRadius)
{
	D3DXVECTOR3 apos = CObjectX::GetPos();// 自身の位置

	if (pos.y >= CObjectX::GetPos().y && pos.y <= CObjectX::GetPos().y + m_size.y ||
		pos.y + size.y >= CObjectX::GetPos().y && pos.y + size.y <= CObjectX::GetPos().y + m_size.y ||
		pos.y <= CObjectX::GetPos().y && pos.y + size.y <= CObjectX::GetPos().y)	// アイテムの高さの範囲なら
	{
		float fDistance = (pos.x - CObjectX::GetPos().x) * (pos.x - CObjectX::GetPos().x) +
			(pos.z - CObjectX::GetPos().z) * (pos.z - CObjectX::GetPos().z);// 距離(2D上)

		// 平方根
		fDistance = (float)sqrt(fDistance);

		if (fDistance <= (fRadius + m_size.x * 0.5f))
		{
			// 当たっている
			return true;
		}
		else
		{
			// 当たっていない
			return false;
		}
	}

	// 当たっていない
	return false;
}