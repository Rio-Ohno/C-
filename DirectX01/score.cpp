//==================================================== 
// 
// スコア　[score.cpp]
// Author: Rio Ohno
// 
//==================================================== 

// インクルード
#include"score.h"
#include<stdio.h>
#include"manager.h"
#include"input.h"

//// 静的メンバ変数
//int CScore::m_nScore = 0;

//==================================================== 
// コンストラクタ
//==================================================== 
CScore::CScore(int nPriority) :CObject(nPriority)
{
	// 値をクリアする
	m_nScore = 0;
	m_nDigit = 0;
	m_Texindx = -1;
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
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		pos.x -= (fWidth + nCnt);

		// 数字の生成、テクスチャの割当
		m_apNumber[nCnt] = CNumber::Create(pos, fWidth, fHeight);
		m_apNumber[nCnt]->CNumber::BindTexindx(m_Texindx);
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
		if (m_apNumber[nCnt] != NULL)
		{
			// 数字の終了処理
			m_apNumber[nCnt]->CNumber::Uninit();
		}
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
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		// 数字の描画処理
		m_apNumber[nCnt]->Draw();
	}
}

//==================================================== 
// 生成処理
//==================================================== 
CScore* CScore::Create(D3DXVECTOR3 pos, int nDigit, float fWidth, float fHeight)
{
	CScore* pScore = NULL;

	// メモリの確保
	pScore = new CScore;

	// テクスチャインデックスの設定
	pScore->m_Texindx = CTexture::TYPE_SCORENUMBER;

	// 桁数の設定
	if (nDigit <= MAX_SCOREDIGHT)
	{
		pScore->m_nDigit = nDigit;
	}
	else
	{
		pScore->m_nDigit = MAX_SCOREDIGHT;
	}

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
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_nScore,nCnt);
	}

	CDebugProc::Print("score：%d\n", m_nScore);
}

//==================================================== 
// テクスチャ割当処理
//==================================================== 
void CScore::BindTexIndx(int nTexIndex)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		m_apNumber[nCnt]->BindTexindx(nTexIndex);
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

//====================================================
// スコアの書き込み処理 
//==================================================== 
void CScore::Save(const char* pFilename)
{
	// 外部ファイルを開く
	FILE* pFile = fopen(pFilename, "w");

	if (pFile != NULL)
	{
		// 数値の書出
		fprintf(pFile, "SCORE_DATA");

		fprintf(pFile, "\n%08d", m_nScore);

		// 終わりの書出
		fprintf(pFile, "\nEND_SCORE_DATA");

		// 外部ファイルを閉じる
		fclose(pFile);
	}
}

//==================================================== 
// スコアの読込処理
//==================================================== 
int CScore::Load(const char* pFilename)
{
	int nScore = 0;
	// 外部ファイルを開く
	FILE* pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{
		char cData = { NULL };
		char cData1[64] = { NULL };

		while (1)
		{
			// 読込
			cData = fscanf(pFile, "%s", &cData1[0]);

			if ((int)cData1[0] == EOF || (char)cData1[0] == NULL)// ファイルの末端、データなしなら
			{
				// ループを抜ける
				break;
			}
			else if (strcmp(&cData1[0], "SCORE_DATA") == 0)// SCORE_DATAなら
			{
				// 数値を読みとる
				cData = fscanf(pFile, "%08d", &nScore);
			}
			else if (strcmp(&cData1[0], "END_SCORE_DATA") == 0)// END_SCORE_DATAなら
			{// 読込完了

				// 外部ファイルを閉じる
				fclose(pFile);

				// ループをぬける
				break;
			}
		}
	}
	return nScore;
}