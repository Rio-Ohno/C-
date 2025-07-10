//====================================================
// 
// 弾 [bullet.h]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include "bullet.h"
#include"manager.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"score.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//====================================================
// コンストラクタ
//====================================================
CBullet::CBullet()
{
	//値をクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//====================================================
// デストラクタ
//====================================================
CBullet::~CBullet()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CBullet:: Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ポリゴンの初期化
	CObject2D::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CBullet::Uninit(void)
{
	// ポリゴンの終了処理
	CObject2D::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CBullet::Update(void)
{
	m_move.x = -BULLET_SPEED;

	// 位置を更新
	D3DXVECTOR3 pos = CObject2D::GetPos() + m_move;

	// 位置の設定
	CObject2D::SetPos(pos);

	// エフェクトの生成
	CEffect* pEffect = CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20, 0.97f);
	pEffect->SetColor(D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f));

	// 寿命のカウントダウン
	m_nLife--;

	// 当たってないなら
	if (CollisionEnemy(pos) == false)
	{
		if (m_nLife <= 0)
		{// 寿命が尽きたら

			// 弾の爆発の生成
			CExplosion::Create(CObject2D::GetPos(), 50.0f);

			// 終了処理
			Uninit();
		}
		else if (pos.x <= 0.0f ||
			pos.x >= SCREEN_WIDTH ||
			pos.y <= 0.0f ||
			pos.y >= SCREEN_HEIGHT)
		{// 画面外に出たら

			// 終了処理
			Uninit();
		}
	}
}

//====================================================
// 描画処理
//====================================================
void CBullet::Draw(void)
{
	// ポリゴンの描画処理
	CObject2D::Draw();
}

//====================================================
// 生成処理
//====================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, float fRadius,int nLife)
{
	int nNumAll = CObject::GetNumAll();

	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// 弾へのポインタ
	CBullet* pBullet = NULL;

	// メモリの確保
	pBullet = new CBullet;

	// 初期化処理
	pBullet->Init(pos, fRadius, fRadius);

	// 寿命の設定
	pBullet->m_nLife = nLife;

	//テクスチャの割当
	pBullet->BindTex(m_pTexture);

	// 種類の設定
	pBullet->SetType(TYPE_BULLET);

	return pBullet;
}

//====================================================
// テクスチャの読込
//====================================================
HRESULT CBullet::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読込
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\fish.png",
		&m_pTexture)))
	{
		return -1;
	}
	
	return S_OK;
}

//====================================================
// テクスチャの破棄
//====================================================
void CBullet::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//====================================================
// テクスチャの破棄
//====================================================
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			// オブジェクトの取得
			CObject* pObj = CObject::GetObject(nPriority, nCnt);

			if (pObj != NULL)
			{
				// 種類の取得
				CObject::TYPE type = pObj->GetType();

				if (type == CObject::TYPE_ENEMY)
				{// 敵なら

					// 当たり判定をとる
					if (pos.x >= pObj->GetPos().x - pObj->GetWidth() * 0.5f &&
						pos.x <= pObj->GetPos().x + pObj->GetWidth() * 0.5f &&
						pos.y >= pObj->GetPos().y - pObj->GetHeight() * 0.5f &&
						pos.y <= pObj->GetPos().y + pObj->GetHeight() * 0.5f)// 当たったら
					{
						// 弾の爆発の生成
						CExplosion::Create(CObject2D::GetPos(), 50.0f);

						CScore::Add(5);

						//// 敵の爆発の生成
						//CExplosion* pExplosion = CExplosion::Create(pObj->GetPos(), 100.0f);
						//pExplosion->SetColor(D3DXCOLOR(1.0f, 0.8f, 0.5f, 1.0f));

						// パーティクルの生成
						CParticle* pParticle = CParticle::Create(pObj->GetPos(), D3DXVECTOR3(0.0f, 0.0f, 6.28f), 30.0f, 8.0f, 8, 15, 6);
						pParticle->SetColor(D3DXCOLOR(1.0f, 0.8f, 0.5f, 0.5f));// 色の設定

						// 敵の破棄
						pObj->Uninit();

						// 弾の破棄
						CBullet::Uninit();

						return true;
					}
				}
			}
		}
	}
	return false;
}
