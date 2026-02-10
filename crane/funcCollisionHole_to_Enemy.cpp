//====================================================
// 
// ゲットホールとエネミーの当たり判定 [funcCollisionHole_to_Enemy.h]
// Author: Rio Ohno
// 
//====================================================

// インクルード
#include "funcCollisionHole_to_Enemy.h"
#include "game.h"
#include "score.h"
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

	// 情報がないなら
	if (pHole == nullptr ||
		pPrizeManager == nullptr)
	{
		return;
	}

	for (auto prize : pPrizeManager->GetPrizeList())
	{
		// 内接していたら
		if (CCollision::CheckEnterCollision(pHole->GetCollider(), (CColliderSphere*)prize->GetCollider()))
		{
			// 死んでる状態じゃないなら
			if (prize->GetNowStateID()!= CStateEnemyBase::STATE_DEATH)
			{
				// ゲットされた数の設定
				pPrizeManager->SetGetNum(prize->GetPrize());

				// スコア加算
				CGame::GetScore()->Add(prize->GetScore());
			}

			// 死んでる状態へ
			prize->ChangeState(std::make_shared<CEnemyStateDeath>());
		}
	}
}