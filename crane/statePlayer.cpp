//====================================================
//
// ステートプレイヤー　[statePlayer.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "statePlayer.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "fieldManager.h"

//====================================================
// プレイヤーステート基盤クラスの終了処理
//====================================================
void CStatePlayerBase::Uninit(void)
{
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}
}

//====================================================
// 何もしていない状態の更新処理
//====================================================
void CStatePlayerNone::Update(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = GetPlayer();

	if (pPlayer != nullptr)
	{
		// 何もしてない処理
		pPlayer->None();
	}
}

//====================================================
// 移動状態の更新処理
//====================================================
void CStatePlayerMove::Update(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = GetPlayer();

	if (pPlayer != nullptr)
	{
		// 移動処理
		pPlayer->Move();
	}
}

//====================================================
// 下がる状態のコンストラクタ
//====================================================
CStatePlayerDown::CStatePlayerDown():CStatePlayerBase(CStatePlayerBase::STATE_DOWN)
{
	// メンバ変数の初期化
	m_nCntFream = 0;		// フレームカウンタ
}

//====================================================
// 下がる状態の初期化処理
//====================================================
void CStatePlayerDown::Init(void)
{
	// フレームカウンタのリセット
	m_nCntFream = 0;
}

//====================================================
// 下がる状態の更新処理
//====================================================
void CStatePlayerDown::Update(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = GetPlayer();

	// キーボードの情報取得
	CKeyboard* pKeyboartd = CManager::GetKeyboard();

	if (pKeyboartd->GetTrigger(DIK_RETURN))// Enterキーを押されたら
	{
		// つかむ状態へ
		pPlayer->ChangeState(std::make_shared<CStatePlayerGrab>());

		return;
	}

	if (pPlayer != nullptr)
	{
		// フレームカウントアップ
		++m_nCntFream;

		// 下がる状態の前の高さを取得
		const float fBaseHeight = pPlayer->GetStartPosition().y;
		const D3DXVECTOR3 pos = pPlayer->GetPosition();

		// 下げる値の算出
		float difHeight = fBaseHeight / (float)LIFT_DOWN_FREAM;

		// 位置の更新
		pPlayer->SetPosition(D3DXVECTOR3(pos.x, pos.y - difHeight, pos.z));

		if (m_nCntFream >= LIFT_DOWN_FREAM ||
			(pos.y - difHeight) <= 0.0f)
		{
			// 波を発生させる
			CFiledManager* pFiled = CGame::GetFieldManager();
			pFiled->SetWave(pos, 50.0f, 20.0f, 25.0f, 0.2f, 1, 0.1f);

			// フレームカウンタのリセット
			m_nCntFream = 0;

			// つかむ状態へ
			pPlayer->ChangeState(std::make_shared<CStatePlayerGrab>());
		}
	}
}

//====================================================
// つかみ状態のコンストラクタ
//====================================================
CStatePlayerGrab::CStatePlayerGrab():CStatePlayerBase(CStatePlayerBase::STATE_GRAB)
{
	// メンバ変数の処理化
	m_nCntFream = 0;
}

//====================================================
// つかみ状態の初期化処理
//====================================================
void CStatePlayerGrab::Init(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = GetPlayer();

	// フレームカウンタのリセット
	m_nCntFream = 0;

	// モーションの設定
	pPlayer->SetMotion(CPlayer::MOTION_CLOSE);
}

//====================================================
// つかみ状態の更新処理
//====================================================
void CStatePlayerGrab::Update(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = GetPlayer();

	if (pPlayer != nullptr)
	{
		if (pPlayer->isFinishMotion())
		{
			if (m_nCntFream == 0)// 最初なら
			{
				// モーションを止める
				pPlayer->SetMotionStop();
			}

			// フレームカウントアップ
			++m_nCntFream;

			if (m_nCntFream >= STOP_FREAM)
			{
				// フレームカウンタリセット
				m_nCntFream = 0;

				// 上がる状態へ
				pPlayer->ChangeState(std::make_shared<CStatePlayerUP>());
			}
		}
	}
}

//====================================================
// 上がる状態のコンストラクタ
//====================================================
CStatePlayerUP::CStatePlayerUP():CStatePlayerBase(CStatePlayerBase::STATE_UP)
{
	// メンバ変数の初期化
	m_nCntFream = 0;// フレームカウンタ
}

//====================================================
// 上がる状態の初期化処理
//====================================================
void CStatePlayerUP::Init(void)
{
	// フレームカウンタのリセット
	m_nCntFream = 0;
}

//====================================================
// 上がる状態の更新処理
//====================================================
void CStatePlayerUP::Update(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = GetPlayer();

	if (pPlayer != nullptr)
	{
		// 下がる状態の前の高さを取得
		const float fBaseHeight = pPlayer->GetStartPosition().y;
		const D3DXVECTOR3 pos = pPlayer->GetPosition();

		// 下げる値の算出
		float difHeight = fBaseHeight / (float)LIFT_UP_FREAM;

		// 位置の更新
		pPlayer->SetPosition(D3DXVECTOR3(pos.x, pos.y + difHeight, pos.z));

		if (m_nCntFream >= LIFT_UP_FREAM ||
			(pos.y - difHeight) >= fBaseHeight)
		{
			// フレームカウンタのリセット
			m_nCntFream = 0;

			// 戻る状態へ
			pPlayer->ChangeState(std::make_shared<CStatePlayerReturn>());
		}
	}
}

//====================================================
// 戻る状態のコンストラクタ
//====================================================
CStatePlayerReturn::CStatePlayerReturn() :CStatePlayerBase(CStatePlayerBase::STATE_RETURN)
{
	// メンバ変数の初期化
	m_nCntFream = 0;
}

//====================================================
// 戻る状態の初期化処理
//====================================================
void CStatePlayerReturn::Init(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = GetPlayer();

	// 必要な情報取得
	const D3DXVECTOR3 startPos = pPlayer->GetStartPosition();	// 最初の位置
	const D3DXVECTOR3 pos = pPlayer->GetPosition();				// 現在の位置

	// メンバ変数の初期化
	m_nCntFream = 0;

	// 差分算出
	D3DXVECTOR3 difPos = startPos - pos;

	m_fDifX = difPos.x/(float)RETURN_FREAM;
	m_fDifZ = difPos.z/(float)RETURN_FREAM;
}

//====================================================
// 戻る状態の更新処理
//====================================================
void CStatePlayerReturn::Update(void)
{
	// プレイヤーの情報取得
	CPlayer* pPlayer = GetPlayer();

	if (pPlayer != nullptr)
	{
		// フレームカウントアップ
		++m_nCntFream;

		// 必要な情報取得
		const D3DXVECTOR3 startPos = pPlayer->GetStartPosition();	// 最初の位置
		const D3DXVECTOR3 pos = pPlayer->GetPosition();				// 現在の位置

		// 位置の更新
		pPlayer->SetPosition(D3DXVECTOR3(pos.x + m_fDifX, pos.y, pos.z + m_fDifZ));

		if (m_nCntFream > RETURN_FREAM ||
			startPos == pos)
		{
			// フレームカウンタのリセット
			m_nCntFream = 0;

			// 位置の設定
			pPlayer->SetPosition(startPos);

			// モーションを動かす
			pPlayer->SetMotionPlay();

			// アームを開く処理
			pPlayer->SetMotion(CPlayer::MOTION_OPEN);

			// 何もない状態へ
			pPlayer->ChangeState(std::make_shared<CStatePlayerNone>());
		}
	}
}