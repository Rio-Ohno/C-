//====================================================
// 
// 衝撃波の管理処理 [shockManager.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include"shockManager.h"

// 静的メンバ変数
CShockPattern* CShockManager::m_pPattern = { NULL };
CShockwave* CShockManager::m_apShockWave[SHOCK_NUM] = { NULL };
int CShockManager::m_anCntFream[SHOCK_NUM] = { 0 };
int CShockManager::m_anPatternIndx[SHOCK_NUM] = { -1 };

//====================================================
// コンストラクタ
//====================================================
CShockManager::CShockManager()
{
	// 各変数の初期化
	for (int nCnt = 0; nCnt < SHOCK_NUM; nCnt++)
	{
		m_apShockWave[nCnt] = { NULL };
		m_anCntFream[nCnt] = 0;
		m_anPatternIndx[nCnt] = -1;
		m_pos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_pPattern = { NULL };
}

//====================================================
// デストラクタ
//====================================================
CShockManager::~CShockManager()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CShockManager::Init(void)
{
	m_pPattern = new CShockPattern;

	CLoadShock::Load("data/SCRIPT/ShockWave.txt", m_pPattern);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CShockManager::Uninit(void)
{
	// m_apShockWaveは勝手に破棄されそう

	// パターンの破棄
	if (m_pPattern != NULL)
	{
		// 終了処理
		m_pPattern->Uninit();

		// メモリの破棄
		delete m_pPattern;
		m_pPattern = NULL;
	}
}

//====================================================
// 更新処理
//====================================================
void CShockManager::Update(void)
{
	for (int nCnt = 0; nCnt < SHOCK_NUM; nCnt++)
	{
		if (m_anPatternIndx[nCnt] >= 0)
		{
			// フレームカウントアップ
			m_anCntFream[nCnt]++;

			// 決められたフレーム数になったら
			if (m_anCntFream[nCnt] >= m_pPattern->GetInfo()[m_anPatternIndx[nCnt]]->GetFream())
			{
				// 衝撃波生成処理
				CShockManager::Spawn(m_anPatternIndx[nCnt]);

				// フレームカウントリセット
				m_anCntFream[nCnt] = 0;
			}
		}
	}
}

//====================================================
// 衝撃波の生成処理
//====================================================
void CShockManager::Spawn(int nPatternIndx)
{
	for (int nCnt = 0; nCnt < SHOCK_NUM; nCnt++)
	{
		if (m_apShockWave[nCnt] == NULL)
		{
			// 衝撃波の生成
			m_apShockWave[nCnt] = CShockwave::Create(m_pos[nPatternIndx], D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 1,
				m_pPattern->GetInfo()[nPatternIndx]->GetLife(),
				m_pPattern->GetInfo()[nPatternIndx]->GetWidth(), 
				m_pPattern->GetInfo()[nPatternIndx]->GetHeight(), 
				m_pPattern->GetInfo()[nPatternIndx]->GetHeight(),
				m_pPattern->GetInfo()[nPatternIndx]->GetSpeed(), 
				m_pPattern->GetInfo()[nPatternIndx]->GetCulling(),
				m_pPattern->GetInfo()[nPatternIndx]->GetCollision());

			m_apShockWave[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), true);

			m_apShockWave[nCnt]->SetVanish(m_pPattern->GetInfo()[nPatternIndx]->GetVanish());

			break;
		}
	}
}

//====================================================
// 設置処理
//====================================================
void CShockManager::Place(int nPatternIndx, int posIndx)
{
	for (int nCnt = 0; nCnt < SHOCK_NUM; nCnt++)
	{
		if (m_anPatternIndx[nCnt] < 0)
		{
			// パターンインデックスの設定
			m_anPatternIndx[nCnt] = nPatternIndx;

			// 位置の設定
			m_pos[m_anPatternIndx[nCnt]] = m_pPattern->Getpos()[posIndx];

			break;
		}
	}
}