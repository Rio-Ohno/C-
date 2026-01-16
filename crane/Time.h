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
#include <vector>
#include <memory>
#include"object.h"
#include"Number.h"

// 前方宣言
class CNumber;
class CObject2D;
class CTimeBase;

// -------------------------------------------------------
// タイムクラス
// -------------------------------------------------------
class CTimeManager :public CObject
{
public:

	// 表示タイプ
	typedef enum
	{
		DISPLAY_MINSEC = 0,// 分秒
		DISPLAY_SECOND,	// 秒
		DISPLAY_MAX
	}DISPLAY;

	// カウント方式
	typedef enum
	{
		CNT_UP = 0,		// カウントアップ
		CNT_DOWN,		// カウントダウン
		CNT_MAX
	}CNT;

	CTimeManager(int nPriority = 7);
	~CTimeManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	int GetFream(void) { return m_nFream; }
	bool GetFinish(void) { return m_bFinish; }

	// フレーム関連
	void SetFream(int nFream) { m_nFream = nFream; }
	void AddFream(int nAdd) { m_nFream += nAdd; }

	// 一時停止関連
	void Play(void) { m_bStop = false; }
	void Stop(void) { m_bStop = true; }

	// テクスチャの割当
	void BindNumTextere(int texIndx);
	void BindColonTexture(int texIndx);

	// その他設定
	void SetColor(D3DXCOLOR col);// 色

	static CTimeManager* Create(CNT countType, DISPLAY type, int nFream, int digit, D3DXVECTOR3 pos, float fWidth, float fHeight);

	// constexper
	static constexpr int MAX_DIGHT = 6;	// 最大桁数

private:
	DISPLAY m_type;	// 表示タイプ
	CNT m_cnt;		// カウント
	std::unique_ptr<CTimeBase> m_pTime;// タイムクラスへのポインタ
	int m_nFream;	// フレーム
	bool m_bFinish;	// 終了
	bool m_bStop;	// 一時停止
};

//**************************************************************************************************************:
// -------------------------------------------------------
// タイムクラス（表示用クラス）
// -------------------------------------------------------
class CTimeBase 
{
public:

	CTimeBase();
	virtual ~CTimeBase() {};

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void) {};
	virtual void Draw(void);
	virtual void BindColonTexture(int texIndex) = 0;
	virtual void SetNumber(int nNowFream) = 0;

	void BindNumTexture(int texIndex);
	void SetColor(D3DXCOLOR col);

	// ゲッター
	std::vector<CNumber*> GetNumber(void)const { return m_pNumber; }
	D3DXVECTOR3 GetPos(void)const { return m_pos; }
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(m_fWidth, m_fHeight); }
	int GetNumNumber(void) { return m_nNumNum; }

	// セッター
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetNumNumber(int nNumNumber) { m_nNumNum = nNumNumber; }
	void SetSize(D3DXVECTOR2 size) { m_fWidth = size.x; m_fHeight = size.y; }


private:

	std::vector<CNumber*> m_pNumber;	// ナンバーのポインタ
	D3DXVECTOR3 m_pos;					// 位置
	int m_nNumNum;						// 桁数
	float m_fWidth;						// 幅
	float m_fHeight;					// 高さ

};

// -------------------------------------------------------
// 分秒バージョン
// -------------------------------------------------------
class CTimeMinSec :public CTimeBase
{
public:
	CTimeMinSec();
	~CTimeMinSec();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindColonTexture(int texIndex);

	void SetNumber(int nNowFream);

private:

	// constexpr
	static constexpr int NUM_UNIT = 2;
	static constexpr int MINIT = 3600;
	static constexpr int SECOND = 60;

	CObject2D* m_pObject2D; // コロン分 
	int m_nTime[NUM_UNIT];	// 表示用タイム
};

// -------------------------------------------------------
// 秒バージョン
// -------------------------------------------------------
class CTimeSecond :public CTimeBase
{
public:
	CTimeSecond();
	~CTimeSecond();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindColonTexture(int texIndex) {};

	void SetNumber(int nNowFream);

private:
	int m_nTime;			// 表示用タイム
};

#endif // !_TIME_H_