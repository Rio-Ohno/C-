//====================================================
//
// モーション[motion.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"motion.h"
#include"key.h"

//====================================================
// コンストラクタ
//====================================================
CMotion::CMotion()
{
	// 値をクリア,初期化
	m_nNumKey = 0;
	m_nNumModel = 0;				// モデル数
	m_bFinish = false;				// 終了したかどうか
	m_bStop = false;

	m_nType = 0;					// 種類の設定
	m_nTypeOld = m_nType;			// 前の種類の記録
	m_nKey = 0;						// 現在のキー
	m_nNextKey = m_nKey + 1;		// 前のキー
	m_nCounter = 0;
}

//====================================================
// デストラクタ
//====================================================
CMotion::~CMotion()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CMotion::Init(CMotion* Motion)
{
	m_nNumModel = Motion->GetNumModel();

	m_nNumKey = Motion->GetInfo()[m_nType]->GetNumKey();

	// モーション情報をコピー
	m_apInfo = Motion->GetInfo();

	// モデル情報をコピー
	m_apModel = Motion->GetModel();

	for (int nCnt = 0; nCnt < (int)m_apModel.size(); ++nCnt)
	{
		m_OffsetPos.push_back(m_apModel[nCnt]->GetPos());
		m_OffsetRot.push_back(m_apModel[nCnt]->GetRot());
	}
	m_CurrentPos = m_OffsetPos;
	m_CurrentRot = m_OffsetRot;

	return S_OK;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CMotion::Init(std::vector<CInfo*> pInfo, std::vector<CModel*> pModel, int NumModel, std::vector<D3DXVECTOR3> OffsetPos, std::vector<D3DXVECTOR3> OffsetRot)
{
	m_nNumModel = NumModel;

	// モーション情報をコピー
	m_apInfo.resize(pInfo.size());
	std::copy(pInfo.begin(), pInfo.end(), m_apInfo.begin());

	// モデルの設定
	for (int nCnt = 0; nCnt < (int)pModel.size(); ++nCnt)
	{
		m_apModel.push_back(new CModel);
		m_apModel[nCnt]->Init(pModel[nCnt]);

		m_OffsetPos.push_back(OffsetPos[nCnt]);
		m_OffsetRot.push_back(OffsetRot[nCnt]);
	}
	m_CurrentPos = m_OffsetPos;
	m_CurrentRot = m_OffsetRot;

	// 親モデルの設定
	for (int nCntModel = 0; nCntModel < (int)pModel.size(); ++nCntModel)
	{
		int nParentIndx = pModel[nCntModel]->GetParentIndx();
		if (nParentIndx != -1)// 親モデルがあるなら
		{
			// 親モデルの設定
			m_apModel[nCntModel]->SetParent(m_apModel[nParentIndx]);
		}
	}

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CMotion::Uninit(void)
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
// モデルの終了処理
//====================================================
void CMotion::UninitModel(void)
{
	// モデルへのポインタの破棄
	for (int nCnt = 0; nCnt < m_nNumModel; ++nCnt)
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
// 設定処理
//====================================================
void CMotion::Set(int nType)
{
	if (m_nTypeOld != nType)
	{
		// 各種初期化
		m_nTypeOld = m_nType;	// 前の種類の記録
		m_nType = nType;		// 種類
		m_nCounter = 0;			// フレームカウンタ

		m_nKey = 0;				// キー
		m_nNextKey = 1;			// 次のキー
		m_nNumKey = m_apInfo[nType]->GetNumKey();	// キー数
		m_bFinish = false;		// 終了しているかどうか
	}
}

//====================================================
// 更新処理
//====================================================
void CMotion::Update(void)
{
	if (m_bStop)// モーションを止めてないなら
	{
		return;
	}
	if (m_apInfo[m_nType]->GetKeyInfo().size() <= 1)
	{
		return;
	}
		// モーションカウンター
		++m_nCounter;

	if (m_nCounter >= m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream())
	{
		// モーションカウンタリセット
		m_nCounter = 0;

		if (m_bFinish == false)
		{
			++m_nKey;
			++m_nNextKey;
		}

		if (m_apInfo[m_nType]->isLoop() == true)
		{
			if (m_apInfo[m_nType]->GetNumKey() > 1)
			{
				if (m_nKey >= m_nNumKey - 1)
				{// 今のキーがキーの最大数だったら
					if (m_nKey >= m_nNextKey)
					{// 今のキーが次のキー以上だったら
						m_nKey = 0;
					}
					else
					{
						m_nNextKey = 0;
					}
				}
			}
			else
			{
				m_nKey = 0;
				--m_nNextKey;
			}
		}
		else
		{
			m_bFinish = true;

			if (m_nKey >= m_nNumKey - 1)
			{// 今のキーがキーの最大数だったら
				//m_bFinish = true;
				m_nKey = 0;
				m_nNextKey = m_nKey + 1;
				m_nType = 0;
			}
			else if (m_nKey > m_nNextKey)
			{// 今のキーが次のキー以上だったら
				m_nKey = 0;
			}

			return;
		}
	}

	CKeyInfo* pKeyInfo = m_apInfo[m_nType]->GetKeyInfo(m_nKey);
	CKeyInfo* pNextKeyInfo = m_apInfo[m_nType]->GetKeyInfo(m_nNextKey);

	// 全パーツの更新
	for (int nCntPart = 0; nCntPart < m_nNumModel; ++nCntPart)
	{
		// 差分格納用
		D3DXVECTOR3 DiffPos = D3DXVECTOR3_NULL;// 位置
		D3DXVECTOR3 DiffRot = D3DXVECTOR3_NULL;// 向き

		// 計算結果格納用
		D3DXVECTOR3 DestPos = D3DXVECTOR3_NULL;// 位置
		D3DXVECTOR3 DestRot = D3DXVECTOR3_NULL;// 向き

		if (m_apInfo[m_nType]->GetNumKey() > 1)
		{
			// 差分
			DiffPos = pNextKeyInfo->GetKey()[nCntPart]->GetPos() - pKeyInfo->GetKey()[nCntPart]->GetPos();
			DiffRot = pNextKeyInfo->GetKey()[nCntPart]->GetRot() - pKeyInfo->GetKey()[nCntPart]->GetRot();

			// 
			DestPos = m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetKey()[nCntPart]->GetPos() + DiffPos * ((float)m_nCounter / (float)m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream());
			DestRot = m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetKey()[nCntPart]->GetRot() + DiffRot * ((float)m_nCounter / (float)m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream());
		}

		// 現在位置の保存
		m_CurrentPos[nCntPart] = m_OffsetPos[nCntPart] + DestPos;
		m_CurrentRot[nCntPart] = m_OffsetRot[nCntPart] + DestRot;

		// 位置を更新
		m_apModel[nCntPart]->SetPos(D3DXVECTOR3(m_CurrentPos[nCntPart]));

		// 向きを更新
		m_apModel[nCntPart]->SetRot(D3DXVECTOR3(m_CurrentRot[nCntPart]));
	}
}

//====================================================
// 終了するかどうか
//====================================================
bool CMotion::isFinish(void)
{
	if (m_apInfo[m_nType]->isLoop() == true)	// もしループをするなら
	{
		return false;
	}
	else										// ループしないなら
	{
		return true;
	}
}

//====================================================
// モーション情報の設定
//====================================================
void CMotion::SetInfo(std::vector<CInfo*> pInfo)
{
	// モーション情報のコピー
	m_apInfo.resize(pInfo.size());
	std::copy(pInfo.begin(), pInfo.end(), m_apInfo.begin());
}

//====================================================
// モデルの設定
//====================================================
void CMotion::SetModel(std::vector<CModel*> pModel)
{
	// リサイズ
	m_apModel.resize(pModel.size());

	// コピー
	std::copy(pModel.begin(), pModel.end(), m_apModel.begin());
}