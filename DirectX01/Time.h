//====================================================
// 
// タイマー処理[Time.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _TIME_H_
#define _TIME_H_

// インクルード
#include"main.h"
#include"object.h"
#include"Number.h"

// マクロ定義
#define MAX_DIGIT (3)

// タイムクラス
class CTime:public CObject
{
public:

	typedef enum
	{
		TYPE_CNTUP = 0,//ストップウォッチ
		TYPE_CNTDOWN,//タイマー
		TYPE_MAX
	}TYPE;

	CTime();
	~CTime();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool GetTimeOver(void) { return m_bTimeOver; };
	void SetPos(D3DXVECTOR3 pos) {};
	void SetRot(D3DXVECTOR3 rot) {};
	void SetColor(D3DXCOLOR col);
	void BindTexIndx(int indx);
	void Stop(void) { m_bPasses = false; };
	void Passes(void) { m_bPasses = true; };

	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3(); };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CTime* Create(TYPE type, int nMax,int digit, D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	void CntUP(void);
	void CntDown(void);
	void SetTime(void);

	CNumber* m_apNumber[6];
	TYPE m_type;
	int m_nTimeLim;
	int m_nTime[3];
	int m_nDigit;
	int m_nCntFrame;
	bool m_bTimeOver;
	bool m_bPasses;
};

#endif // !_TIME_H_