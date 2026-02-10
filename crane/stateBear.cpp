//====================================================
// 
// 熊専用ステート　[stateBear.cpp]
// Author: Rio Ohno
// 
//====================================================

// インクルード
#include "stateBear.h"
#include "game.h"
#include "enemy.h"
#include "statePlayer.h"
#include "player.h"

//==============================================
// ニュートラル状態のコンストラクタ
//==============================================
CBearStateNeutral::CBearStateNeutral():CStateEnemyBase(CStateEnemyBase::STATE_NEUTRAL)
{
	// メンバ変数の初期化
	m_nCntFream = 0;
}

//==============================================
// ニュートラル状態の初期化処理
//==============================================
void CBearStateNeutral::Init(void)
{
	// フレームカウンタの初期化
	m_nCntFream = 0;

	CEnemyBase* pEnemy = GetEnemy();

	// 移動量のリセット
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 重力の設定
	pEnemy->SetGravity(GRAVITY);
	pEnemy->SetGravity(true);
}

//==============================================
// ニュートラル状態の更新処理
//==============================================
void CBearStateNeutral::Update(void)
{
	// フレームカウントアップ
	++m_nCntFream;

	// 敵の情報取得
	CEnemyBase* pEnemy = CStateEnemyBase::GetEnemy();
	
	// 現在の移動量の取得
	D3DXVECTOR3 move = pEnemy->GetMove();

	// 移動量の減衰
	pEnemy->SetMove(D3DXVECTOR3(
		move.x + (0.0f - move.x) * 0.09f, 
		move.y, 
		move.z + (0.0f - move.z) * 0.09f));

	if (m_nCntFream >= FREAM)
	{
		// 歩く状態へ
		pEnemy->ChangeState(std::make_shared<CBearStateWalk>());
	}
}

//==============================================
// 歩く状態のコンストラクタ
//==============================================
CBearStateWalk::CBearStateWalk() :CStateEnemyBase(CStateEnemyBase::STATE_WALK)
{
	// 各メンバ変数の初期化
	m_nCntFream = 0;// フレームカウンタ
	m_rotY = 0.0f;	// 向き
}

//==============================================
// 歩く状態の初期化処理
//==============================================
void CBearStateWalk::Init(void)
{
	CEnemyBase* pEnemy = GetEnemy();
	m_nCntFream = 0;// フレームカウンタ

	// 重力の係数再設定
	pEnemy->SetGravity(GRAVITY);
	pEnemy->SetGravity(true);

	// 移動量のリセット
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	int nDiviRot = rand() % DIVI_ROT;

	// 歩く方向の設定
	m_rotY = (D3DX_PI * 2.0f) * (0.125f * nDiviRot);
}

//==============================================
// 歩く状態の更新処理
//==============================================
void CBearStateWalk::Update(void)
{
	// クレームカウントアップ
	++m_nCntFream;

	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();

	// 現在の移動量取得
	D3DXVECTOR3 move = pEnemy->GetMove();

	move.x -= sinf(m_rotY) * WALK_SPEED;
	move.z -= cosf(m_rotY) * WALK_SPEED;

	// 移動量の設定
	pEnemy->SetMove(move);

	// 移動量の減衰
	pEnemy->SetMove(D3DXVECTOR3(
		move.x + (0.0f - move.x) * MOVE_DECAY,
		move.y,
		move.z + (0.0f - move.z) * MOVE_DECAY));

	// 向きの設定
	pEnemy->SetRot(D3DXVECTOR3(0.0f, m_rotY, 0.0f));

	if (m_nCntFream >= FREAM)
	{
		// 何もしていない状態へ
		pEnemy->ChangeState(std::make_shared<CBearStateNeutral>());
	}
}

//==============================================
// 逃げる状態クラスのコンストラクタ
//==============================================
CBearStateRun::CBearStateRun() :CStateEnemyBase(CStateEnemyBase::STATE_RUN)
{
	// 各メンバ変数の初期化
	m_rotY = 0.0f;
}

//==============================================
// 逃げる状態クラスの初期化処理
//==============================================
void CBearStateRun::Init(void)
{
	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();

	// 重力の係数再設定
	pEnemy->SetGravity(GRAVITY);
	pEnemy->SetGravity(true);// 重力をかける

	int nDiviRot = rand() % DIVI_ROT;

	// 逃げる方向の設定
	m_rotY = (D3DX_PI * 2.0f) * (0.125f * nDiviRot);
}

//==============================================
// 逃げる状態クラスの更新処理
//==============================================
void CBearStateRun::Update(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = CGame::GetPlayer();

	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();

	if (pPlayer->GetState() == CStatePlayerBase::STATE_MOVE ||
		pPlayer->GetState() == CStatePlayerBase::STATE_DOWN)
	{
		// 位置の差分算出
		D3DXVECTOR3 Distance = pPlayer->GetPosition() - pEnemy->GetPos();
		float fDistSq = D3DXVec3LengthSq(&Distance);						// 距離の累乗算出

		if (fDistSq <= (RANGE_AWARENESS * RANGE_AWARENESS))// 範囲内なら
		{
			// 現在の移動量取得
			D3DXVECTOR3 move = pEnemy->GetMove();

			move.x += sinf(m_rotY) * RUN_SPEED;
			move.z += cosf(m_rotY) * RUN_SPEED;

			// 移動量の設定
			pEnemy->SetMove(move);
		}
		else// 範囲外なら
		{
			// 何もしていない状態
			pEnemy->ChangeState(std::make_shared<CEnemyStateNone>());
		}
	}
}