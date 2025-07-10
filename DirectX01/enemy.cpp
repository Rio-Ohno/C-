//====================================================
//
// 敵[enemy.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"enemy.h"
#include"manager.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;

////====================================================
//// コンストラクタ
////====================================================
//CEnemy::CEnemy()
//{
//	//値をクリア
//	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_fLife = 0;
//}

//====================================================
// コンストラクタ
//====================================================
CEnemy::CEnemy(int nPriority) :CObject2D(nPriority)
{
	//値をクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLife = 0;
}

//====================================================
// デストラクタ
//====================================================
CEnemy::~CEnemy()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ポリゴンの初期化
	CObject2D::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CEnemy::Uninit(void)
{
	// ポリゴンの終了処理
	CObject2D::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CEnemy::Update(void)
{
}

//====================================================
// 描画処理
//====================================================
void CEnemy::Draw(void)
{
	// ポリゴンの描画処理
	CObject2D::Draw();
}

//====================================================
// 生成処理
//====================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// 弾へのポインタ
	CEnemy* pEnemy = NULL;

	// メモリの確保
	pEnemy = new CEnemy;

	// 初期化処理
	pEnemy->Init(pos, fWidth, fHeight);

	//テクスチャの割当
	pEnemy->BindTex(m_pTexture);

	// 種類の設定
	pEnemy->SetType(CObject::TYPE_ENEMY);

	return pEnemy;
}

//====================================================
// テクスチャの読込
//====================================================
HRESULT CEnemy::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読込
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cat001.png",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;
}

//====================================================
// テクスチャの破棄
//====================================================
void CEnemy::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}