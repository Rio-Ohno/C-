//====================================================
// 
// ゲットホールとエネミーの当たり判定 [funcCollisionHole_to_Enemy.h]
// Author: Rio Ohno
// 
//====================================================
#ifndef _FUNCCOLLISIONHOLE_TO_ENEMY_H_
#define _FUNCCOLLISIONHOLE_TO_ENEMY_H_

// インクルード
#include "function.h"

class CFuncCollisionHoleToEnemy :public CFunctionBase
{
public:

	CFuncCollisionHoleToEnemy() {};
	~CFuncCollisionHoleToEnemy() {};

	void Init(void) {};
	void Uninit(void) {};
	void Update(void);
};
#endif // !_FUNCCOLLISIONHOLE_TO_ENEMY_H_