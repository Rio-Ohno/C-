//====================================================
// 
// モーション情報読込クラス[loadmotion.cpp]
// Author: Rio Ohno
// 
//====================================================

// インクルード
#include "loadmotion.h"
#include "loadtxt.h"
#include "motion.h"
#include "model.h"
#include "key.h"
#include <stdio.h>
#include <string.h>

// 静的メンバ変数
CLoadtxt* CLoadMotion::m_pLoadtxt = nullptr;

//====================================================
// コンストラクタ
//====================================================
CLoadMotion::CLoadMotion()
{
	// 値をクリア,初期化
	m_pLoadtxt = { nullptr };		// テキスト読込へのポインタ
	m_nNumParts = 0;				// パーツ数
	m_nModelCount = 0;
	m_nKeyCount = 0;				// キーのカウンタ
	m_nKeyInfoCount = 0;			// キー情報のカウンタ
	m_nInfoCount = 0;				// モーション情報のカウンタ
	m_fJump = 0.0f;					// ジャンプ量
	m_fSpeed = 0.0f;				// スピード
	m_fRadiusShaow = 0.0f;			// 影の半径
}

//====================================================
// デストラクタ
//====================================================
CLoadMotion::~CLoadMotion()
{
	// なし
}

//====================================================
// スクリプトの最初の読込
//====================================================
void CLoadMotion::LoadMotionTXT(const char* pFileName, CMotion* pMotion)
{
	char cData[2] = { NULL };
	char cData1[NUM_CHAR] = { NULL };

	// 外部ファイルを開く
	FILE* pFile = fopen(pFileName, "r");

	// 外部ファイル情報がないなら
	if (pFile == nullptr)
	{
		return;
	}

	// メモリの確保
	m_pLoadtxt = new CLoadtxt;

	while (1)
	{
		fgets(cData, 2, pFile);

		if (*cData != '#')
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "SCRIPT") == 0)// SCRIPTなら
			{
				// コメントを読み飛ばす
				m_pLoadtxt->SkipComment(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
				break;
			}
		}
		else
		{
			// コメントを読み飛ばす
			m_pLoadtxt->SkipComment(pFile);

			// 文字列の初期化
			cData1[0] = { NULL };
		}
	}

	// 続きを読込む
	LoadMotion(pFile, pMotion);
	fclose(pFile);

	if (m_pLoadtxt != NULL)// 中身があるなら
	{
		// メモリの開放
		delete m_pLoadtxt;
		m_pLoadtxt = NULL;
	}
}

//====================================================
// スクリプトの読込
//====================================================
void CLoadMotion::LoadMotion(FILE* pFile, CMotion* pMotion)
{
	char cData[2] = { NULL };
	char cData1[NUM_CHAR] = { NULL };
	int nData = 0;
	std::vector<CInfo*> apInfo;
	std::vector<char*> ModelPath;

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "NUM_MODEL") == 0)// NUM_MODELなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の取得
				nData = m_pLoadtxt->LoadInt(pFile);

				// パーツモデル数の設定
				pMotion->SetNumModel(nData);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "MODEL_FILENAME") == 0)// MODEL_FILENAMEなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 文字列の取得
				char* path = m_pLoadtxt->LoadPath(pFile);
				ModelPath.push_back(path);

				// パスの設定
				m_PartPath = ModelPath;

				// パーツのインデックスカウント
				++m_nKeyCount;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "CHARACTERSET") == 0)// CHARACTERSETなら
			{
				// キャラクター情報の読込
				LoadCharacterInfo(pFile, pMotion);

				// カウンターの初期化
				m_nKeyCount = 0;

				//文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "MOTIONSET") == 0)// MOTIONSETなら
			{
				// モーション情報の読込
				apInfo.push_back(LoadInfo(pFile));

				++m_nInfoCount;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_SCRIPT") == 0)
			{
				pMotion->SetInfo(apInfo);
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
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}

	for (auto Path : ModelPath)
	{
		delete Path;
	}
	ModelPath.clear();
}

//====================================================
// キャラクター情報の読込
//====================================================
void CLoadMotion::LoadCharacterInfo(FILE* pFile, CMotion* pMotion)
{
	char cData[2] = { NULL };
	char cData1[NUM_CHAR] = { NULL };
	int nData = 0;
	float fData = 0.0f;
	std::vector<CModel*> apModel;

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "NUM_PARTS") == 0)// NUM_PARTSなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				nData = m_pLoadtxt->LoadInt(pFile);

				// パーツ数の設定
				m_nNumParts = nData;

				// 文字列の初期化
				cData[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "MOVE") == 0)// MOVEなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				fData = m_pLoadtxt->LoadFloat(pFile);

				// 移動量の設定
				m_fSpeed = fData;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "JUMP") == 0)// JUMPなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				fData = m_pLoadtxt->LoadFloat(pFile);

				// 移動量の設定
				m_fJump = fData;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "RADIUS") == 0)// RADIUSなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				fData = m_pLoadtxt->LoadFloat(pFile);

				// 移動量の設定
				m_fRadiusShaow = fData;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "PARTSSET") == 0)// PARTSETなら
			{
				// パーツ情報の読込
				apModel.push_back(LoadModel(pFile, pMotion));

				pMotion->SetModel(apModel);

				// 文字列の初期化
				cData1[0] = { NULL };

				++m_nModelCount;
			}
			else if (strcmp(&cData1[0], "END_CHARACTERSET") == 0)// END_CHARACTERSETなら
			{
				// 文字列の初期化
				cData1[0] = { NULL };

				m_nModelCount = 0;
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
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
}

//====================================================
// モデル情報の読込
//====================================================
CModel* CLoadMotion::LoadModel(FILE* pFile, CMotion* pMotion)
{
	char cData[2] = { NULL };
	char cData1[NUM_CHAR] = { NULL };
	int nParent = 0;
	int nData = 0;
	D3DXVECTOR3 pos = {};
	D3DXVECTOR3 rot = {};
	CModel* pModel = nullptr;

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "INDEX") == 0)// INDEXなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				nData = m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "PARENT") == 0)// PARENTなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				nParent = m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "POS") == 0)// POSなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				pos.x = m_pLoadtxt->LoadFloat(pFile);
				pos.y = m_pLoadtxt->LoadFloat(pFile);
				pos.z = m_pLoadtxt->LoadFloat(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "ROT") == 0)// ROTなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				rot.x = m_pLoadtxt->LoadFloat(pFile);
				rot.y = m_pLoadtxt->LoadFloat(pFile);
				rot.z = m_pLoadtxt->LoadFloat(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_PARTSSET") == 0)// END_PARTSSETなら
			{
				// 文字列の初期化
				cData1[0] = { NULL };

				// 格納用モデルポインタ
				CModel* pParent = nullptr;

				// モデルの生成処理
				pModel = CModel::Create(pos, rot, (const char*)m_PartPath[m_nModelCount]);

				// 親モデルがあるなら
				if (nParent > -1 && nParent < m_nModelCount)
				{
					// モデルの取得
					pParent = pMotion->GetModel()[nParent];

					// インデックスの保存
					pModel->SetParentIndx(nParent);
				}

				// 親モデルの設定
				pModel->CModel::SetParent(pParent);

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
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
	return pModel;
}

//====================================================
// モーション情報の取得
//====================================================
CInfo* CLoadMotion::LoadInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[NUM_CHAR] = { NULL };
	int nNumKay = 0;
	bool bLoop = false;
	CInfo* pInfo = { nullptr };
	std::vector<CKeyInfo*> apKeyInfo;

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "LOOP") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				bLoop = (bool)m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "NUM_KEY") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				nNumKay = m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "KEYSET") == 0)
			{
				// キー情報の読込
				apKeyInfo.push_back(LoadKeyInfo(pFile));

				++m_nKeyInfoCount;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_MOTIONSET") == 0)
			{
				pInfo = CInfo::Create(bLoop, nNumKay);

				pInfo->SetKeyInfo(apKeyInfo);

				m_nKeyInfoCount = 0;

				// 文字列の初期化
				cData1[0] = { NULL };
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
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
	return pInfo;
}

//====================================================
// キー情報の取得
//====================================================
CKeyInfo* CLoadMotion::LoadKeyInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	int nFream = 0;
	std::vector<CKEY*> apKey;
	CKeyInfo* pKeyInfo = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "FRAME") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				nFream = m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "KEY") == 0)
			{
				// キーの読込
				apKey.push_back(LoadKey(pFile));

				++m_nKeyCount;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_KEYSET") == 0)
			{
				// キー情報の生成
				pKeyInfo = CKeyInfo::Create(nFream);

				// キーの設定
				pKeyInfo->SetKey(apKey);

				m_nKeyCount = 0;

				// 文字列の初期化
				cData1[0] = { NULL };
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
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
	return pKeyInfo;
}

//====================================================
// キーの読込処理
//====================================================
CKEY* CLoadMotion::LoadKey(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[NUM_CHAR] = { NULL };
	float afPos[3] = {};
	float afRot[3] = {};
	CKEY* pKey = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "POS") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				for (int nCnt = 0; nCnt < 3; ++nCnt)
				{
					afPos[nCnt] = m_pLoadtxt->LoadFloat(pFile);
				}

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				for (int nCnt = 0; nCnt < 3; ++nCnt)
				{
					afRot[nCnt] = m_pLoadtxt->LoadFloat(pFile);
				}

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_KEY") == 0)
			{
				// キーの生成
				pKey = CKEY::Create(afPos[0], afPos[1], afPos[2], afRot[0], afRot[1], afRot[2]);

				// 文字列の初期化
				cData1[0] = { NULL };

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
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}

	return pKey;
}

//====================================================
// 読込した情報を返す
//====================================================
CMotion* CLoadMotion::Load(const char* pFileName, CMotion* pMotion)
{
	CLoadMotion* pLoad = nullptr;

	pLoad = new CLoadMotion;

	// テキスト読込
	pLoad->LoadMotionTXT(pFileName, pMotion);

	// メモリの開放
	delete pLoad;
	pLoad = nullptr;

	return pMotion;
}