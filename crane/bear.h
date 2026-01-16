//==============================================
//
// 熊 [bear.h]
// Author:Rio Ohno
//
//==============================================

#ifndef _BEAR_H_
#define _BEAR_H_

// インクルード
#include "enemy.h"
#include "stateEnemy.h"

// 前方宣言
class CColliderSphere;
class CMotion;
class CMotionInfo;

// くま（Prize）クラス
class CBear :public CEnemyBase
{
public:

	typedef enum
	{
		MOTION_NEUTRAL=0,
		MOTION_RUN,
		MOTION_FLUTTER,
		MOTION_MAX
	}MOTION;

	CBear();
	~CBear(); 

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBear* Create(D3DXVECTOR3 pos, std::shared_ptr<CMotionInfo> pMotion);
	static CMotion* Load(void);

private:

	void UpdateColliderPos(void);
	void SetState(void);

	// constexpr
	static constexpr const char* MOTIONFILE_NAME = "data/SCRIPT/motion/enemy/bear/motion.txt";// モーションファイルパス
	static constexpr int BODY_INDEX = 0;
	static constexpr int HEAD_INDEX = 1;

	CMotion* m_pMotion;				// モーションへのポインタ

	CColliderSphere* m_collider;	// コライダー
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	int m_nCntFream;				// フレームカウンタ
};

// くま専用ステートクラス------------------------------------------------------------------------------------------------------
// 逃げるクラス
class CBearStateRun :public CStateEnemyBase
{
public:
	CBearStateRun();
	~CBearStateRun();

	void Init(void);
	void Uninit(void) {};
	void Update(void);
private:

	// constexpr
	static constexpr float GRAVITY = 0.9f;
};
#endif // !_BEAR_H_