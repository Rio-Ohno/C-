//====================================================
//
// 敵(プライズ)マネージャー　[PrizeManager.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "PrizeManager.h"
#include "manager.h"
#include "collider.h"
#include "stateEnemy.h"
#include "motion.h"
#include "box.h"
#include "bear.h"

// 静的メンバ変数
std::vector<CEnemyBase*> CPrizemanager::m_apEnemy;
std::vector<std::shared_ptr<CMotionInfo>> CPrizemanager::m_apMotion;
int CPrizemanager::m_anGetNum[CEnemyBase::PRIZE_MAX] = { 0 };

//====================================================
// コンストラクタ
//====================================================
CPrizemanager::CPrizemanager()
{
	for (int nCnt = 0; nCnt < CEnemyBase::PRIZE_MAX; ++nCnt)
	{
		m_apMotion.push_back(nullptr);
		m_anGetNum[nCnt] = 0;
	}

	// プライズの総数
	m_nCntFream = 0;
	m_nNum = 0;
}

//====================================================
// デストラクタ
//====================================================
CPrizemanager::~CPrizemanager()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
void CPrizemanager::Create(CEnemyBase::PRIZE type, D3DXVECTOR3 pos)
{
	// 生成処理
	switch (type)
	{
	case CEnemyBase::PRIZE_BOX:// 箱

		m_apEnemy.push_back(CPrizeBox::Create(pos));
		++m_nNum;// 総数カウントアップ
			break;

	case CEnemyBase::PRIZE_BEAR:// 熊

		m_apEnemy.push_back(CBear::Create(pos, m_apMotion[type]));
		++m_nNum;// 総数カウントアップ
			break;
	default:
		break;
	}
}

//====================================================
// 初期化処理
//====================================================
void CPrizemanager::Init(void)
{
	// モーション情報の読込
	MotionLoad();
}

//====================================================
// 終了処理
//====================================================
void CPrizemanager::Uninit(void)
{
	for (auto& list : m_apEnemy)
	{
		if (list != nullptr)
		{
			// 終了処理
			list->Uninit();

			list = nullptr;
		}
	}

	// リストから消す
	m_apEnemy.clear();

	for (auto& motion : m_apMotion)
	{
		if (motion != nullptr)
		{
			// 終了処理
			motion->Uninit();
			motion->UninitModel();

			motion.reset();
			motion = nullptr;
		}
	}

	// モーションリストから消す
	m_apMotion.clear();
}

//====================================================
// 更新処理
//====================================================
void CPrizemanager::Update(void)
{
	// 生成処理
	Spawn();

	// 敵同士の当たり判定
	Collision();

	// 死亡処理
	RangeDeath();// 範囲
	Death();

	// デバック表示
	CManager::GetDebug()->Print("m_nNum: %d\n", m_nNum);// 敵の総数
}

//====================================================
// 描画処理
//====================================================
void CPrizemanager::Draw(void)
{
	// なし
}

//====================================================
// 出現処理
//====================================================
void CPrizemanager::Spawn(void)
{
	if (m_nNum < NUM_MIN)
	{
		for (int nCnt = 0; nCnt < (NUM_MIN - m_nNum); ++nCnt)
		{
			// 種類をランダムで決める
			int type = rand() % ((int)CEnemyBase::PRIZE_MAX - 1) + 1;

			// 位置をランダムで決める
			float posX = (float)((rand() % 260) - 130);
			float posZ = (float)((rand() % 140) - 70);

			// 生成処理
			CPrizemanager::Create((CEnemyBase::PRIZE)type, D3DXVECTOR3(posX, 80.0f, posZ));
		}
	}
}

//====================================================
// 出現処理(位置指定版)
//====================================================
void CPrizemanager::Spawn(D3DXVECTOR3 pos)
{
	if (m_nNum < NUM_MIN)
	{
		for (int nCnt = 0; nCnt < (NUM_MIN - m_nNum); ++nCnt)
		{
			// 種類をランダムで決める
			int type = rand() % (int)CEnemyBase::PRIZE_MAX;

			// 生成処理
			CPrizemanager::Create((CEnemyBase::PRIZE)type, pos);
		}
	}
}

//====================================================
// フレームによるスポーン処理
//====================================================
void CPrizemanager::SpawnByFream(void)
{
	// フレームカウントアップ
	++m_nCntFream;

	if (m_nCntFream > FREAM)
	{
		// フレームカウンタリセット
		m_nCntFream = 0;
		if (m_nNum < NUM_MAX)// 最大数を超えていないなら
		{
			// 種類をランダムで決める
			int type = rand() % ((int)CEnemyBase::PRIZE_MAX - 1) + 1;

			// 位置をランダムで決める
			float posX = (float)((rand() % 280) - 140);
			float posZ = (float)((rand() % 140) - 70);

			// 生成処理
			CPrizemanager::Create((CEnemyBase::PRIZE)type, D3DXVECTOR3(posX, 80.0f, posZ));
		}
	}
}

//====================================================
// 敵同士の当たり判定
//====================================================
void CPrizemanager::Collision(void)
{
	for (size_t self = 0; self < m_apEnemy.size(); self++)
	{
		// 判定をとる敵
		CEnemyBase* pSelf = m_apEnemy[self];

		// 捕まってる状態なら
		if (pSelf->GetNowStateID() == CStateEnemyBase::STATE_CAUGHT)
		{
			// スキップ
			continue;
		}

		for (size_t other = self + 1; other < m_apEnemy.size(); other++)
		{
			// 判定をとる敵
			CEnemyBase* pOther = m_apEnemy[other];

			// 距離算出
			D3DXVECTOR3 diff = pSelf->GetPos() - pOther->GetPos();
			float fDist = D3DXVec3Length(&diff);

			float fMinDistance = pSelf->GetCollider()->GetMinDistance() + pOther->GetCollider()->GetMinDistance();

			// 当たり判定
			if (fDist < fMinDistance * 0.5f)
			{
				float fPenetration = (fMinDistance - fDist) * 0.5f;

				D3DXVECTOR3 Vec;
				D3DXVec3Normalize(&Vec, &diff);

				// 移動量更新
				pSelf->SetMove((Vec * fPenetration) * PUSHING_OUT);
				pOther->SetMove(-(Vec * fPenetration) * PUSHING_OUT);
			}
		}
	}
}

//====================================================
// モーションの読込
//====================================================
void CPrizemanager::MotionLoad(void)
{
	// 各種モーションの読込
	CMotion* pBear = CBear::Load();
	m_apMotion[CEnemyBase::PRIZE_BEAR] = std::make_shared<CMotionInfo>();	// 熊
	m_apMotion[CEnemyBase::PRIZE_BEAR]->SetNumModel(pBear->GetNumModel());
	m_apMotion[CEnemyBase::PRIZE_BEAR]->SetInfo(pBear->GetInfo());
	m_apMotion[CEnemyBase::PRIZE_BEAR]->SetModel(pBear->GetModel());

	delete pBear;
}

//====================================================
// 全て消す処理
//====================================================
void CPrizemanager::DeleteAll(void)
{
	for (auto list : m_apEnemy)
	{
		list->ChangeState(std::make_shared<CEnemyStateDeath>());
	}
}

//====================================================
// 死亡処理
//====================================================
void CPrizemanager::Death(void)
{
	for (auto prize = m_apEnemy.begin(); prize != m_apEnemy.end();)// イテレータというらしい
	{
		if ((*prize)->isDeath())
		{
			// 終了処理
			(*prize)->Uninit();

			// リストから外す
			prize = m_apEnemy.erase(prize);

			// 総数を減らす
			--m_nNum;
		}
		else
		{
			++prize;
		}
	}
}

//====================================================
// 範囲死亡処理
//====================================================
void CPrizemanager::RangeDeath(void)
{
	for (auto prize = m_apEnemy.begin(); prize != m_apEnemy.end();)// イテレータ
	{
		if ((*prize)->GetPos().y < -50.0f ||
			(*prize)->GetPos().y > 100.0f)
		{
			// 死亡状態へ
			(*prize)->ChangeState(std::make_shared<CEnemyStateDeath>());
		}
		++prize;
	}
}