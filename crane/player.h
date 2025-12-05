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
#include <memory>

// 前方宣言
class CLoadMotion;
class CMeshCylinder;
class CInput;
class CStateMachine;
class CStatePlayerBase;

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
	void SetMotion(const char* pFileName);
	void SetMotion(const MOTION motion) { m_pMotion->Set(motion); };
	void SetMotionStop(void) { m_pMotion->Stop(); }
	void SetMotionPlay(void) { m_pMotion->Play(); }

	D3DXVECTOR3 GetPosition(void) const{ return m_pos; }
	D3DXVECTOR3 GetStartPosition(void)const { return m_posBase; }
	int GetMotionType(void)const { return m_pMotion->GetType(); }
	bool isFinishMotion(void)const { return m_pMotion->GetFinish(); }

	static CPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	void None(void);
	void Move(void);

private:

	// constexpr
	static constexpr const char* MOTION_FILE_NAME = "data/SCRIPT/motion/player/motion.txt";// モーションファイルパス
	static constexpr float SPEED = 0.075f;			// スピード
	static constexpr int LIFT_UP_FREAM = 120;		// リフトアップにかけるフレーム
	static constexpr float MOVE_LIMIT = 0.03f;		// 移動量の最大最小値

	static CMotion* m_pMotion;				// モーションへのポインタ
	static CLoadMotion* m_pLoadMotion;		// モーションテキスト読込クラス
	static CMeshCylinder* m_pCylinder;		// メッシュシリンダー
	std::unique_ptr <CStateMachine> m_statePlayer;	// 状態管理クラスへのポインタ

	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_posBase;					// 最初の位置保存用
	D3DXVECTOR3 m_posOld;					// 前フレームの位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_move;						// 移動量
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	int m_nCntFream;						// フレームカウンタ
};

#endif // !_PLAYER_H_