//====================================================
//
// �����̏o���p�^�[�����[notePattern.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _NOTEPATTERN_H_
#define _NOTEPATTERN_H_

// �C���N���[�h
#include"main.h"

// �}�N����`
#define NUM_PATTERN_NOTE (3)
#define NUM_NOTE (10)

// �����̈ʒu���
class CNotePos
{
public:

	CNotePos();
	~CNotePos();

	D3DXVECTOR3 GetPos(void);

	static CNotePos* Create(float posX, float posY, float posZ);

private:

	float m_PosX;		// �ʒu(X��)
	float m_PosY;		// �ʒu(Y��)
	float m_PosZ;		// �ʒu(Z��)
};

// �����̃p�^�[�����
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
	int m_nNum;			// �����̐�
};

// �p�^�[�����
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
	static int m_nMaxNum;	// �����̍ő吔
	static int m_nNumInfo;
};
#endif // !_NOTEPATTERN_H_