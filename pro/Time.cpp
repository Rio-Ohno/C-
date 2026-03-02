//====================================================
// 
// タイマー処理[Time.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include"Time.h"
#include "object2D.h"

//========================================================
// タイムマネージャーのコンストラクタ
//========================================================
CTimeManager::CTimeManager(int nPriority):CObject(nPriority)
{
	// 種類の設定
	CObject::SetType(CObject::TYPE_UI);

	// 各メンバ変数の初期化
	m_cnt = CNT_DOWN;
	m_type = DISPLAY_SECOND;
	m_pTime = nullptr;
	m_nFream = 0;

	m_bFinish = false;
	m_bStop = false;
}

//========================================================
// タイムマネージャーのデストラクタ
//========================================================
CTimeManager::~CTimeManager()
{
	// なし
}

//========================================================
// 数字のテクスチャ設定
//========================================================
void CTimeManager::BindNumTextere(int texIndx)
{
	m_pTime->BindNumTexture(texIndx);
}

//========================================================
// コロンのテクスチャ設定
//========================================================
void CTimeManager::BindColonTexture(int texIndx)
{
	m_pTime->BindColonTexture(texIndx);
}

//========================================================
// 色の設定
//========================================================
void CTimeManager::SetColor(D3DXCOLOR col)
{
	m_pTime->SetColor(col);
}

//========================================================
// タイムマネージャーの生成処理
//========================================================
CTimeManager* CTimeManager::Create(CNT countType, DISPLAY type, int nFream, int digit, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTimeManager* pTimeManager = nullptr;

	// メモリの確保
	pTimeManager = new CTimeManager;

	// 各メンバ変数の初期化
	pTimeManager->m_cnt = countType;		// カウントタイプ
	pTimeManager->m_type = type;			// 表示タイプ

	if (pTimeManager->m_cnt == CNT_DOWN)	// カウントダウンなら
	{
		pTimeManager->m_nFream = nFream;	// フレーム
	}
	
	if (digit <= 2&&
		type==DISPLAY_MINSEC)// 二桁以下で分秒タイプなら
	{
		pTimeManager->m_type = DISPLAY_SECOND;// 秒タイプにする
	}

	// 初期化処理
	pTimeManager->Init();

	if (pTimeManager->m_pTime != nullptr)
	{
		// 各設定
		pTimeManager->m_pTime->SetPos(pos);								// 位置
		pTimeManager->m_pTime->SetNumNumber(digit);						// 桁数
		pTimeManager->m_pTime->SetSize(D3DXVECTOR2(fWidth, fHeight));	// 1ポリゴンのサイズ設定

		// 初期化処理
		pTimeManager->m_pTime->Init();
	}

	if (pTimeManager->m_pTime == nullptr ||
		pTimeManager == nullptr)
	{
		return nullptr;
	}

	return pTimeManager;
}

//========================================================
// タイムマネージャーの初期化処理
//========================================================
HRESULT CTimeManager::Init(void)
{
	switch (m_type)
	{
	case DISPLAY_MINSEC:
		m_pTime = std::make_unique<CTimeMinSec>();
		break;
	case DISPLAY_SECOND:

		m_pTime = std::make_unique<CTimeSecond>();
		break;
	default:
		break;
	}

	return S_OK;
}

//========================================================
// タイムマネージャーの終了処理
//========================================================
void CTimeManager::Uninit(void)
{
	if (m_pTime != nullptr)
	{
		// 終了処理
		m_pTime->Uninit();

		m_pTime.reset();
		m_pTime = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}

//========================================================
// タイムマネージャーの更新処理
//========================================================
void CTimeManager::Update(void)
{
	if (!m_bStop && !m_bFinish)
	{
		switch (m_cnt)
		{
		case CNT_UP:

			// フレームカウントアップ
			++m_nFream;
			break;
		case CNT_DOWN:

			// 0より大きいなら
			if (m_nFream > 0)
			{
				// フレームカウントダウン
				--m_nFream;
			}
			else
			{
				m_bFinish = true;
			}
			break;
		default:
			break;
		}

		// タイムの更新処理
		m_pTime->Update();

		// 表示数値の設定
		m_pTime->SetNumber(m_nFream);
	}
}

//========================================================
// タイムマネージャーの描画処理
//========================================================
void CTimeManager::Draw(void)
{
	// タイムの描画処理
	m_pTime->Draw();
}

//========================================================
// タイムのコンストラクタ
//========================================================
CTimeBase::CTimeBase()
{
	// 各メンバ変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_nNumNum = 0;
}

//========================================================
// タイムの初期化処理
//========================================================
HRESULT CTimeBase::Init(void)
{
	for (int nCnt = 0; nCnt < m_nNumNum; ++nCnt)
	{
		m_pos.x -= (m_fWidth);

		// 生成処理
		m_pNumber.push_back(CNumber::Create(m_pos, m_fWidth, m_fHeight));
	}

	return S_OK;
}

//========================================================
// タイムの終了処理
//========================================================
void CTimeBase::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nNumNum; ++nCnt)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			// 終了処理
			m_pNumber[nCnt]->Uninit();

			m_pNumber[nCnt] = nullptr;
		}
	}
}

//========================================================
// タイムの描画処理
//========================================================
void CTimeBase::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nNumNum; ++nCnt)
	{
		// 描画処理
		m_pNumber[nCnt]->Draw();
	}
}

//========================================================
// タイムのテクスチャの設定
//========================================================
void CTimeBase::BindNumTexture(int texIndex)
{
	for (int nCnt = 0; nCnt < m_nNumNum; ++nCnt)
	{
		// 描画処理
		m_pNumber[nCnt]->BindTexindx(texIndex);
	}
}

//========================================================
// 色の設定
//========================================================
void CTimeBase::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < m_nNumNum; ++nCnt)
	{
		// 描画処理
		m_pNumber[nCnt]->SetColor(col);
	}
}

// 子クラス***********************************************************************************************************************************************

//========================================================
// 分秒タイプのコンストラクタ
//========================================================
CTimeMinSec::CTimeMinSec()
{
	m_pObject2D = nullptr;

	for (int nCnt = 0; nCnt < NUM_UNIT; ++nCnt)
	{
		m_nTime[nCnt] = 0;
	}
}

//========================================================
// 分秒タイプのデストラクタ
//========================================================
CTimeMinSec::~CTimeMinSec()
{
	// なし
}

//========================================================
// 分秒タイプの初期化処理
//========================================================
HRESULT CTimeMinSec::Init(void)
{
	// 基底クラスの初期化
	CTimeBase::Init();

	// 位置の取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 Diffpos = pos;

	for (int nCnt = 2; nCnt < GetNumNumber(); ++nCnt)
	{
		// 位置ずらし
		Diffpos.x -= (GetSize().x);

		// 位置の設定
		GetNumber()[nCnt]->SetPos(Diffpos);
	}

	// オブジェクト2D（コロン）の生成
	m_pObject2D = CObject2D::Create(D3DXVECTOR3(pos.x , pos.y, pos.z), GetSize().x, GetSize().y);

	return S_OK;
}

//========================================================
// 分秒タイプの終了処理
//========================================================
void CTimeMinSec::Uninit(void)
{
	// 基底クラスの終了処理
	CTimeBase::Uninit();

	if (m_pObject2D != nullptr)
	{
		// 終了処理
		m_pObject2D->Uninit();

		m_pObject2D = nullptr;
	}
}

//========================================================
// 分秒タイプの更新処理
//========================================================
void CTimeMinSec::Update(void)
{
	// 基底クラスの更新処理
	CTimeBase::Update();
}

//========================================================
// 分秒タイプの描画処理
//========================================================
void CTimeMinSec::Draw(void)
{
	// 基底クラスの描画処理
	CTimeBase::Draw();
}

//========================================================
// コロンのテクスチャの設定
//========================================================
void CTimeMinSec::BindColonTexture(int texIndex)
{
	// コロンのテクスチャ割当
	m_pObject2D->BindTexIndx(texIndex);
}

//========================================================
// 分秒タイプの数字の設定
//========================================================
void CTimeMinSec::SetNumber(int nNowFream)
{
	if (nNowFream > 0)
	{
		m_nTime[0] = nNowFream / SECOND;	// 秒
		m_nTime[0] = m_nTime[0] % SECOND;
		m_nTime[1] = nNowFream / MINIT;		// 分
	}

	for (int nCntNumber = 0; nCntNumber < GetNumNumber(); ++nCntNumber)// 桁分回す
	{
		// 単位の算出(0：秒、1：分)
		int unit = nCntNumber / NUM_UNIT;

		// 表示数値の設定
		GetNumber()[nCntNumber]->SetNum(m_nTime[unit], nCntNumber % NUM_UNIT);
	}
}

//========================================================
// 秒バージョンのコンストラクタ
//========================================================
CTimeSecond::CTimeSecond()
{
	// メンバ変数の初期化
	m_nTime = 0;
}

//========================================================
// 秒バージョンのデストラクタ
//========================================================
CTimeSecond::~CTimeSecond()
{
	// なし
}

//========================================================
// 秒バージョンの初期化処理
//========================================================
HRESULT CTimeSecond::Init(void)
{
	// 基底クラスの初期化
	CTimeBase::Init();

	return S_OK;
}

//========================================================
// 秒バージョンの終了処理
//========================================================
void CTimeSecond::Uninit(void)
{
	// 基底クラスの終了処理
	CTimeBase::Uninit();
}

//========================================================
// 秒バージョンの更新処理
//========================================================
void CTimeSecond::Update(void)
{
	// 基底クラスの更新処理
	CTimeBase::Update();
}

//========================================================
// 秒バージョンの描画処理
//========================================================
void CTimeSecond::Draw(void)
{
	// 基底クラスの描画処理
	CTimeBase::Draw();
}

//========================================================
// 秒バージョンの表示する数値の設定
//========================================================
void CTimeSecond::SetNumber(int nNowFream)
{
	// 秒算出
	m_nTime = nNowFream / 60;

	for (int nCntNumber = 0; nCntNumber < GetNumNumber(); ++nCntNumber)// 桁分回す
	{
		// 表示数値の設定
		GetNumber()[nCntNumber]->SetNum(m_nTime, nCntNumber);
	}
}