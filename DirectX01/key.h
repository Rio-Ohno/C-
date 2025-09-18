//====================================================
//
// ���[�V�����̃L�[[key.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _KEY_H_
#define _KEY_H_

// �C���N���[�h
#include"main.h"

// �}�N����`
#define MAX_KEY (20)
#define MAX_KEY_INFO (10)

// �p�[�c�̃L�[���N���X
class CKEY
{
public:
	CKEY();
	~CKEY();

	static CKEY* Create(float fposX, float fposY, float fposZ, float frotX, float frotY, float frotZ);
	float GetPos(const char* Axis);
	float GetRot(const char* Axis);
	
private:
	float m_fposX;		// �ʒu(X��)
	float m_fposY;		// �ʒu(Y��)
	float m_fposZ;		// �ʒu(Z��)
	float m_frotX;		// ����(X��)
	float m_frotY;		// ����(Y��)
	float m_frotZ;		// ����(Z��)
};

// �L�[���̃N���X
class CKeyInfo
{
public:
	CKeyInfo();
	~CKeyInfo();

	static CKeyInfo* Create(int m_nFream);
	void SetKey(CKEY** pKey);
	CKEY** GetKey(void) { return m_apKey; };
	int GetFream(void) { return m_nFream; };
	void Uninit(void);

private:
	CKEY* m_apKey[MAX_KEY];
	int m_nFream;		// ������t���[��
};

// ���[�V�������N���X
class CInfo
{
public:
	CInfo();
	~CInfo();

	void Uninit(void);

	static CInfo* Create(bool Loop,int nNumKey);

	void SetKeyInfo(CKeyInfo** pKeyInfo);

	CKeyInfo* GetKeyInfo(int indx) { return m_apKeyInfo[indx]; };
	int GetNumKey(void) { return m_nNumKey; };
	bool isLoop(void) { return m_bLoop; };

private:
	CKeyInfo* m_apKeyInfo[MAX_KEY_INFO];
	bool m_bLoop;
	int m_nNumKey;
};

#endif // !_KEY_H_
