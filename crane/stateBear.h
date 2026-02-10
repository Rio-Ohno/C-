//====================================================
// 
// 熊専用ステート　[stateBear.h]
// Author: Rio Ohno
// 
//====================================================
#ifndef _STATEBEAR_H_
#define _STATEBEAR_H_

// インクルード
#include "stateEnemy.h"

// ニュートラル状態クラス
class CBearStateNeutral :public CStateEnemyBase
{
public:
	CBearStateNeutral();
	~CBearStateNeutral() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);

private:
	// constexpr
	static constexpr int FREAM = 300;	// フレーム数
	static constexpr float GRAVITY = 0.9f;			// 重力

	int m_nCntFream;	// フレームカウンタ
};

// 歩く状態クラス
class CBearStateWalk :public CStateEnemyBase
{
public:
	CBearStateWalk();
	~CBearStateWalk() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);

private:

	// constexpr
	static constexpr int FREAM = 150;				// フレーム数
	static constexpr int DIVI_ROT = 8;				// 逃げる方位(8方位)
	static constexpr float GRAVITY = 0.9f;			// 重力
	static constexpr float WALK_SPEED = 0.025f;		// 歩くときのスピード
	static constexpr float MOVE_DECAY = 0.09f;		// 移動量の減衰係数

	float m_rotY;			// 向き
	int m_nCntFream;		// フレームカウンタ

};

// 逃げる状態クラス
class CBearStateRun :public CStateEnemyBase
{
public:
	CBearStateRun();
	~CBearStateRun() {};

	void Init(void);
	void Uninit(void) {};
	void Update(void);
private:

	// constexpr
	static constexpr int DIVI_ROT = 8;				// 逃げる方位(8方位)
	static constexpr float RUN_SPEED = 0.05f;		// 逃げるときのスピード
	static constexpr float RANGE_AWARENESS = 30.0f;	// 気が付く範囲
	static constexpr float GRAVITY = 0.9f;			// 重力

	float m_rotY;		// 逃げる向き
};
#endif // !_STATEBEAR_H_