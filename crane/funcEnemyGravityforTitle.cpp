//====================================================
// 
// 敵の重力判定(タイトル用)[funcEnemyGravityforTitle.cpp]
// Author: Rio Ohno
// 
//====================================================

// インクルード
#include "funcEnemyGravityforTitle.h"
#include "title.h"
#include "PrizeManager.h"
#include "meshfield.h"

//====================================================
// 敵の重力処理(タイトル用)
//====================================================
void CFuncTitleEnemyGravity::Update(void)
{
	// タイトルの各オブジェクトの情報取得
	CPrizemanager* pPrize = CTitle::GetPrizemanager();	// プライズマネージャー
	CMeshField* pField = CTitle::GetField();			// フィールド

	if (pPrize != nullptr && pField != nullptr)// ヌルチェック
	{
		for (auto prize : pPrize->GetPrizeList())
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