//====================================================
// 
// タイマー処理[Time.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include"Time.h"

//====================================================
// コンストラクタ
//====================================================
CTime::CTime()
{
	// 変数の初期化
	m_bTimeOver = false;
	m_bPasses = true;
	m_nDigit = 0;
	m_nCntFrame = 0;
	m_nTimeLim = 0;
}

//====================================================
// デストラクタ
//====================================================
CTime::~CTime()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CTime* CTime::Create(TYPE type, int nMax, int digit, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTime* pTime = NULL;

	// メモリの確保
	pTime = new CTime;

	// 変数の設定
	pTime->m_type = type;
	pTime->m_nDigit = digit;
	pTime->m_nTimeLim = nMax;

	// 初期化処理
	pTime->Init(pos, fWidth, fHeight);

	return pTime;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CTime::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		pos.x -= (fWidth);

		// 数字の生成
		m_apNumber[nCnt] = CNumber::Create(pos, fWidth, fHeight);
	}

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// 数字の終了処理
			m_apNumber[nCnt]->CNumber::Uninit();
		}
	}

	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処置
//====================================================
void CTime::Update(void)
{
	// ゲームオーバーではないなら
	if (m_bTimeOver == false)
	{
		if (m_bPasses == true)
		{
			switch (m_type)
			{

			case TYPE_CNTUP:

				// カウントアップ処理
				CntUP();

				break;

			case TYPE_CNTDOWN:

				// カウントダウン処理
				CntDown();

				break;

			default:

				break;
			}

			// 数値の設定処理
			SetTime();
		}
	}
}

//====================================================
// 描画処理
//====================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// 数字の描画処理
			m_apNumber[nCnt]->Draw();
		}
	}
}

//====================================================
// 色の設定処理
//====================================================
void CTime::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < m_nDigit * 2; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// 色の設定処理
			m_apNumber[nCnt]->SetColor(col);
		}
	}
}

//====================================================
// テクスチャインデックスの割当
//====================================================
void CTime::BindTexIndx(int indx)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// テクスチャインデックスの設定処理
			m_apNumber[nCnt]->BindTexindx(indx);
		}
	}
}

//====================================================
// カウントアップの更新処理
//====================================================
void CTime::CntUP(void)
{
	//時間カウント
	m_nCntFrame++;

	m_nTime[0] = m_nCntFrame;

	if (m_nTime[0] == 60)
	{
		m_nTime[1]++;
		m_nTime[0] = 0;
		m_nCntFrame = 0;
	}
	if (m_nTime[1] == 60)
	{	
		m_nTime[2]++;
		m_nTime[1] = 0;
	}
}

//====================================================
// カウントダウンの更新処理
//====================================================
void CTime::CntDown(void)
{
	//時間カウント(フレーム)
	m_nCntFrame++;

	m_nTime[0] = m_nTimeLim;

	if (m_nCntFrame == 60)//60フレームたったら
	{
		//一秒減らす
		m_nTimeLim--;

		//フレームカウンタの初期化
		m_nCntFrame = 0;
	}

	if (m_nTimeLim < 0)//タイムが0になったら
	{
		//ゲームを終わらせる
		m_bTimeOver = true;
	}
}

//========================================================
// タイマーの設定
//========================================================
void CTime::SetTime(void)
{
	int nDigit = 0;
	int nCntTime1, nCntTime2 = 0;
	int Time[3] = { 0,0,0 };

	if (m_type == TYPE_CNTUP)
	{
		for (nCntTime1 = 0; nCntTime1 < m_nDigit * 0.5f; nCntTime1++)
		{
			Time[nCntTime1] = m_nTime[nCntTime1];
		}
	}
	else if (m_type == TYPE_CNTDOWN)
	{
		Time[0] = m_nTime[0];
	}

	// 表示数値の設定
	for (nCntTime1 = 0; nCntTime1 < m_nDigit; nCntTime1++)
	{
		if (m_type == TYPE_CNTUP)
		{
			int n = nCntTime1 / 2;
			int i = m_apNumber[nCntTime1]->SetNum(Time[n], nCntTime1 % 2);
		}
		else
		{
			int i = m_apNumber[nCntTime1]->SetNum(Time[0], nCntTime1);
		}
	}
}