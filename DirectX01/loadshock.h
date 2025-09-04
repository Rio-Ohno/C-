//====================================================
// 
// 波のパターン読込処理 [loadshock.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _LOADSHOCK_H_
#define _LOADSHOCK_H_

// インクルード
#include"main.h"
#include"loadtxt.h"

// マクロ定義
#define SHOCK_PATTERN_NUM (3)
#define SHOCK_NUM (16)

// 衝撃波の情報クラス
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
	int m_nFream;		// 生成間隔フレーム
	int m_nVanish;		// 消滅フレーム
	int m_nLife;		// 寿命
	float m_fWidth;		// 幅
	float m_fHeight;	// 高さ
	float m_fRadius;	// 半径
	float m_fSpeed;		// スピード
	bool m_bCulling;	// カリングするかどうか
	bool m_bCollision;	// 当たり判定をとるかどうか
};

// 衝撃波のパターンクラス
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

// 衝撃波のパターン読込クラス
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