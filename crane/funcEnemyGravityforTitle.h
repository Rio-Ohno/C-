//====================================================
// 
// 敵の重力判定(タイトル用)[funcEnemyGravityforTitle.h]
// Author: Rio Ohno
// 
//====================================================

#ifndef _FUNCENEMYGRAVITYFORTITLE_H_
#define _FUNCENEMYGRAVITYFORTITLE_H_

// インクルード
#include "function.h"

class CFuncTitleEnemyGravity :public CFunctionBase
{
public:
	CFuncTitleEnemyGravity() {};
	~CFuncTitleEnemyGravity() {};

	void Init(void) {};
	void Uninit(void) {};
	void Update(void);
};
#endif // !_FUNCENEMYGRAVITYFORTITLE_H_