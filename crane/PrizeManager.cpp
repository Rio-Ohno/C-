//====================================================
//
// 敵(プライズ)マネージャー　[PrizeManager.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "PrizeManager.h"
#include "stateEnemy.h"
#include "motion.h"
#include "box.h"
#include "bear.h"

// 静的メンバ変数
std::vector<CEnemyBase*> CPrizemanager::m_apEnemy;
std::vector<std::shared_ptr<CMotionInfo>> CPrizemanager::m_apMotion;

//====================================================
// コンストラクタ
//====================================================
CPrizemanager::CPrizemanager()
{
	for (int nCnt = 0; nCnt < CEnemyBase::PRIZE_MAX; ++nCnt)
	{
		m_apMotion.push_back(nullptr);
	}

	// プライズの総数
	m_nNum = 0;
}

//====================================================
// デストラクタ
//====================================================
CPrizemanager::~CPrizemanager()
{
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
			break;

	case CEnemyBase::PRIZE_BEAR:// 熊

		m_apEnemy.push_back(CBear::Create(pos, m_apMotion[type]));
			break;
	default:
		break;
	}

	++m_nNum;// 総数カウントアップ

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
			int type = rand() % (int)CEnemyBase::PRIZE_MAX;
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
	// 死亡処理
	Death();
}

//====================================================
// 描画処理
//====================================================
void CPrizemanager::Draw(void)
{
	// なし
}

//====================================================
// 死亡処理
//====================================================
void CPrizemanager::Death(void)
{
	for (auto prize = m_apEnemy.begin(); prize!=m_apEnemy.end();)// イテレータというらしい
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