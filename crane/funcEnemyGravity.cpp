//====================================================
//
// 敵の重力処理[funcEnemyGravity.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "funcEnemyGravity.h"
#include "game.h"
#include "PrizeManager.h"
#include "meshfield.h"

//====================================================
// 敵の重力処理
//====================================================
void CFuncEnemyGaravity::Update(void)
{
	CPrizemanager* pPrizeManager = CGame::GetPrizeManager();
	CMeshField* pField = CGame::GetField();

	if (pField != nullptr &&
		pPrizeManager != nullptr)
	{
		for (auto prize : pPrizeManager->GetPrizeList())
		{
			if (prize->isGravity() &&
				prize->GetGravity() > 0.0f)
			{
				// 敵の現在の移動量を取得
				D3DXVECTOR3 move = prize->GetMove();

				move.y += (pField->GetHeight(prize->GetPos()) - move.y) * prize->GetGravity();

				// 重力として加える
				prize->SetMove(move);
			}
		}
	}
}