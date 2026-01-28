//====================================================
// 
// “G“¯m‚Ì“–‚½‚è”»’è[funcCollisionEnemyToEnemy.h]
// Author: Rio Ohno
// 
//====================================================
#ifndef  _FUNCCOLLISIONENEMYTOENEMY_H_
#define _FUNCCOLLISIONENEMYTOENEMY_H_

// ƒCƒ“ƒNƒ‹[ƒh
#include "function.h"

// “G“¯m‚Ì“–‚½‚è”»’è
class  CFuncCollisionEnemyToEnemy:public CFunctionBase
{
public:
	CFuncCollisionEnemyToEnemy() {};
	~CFuncCollisionEnemyToEnemy() {};

	void Init(void)override {};
	void Uninit(void)override {};
	void Update(void)override;

private:

};
#endif // ! _FUNCCOLLISIONENEMYTOENEMY_H_
