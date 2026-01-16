//====================================================
//
// 敵の重力処理[funcEnemyGravity.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _FUNCENEMYGRAVITY_H_
#define _FUNCENEMYGRAVITY_H_

// インクルード
#include "function.h"

// 敵とプレイヤーの当たり判定クラス
class CFuncEnemyGaravity :public CFunctionBase
{
public:

	CFuncEnemyGaravity() {};
	~CFuncEnemyGaravity() {};

	void Init(void)override {};
	void Uninit(void)override {};
	void Update(void)override;
};
#endif
