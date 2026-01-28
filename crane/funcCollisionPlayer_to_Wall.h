//====================================================
//
// 壁とプレイヤーの当たり判定　[funcCollisionPlayer_to_Wall.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _FUNCCOLLISIONPLAYER_TO_WALL_H_
#define _FUNCCOLLISIONPLAYER_TO_WALL_H_

// インクルード
#include "function.h"

// 壁とプレイヤーの当たり判定クラス
class CFuncCollisionPlayerToWall :public CFunctionBase
{
public:

	CFuncCollisionPlayerToWall() {};
	~CFuncCollisionPlayerToWall() {};

	void Init(void)override {};
	void Uninit(void)override {};
	void Update(void)override;
};
#endif
