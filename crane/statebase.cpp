//====================================================
// 
// 状態管理 [statebase.cpp]
// Author：Rio Ohno
// 
//====================================================

// インクルード
#include "statebase.h"

//====================================================
// 状態基底クラスのコンストラクタ
//====================================================
CStateBase::CStateBase()
{
	// なし
}

//====================================================
// 状態マシンのコンストラクタ
//====================================================
CStateMachine::CStateMachine()
{
	m_pNowState = nullptr;
}

//====================================================
// 状態マシンのデストラクタ
//====================================================
CStateMachine::~CStateMachine()
{
}

//====================================================
// 状態マシンの変更処理
//====================================================
void CStateMachine::Change(std::shared_ptr<CStateBase> pNewState)
{
	if (m_pNowState != nullptr)
	{
		// nullなら
		if (!pNewState)
		{
			return;
		}
		// 状態が同じなら
		if (m_pNowState->GetStateID() == pNewState->GetStateID())
		{
			//// 破棄
			//pNewState.reset();
			return;
		}

		// 今の状態を生成
		m_pNowState->Uninit();
		m_pNowState.reset();
	}

	// 状態の設定
	m_pNowState = pNewState;

	// 今の状態ポインタの初期化処理
	m_pNowState->Init();
}

//====================================================
// 状態マシンの更新処理
//====================================================
void CStateMachine::Update(void)
{
	// 更新処理
	if (m_pNowState != nullptr)
	{
		m_pNowState->Update();
	}
}