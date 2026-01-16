//====================================================
//
// 敵とプレイヤーの当たり判定　[funcCollisionPlayer_to_Enemy.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _FUNCCOLLISIONPLAYER_TO_ENEMY_H_
#define _FUNCCOLLISIONPLAYER_TO_ENEMY_H_

// インクルード
#include "function.h"

// 敵とプレイヤーの当たり判定クラス
class CFuncCollisionPlayerToEnemy:public CFunctionBase
{
public:

	CFuncCollisionPlayerToEnemy() {};
	~CFuncCollisionPlayerToEnemy() {};

	void Init(void)override {};
	void Uninit(void)override {};
	void Update(void)override;

	void SetState(void);
};
#endif