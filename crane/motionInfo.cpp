//====================================================
// 
// モーション情報クラス[motionInfo.cpp]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include "motionInfo.h"
#include "key.h"
#include "model.h"

//====================================================
// モーション情報クラスのコンストラクタ
//====================================================
CMotionInfo::CMotionInfo()
{
	// 値をクリア,初期化
	m_nNumModel = 0;
}

//====================================================
// モーション情報クラスのコピーコンストラクタ
//====================================================
CMotionInfo::CMotionInfo(const CMotionInfo& other)
{

	// オフセット(位置)
	this->m_OffsetPos = other.m_OffsetPos;

	// オフセット(角度)
	this->m_OffsetRot = other.m_OffsetRot;

	// モーション情報のコピー
	this->m_apInfo = other.m_apInfo;

	// モデル情報のコピー
	this->m_apModel = other.m_apModel;

	this->m_nNumModel = other.m_nNumModel;
}

//====================================================
// モーション情報クラスの終了処理
//====================================================
void CMotionInfo::Uninit(void)
{
	// モーション情報の破棄
	for (int nCnt = 0; nCnt < (int)m_apInfo.size(); ++nCnt)
	{
		if (m_apInfo[nCnt] != nullptr)
		{
			// 終了処理
			m_apInfo[nCnt]->Uninit();

			// メモリの開放
			delete m_apInfo[nCnt];
			m_apInfo[nCnt] = nullptr;
		}
	}
}

//====================================================
// モデルの情報終了処理
//====================================================
void CMotionInfo::UninitModel(void)
{
	// モデルへのポインタの破棄
	for (int nCnt = 0; nCnt < (int)m_apModel.size(); ++nCnt)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			// 終了処理
			m_apModel[nCnt]->Uninit();

			// メモリの開放
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}
}

//====================================================
// モーション情報の設定処理
//====================================================
void CMotionInfo::SetInfo(std::vector<CInfo*> pInfo)
{
	// モーション情報のコピー
	m_apInfo.resize(pInfo.size());
	std::copy(pInfo.begin(), pInfo.end(), m_apInfo.begin());
}

//====================================================
// モデル情報の設定処理
//====================================================
void CMotionInfo::SetModel(std::vector<CModel*> pModel)
{
	// モデル情報のコピー
	m_apModel.resize(pModel.size());
	std::copy(pModel.begin(), pModel.end(), m_apModel.begin());

	for (int nCnt = 0; nCnt < (int)m_apModel.size(); ++nCnt)
	{
		m_OffsetPos.push_back(m_apModel[nCnt]->GetPos());
		m_OffsetRot.push_back(m_apModel[nCnt]->GetRot());
	}
}