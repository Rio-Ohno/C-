//====================================================
//
// 音符の読込 [loadnote.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"loadnote.h"

// 静的メンバ変数
CLoadtxt* CLoadNote::m_LoadTxt = { NULL };

//====================================================
// コンストラクタ
//====================================================　
CLoadNote::CLoadNote()
{
	// 変数の初期化
	m_LoadTxt = { NULL };
	m_nInfoCount = 0;
	m_nPosCount = 0;
}

//====================================================
// デストラクタ　
//====================================================　
CLoadNote::~CLoadNote()
{
	// なし
}

//====================================================
// 冒頭読込
//====================================================　
void CLoadNote::LoadScript(const char* pFilename, CNotePattern* pNotePattern)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };

	// 外部ファイルを開く
	FILE* pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{
		// メモリの確保
		m_LoadTxt = new CLoadtxt;

		while (1)
		{
			fgets(cData, 2, pFile);

			if (*cData != '#')
			{
				strcat(cData1, cData);

				if (strcmp(&cData1[0], "SCRIPT") == 0)// SCRIPTなら
				{
					// コメントを読み飛ばす
					m_LoadTxt->SkipComment(pFile);

					// 文字列の初期化
					cData1[0] = { NULL };
					break;
				}
			}
			else
			{
				// コメントを読み飛ばす
				m_LoadTxt->SkipComment(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
		}

		// 続きを読込む
		LoadPattern(pFile, pNotePattern);
		fclose(pFile);
	}

	if (m_LoadTxt != NULL)// 中身があるなら
	{
		// メモリの開放
		delete m_LoadTxt;
		m_LoadTxt = NULL;
	}
}

//====================================================
// 全パターン情報の読込　
//====================================================　
void CLoadNote::LoadPattern(FILE* pFile, CNotePattern* pNotePattern)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	int nData = 0, NumInfo = 0;
	CNoteInfo* apInfo[NUM_PATTERN_NOTE] = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "MAX_NUM") == 0)// MAX_NUMなら
			{
				// =の読み飛ばし
				m_LoadTxt->SkipEqual(pFile);

				// 数値の取得
				nData = m_LoadTxt->LoadInt(pFile);

				// モデル数の設定
				pNotePattern->SetMaxNum(nData);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "NUM_INFO") == 0)// NUM_INFOなら
			{
				// =の読み飛ばし
				m_LoadTxt->SkipEqual(pFile);

				// 数値の取得
				NumInfo = m_LoadTxt->LoadInt(pFile);

				// パターン数の設定
				pNotePattern->SetNumInfo(NumInfo);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "INFOSET") == 0)// MOTIONSETなら
			{
				// モーション情報の読込
				apInfo[m_nInfoCount] = LoadInfo(pFile);

				m_nInfoCount++;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_SCRIPT") == 0)
			{
				pNotePattern->SetNoteInfo(apInfo);
				m_nInfoCount = 0;
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
				m_LoadTxt->SkipComment(pFile);
			}
		}
	}
}

//====================================================
// NoteInfoの読込　
//====================================================　
CNoteInfo* CLoadNote::LoadInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	int nNum = 0;
	CNotePos* apPos[NUM_NOTE] = { NULL };
	CNoteInfo* pInfo = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "NUM_NOTE") == 0)// MAX_NUMなら
			{
				// =の読み飛ばし
				m_LoadTxt->SkipEqual(pFile);

				// 数値の取得
				nNum = m_LoadTxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "POSSET") == 0)// MOTIONSETなら
			{
				// モーション情報の読込
				apPos[m_nPosCount] = LoadPos(pFile);

				m_nPosCount++;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_INFOSET") == 0)
			{
				pInfo = CNoteInfo::Create(nNum);

				pInfo->SetNotePos(apPos);

				m_nPosCount = 0;
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
				m_LoadTxt->SkipComment(pFile);
			}
		}
	}

	return pInfo;
}

//====================================================
// CNotePosの読込　
//====================================================　
CNotePos* CLoadNote::LoadPos(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	float afPos[3] = { 0.0f };
	CNotePos* pPos = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "POS") == 0)// MAX_NUMなら
			{
				// =の読み飛ばし
				m_LoadTxt->SkipEqual(pFile);

				// 少数の読込
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					afPos[nCnt] = m_LoadTxt->LoadFloat(pFile);
				}

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_POSSET") == 0)
			{
				pPos = CNotePos::Create(afPos[0], afPos[1], afPos[2]);

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
				m_LoadTxt->SkipComment(pFile);
			}
		}
	}
	return pPos;
}

//====================================================
// 読込開始処理
//====================================================　
void CLoadNote::Load(const char* pFilename, CNotePattern* pNotePattern)
{
	CLoadNote* load = NULL;

	// メモリの確保
	load = new CLoadNote;

	load->LoadScript(pFilename, pNotePattern);

	delete load;
	load = NULL;
}