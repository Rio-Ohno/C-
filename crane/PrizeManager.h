//====================================================
//
// 敵(プライズ)マネージャー　[PrizeManager.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _PRIZEMANAGER_H_
#define _PRIZEMANAGER_H_

// インクルード
#include "main.h"
#include "enemy.h"
#include <vector>

// 前方宣言
class CMotionInfo;

// 敵（プライズ）マネージャー
class CPrizemanager
{
public:
	CPrizemanager();
	~CPrizemanager();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Create(CEnemyBase::PRIZE type,D3DXVECTOR3 pos);
	
	std::vector<CEnemyBase*> GetPrizeList(void)const { return m_apEnemy; }

	void Spawn(void);
	void Spawn(D3DXVECTOR3 pos);
	void SpawnByFream(void);
	void Collision(void);
	void MotionLoad(void);
	void DeleteAll(void);
	void SetGetNum(CEnemyBase::PRIZE prize) { ++m_anGetNum[prize]; }

private:

	void Death(void);		// 死亡処理
	void RangeDeath(void);	// 範囲死
	void RandmCreate(void);

	// constexpr
	static constexpr int NUM_MIN = 5;					// 敵の最低数
	static constexpr int NUM_MAX = 10;					// 敵の最大数
	static constexpr int FREAM = 300;					// スポーン間隔
	static constexpr float SPAWN_RANGE_X_MAX = 35.0f;	// スポーンする範囲の最大値(X軸)
	static constexpr float SPAWN_RANGE_X_MIN = -120.0f;	// スポーンする範囲の最小値(X軸)
	static constexpr float SPAWN_RANGE_Z_MAX = 25.0f;	// スポーンする範囲の最大値(Z軸)
	static constexpr float SPAWN_RANGE_Z_MIN = -110.0f;	// スポーンする範囲の最小値(Z軸)
	static constexpr float PUSHING_OUT = 0.05f;			// 当たり判定押し出すときの係数
	static constexpr float MAX_HIGHT = 100.0f;			// 高さの最大値
	static constexpr float MIN_HIGHT = -50.0f;			// 高さの最小値

	static std::vector<CEnemyBase*> m_apEnemy;						// 敵のポインタ
	static std::vector<std::shared_ptr<CMotionInfo>> m_apMotion;	// 敵のモーションポインタ
	static int m_anGetNum[CEnemyBase::PRIZE_MAX];					// ゲットされた数
	int m_nCntFream;												// フレームカウンター
	int m_nNum;														// 現在の総数
};
#endif // !_PRIZEMANAGER_H_
