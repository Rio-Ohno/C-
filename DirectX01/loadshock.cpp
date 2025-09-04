//====================================================
// 
// 波のパターン読込処理 [loadshock.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include"loadshock.h"

// 静的メンバ変数
CLoadtxt* CLoadShock::m_pLoadTxt = { NULL };
CShockInfo* CShockPattern::m_apInfo[SHOCK_PATTERN_NUM] = { NULL };

//====================================================
// 衝撃波の情報のコンストラクタ
//====================================================
CShockInfo::CShockInfo()
{
	// 各変数の初期化
	m_nFream = 0;
	m_nVanish = 0;
	m_nLife = 0;

	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fRadius = 0.0f;
	m_fSpeed = 0.0f;

	m_bCulling = true;
	m_bCollision = false;
}

//====================================================
// 衝撃波の情報のデストラクタ
//====================================================
CShockInfo::~CShockInfo()
{
	// なし
}

//====================================================
// 衝撃波の情報の生成処理
//====================================================
CShockInfo* CShockInfo::Create(int nFream, int nVanish, int nLife, float fWidth, float fHeight, float fRadius, float fSpeed, bool bCulling, bool bCollision)
{
	CShockInfo* pPattern = NULL;

	// メモリの確保
	pPattern = new CShockInfo;

	// 各変数の設定
	pPattern->m_nFream = nFream;
	pPattern->m_nVanish = nVanish;
	pPattern->m_nLife = nLife;
	pPattern->m_fWidth = fWidth;
	pPattern->m_fHeight = fHeight;
	pPattern->m_fRadius = fRadius;
	pPattern->m_fSpeed = fSpeed;
	pPattern->m_bCulling = bCulling;
	pPattern->m_bCollision = bCollision;

	return pPattern;
}

//====================================================
// 衝撃波のパターンのコンストラクタ
//====================================================
CShockPattern::CShockPattern()
{
	// 各変数の初期化
	for (int nCnt = 0; nCnt < SHOCK_PATTERN_NUM; nCnt++)
	{
		m_apInfo[nCnt] = { NULL };
	}

	m_nNumInfo = 0;
}

//====================================================
// 衝撃波のパターンのデストラクタ
//====================================================
CShockPattern::~CShockPattern()
{
	// なし
}

//====================================================
// 終了処理
//====================================================
void CShockPattern::Uninit(void)
{
	for (int nCnt = 0; nCnt < SHOCK_PATTERN_NUM; nCnt++)
	{
		if (m_apInfo[nCnt] != NULL)
		{
			// メモリの破棄
			delete m_apInfo[nCnt];
			m_apInfo[nCnt] = NULL;
		}
	}
}

//====================================================
// 衝撃波の情報設定処理
//====================================================
void CShockPattern::SetInfo(CShockInfo** ppInfo)
{
	for (int nCnt = 0; nCnt < SHOCK_PATTERN_NUM; nCnt++)
	{
		if (ppInfo[nCnt] != NULL)
		{
			m_apInfo[nCnt] = ppInfo[nCnt];
		}
	}
}

//====================================================
// 位置の設定処理
//====================================================
void CShockPattern::SetPos(D3DXVECTOR3* pos)
{
	for(int nCnt=0;nCnt<SHOCK_NUM;nCnt++)
	{
		if (pos[nCnt] != NULL)
		{
			m_pos[nCnt] = pos[nCnt];
		}
	}
}

//====================================================
// 衝撃波のパターンの読込のコンストラクタ
//====================================================
CLoadShock::CLoadShock()
{
	// 各変数の初期化

	m_pLoadTxt = { NULL };

	m_nCntInfo = 0;
	m_nCntPos = 0;
}

//====================================================
// 衝撃波のパターンの読込のデストラクタ
//====================================================
CLoadShock::~CLoadShock()
{
	// なし
}

//====================================================
// 衝撃波のパターンの読込処理呼び出し処理
//====================================================
void CLoadShock::Load(const char* FilePass, CShockPattern* pPattern)
{
	CLoadShock* pShock = NULL;

	// メモリの確保
	pShock = new CLoadShock;

	pShock->LoadScript(FilePass, pPattern);

	// メモリの破棄
	delete pShock;
	pShock = NULL;
}

//====================================================
// 衝撃波のパターンの読込開始処理
//====================================================
void CLoadShock::LoadScript(const char* FilePass, CShockPattern* pPattern)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };

	// 外部ファイルを開く
	FILE* pFile = fopen(FilePass, "r");

	if (pFile != NULL)
	{
		// メモリの確保
		m_pLoadTxt = new CLoadtxt;

		while (1)
		{
			fgets(cData, 2, pFile);

			if (*cData != '#')
			{
				strcat(cData1, cData);

				if (strcmp(&cData1[0], "SCRIPT") == 0)// SCRIPTなら
				{
					// コメントを読み飛ばす
					m_pLoadTxt->SkipComment(pFile);

					// 文字列の初期化
					cData1[0] = { NULL };
					break;
				}
			}
			else
			{
				// コメントを読み飛ばす
				m_pLoadTxt->SkipComment(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
		}

		// 続きを読込む
		LoadPattern(pFile, pPattern);
		fclose(pFile);
	}

	if (m_pLoadTxt != NULL)// 中身があるなら
	{
		// メモリの開放
		delete m_pLoadTxt;
		m_pLoadTxt = NULL;
	}
}

//====================================================
// 衝撃波のパターンの読込処理
//====================================================
void CLoadShock::LoadPattern(FILE* pFile, CShockPattern* pPattern)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	int NumInfo = 0;
	CShockInfo* apInfo[SHOCK_PATTERN_NUM] = { NULL };
	D3DXVECTOR3 pos[SHOCK_NUM] = {};

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "MAX_NUM") == 0)// MAX_NUMなら
			{
				// =の読み飛ばし
				m_pLoadTxt->SkipEqual(pFile);

				// 数値の取得
				NumInfo = m_pLoadTxt->LoadInt(pFile);

				// モデル数の設定
				pPattern->SetNumInfo(NumInfo);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "POSSET") == 0)// POSSETなら
			{
				// 位置の読込
				pos[m_nCntPos] = LoadPos(pFile);

				m_nCntPos++;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "INFOSET") == 0)// MOTIONSETなら
			{
				// モーション情報の読込
				apInfo[m_nCntInfo] = LoadPatternInfo(pFile);

				m_nCntInfo++;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_SCRIPT") == 0)
			{
				pPattern->SetInfo(apInfo);
				pPattern->SetPos(pos);
				m_nCntInfo = 0;
				break;
			}
		}
		else
		{
			// 文字列の初期化
			cData1[0] = { NULL };

			if (cData[0] == '#')// #なら
			{
				// コメントを読み飛ばす
				m_pLoadTxt->SkipComment(pFile);
			}
		}
	}
}

//====================================================
// 衝撃波のパターンの詳細読込処理
//====================================================
CShockInfo* CLoadShock::LoadPatternInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	char cData2[16] = { NULL };
	int nFream = 0, nLife = 0, nVanish = 0;
	float fWidth = 0.0f, fHeight = 0.0f, fRadiuse = 0.0f, fSpeed = 0.0f;
	bool bCulling = false, bCollision = false;
	CShockInfo* pInfo = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "FREAM") == 0)// FREAMなら
			{
				// =の読み飛ばし
				m_pLoadTxt->SkipEqual(pFile);

				nFream = m_pLoadTxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "VANISH") == 0)// VANISHなら
			{
				// =の読み飛ばし
				m_pLoadTxt->SkipEqual(pFile);

				nVanish = m_pLoadTxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "LIFE") == 0)// LIFEなら
			{
				// =の読み飛ばし
				m_pLoadTxt->SkipEqual(pFile);

				nLife = m_pLoadTxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "WIDTH") == 0)// WIDTHなら
			{
				// =の読み飛ばし
				m_pLoadTxt->SkipEqual(pFile);

				fWidth = m_pLoadTxt->LoadFloat(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "HEIGHT") == 0)// HEIGHTなら
			{
				// =の読み飛ばし
				m_pLoadTxt->SkipEqual(pFile);

				fHeight = m_pLoadTxt->LoadFloat(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "RADIUS") == 0)// RADIUSなら
			{
				// =の読み飛ばし
				m_pLoadTxt->SkipEqual(pFile);

				fRadiuse = m_pLoadTxt->LoadFloat(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "SPEED") == 0)// SPEEDなら
			{
				// =の読み飛ばし
				m_pLoadTxt->SkipEqual(pFile);

				fSpeed = m_pLoadTxt->LoadFloat(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "CULLING") == 0)// CULLINGなら
			{
				// 空白の読み飛ばし
				m_pLoadTxt->SkipBlank(pFile);

				// 文字列の読込
				m_pLoadTxt->LoadPath(pFile, cData2);

				if (strcmp(&cData2[0], "TRUE") == 0 || strcmp(&cData2[0], "true") == 0)
				{
					bCulling = true;
				}

				// 文字列の初期化
				cData1[0] = { NULL };
				cData2[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "COLLISION") == 0)// COLLISIONなら
			{
				// 空白の読み飛ばし
				m_pLoadTxt->SkipBlank(pFile);

				// 文字列の読込
				m_pLoadTxt->LoadPath(pFile, cData2);

				if (strcmp(&cData2[0], "TRUE") == 0 || strcmp(&cData2[0], "true") == 0)
				{
					bCollision = true;
				}

				// 文字列の初期化
				cData1[0] = { NULL };
				cData2[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_INFOSET") == 0)
			{
				// 生成処理
				pInfo = CShockInfo::Create(nFream, nVanish, nLife, fWidth, fHeight, fRadiuse, fSpeed, bCulling, bCollision);

				break;
			}
		}
		else
		{
			// 文字列の初期化
			cData1[0] = { NULL };

			if (cData[0] == '#')// #なら
			{
				// コメントを読み飛ばす
				m_pLoadTxt->SkipComment(pFile);
			}
		}
	}
	return pInfo;
}

//====================================================
// 位置の読込処理
//====================================================
D3DXVECTOR3 CLoadShock::LoadPos(FILE* pFile)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	float afPos[3] = { 0.0f };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "POS") == 0)// MAX_NUMなら
			{
				// =の読み飛ばし
				m_pLoadTxt->SkipEqual(pFile);

				// 少数の読込
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					afPos[nCnt] = m_pLoadTxt->LoadFloat(pFile);
				}

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_POSSET") == 0)
			{
				pos = D3DXVECTOR3(afPos[0], afPos[1], afPos[2]);

				break;
			}
		}
		else
		{
			// 文字列の初期化
			cData1[0] = { NULL };

			if (cData[0] == '#')// #なら
			{
				// コメントを読み飛ばす
				m_pLoadTxt->SkipComment(pFile);
			}
		}
	}
	return pos;
}