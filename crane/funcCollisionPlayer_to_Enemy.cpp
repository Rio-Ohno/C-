//====================================================
//
// 敵とプレイヤーの当たり判定　[funcCollisionPlayer_to_Enemy.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "funcCollisionPlayer_to_Enemy.h"
#include "game.h"
#include "player.h"
#include "PrizeManager.h"
#include "stateEnemy.h"
#include "collision.h"

//====================================================
// 敵とプレイヤーの当たり判定処理の更新処理
//====================================================
void CFuncCollisionPlayerToEnemy::Update(void)
{
	// 各情報取得
	CPlayer* pPlayer = CGame::GetPlayer();				// プレイヤー
	CPrizemanager* Prize = CGame::GetPrizeManager();	// プライズマネージャー

	// どちらかがnullなら
	if (pPlayer == nullptr ||
		Prize == nullptr)
	{
		return;
	}

	// プレイヤーが当たり判定をとらないなら
	if (!pPlayer->isCollisionEnemy())
	{
		for (auto prize : Prize->GetPrizeList())
		{
			// 現状捕まってる状態なら
			if (prize->GetNowStateID() == CStateEnemyBase::STATE_CAUGHT)
			{
				// 落ちてる状態へ
				prize->ChangeState(std::make_shared<CEnemyStateFall>());
			}
		}
		return;
	}

	for (auto prize : Prize->GetPrizeList())
	{
		// 敵が死んでる状態なら
		if (prize->isDeath())
		{
			continue;
		}

		// 当たり判定
		if (CCollision::CheckCollision(pPlayer->GetCollider(), (CColliderSphere*)prize->GetCollider()))
		{
			// 捕まってる状態へ
			prize->ChangeState(std::make_shared<CEnemyStateCaught>());

			// 敵をプレイヤーに沿って移動させる
			prize->SetMove(pPlayer->GetMove());
		}
		else
		{
			// 現状捕まってる状態なら
			if (prize->GetNowStateID() == CStateEnemyBase::STATE_CAUGHT)
			{
				// 落ちてる状態へ
				prize->ChangeState(std::make_shared<CEnemyStateFall>());
			}
		}
	}
}