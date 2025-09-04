//====================================================
// 
// �g�̃p�^�[���Ǎ����� [loadshock.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _LOADSHOCK_H_
#define _LOADSHOCK_H_

// �C���N���[�h
#include"main.h"
#include"loadtxt.h"

// �}�N����`
#define SHOCK_PATTERN_NUM (3)
#define SHOCK_NUM (16)

// �Ռ��g�̏��N���X
class CShockInfo
{
public:
	CShockInfo();
	~CShockInfo();

	void SetFream(int nFream) { m_nFream = nFream; };
	void SetVanish(int nVanish) { m_nVanish = nVanish; };
	void SetLife(int nLife) { m_nLife = nLife; };
	void SetWidth(float fWidth) { m_fWidth = fWidth; };
	void SetHeight(float fHeight) { m_fHeight = fHeight; };
	void SetRadius(float fRadius) { m_fRadius = fRadius; };
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; };
	void SetCulling(bool bCulling) { m_bCulling = bCulling; };
	void SetCollision(bool bCollision) { m_bCollision = bCollision; };

	int GetFream(void) { return m_nFream; };
	int GetVanish(void) { return m_nVanish; };
	int GetLife(void) { return m_nLife; };
	float GetWidth(void) { return m_fWidth; };
	float GetHeight(void) { return m_fHeight; };
	float GetRadius(void) { return m_fRadius; };
	float GetSpeed(void) { return m_fSpeed; };
	bool GetCulling(void) { return m_bCulling; };
	bool GetCollision(void) { return m_bCollision; };

	static CShockInfo* Create(int nFream,int nVanish, int nLife, float fWidth, float fHeight, float fRadius, float fSpeed, bool bCulling, bool bCollision);

private:
	int m_nFream;		// �����Ԋu�t���[��
	int m_nVanish;		// ���Ńt���[��
	int m_nLife;		// ����
	float m_fWidth;		// ��
	float m_fHeight;	// ����
	float m_fRadius;	// ���a
	float m_fSpeed;		// �X�s�[�h
	bool m_bCulling;	// �J�����O���邩�ǂ���
	bool m_bCollision;	// �����蔻����Ƃ邩�ǂ���
};

// �Ռ��g�̃p�^�[���N���X
class CShockPattern
{
public:
	CShockPattern();
	~CShockPattern();

	void Uninit(void);

	void SetInfo(CShockInfo** ppInfo);
	void SetPos(D3DXVECTOR3* pos);
	void SetNumInfo(int nNumInfo) { m_nNumInfo = nNumInfo; };

	CShockInfo** GetInfo(void) { return m_apInfo; };
	D3DXVECTOR3* Getpos(void) { return m_pos; };
	int GetNumInfo(void) { return m_nNumInfo; };

private:
	static CShockInfo* m_apInfo[SHOCK_PATTERN_NUM];
	D3DXVECTOR3 m_pos[SHOCK_NUM];
	int m_nNumInfo;
};

// �Ռ��g�̃p�^�[���Ǎ��N���X
class CLoadShock
{
public:
	CLoadShock();
	~CLoadShock();

	static void Load(const char* FilePass, CShockPattern* pPattern);
	void LoadScript(const char* FilePass, CShockPattern* pPattern);
	void LoadPattern(FILE* pFile, CShockPattern* pPattern);
	CShockInfo* LoadPatternInfo(FILE* pFile);
	D3DXVECTOR3 LoadPos(FILE* pFile);

private:
	static CLoadtxt* m_pLoadTxt;
	int m_nCntInfo;
	int m_nCntPos;
};
#endif // !_LOADSHOCK_H_