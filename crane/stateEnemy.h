//====================================================
//
// ステートエネミー　[stateEnemy.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _STATEENEMY_H_
#define _STATEENEMY_H_

// インクルード
#include "statebase.h"
#include "main.h"

// 前方宣言
class CEnemyBase;

// ステートエネミー基盤
class CStateEnemyBase :public CStateBase
{
public:

	typedef enum
	{
		STATE_NONE = 0,	// 何もしていない
		STATE_CAUGHT,	// 捕まる
		STATE_FALL,		// 落ちる
		STATE_DEATH,	// 死
		STATE_NEUTRAL,	// ニュートラル
		STATE_RUN,		// 逃げる
		STATE_MAX
	}STATE;

	CStateEnemyBase();
	CStateEnemyBase(STATE state);
	virtual~CStateEnemyBase() {};

	virtual void Init(void) override {};
	virtual void Uninit(void)override {};
	virtual void Update(void) override {};
	int GetStateID(void)const override { return m_stateID; };

	void SetEnemy(CEnemyBase* pEnemy) { m_pEnemy = pEnemy; }

protected:

	CEnemyBase* GetEnemy(void) { return m_pEnemy; }

private:
	CEnemyBase* m_pEnemy;
	STATE m_stateID;
};

// 何もしてない状態クラス
class CEnemyStateNone :public CStateEnemyBase
{
public:
	CEnemyStateNone():CStateEnemyBase(STATE_NONE) {};
	~CEnemyStateNone() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);
private:
	// constexpr

	static constexpr float GRAVITY = 0.9f;// 重力係数

};

// 捕まった状態クラス
class CEnemyStateCaught :public CStateEnemyBase
{
public:
	CEnemyStateCaught() :CStateEnemyBase(STATE_CAUGHT) {};
	~CEnemyStateCaught() {};

	void Init(void) {};
	void Uninit(void) {};
	void Update(void);
};

// 落ちてる状態クラス
class CEnemyStateFall:public CStateEnemyBase
{
public:
	CEnemyStateFall() :CStateEnemyBase(STATE_FALL) {};
	~CEnemyStateFall() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);
private:
	// constexpr

	static constexpr float GRAVITY = 0.003f;// 重力係数
	static constexpr float LANDING = 5.0f;	// 着地判定をする高さの上限
};

// 死んでる状態クラス
class CEnemyStateDeath :public CStateEnemyBase
{
public:
	CEnemyStateDeath() :CStateEnemyBase(STATE_DEATH) { m_nCntFream = 0; };
	~CEnemyStateDeath() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);

private:
	// constexpr
	static constexpr int VANISH_FREAM = 10;	// 消えるまでのフレーム
	static constexpr float GRAVITY = 0.5f;// 重力係数

	int m_nCntFream;	//　フレームカウンタ
};

//// ニュートラル状態クラス
//class CEnemyStateNeutral :public CStateEnemyBase
//{
//public:
//	CEnemyStateNeutral() :CStateEnemyBase(STATE_NEUTRAL) {};
//	~CEnemyStateNeutral() {};
//
//	void Init(void);
//	void Uninit(void);
//	void Update(void);
//};
//
//// 逃げる状態クラス
//class CEnemyStateRun :public CStateEnemyBase
//{
//public:
//	CEnemyStateRun() :CStateEnemyBase(STATE_RUN) {};
//	~CEnemyStateRun() {};
//
//	void Init(void);
//	void Uninit(void);
//	void Update(void);
//};
#endif // ! _STATEENEMY_H_