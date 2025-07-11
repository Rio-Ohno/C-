//====================================================
//
// レンダラー[renderer.cpp]
// Author:Rio Ohno
//
//====================================================

//インクルード
#include "renderer.h"
#include"manager.h"
#include"input.h"
#include "object.h"

// 静的メンバ変数
CSound* CRenderer::m_pSound = { NULL };

//====================================================
// コンストラクタ
//====================================================
CRenderer::CRenderer()
{
	//クリアにする
	m_pD3D = NULL;
	m_pD3DDevice = NULL;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apTexMT[nCnt] = NULL;
	}
}

//====================================================
// デストラクタ
//====================================================
CRenderer::~CRenderer()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;             //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;      //プレゼンテーションパラメータ

	//DirectX3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));                               // パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                            // ゲーム画面のサイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                          // ゲーム画面のサイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;                           // バックバッファの形式
	d3dpp.BackBufferCount = 1;                                       // バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                        // ダブルバッファの切り替え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;                             // デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                       // デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;                                        // ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//DirectX3Dデバイスの生成（描画処理と頂点処理をハードウェア行う）
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//DirectX3Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う）
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//========================================================
	// マルチターゲットレンダリング
	// =======================================================
	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

	// レンダリングターゲット用テクスチャの生成
	m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
								SCREEN_HEIGHT, 
								1, 
								D3DUSAGE_RENDERTARGET,
								D3DFMT_A8R8G8B8, 
								D3DPOOL_DEFAULT, 
								&m_pTexMT, 
								NULL);

	// テクスチャインターフェースの生成
	m_pTexMT->GetSurfaceLevel(0, &m_pRenderMT);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// レンダリングターゲット用テクスチャの生成
		m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_apTexMT[nCnt],
			NULL);

		// テクスチャインターフェースの生成
		m_apTexMT[nCnt]->GetSurfaceLevel(0, &m_apRenderMT[nCnt]);

	}

	// テクスチャレンダリング用Zバッファの生成
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH, 
											SCREEN_HEIGHT, 
											D3DFMT_D16, 
											D3DMULTISAMPLE_NONE, 
											0, 
											TRUE, 
											&m_pZBuffMT, 
											NULL);

	// 現在のレンダリングターゲットを取得(保存)
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	// 現在のzバッファを取得(保存)
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);

	// レンダリングターゲットを生成したテクスチャに設定
	m_pD3DDevice->SetRenderTarget(0, m_pRenderMT);

	// zバッファを生成したzバッファに設定
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// レンダリング用テクスチャのクリア
	m_pD3DDevice->Clear(0,
						NULL,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(0, 0, 0, 0), 
						1.0f, 
						0);

	// レンダリングターゲットを元に戻す
	m_pD3DDevice->SetRenderTarget(0, pRenderDef);

	// zバッファを元に戻す
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	// テクスチャレンダリング用ビューポートの設定
	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = SCREEN_WIDTH;
	m_viewportMT.Height = SCREEN_HEIGHT;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 1.0f;

	//頂点バッファの生成
	m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMT,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
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
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファのアンロック
	m_pVtxBuffMT->Unlock();

	//----------------------------------
	// サウンド
	//----------------------------------

	// メモリの確保
	m_pSound = new CSound;

	// 初期化
	m_pSound->Init(hWnd);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CRenderer::Uninit(void)
{
	//========================================================
	// 各種オブジェクトの終了処理
	// =======================================================

	// テクスチャの破棄
	if (m_pTexMT != NULL)
	{
		m_pTexMT->Release();
		m_pTexMT = NULL;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apTexMT[nCnt] != NULL)
		{
			m_apTexMT[nCnt]->Release();
			m_apTexMT[nCnt] = NULL;
		}
	}

	if (m_pSound != NULL)
	{
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	//DirectX3Dデバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//DirectX3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//====================================================
// 更新処理
//====================================================
void CRenderer::Update(void)
{
	//キーボードの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	//========================================================
	// 各種オブジェクトの更新処理
	//========================================================
	CObject::UpdateAll();

#if _DEBUG

	if (pKeyboard->GetTrigger(DIK_F2) == true)// ワイヤーフレームにする
	{
		CRenderer::onWireFrame();
	}
	else if (pKeyboard->GetTrigger(DIK_F1) == true)// ワイヤーフレームを切る
	{
		CRenderer::offWireFrame();
	}

#endif
}

//====================================================
// 描画処理
//====================================================
void CRenderer::Draw(void)
{
	LPDIRECT3DSURFACE9 pRenderWk;
	LPDIRECT3DTEXTURE9 pTexWk;

	// バックバッファのクリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 現在のレンダリングターゲットを取得(保存)
	m_pD3DDevice->GetRenderTarget(0, &pRenderWk);

	//// フィードバックエフェクトをつけるなら
	//if (isFeedbackEffect() == true)
	//{
	//	//// レンダリングターゲットをテクスチャ[0]に設定
	//	//m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);
	//}
	//else if (isFeedbackEffect() == false)
	//{
	//
	//}

	// テクスチャ[0]のクリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//画面クリア（バックバッファ＆Zバッファのクリア）
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//描画開始が成功した場合

	//========================================================
	// 各種オブジェクトの描画処理
	//========================================================
	
		//全てのオブジェクトの描画処理
		CObject::DrawAll();

		//頂点情報へのポインタ
		VERTEX_2D* pVtx = NULL;

		//頂点バッファをロック
		m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			//頂点カラーの設定
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.99f);
		}

		//頂点バッファのアンロック
		m_pVtxBuffMT->Unlock();

		//頂点バッファをデータストリームに設定
		m_pD3DDevice->SetStreamSource(0, m_pVtxBuffMT, 0, sizeof(VERTEX_2D));

		//テクスチャの設定
		m_pD3DDevice->SetTexture(0, m_apTexMT[1]);

		//頂点フォーマットの設定
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		//ポリゴンの描画
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// レンダリングターゲットを元に戻す
		m_pD3DDevice->SetRenderTarget(0, pRenderWk);

		//頂点バッファをロック
		m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			//頂点カラーの設定
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//頂点バッファのアンロック
		m_pVtxBuffMT->Unlock();

		//テクスチャの設定
		m_pD3DDevice->SetTexture(0, m_apTexMT[0]);

		//ポリゴンの描画
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//描画終了
		m_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	// テクスチャを入れ変える
	pTexWk = m_apTexMT[0];
	m_apTexMT[0] = m_apTexMT[1];
	m_apTexMT[1] = pTexWk;

	pRenderWk = m_apRenderMT[0];
	m_apRenderMT[0] = m_apRenderMT[1];
	m_apRenderMT[1] = pRenderWk;
}

//====================================================
// デバイスの取得
//====================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)const
{
	return m_pD3DDevice;
}

//====================================================
// レンダリングターゲットの変更
//====================================================
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	D3DXMATRIX mtxView, mtxProjection;
	float fAspect;

	// レンダリングターゲットを生成したテクスチャに設定
	m_pD3DDevice->SetRenderTarget(0, m_pRenderMT);

	//// レンダリングターゲットを生成したテクスチャに設定
	//m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

	// zバッファを生成したzバッファに設定
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// テクスチャレンダリング用のビューポートを設定
	m_pD3DDevice->SetViewport(&m_viewportMT);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);

	// ビューマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	// プロジェクションマトリックスの生成
	fAspect = (float)m_viewportMT.Width / (float)m_viewportMT.Height;

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection, 
								D3DXToRadian(45.0f),
								fAspect,
								10.0f,
								1000.0f);

	// プロジェクションマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}