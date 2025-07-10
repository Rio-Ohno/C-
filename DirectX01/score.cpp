//==================================================== 
// 
// スコア　[score.cpp]
// Author: Rio Ohno
// 
//==================================================== 

// インクルード
#include"score.h"
#include"manager.h"
#include"input.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;
int CScore::m_nScore = 0;

//==================================================== 
// コンストラクタ
//==================================================== 
CScore::CScore(int nPriority) :CObject(nPriority)
{
	// 値をクリアする
	m_nScore = 0;
}

//==================================================== 
// デストラクタ
//==================================================== 
CScore::~CScore()
{
	//　なし
}

//==================================================== 
// 初期化処理
//==================================================== 
HRESULT CScore::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGHT; nCnt++)
	{
		pos.x -= (fWidth + nCnt);

		// 数字の生成、テクスチャの割当
		m_apNumber[nCnt] = CNumber::Create(pos, fWidth, fHeight);
		m_apNumber[nCnt]->CNumber::BindTex(m_pTexture);
	}
	return S_OK;
}

//==================================================== 
// 終了処理
//==================================================== 
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGHT; nCnt++)
	{
		// 数字の終了処理
		m_apNumber[nCnt]->CNumber::Uninit();
	}
	// オブジェクトの破棄
	CObject::Release();
}

//==================================================== 
// 更新処理
//==================================================== 
void CScore::Update(void)
{
#if _DEBUG
	//キーボードの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetPress(DIK_UP) == true)
	{
		// スコア加算
		CScore::Add(5);
	}
	else if (pKeyboard->GetPress(DIK_DOWN) == true)
	{
		// スコア減算
		CScore::Diff(5);
	}

#endif
	// スコアの設定
	CScore::SetScore();
}

//==================================================== 
// 描画処理
//==================================================== 
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGHT; nCnt++)
	{
		// 数字の描画処理
		m_apNumber[nCnt]->Draw();
	}
}

//==================================================== 
// テクスチャの読込
//==================================================== 
HRESULT CScore::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読込
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;
}

//==================================================== 
// テクスチャの破棄
//==================================================== 
void CScore::UnLoad(void)
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
CScore* CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScore* pScore = NULL;

	// メモリの確保
	pScore = new CScore;

	// 初期化処理
	pScore->Init(pos, fWidth, fHeight);

	// 種類の設定
	pScore->SetType(TYPE_UI);

	return pScore;
}

//==================================================== 
// スコアの設定処理
//==================================================== 
void CScore::SetScore(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGHT; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_nScore,nCnt);
	}
}

//==================================================== 
// スコア加算処理
//==================================================== 
void CScore::Add(const int nAdd)
{
	m_nScore += nAdd;
}

//==================================================== 
// スコア減算処理
//==================================================== 
void CScore::Diff(const int nDiff)
{
	if ((m_nScore - nDiff) >= 0)
	{
		m_nScore -= nDiff;
	}
}