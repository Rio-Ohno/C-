//====================================================
//
// 敵(プライズ)　[enemy.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "enemy.h"
#include "collider.h"
#include "stateEnemy.h"
#include "shadowS.h"

//====================================================
// 敵の基盤クラスのコンストラクタ
//====================================================
CEnemyBase::CEnemyBase(int nPriority):CObject(nPriority)
{
	// メンバ変数の初期化
	m_enemytype = ACTION_NONE;
	m_prize = PRIZE_NONE;

	m_collider = nullptr;
	m_pShadow = nullptr;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fGravity = 1.0f;

	m_bGravity = true;
	m_bDeath = false;
}

//====================================================
// 敵の基盤クラスの初期化処理
//====================================================
HRESULT CEnemyBase::Init(void)
{
	// ステートマシーンの生成処理
	m_stateMachine = std::make_unique<CStateMachine>();

	// 影の生成処理
	m_pShadow = CShadowS::Create(m_pos, m_rot);

	return S_OK;
}

//====================================================
// 敵の基盤クラスの終了処理
//====================================================
void CEnemyBase::Uninit(void)
{
	// 影の破棄
	if (m_pShadow != nullptr)
	{
		// 終了処理
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}
}

//====================================================
// 敵の基盤クラスの更新処理
//====================================================
void CEnemyBase::Update(void)
{
	// ステートマシーンの更新処理
	m_stateMachine->Update();

	// 影の位置更新
	m_pShadow->SetPos(m_pos);

	// 位置の更新
	m_pos += m_move;
}

//====================================================
// 状態を変える処理
//====================================================
void CEnemyBase::ChangeState(std::shared_ptr<CStateEnemyBase> state)
{
	state->SetEnemy(this);
	m_stateMachine->Change(state);
}