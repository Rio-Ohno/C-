//====================================================
//
// 敵(プライズ)　[enemy.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

// インクルード
#include "object.h"
#include "statebase.h"

// 前方宣言
class CColliderBase;	// 当たり判定
class CStateEnemyBase;	// 状態クラス
class CStateMachine;	// ステートマシーン
class CShadowS;			// 影

// 敵の基盤クラス
class CEnemyBase :public CObject
{
public:

	// 行動タイプ
	typedef enum
	{
		ACTION_NONE=0,	// 動かない
		ACTION_MOVE,	// 動く（にげる）
		ACTION_MAX
	}ACTION;

	// 種類
	typedef enum
	{
		PRIZE_NONE=0,
		PRIZE_BOX,
		PRIZE_BEAR,
		PRIZE_MAX
	}PRIZE;

	CEnemyBase(int nPriority = 3);
	virtual ~CEnemyBase() {};

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void) = 0;

	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void AddMove(D3DXVECTOR3 move) { m_move += move; }

	// セッター
	void SetCollider(CColliderBase* collider) { m_collider = collider; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetEnemyActionType(ACTION enemytype) { m_enemytype = enemytype; }
	void SetPrize(PRIZE prize) { m_prize = prize; }
	void SetGravity(float fGravity) { m_fGravity = fGravity; }
	void SetGravity(bool bGravity) { m_bGravity = bGravity; }
	void Death(void) { m_bDeath = true; }

	// ゲッター
	CColliderBase* GetCollider(void) { return m_collider; }		// コライダー
	CShadowS* GetShadow(void) { return m_pShadow; }				// 影
	D3DXVECTOR3 GetPos(void) { return m_pos; }					// 位置
	D3DXVECTOR3 GetRot(void) { return m_rot; }					// 向き
	D3DXVECTOR3 GetMove(void) { return m_move; }				// 移動量
	int GetEnemyActionType(void) { return m_enemytype; }		// 行動の種類
	int GetPrize(void) { return m_prize; }						// 種類
	int GetNowStateID(void) { return m_stateMachine->GetID(); }	// 現在の状態ID
	float GetGravity(void) { return m_fGravity; }				// 重力係数
	bool isGravity(void) { return m_bGravity; }					// 重力をかけるかどうか
	bool isDeath(void) { return m_bDeath; }						// 死んでいるかどうか

	void ChangeState(std::shared_ptr<CStateEnemyBase> state);	// ステートを変える処理

private:
	CColliderBase* m_collider;	// コライダー
	CShadowS* m_pShadow;		// 影
	ACTION m_enemytype;			// 動くかどうかのタグ
	PRIZE m_prize;				// 種類
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
	D3DXVECTOR3 m_move;			// 移動量
	std::unique_ptr <CStateMachine> m_stateMachine;	// 状態管理クラスへのポインタ
	float m_fGravity;			// 重力係数
	bool m_bGravity;			// 重力をかけるかどうか
	bool m_bDeath;				// 死亡フラグ
};
#endif