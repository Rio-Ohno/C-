//====================================================
//
// �����̓Ǎ� [loadnote.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _LOADNOTE_H_
#define _LOADNOTE_H_

// �C���N���[�h
#include"main.h"
#include"loadtxt.h"
#include"notePattern.h"

// �����̏��Ǎ��N���X
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
