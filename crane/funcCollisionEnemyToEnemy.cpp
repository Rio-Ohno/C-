//====================================================
// 
// “G“¯m‚Ì“–‚½‚è”»’è[funcCollisionEnemyToEnemy.cpp]
// Author: Rio Ohno
// 
//====================================================

// ƒCƒ“ƒNƒ‹[ƒh
#include "funcCollisionEnemyToEnemy.h"
#include "PrizeManager.h"
#include "enemy.h"
#include "collision.h"
#include "game.h"

//====================================================
// “G“¯m‚Ì“–‚½‚è”»’è
//====================================================
void CFuncCollisionEnemyToEnemy::Update(void)
{
	CPrizemanager* Prize = CGame::GetPrizeManager();
	CCollision* pCollision = new CCollision;

	for (size_t self = 0; self < Prize->GetPrizeList().size(); self++)
	{
		// ”»’è‚ğ‚Æ‚é“G
		CEnemyBase* pSelf = Prize->GetPrizeList()[self];

		for (size_t other = self + 1; other < Prize->GetPrizeList().size(); other++)
		{
			// ”»’è‚ğ‚Æ‚é“G
			CEnemyBase* pOther = Prize->GetPrizeList()[other];

			// ‹——£Zo
			D3DXVECTOR3 diff = pSelf->GetPos() - pOther->GetPos();
			float fDist = D3DXVec3Length(&diff);

			float fMinDistance = pSelf->GetCollider()->GetMinDistance() + pOther->GetCollider()->GetMinDistance();

			// “–‚½‚è”»’è
			if (fDist < fMinDistance * 0.5f)
			{
				float fPenetration = (fMinDistance - fDist) * 0.5f;

				D3DXVECTOR3 Vec;
				D3DXVec3Normalize(&Vec, &diff);

				// ˆÚ“®—ÊXV
				pSelf->SetMove((Vec * fPenetration) * 0.05f);
				pOther->SetMove(-(Vec * fPenetration) * 0.05f);
			}
		}
	}
	delete pCollision;
}