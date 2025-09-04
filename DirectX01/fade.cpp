//====================================================
//
//フェード処理[fade.cpp]
//Author:Rio Ohno
//
//====================================================

// インクルード
#include"fade.h"
#include"manager.h"

//====================================================
// コンストラクタ
//====================================================
CFade::CFade()
{
	// 変数の初期化
	m_fade = FADE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);        //黒いポリゴン（不透明）にしておく
	m_pVtxBuff = { NULL };
}

//====================================================
// デストラクタ
//====================================================
CFade::~CFade()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CFade::Init(void)
{
	m_fade = FADE_IN;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);        //黒いポリゴン（不透明）にしておく

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx{};

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点バッファの生成、頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CFade::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//====================================================
// 更新処理
//====================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			//フェードインの状態
			m_colorFade.a -= 0.02f;

			if (m_colorFade.a < 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			//フェードアウト状態
			m_colorFade.a += 0.02f;

			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;

				//モード設定（次の画面に移行）
				CManager::SetMode(m_modeNext);
			}
		}

		VERTEX_2D* pVtx{};

		//頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//====================================================
// 描画処理
//====================================================
void CFade::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファのデータストリームを設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================================================
//フェードの設定処理
//=============================================================================================================
void CFade::Set(CScene::MODE modeNext)
{
	m_fade = FADE_OUT;                                                         //フェードアウト状態へ
	m_modeNext = modeNext;                                                     //次の画面を設定
}

//=============================================================================================================
//フェードの取得処理
//=============================================================================================================
CFade::FADE CFade::Get(void)
{
	return m_fade;
}