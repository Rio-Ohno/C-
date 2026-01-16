//====================================================
// 
//  当たり判定 [collision.h]
// Author：Rio Ohno
// 
//====================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

// インクルード
#include "main.h"
#include "collider.h"

// ---------------------------------------------------
// 当たり判定のクラス
// ---------------------------------------------------
class CCollision
{
public:
	CCollision() {};
	~CCollision() {};

	HRESULT Init(void) {};
	void Uninit(void) {};
	
	bool CheckCollision(CColliderSphere* aSphere, CColliderSphere* bSphere);
	bool CheckEnterCollision(CColliderCylinder* pCylinder, CColliderSphere* pSphere);
};

#endif // !_COLLISION_H_
