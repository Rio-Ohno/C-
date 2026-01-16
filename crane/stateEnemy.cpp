//====================================================
//
// ステートエネミー　[stateEnemy.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "stateEnemy.h"
#include "enemy.h"
#include "particle3D.h"

//====================================================
// ステートエネミー基盤のコンストラクタ
//====================================================
CStateEnemyBase::CStateEnemyBase()
{
	m_pEnemy = nullptr;
	m_stateID = STATE_NONE;
}

//====================================================
// ステートエネミー基盤のコンストラクタ
//====================================================
CStateEnemyBase::CStateEnemyBase(STATE state)
{
	m_pEnemy = nullptr;
	m_stateID = state;
}

//====================================================
// 何もしていない状態の初期化処理
//====================================================
void CEnemyStateNone::Init(void)
{
	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();

	if (pEnemy != nullptr)
	{
		pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));// 移動量の初期化
		pEnemy->SetGravity(GRAVITY);// 重力の再設定
	}
}

//====================================================
// 何もしていない状態の更新状態
//====================================================
void CEnemyStateNone::Update(void)
{
	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();
	pEnemy->SetGravity(true);// 重力をかける
}

//====================================================
// 捕まってる状態の更新処理
//====================================================
void CEnemyStateCaught::Update(void)
{
	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();
	pEnemy->SetGravity(false);// 重力をかけない
}

//====================================================
// 落ちる状態の初期化処理
//====================================================
void CEnemyStateFall::Init(void)
{
	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();

	if (pEnemy != nullptr)
	{
		// 移動量の初期化
		pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// 重力の係数再設定
		pEnemy->SetGravity(GRAVITY);
		pEnemy->SetGravity(true);// 重力をかける
	}
}

//====================================================
// 落ちる状態の更新処理
//====================================================
void CEnemyStateFall::Update(void)
{
	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();

	if (pEnemy != nullptr)
	{
		// 着地しているかどうか
		if (pEnemy->GetPos().y <= LANDING)// LANDINGより下にいるなら
		{
			// 何もしていない状態へ
			pEnemy->ChangeState(std::make_shared<CEnemyStateNone>());
		}
	}
}

//====================================================
// 印出る状態の初期化処理
//====================================================
void CEnemyStateDeath::Init(void)
{
	// メンバ変数の初期化
	m_nCntFream = 0; // フレームカウンタ

	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();

	// 重力の係数再設定
	pEnemy->SetGravity(GRAVITY);
	pEnemy->SetGravity(true);// 重力をかける
}

//====================================================
// 死んでる状態の更新処理
//====================================================
void CEnemyStateDeath::Update(void)
{
	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();

	if (pEnemy != nullptr)
	{
		// フレームカウントアップ
		++m_nCntFream;

		if (m_nCntFream >= VANISH_FREAM)
		{
			// パーティクルの生成
			CParticle3D* pParticle = CParticle3D::Create(pEnemy->GetPos(),
				D3DXVECTOR3(D3DX_PI * 0.25f, D3DX_PI * 2.0f, 0.0f),
				10.0f, 0.8f, 10, 45, 6, 0);

			// 色をランダムにする
			pParticle->SetRandMode(true);

			// 死亡フラグをたてる処理
			pEnemy->Death();
		}
	}
}