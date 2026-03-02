//====================================================
// 
//  当たり判定の計算クラス [collision.h]
// Author：Rio Ohno
// 
//====================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

// インクルード
#include "main.h"
#include "collider.h"

// 当たり判定のクラス
class CCollision
{
public:
	CCollision() {};
	~CCollision() {};

	HRESULT Init(void) {};
	void Uninit(void) {};
	
	static bool CheckCollision(CColliderSphere* aSphere, CColliderSphere* bSphere);
	static bool CheckEnterCollision(CColliderCylinder* pCylinder, CColliderSphere* pSphere);
};

#endif // !_COLLISION_H_
