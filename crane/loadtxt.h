//====================================================
//
// txt読込[loadtxt.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _LOADTXT_H_
#define _LOADTXT_H_

// インクルード
#include"main.h"
#include<stdio.h>
#include<vector>

// テキスト読込クラス
class CLoadtxt
{
public:
	CLoadtxt();
	~CLoadtxt();

	void SkipComment(FILE* pFile);
	void SkipEqual(FILE* pFile);
	void SkipBlank(FILE* pFile);
	int LoadInt(FILE* pFile);							
	float LoadFloat(FILE* pFile);			
	char* LoadPath(FILE* pFile, char* cData2);
	char* LoadPath(FILE* pFile);
	std::vector<char*> LoadPath(FILE* pFile, std::vector<char*> cVector);
};
#endif // !_LOADTXT_H_
