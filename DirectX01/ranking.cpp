//====================================================
//
// ランキングシーン処理 [ranking.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"ranking.h"
#include<stdio.h>
#include"manager.h"
#include"meshSphere.h"

// 静的メンバ変数
CScore* CRanking::m_apScore[NUM_RANK] = { NULL };
CRanking::MODE CRanking::m_mode = CRanking::MODE::MODE_DISPLAY;

//====================================================
// コンストラクタ
//====================================================
CRanking::CRanking()
{
	// 各メンバ変数の初期化
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		m_apScore[nCnt] = { NULL };
	}

	m_nRank = -1;
	m_nCntFream = 0;
	m_nCntFreamColor = 0;

	m_bFlashing = false;
}

//====================================================
// デストラクタ
//====================================================
CRanking::~CRanking()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ランキングの読込処理
	Load(SAVEFILE_RANKING);

	if (m_mode == MODE_GAME)// ゲームなら
	{
		// バブルソート
		Sort();

		// ランキング入りしたなら
		if (m_nRank >= 0)
		{
			// 点滅フラグを立てる
			m_bFlashing = true;
		}
	}

	// カメラ位置の設定
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 90.0f, -190.0f), D3DXVECTOR3(0.0f, 0.0f, 270.0f));

	// 球体の生成
	CMeshSphere*pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	pSphere->BindTexIndex(CTexture::TYPE_SKY_RANKING);

	// 2Dポリゴン
	CObject2D* pRanking = CObject2D::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), 720.0f, 150.0f);
	pRanking->BindTexIndx(CTexture::TYPE_RANKING);

	// スコアの生成
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		// スコアの生成
		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(840.0f, 200.0f + 110.0f * nCnt, 0.0f), 7, 50.0f, 100.0f);
		m_apScore[nCnt]->BindTexIndx(CTexture::TYPE_TIMENUMBER);
		
		// スコアの設定
		m_apScore[nCnt]->Add(m_anScore[nCnt]);
	}

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CRanking::Uninit(void)
{
	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CRanking::Update(void)
{
	// スペースを押したらタイトルへ
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) == true)
	{
		CManager::GetFade()->Set(CScene::MODE_TITLE);
	}

	// ランキングのリセット
	CRanking::Reset();

	if (m_mode == MODE_DISPLAY)// ディスプレイなら
	{
		// フレームカウントアップ
		m_nCntFream++;

		if (m_nCntFream >= DISPLAY_FREAM)
		{
			// フレームカウントリセット
			m_nCntFream = 0;

			// タイトルへ
			CManager::GetFade()->Set(CScene::MODE_TITLE);
		}
	}
	else if(m_mode == MODE_GAME)// ゲームなら
	{
		// 点滅処理
		CRanking::Flashing();
	}
}

//====================================================
// 描画処理
//====================================================
void CRanking::Draw(void)
{
	// なし
}

//====================================================
// 読込処理
//====================================================
void CRanking::Load(const char* FileName)
{
	// 外部ファイルを開く
	FILE* pFile = fopen(FileName, "r");

	// 外部ファイルが開けたなら
	if (pFile != NULL)
	{
		char aString[32] = {};// 文字列格納用
		char cData;// 警告よけ用

		int nData[NUM_RANK] = { 0 };

		while (1)
		{
			// 読込
			cData = fscanf(pFile, "%s", &aString[0]);

			if ((int)aString[0] == EOF || (char)aString[0] == NULL)// ファイルの末端、データなしなら
			{
				// ループを抜ける
				break;
			}
			else if (strcmp(&aString[0], "RANKING_DATA") == 0)// RANKING_DATAなら
			{
				// 数値を読みとる
				for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
				{
					cData = fscanf(pFile, "%08d", &nData[nCnt]);
				}
			}
			else if (strcmp(&aString[0], "END_RANKING_DATA") == 0)// END_RANKING_DATAなら
			{// 読込完了

				// 数値の保存
				for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
				{
					m_anScore[nCnt] = nData[nCnt];
				}

				// 外部ファイルを閉じる
				fclose(pFile);

				// ループをぬける
				break;
			}
		}
	}
}

//====================================================
// 書き込み処理
//====================================================
void CRanking::Save(const char* FileName)
{
	// 外部ファイルを開く
	FILE* pFile = fopen(FileName, "w");

	// 外部ファイルを開けたなら
	if (pFile != NULL)
	{
		// 数値の書出
		fprintf(pFile, "RANKING_DATA");

		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			fprintf(pFile, "\n%08d", m_anScore[nCnt]);
		}

		// 終わりの書出
		fprintf(pFile, "\nEND_RANKING_DATA");

		// 外部ファイルを閉じる
		fclose(pFile);
	}
}

//====================================================
// バブルソート
//====================================================
void CRanking::Sort(void)
{
	// スコアの読込
	int nScore = CScore::Load(SAVEFILE_SCORE);

	int anScore[NUM_RANK + 1] = { 0 };

	// 数値格納
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		anScore[nCnt] = m_anScore[nCnt];
	}

	anScore[NUM_RANK] = nScore;

	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		for (int nNext = nCntRank + 1; nNext < NUM_RANK + 1; nNext++)// 配列の次の数値
		{
			// 降順
			if (anScore[nCntRank] < anScore[nNext])
			{
				int nData = anScore[nCntRank];// 一時保存

				// 数値の入れ替え
				anScore[nCntRank] = anScore[nNext];

				anScore[nNext] = nData;
			}
		}
	}

	// ランキングに代入
	for (int nRanking = 0; nRanking < NUM_RANK; nRanking++)
	{
		m_anScore[nRanking] = anScore[nRanking];

		if (m_anScore[nRanking] == nScore)
		{
			// 順位の保存
			m_nRank = nRanking;
		}
	}

	// 書込処理
	Save(SAVEFILE_RANKING);
}

//====================================================
// 点滅処理
//====================================================
void CRanking::Flashing(void)
{
	if (m_bFlashing == true)
	{
		// フレームカウントアップ
		m_nCntFreamColor++;

		if (m_nCntFreamColor == 30)
		{
			// 色の設定(黄)
			m_apScore[m_nRank]->SetColor(D3DXCOLOR(1.0f, 0.9f, 0.31f, 1.0f));
		}
		else if(m_nCntFreamColor>=60)
		{
			// 色の設定(白)
			m_apScore[m_nRank]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// フレームカウントリセット
			m_nCntFreamColor = 0;
		}
	}
}

//====================================================
// ランキングのリセット
//====================================================
void CRanking::Reset(void)
{
	// 左シフトを押しながら
	if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT) == true)
	{
		// R　を押したら
		if (CManager::GetKeyboard()->GetTrigger(DIK_R) == true)
		{
			// 数値の初期化
			for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
			{
				m_anScore[nCnt] = 0;
			}

			// 初期化後の数値の保存
			CRanking::Save(SAVEFILE_RANKING);
		}
	}
}
