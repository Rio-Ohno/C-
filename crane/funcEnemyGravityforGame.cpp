//====================================================
//
// 敵の重力処理(ゲームシーン用)[funcEnemyGravityforGame.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "funcEnemyGravityforGame.h"
#include "game.h"
#include "PrizeManager.h"
#include "meshfield.h"

//====================================================
// 敵の重力処理
//====================================================
void CFuncGameEnemyGaravity::Update(void)
{
	// 各情報取得
	CPrizemanager* pPrizeManager = CGame::GetPrizeManager();	// プライズマネージャー
	CMeshField* pField = CGame::GetField();						// フィールド

	// 情報がないなら
	if (pField == nullptr ||
		pPrizeManager == nullptr)
	{
		return;
	}

	for (auto prize : pPrizeManager->GetPrizeList())
	{
		// 重力をかけるかつ重力係数があるなら
		if (prize->isGravity() &&
			prize->GetGravity() > 0.0f)
		{
			// 敵の現在の移動量を取得
			D3DXVECTOR3 move = prize->GetMove();

			// 移動量の更新
			move.y += (pField->GetHeight(prize->GetPos()) - move.y) * prize->GetGravity();

			// 重力として加える
			prize->SetMove(move);
		}
	}
}