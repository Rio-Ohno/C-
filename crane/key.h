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
#include<vector> 

// パーツのキークラス
class CKEY
{
public:
	CKEY();
	~CKEY();

	typedef enum
	{
		AXIS_X=0,
		AXIS_Y,
		AXIS_Z,
		AXIS_MAX
	}AXIS;

	static CKEY* Create(float fposX, float fposY, float fposZ, float frotX, float frotY, float frotZ);
	float GetPos(int Axis);
	float GetRot(int Axis);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	
private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
};

// キー情報のクラス
class CKeyInfo
{
public:
	CKeyInfo();
	~CKeyInfo();

	static CKeyInfo* Create(int m_nFream);
	void SetKey(std::vector<CKEY*> pKey);
	std::vector<CKEY*> GetKey(void) { return m_apKey; };
	int GetFream(void) { return m_nFream; };
	void Uninit(void);

private:
	std::vector<CKEY*> m_apKey;
	int m_nFream;		// かかるフレーム
};

// モーション情報クラス
class CInfo
{
public:
	CInfo();
	CInfo(const CInfo& other);
	~CInfo();

	void Uninit(void);

	static CInfo* Create(bool Loop,int nNumKey);

	void SetKeyInfo(std::vector<CKeyInfo*> pKeyInfo);

	CKeyInfo* GetKeyInfo(int indx) { return m_apKeyInfo[indx]; };
	std::vector<CKeyInfo*> GetKeyInfo(void) { return m_apKeyInfo; };
	int GetNumKey(void) { return m_nNumKey; };
	bool isLoop(void) { return m_bLoop; };

private:
	std::vector<CKeyInfo*> m_apKeyInfo;
	bool m_bLoop;
	int m_nNumKey;
};

#endif // !_KEY_H_
