//==================================================== 
// 
// 数値の管理　[Number.cpp]
// Author: Rio Ohno
// 
//==================================================== 

// インクルード
#include"Number.h"
#include"manager.h"

//==================================================== 
// コンストラクタ
//==================================================== 
CNumber::CNumber()
{
	// 各初期化
	m_pVtxBuff = NULL;							// 頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_Texindx = -1;								// テクスチャインデックス
	m_fWidth = 0;								// 幅
	m_fHeight = 0;								// 高さ
}

//==================================================== 
// デストラクタ
//==================================================== 
CNumber::~CNumber()
{
	// なし
}

//==================================================== 
// 初期化処理
//==================================================== 
void CNumber::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 各変数の初期化
	m_pos = pos;// 位置
	m_fWidth = fWidth;// 幅
	m_fHeight = fHeight;// 高さ

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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/,
		m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/,
		m_pos.z);

	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/,
		m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/,
		m_pos.z);

	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/,
		m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/,
		m_pos.z);

	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/,
		m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/,
		m_pos.z);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//rhwの設定
		pVtx[nCnt].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//==================================================== 
// 終了処理
//==================================================== 
void CNumber::Uninit(void)
{
	//バッファーの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// メモリの破棄
	delete this;
}

//==================================================== 
// 更新処理
//==================================================== 
void CNumber::Update(void)
{

}

//==================================================== 
// 描画処理
//==================================================== 
void CNumber::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャクラスへのポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	//ポリゴンの描画処理

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_Texindx));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==================================================== 
// 色の取得処理
//==================================================== 
D3DXCOLOR CNumber::GetColor(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	D3DXCOLOR col = {};

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
	col = pVtx[0].col;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return col;
}

//==================================================== 
// 色の設定
//==================================================== 
void CNumber::SetColor(D3DXCOLOR col)
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

//==================================================== 
// 生成処理
//==================================================== 
CNumber* CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CNumber* pNumber = NULL;
	pNumber = new CNumber;

	pNumber->Init(pos,fWidth,fHeight);

	return pNumber;
}

//==================================================== 
// 各桁の数値を設定
//==================================================== 
int CNumber::SetNum(int nNumber,int nDight)
{
	int nNum = 0;// 各桁の数値格納用
	int nDiffDight = 10;

	for (int nCnt = 0; nCnt < nDight; nCnt++)
	{
		nNumber /= 10;
	}

	// 数値の特定
	nNum = nNumber % 10;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
		//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.1f * nNum, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (nNum + 1.0f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * nNum, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (nNum + 1.0f), 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return nNum;
}