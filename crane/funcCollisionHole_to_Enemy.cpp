//====================================================
// 
// ゲットホールとエネミーの当たり判定 [funcCollisionHole_to_Enemy.h]
// Author: Rio Ohno
// 
//====================================================

// インクルード
#include "funcCollisionHole_to_Enemy.h"
#include "game.h"
#include "hole.h"
#include "PrizeManager.h"
#include "stateEnemy.h"
#include "collision.h"

//====================================================
// 更新処理
//====================================================
void CFuncCollisionHoleToEnemy::Update(void)
{
	// 各情報取得
	CHole* pHole = CGame::GetHole();							// ゲットホール
	CPrizemanager* pPrizeManager = CGame::GetPrizeManager();	// プライズマネージャー
	CCollision* pCollision = new CCollision;					// 当たり判定

	if (pHole != nullptr && pPrizeManager != nullptr)
	{
		for (auto prize : pPrizeManager->GetPrizeList())
		{
			if (pCollision->CheckEnterCollision(pHole->GetCollider(), (CColliderSphere*)prize->GetCollider()))// 内接していたら
			{
				// 死んでる状態へ
				prize->ChangeState(std::make_shared<CEnemyStateDeath>());
			}
		}
	}

	delete pCollision;
}