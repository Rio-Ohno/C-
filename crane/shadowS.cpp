//====================================================
//
// 影[shadowS.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"shadowS.h"
#include"manager.h"
#include"input.h"

// 静的メンバ変数
bool CShadowS::m_bmodel = false;

//====================================================
// コンストラクタ
//====================================================
CShadowS::CShadowS(int nPriority):CObjectX(nPriority)
{
	m_pVtxBuff = { NULL };
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//====================================================
// デストラクタ
//====================================================
CShadowS::~CShadowS()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CShadowS* CShadowS::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CShadowS* pShadowS = NULL;

	// メモリの確保
	pShadowS = new CShadowS;

	// モデルのファイルパスの割当
	pShadowS->BindModel("data\\MODEL\\shadow.x");

	// 位置の設定
	pShadowS->SetPos(pos);
	pShadowS->SetRot(rot);

	// 初期化処理
	pShadowS->Init();

	return pShadowS;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CShadowS::Init(void)
{
	// モデルの初期化処理
	CObjectX::Init();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();


	//ポリゴンの初期化処理

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//rhwの設定
		pVtx[nCnt].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[nCnt].col = D3DCOLOR_RGBA(0, 0, 0, 200);
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CShadowS::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの終了処理
	CObjectX::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CShadowS::Update(void)
{
	// オブジェクトの更新
	CObjectX::Update();

#ifdef _DEBUG

	// 入力
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	// 影モデルを表示するかどうか
	if (pKeyboard->GetTrigger(DIK_F3) == true)
	{
		m_bmodel = m_bmodel ? false : true;
	}
#endif // _DEBUG
}

//====================================================
// 描画処理
//====================================================
void CShadowS::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 向き・位置の取得
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 rot = CObjectX::GetRot();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_bmodel == false)
	{
		// ステンシルテストを有効にする
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// Zバッファへの書き込みを無効にする
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		// カラーバッファへの書き込みを無効にする
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

		// ステンシルバッファの比較パラメータを設定
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);

		//表面をカリング
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}

	 //影モデルの描画処理
	CObjectX::Draw();

	if (m_bmodel == false)
	{
		// ステンシルバッファの参照値を設定("1"にする)
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		// ステンシルバッファの比較パラメータを設定
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);

		// 表面をカリング
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// 影モデルの描画処理
		CObjectX::Draw();
	}
		// カラーバッファへの書き込みを有効にする
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);

	if (m_bmodel == false)
	{
		// ステンシルバッファの参照値を設定("2"にする)
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

		// ステンシルバッファの比較パラメータを設定
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);


		// 画面サイズの黒ポリゴン描画
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// 全て元に戻す
	
	// ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// Zバッファへの書き込みを有効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//カリングをつける
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//====================================================
// 影の色設定
//====================================================
void CShadowS::SetColor(D3DXCOLOR col)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//頂点カラーの設定
		pVtx[nCnt].col = col;
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}