//====================================================
// 
// 状態管理 [statebase.h]
// Author：Rio Ohno
// 
//====================================================
#ifndef _STATEBASE_H_
#define _STATEBASE_H_

// インクルード
#include<memory>

// 状態基底クラス------------------------------------
class CStateBase
{
public:
	CStateBase();
	~CStateBase() {};
	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual int GetStateID(void) const = 0;
};

// 状態マシーンクラス---------------------------------
class CStateMachine
{
public:
	CStateMachine();
	~CStateMachine();
	void Change(std::shared_ptr<CStateBase> pNewState);
	void Update(void);
	int GetID(void) { return m_pNowState->GetStateID(); }
private:
	std::shared_ptr<CStateBase> m_pNowState; // 現在の状態ポインタ
};

#endif // !_STATEBASE_H_

