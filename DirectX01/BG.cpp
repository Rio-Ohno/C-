//====================================================
//
// 背景[BG.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "BG.h"
#include"manager.h"


// 静的メンバ変数
LPDIRECT3DTEXTURE9 CBG::m_pTexture = NULL;
LPDIRECT3DTEXTURE9 CBGManager::m_pTexture[MAX_BG] = { NULL };
CBG* CBGManager::m_apBG[MAX_BG] = { NULL };

////====================================================
//// コンストラクタ
////====================================================
//CBG::CBG()
//{
//	// 値をクリアにする
//	m_fScroll = 0;
//}

//====================================================
// コンストラクタ
//====================================================
CBG::CBG(int nPriority) :CObject2D(nPriority)
{
	// 値をクリアにする
	m_fScroll = 0;
	m_fMemScroll = 0;
}

//====================================================
// デストラクタ
//====================================================
CBG::~CBG()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CBG::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ポリゴンの初期化
	CObject2D::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CBG::Uninit()
{
	// ポリゴンの終了処理
	CObject2D::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CBG::Update()
{
	if (m_fScroll != 0)
	{
		m_fMemScroll -= m_fScroll;

		// バッファーの取得
		LPDIRECT3DVERTEXBUFFER9 pBuff = this->GetBuffer();

		//頂点情報へのポインタ
		VERTEX_2D* pVtx = NULL;

		//頂点バッファをロック
		pBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(m_fMemScroll, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f + m_fMemScroll, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_fMemScroll, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f + m_fMemScroll, 1.0f);

		//頂点バッファのアンロック
		pBuff->Unlock();

		if (m_fMemScroll > 1.0f)
		{// 1より大きいなら
			m_fMemScroll -= 1.0f;
		}
	}
}

//====================================================
// 描画処理
//====================================================
void CBG::Draw()
{
	// ポリゴンの描画処理
	CObject2D::Draw();
}

//====================================================
// テクスチャの読み込み
//====================================================
HRESULT CBG::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読込
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\BG.jpg",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;
}

//====================================================
// テクスチャの破棄
//====================================================
void CBG::UnLoad()
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//====================================================
// 生成処理
//====================================================
CBG* CBG::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fScroll)
{
	CBG* pBG = NULL;

	// メモリの確保
	pBG = new CBG;

	// 初期化処理
	pBG->Init(pos, fWidth, fHeight);

	pBG->m_fScroll = fScroll;

	// テクスチャの割当
	pBG->BindTex(m_pTexture);

	// 種類の設定
	pBG->SetType(CObject::TYPE_BG);

	return pBG;
}

//CBGManager***************************************************************************************************************************************************************

//====================================================
// コンストラクタ
//====================================================
CBGManager::CBGManager(int nPriority):CObject(nPriority)
{
	//　なし
}

//====================================================
// デストラクタ
//====================================================
CBGManager::~CBGManager()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CBGManager::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apBG[nCnt] = CBG::Create(pos, SCREEN_WIDTH, SCREEN_HEIGHT, Scroll_SPEED * (nCnt + 1));
		m_apBG[nCnt]->BindTex(m_pTexture[nCnt]);
	}
	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CBGManager::Uninit()
{
	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CBGManager::Update()
{
}

//====================================================
// 描画処理
//====================================================
void CBGManager::Draw()
{
}

//====================================================
// テクスチャの読み込み
//====================================================
HRESULT CBGManager::Load()
{
	//テクスチャ
	static const char* BG_TEXTURE[MAX_BG] =
	{
		"data\\TEXTURE\\BG001.jpg",
		"data\\TEXTURE\\bg101.png",
		"data\\TEXTURE\\bg102.png",
	};

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//テクスチャの読込
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			BG_TEXTURE[nCnt],
			&m_pTexture[nCnt])))
		{
			return -1;
		}
	}

	return S_OK;
}

//====================================================
// テクスチャの破棄
//====================================================
void CBGManager::UnLoad()
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{			  
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//====================================================
// 生成処理
//====================================================
CBGManager* CBGManager::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CBGManager* pBGScroll = NULL;

	 //メモリの確保
	pBGScroll = new CBGManager;

	// 初期化処理
	pBGScroll->Init(pos, fWidth, fHeight);

	// 種類の設定
	pBGScroll->SetType(CObject::TYPE_BG);

	return pBGScroll;
}
