//====================================================
//
// モーションのキー[key.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _KEY_H_
#define _KEY_H_

// インクルード
#include"main.h"

// マクロ定義
#define MAX_KEY (20)
#define MAX_KEY_INFO (10)

// パーツのキー情報クラス
class CKEY
{
public:
	CKEY();
	~CKEY();

	static CKEY* Create(float fposX, float fposY, float fposZ, float frotX, float frotY, float frotZ);
	float GetPos(const char* Axis);
	float GetRot(const char* Axis);
	
private:
	float m_fposX;		// 位置(X軸)
	float m_fposY;		// 位置(Y軸)
	float m_fposZ;		// 位置(Z軸)
	float m_frotX;		// 向き(X軸)
	float m_frotY;		// 向き(Y軸)
	float m_frotZ;		// 向き(Z軸)
};

// キー情報のクラス
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
	int m_nFream;		// かかるフレーム
};

// モーション情報クラス
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
