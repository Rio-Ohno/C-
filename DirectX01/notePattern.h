//====================================================
//
// 音符の出現パターン情報[notePattern.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _NOTEPATTERN_H_
#define _NOTEPATTERN_H_

// インクルード
#include"main.h"

// マクロ定義
#define NUM_PATTERN_NOTE (5)
#define NUM_NOTE (10)

// 音符の位置情報
class CNotePos
{
public:

	CNotePos();
	~CNotePos();

	D3DXVECTOR3 GetPos(void);

	static CNotePos* Create(float posX, float posY, float posZ);

private:

	float m_PosX;		// 位置(X軸)
	float m_PosY;		// 位置(Y軸)
	float m_PosZ;		// 位置(Z軸)
};

// 音符のパターン情報
class CNoteInfo
{
public:

	CNoteInfo();
	~CNoteInfo();

	void Uninit(void);

	void SetNotePos(CNotePos** pNotePos);

	CNotePos** GetNotePos(void) { return m_apPos; };
	int GetNum(void) { return m_nNum; };

	static CNoteInfo* Create(int nNum);

private:

	CNotePos* m_apPos[NUM_NOTE];
	int m_nNum;			// 音符の数
};

// パターン情報
class CNotePattern
{
public:

	CNotePattern();
	~CNotePattern();

	void Uninit(void);

	void SetNoteInfo(CNoteInfo** pNoteInfo);
	void SetMaxNum(int nMaxNum) { m_nMaxNum = nMaxNum; };
	void SetNumInfo(int nNumInfo) { m_nNumInfo = nNumInfo; };

	CNoteInfo** GetNoteInfo(void) { return m_apInfo; };
	int GetMaxNum(void) { return m_nMaxNum; };
	int GetNumInfo(void) { return m_nNumInfo; };

	static CNotePattern* Create(const int nMaxNum);

private:

	CNoteInfo* m_apInfo[NUM_PATTERN_NOTE];
	static int m_nMaxNum;	// 音符の最大数
	static int m_nNumInfo;
};
#endif // !_NOTEPATTERN_H_