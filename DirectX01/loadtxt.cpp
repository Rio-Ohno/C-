//====================================================
//
// txt読込[loadtxt.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"loadtxt.h"
#include <stdlib.h>

//====================================================
// コンストラクタ
//====================================================
CLoadtxt::CLoadtxt()
{
	// なし
}

//====================================================
// デストラクタ
//====================================================
CLoadtxt::~CLoadtxt()
{
	// なし
}

//====================================================
// シャープ以降を飛ばす処理
//====================================================
void CLoadtxt::SkipComment(FILE* pFile)
{
	char cData[2] = {};
	char cData1[128] = {};

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a)// 改行コードではないなら
		{
			strcat(cData1, cData);
		}
		else
		{
			break;
		}
	}
}

//====================================================
//  = を読み飛ばす処理
//====================================================
void CLoadtxt::SkipEqual(FILE* pFile)
{
	int nData;
	nData = fgetc(pFile);
	nData = fgetc(pFile);
	nData = fgetc(pFile);
}

//====================================================
// 空白を読み飛ばす処理
//====================================================
void CLoadtxt::SkipBlank(FILE* pFile)
{
	char nData;
	nData = (char)fgetc(pFile);

	int i = 0;
}

//====================================================
// 整数を読み込む処理
//====================================================
int CLoadtxt::LoadInt(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	int nData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			nData = atoi(cData1);// char型からint型へ
			cData1[0] = { NULL };
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return nData;
}

//====================================================
// 浮動小数を読み込む処理
//====================================================
float CLoadtxt::LoadFloat(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	float fData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			fData = (float)atof(cData1); // char型からdouble型->float型へ
			cData1[0] = { NULL };
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return fData;
}

//====================================================
// 文字列型を読み込む処理
//====================================================
char* CLoadtxt::LoadPath(FILE* pFile, char* cData2)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char filepath[32] = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != 0x23 && cData[0] != 0x20 && cData[0] != 0x09)// 改行 # 空白 tabじゃないなら
		{
			strcat(cData1, cData);
		}
		else
		{
			cData2 = cData1;
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return cData2;
}