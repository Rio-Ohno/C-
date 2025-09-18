//====================================================
//
// 音符の読込 [loadnote.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _LOADNOTE_H_
#define _LOADNOTE_H_

// インクルード
#include"main.h"
#include"loadtxt.h"
#include"notePattern.h"

// 音符の情報読込クラス
class CLoadNote
{
public:
	CLoadNote();
	~CLoadNote();

	void LoadScript(const char* pFilename, CNotePattern* pNotePattern);
	void LoadPattern(FILE* pFile, CNotePattern* pNotePattern);
	CNoteInfo* LoadInfo(FILE* pFile);
	CNotePos* LoadPos(FILE* pFile);

	static void Load(const char* pFilename, CNotePattern* pNotePattern);

private:
	static CLoadtxt* m_LoadTxt;

	int m_nInfoCount;
	int m_nPosCount;
};

#endif // !_LOADNOTE_H_
