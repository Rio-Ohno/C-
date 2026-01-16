//====================================================
//
// 敵とプレイヤーの当たり判定　[funcCollisionPlayer_to_Enemy.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "funcCollisionPlayer_to_Enemy.h"
#include "game.h"
#include "collision.h"
#include "statePlayer.h"
#include "player.h"
#include "PrizeManager.h"
#include "stateEnemy.h"
#include "manager.h"

//====================================================
// 敵とプレイヤーの当たり判定処理の更新処理
//====================================================
void CFuncCollisionPlayerToEnemy::Update(void)
{
	CPlayer* pPlayer = CGame::GetPlayer();
	CPrizemanager* Prize = CGame::GetPrizeManager();
	CCollision* pCollision = new CCollision;

	if (pPlayer != nullptr && Prize != nullptr)
	{
		if (pPlayer->isCollisionEnemy())
		{
			for (auto prize : Prize->GetPrizeList())
			{
				if (!prize->isDeath())// 敵が死んでる状態じゃないなら
				{
					// 当たり判定
					if (pCollision->CCollision::CheckCollision(pPlayer->GetCollider(), (CColliderSphere*)prize->GetCollider()))
					{
						// 敵のステートを変える
						prize->ChangeState(std::make_shared<CEnemyStateCaught>());

						// 敵をプレイヤーに沿って移動させる
						prize->SetMove(pPlayer->GetMove());
					}
					else
					{
						if (prize->GetNowStateID() == CStateEnemyBase::STATE_CAUGHT)// 現状捕まってる状態なら
						{
							// 落ちてる状態へ
							prize->ChangeState(std::make_shared<CEnemyStateFall>());
						}
					}
				}
			}

			delete pCollision;
		}
		else
		{
			for (auto prize : Prize->GetPrizeList())
			{
				if (prize->GetNowStateID() == CStateEnemyBase::STATE_CAUGHT)// 現状捕まってる状態なら
				{
					// 落ちてる状態へ
					prize->ChangeState(std::make_shared<CEnemyStateFall>());
				}
			}

			delete pCollision;
		}
	}

}