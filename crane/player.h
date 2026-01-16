//====================================================
//
// プレイヤー　[player.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

// インクルード
#include "object.h"
#include "motion.h"
#include "statebase.h"
#include <memory>

// 前方宣言
class CLoadMotion;		// モーション読込クラス
class CMeshCylinder;	// メッシュシリンダークラス
class CInput;			// 入力処理クラス
class CStateMachine;	// ステートマシーン
class CStatePlayerBase;	// プレイヤーステート基盤クラス
class CColliderSphere;	// コライダー(球)

// プレイヤークラス
class CPlayer :public CObject
{
public:

	typedef enum
	{
		MOTION_NEUTRAL=0,
		MOTION_CLOSE,	// アームを閉じる
		MOTION_OPEN,	// アームを開ける
		MOTION_MAX
	}MOTION;

	CPlayer();
	~CPlayer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void ChangeState(std::shared_ptr<CStatePlayerBase> stateBasePlayer);

	void SetPosition(const D3DXVECTOR3 Newpos) { m_pos = Newpos; }
	void SetMoveY(const float moveY) { m_move.y = moveY; }
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }
	void SetCollisionEnemy(bool bCollision) { m_bCollisionToPrize = bCollision; }
	void SetMotion(const char* pFileName);
	void SetMotion(const MOTION motion) { m_pMotion->Set(motion); };
	void SetMotionStop(void) { m_pMotion->Stop(); }
	void SetMotionPlay(void) { m_pMotion->Play(); }

	int GetState(void) { return m_statePlayer->GetID(); }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetPosition(void) const{ return m_pos; }
	D3DXVECTOR3 GetStartPosition(void)const { return m_posBase; }
	D3DXVECTOR3 GetModelPos(int modelindx)const { return m_pMotion->GetModelPos(modelindx); }
	CColliderSphere* GetCollider(void) { return m_collider; }
	int GetMotionType(void)const { return m_pMotion->GetType(); }
	bool isCollisionEnemy(void)const { return m_bCollisionToPrize; }
	bool isFinishMotion(void)const { return m_pMotion->GetFinish(); }

	static CPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	void None(void);
	void Move(void);
	void Collision(void);

private:

	// constexpr
	static constexpr const char* MOTION_FILE_NAME = "data/SCRIPT/motion/player/motion.txt";// モーションファイルパス
	static constexpr int LIFT_UP_FREAM = 120;		// リフトアップにかけるフレーム
	static constexpr int BODY_INDX = 0;				// 本体のモデルインデックス
	static constexpr int R_ARM_INDX = 2;			// Rアームのモデルインデックス
	static constexpr int L_ARM_INDX = 4;			// Lアームのモデルインデックス
	static constexpr float SPEED = 0.075f;			// スピード
	static constexpr float MOVE_LIMIT = 0.03f;		// 移動量の最大最小値

	static CMotion* m_pMotion;				// モーションへのポインタ
	static CMeshCylinder* m_pCylinder;		// メッシュシリンダー
	static CColliderSphere* m_collider;		// コライダー
	std::unique_ptr <CStateMachine> m_statePlayer;	// 状態管理クラスへのポインタ

	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_posBase;					// 最初の位置保存用
	D3DXVECTOR3 m_posOld;					// 前フレームの位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_move;						// 移動量
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	int m_nCntFream;						// フレームカウンタ
	bool m_bCollisionToPrize;				// 敵との当たり判定をとるかどうか
};

#endif // !_PLAYER_H_