//====================================================
//
// 敵の重力処理(ゲームシーン用)[funcEnemyGravityforGame.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _FUNCENEMYGRAVITY_H_
#define _FUNCENEMYGRAVITY_H_

// インクルード
#include "function.h"

// 敵の重力処理クラス
class CFuncGameEnemyGaravity :public CFunctionBase
{
public:

	CFuncGameEnemyGaravity() {};
	~CFuncGameEnemyGaravity() {};

	void Init(void)override {};
	void Uninit(void)override {};
	void Update(void)override;
};
#endif
