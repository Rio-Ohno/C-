//====================================================
//
// 影[shadow.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"shadow.h"
#include"manager.h"

//====================================================
// コンストラクタ
//====================================================
CShadow::CShadow()
{
	// なし
}

//====================================================
// デストラクタ
//====================================================
CShadow::~CShadow()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CShadow* pShadow = NULL;

	// メモリの確保
	pShadow = new CShadow;

	// 位置の設定
	pShadow->SetPos(pos);
	pShadow->SetSize(D3DXVECTOR2(fRadius, fRadius));

	// 初期化処理
	pShadow->Init();

	// テクスチャの割当
	pShadow->BindTexIndex(CTexture::TYPE_SHADOW);

	return pShadow;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CShadow::Init(void)
{
	// ポリゴンの初期化処理
	CObject3D::Init();
	CObject3D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CShadow::Uninit(void)
{
	// ポリゴンの終了処理
	CObject3D::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CShadow::Update(void)
{
	// なし
}

//====================================================
// 描画処理
//====================================================
void CShadow::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0.05f);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ポリゴンの描画処理
	CObject3D::Draw();

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}