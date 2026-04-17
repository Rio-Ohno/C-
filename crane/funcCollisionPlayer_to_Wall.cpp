//====================================================
//
// 壁とプレイヤーの当たり判定　[funcCollisionPlayer_to_Wall.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "funcCollisionPlayer_to_Wall.h"
#include "game.h"
#include "wall.h"
#include "player.h"

//====================================================
// 壁とプレイヤーのあたり判定
//====================================================
void CFuncCollisionPlayerToWall::Update(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = CGame::GetPlayer();

	if (pPlayer == nullptr)
	{
		return;
	}

	for (int nCnt = 0; nCnt < CGame::NUM_WALL; ++nCnt)
	{
		CWall* pWall = CGame::GetApWall()[nCnt];

		if (pWall != nullptr&&
			pWall->isColision(pPlayer->GetPosition()))
		{
			// プレイヤーの前の位置を取得
			D3DXVECTOR3 oldpos = pPlayer->GetOldPosition();

			// 前の位置に戻す
			pPlayer->SetPosition(oldpos);

			// 移動量リセット
			pPlayer->SetMove(D3DXVECTOR3_NULL);
		}
	}
}