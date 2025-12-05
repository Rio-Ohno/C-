//====================================================
//
// ステートプレイヤー　[statePlayer.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _STATEPLAYER_H_
#define _STATEPLAYER_H_

// インクルード
#include "statebase.h"

// 前方宣言
class CPlayer;

// プレイヤーステート基盤クラス------------------------
class CStatePlayerBase :public CStateBase
{
public:

	typedef enum
	{
		STATE_NONE = 0,	// 何もしていない
		STATE_MOVE,		// 移動
		STATE_DOWN,		// 下がる
		STATE_GRAB,		// つかみ
		STATE_UP,		// 上がる
		STATE_RETURN,	// 戻る
		STATE_MAX
	}STATE;

	CStatePlayerBase() { m_stateID = (STATE)0; m_pPlayer = nullptr; };
	CStatePlayerBase(STATE state) { m_stateID = state; m_pPlayer = nullptr; };
	virtual ~CStatePlayerBase() {}

	virtual void Init(void) {};
	virtual void Uninit(void);
	virtual void Update(void) {};
	int GetStateID(void)const { return m_stateID; };

	void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; };

protected:

	CPlayer* GetPlayer(void) { return m_pPlayer; };

private:

	CPlayer* m_pPlayer;
	STATE m_stateID;
};

// 何もない状態クラス----------------------------------
class CStatePlayerNone :public CStatePlayerBase
{
public:
	CStatePlayerNone() :CStatePlayerBase(CStatePlayerBase::STATE_NONE) {};
	~CStatePlayerNone() {};

	void Init(void) {};
	void Uninit(void) {};
	void Update(void);
};


// 移動状態クラス--------------------------------------
class CStatePlayerMove :public CStatePlayerBase
{
public:
	CStatePlayerMove() :CStatePlayerBase(CStatePlayerBase::STATE_MOVE) {};
	~CStatePlayerMove() {};

	void Init(void) {};
	void Uninit(void) {};
	void Update(void);

private:
};

// 下がる状態クラス--------------------------------------
class CStatePlayerDown :public CStatePlayerBase
{
public:
	CStatePlayerDown();
	~CStatePlayerDown() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);

private:

	// constexpr
	static constexpr int LIFT_DOWN_FREAM = 120;		// リフトダウンにかけるフレーム

	int m_nCntFream;// フレームカウンタ
};

// つかみ状態クラス-------------------------------------
class CStatePlayerGrab :public CStatePlayerBase
{
public:
	CStatePlayerGrab();
	~CStatePlayerGrab() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);
private:

	// constexpr
	static constexpr int STOP_FREAM = 40;// つかんで止まってるフレーム

	int m_nCntFream;// フレームカウンタ
};

// 上がる状態クラス--------------------------------------
class CStatePlayerUP :public CStatePlayerBase
{
public:
	CStatePlayerUP();
	~CStatePlayerUP() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);

private:

	// constexpr
	static constexpr int LIFT_UP_FREAM = 120;		// リフトアップにかけるフレーム

	int m_nCntFream;// フレームカウンタ
};

// 戻る状態クラス
class CStatePlayerReturn :public CStatePlayerBase
{
public:
	CStatePlayerReturn();
	~CStatePlayerReturn() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);

private:

	// constexpr
	static constexpr int RETURN_FREAM = 40;			// 元に位置に戻るのにかけるフレーム

	int m_nCntFream;	// フレームカウンタ
	float m_fDifX;		// X軸の減らす値
	float m_fDifZ;		// Z軸の減らす値
};
#endif