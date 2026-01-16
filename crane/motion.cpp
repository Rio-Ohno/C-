//====================================================
//
// モーション[motion.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"motion.h"

// 静的メンバ変数
CLoadtxt* CLoadMotion::m_pLoadtxt = nullptr;

//====================================================
// コンストラクタ
//====================================================
CMotion::CMotion()
{
	// 値をクリア,初期化
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		m_apModel[nCnt] = { nullptr };	// モデルへのポインタ

		m_OffsetPos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_OffsetRot[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_apInfo[nCnt] = { nullptr };	// モーション情報へのポインタ
	}

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

	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		if (Motion->GetInfo()[nCnt] != nullptr)
		{
			m_apInfo[nCnt] = Motion->GetInfo()[nCnt];
		}
	}

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt] = Motion->GetModel()[nCnt];

		m_OffsetPos[nCnt] = m_apModel[nCnt]->GetPos();
		m_OffsetRot[nCnt] = m_apModel[nCnt]->GetRot();
	}

	return S_OK;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CMotion::Init(CInfo** pInfo, CModel** pModel, int NumModel, D3DXVECTOR3* OffsetPos, D3DXVECTOR3* OffsetRot)
{
	m_nNumModel = NumModel;

	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		if (pInfo[nCnt] != nullptr)
		{
			m_apInfo[nCnt] = pInfo[nCnt];
		}
	}

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt] = pModel[nCnt];

		m_OffsetPos[nCnt] = OffsetPos[nCnt];
		m_OffsetRot[nCnt] = OffsetRot[nCnt];
	}

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CMotion::Uninit(void)
{
	// モーション情報の破棄
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
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
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
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
		m_bFinish = false;
	}
}

//====================================================
// 更新処理
//====================================================
void CMotion::Update(void)
{
	if (!m_bStop)// モーションを止めてないなら
	{
		// モーションカウンター
		m_nCounter++;

		if (m_nCounter >= m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream())
		{
			// モーションカウンタリセット
			m_nCounter = 0;

			if (m_bFinish == false)
			{
				m_nKey++;
				m_nNextKey++;
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
		for (int nCntPart = 0; nCntPart < m_nNumModel; nCntPart++)
		{
			// 差分格納用
			D3DXVECTOR3 DiffPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 位置
			D3DXVECTOR3 DiffRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 向き

			// 計算結果格納用
			D3DXVECTOR3 DestPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 位置
			D3DXVECTOR3 DestRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 向き

			if (m_apInfo[m_nType]->GetNumKey() > 1)
			{
				// 差分
				DiffPos.x = pNextKeyInfo->GetKey()[nCntPart]->GetPos("X") - pKeyInfo->GetKey()[nCntPart]->GetPos("X");
				DiffPos.y = pNextKeyInfo->GetKey()[nCntPart]->GetPos("Y") - pKeyInfo->GetKey()[nCntPart]->GetPos("Y");
				DiffPos.z = pNextKeyInfo->GetKey()[nCntPart]->GetPos("Z") - pKeyInfo->GetKey()[nCntPart]->GetPos("Z");

				DiffRot.x = pNextKeyInfo->GetKey()[nCntPart]->GetRot("X") - pKeyInfo->GetKey()[nCntPart]->GetRot("X");
				DiffRot.y = pNextKeyInfo->GetKey()[nCntPart]->GetRot("Y") - pKeyInfo->GetKey()[nCntPart]->GetRot("Y");
				DiffRot.z = pNextKeyInfo->GetKey()[nCntPart]->GetRot("Z") - pKeyInfo->GetKey()[nCntPart]->GetRot("Z");

				// 
				DestPos.x = m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetKey()[nCntPart]->GetPos("X") + (DiffPos.x * ((float)m_nCounter / (float)m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream()));
				DestPos.y = m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetKey()[nCntPart]->GetPos("Y") + (DiffPos.y * ((float)m_nCounter / (float)m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream()));
				DestPos.z = m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetKey()[nCntPart]->GetPos("Z") + (DiffPos.z * ((float)m_nCounter / (float)m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream()));

				DestRot.x = m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetKey()[nCntPart]->GetRot("X") + DiffRot.x * ((float)m_nCounter / (float)m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream());
				DestRot.y = m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetKey()[nCntPart]->GetRot("Y") + DiffRot.y * ((float)m_nCounter / (float)m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream());
				DestRot.z = m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetKey()[nCntPart]->GetRot("Z") + DiffRot.z * ((float)m_nCounter / (float)m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream());
			}

			// 現在位置の保存
			m_CurrentPos[nCntPart] = m_OffsetPos[nCntPart] + DestPos;
			m_CurrentRot[nCntPart] = m_OffsetRot[nCntPart] + DestRot;

			// 位置を更新
			m_apModel[nCntPart]->SetPos(D3DXVECTOR3(m_OffsetPos[nCntPart] + DestPos));

			// 向きを更新
			m_apModel[nCntPart]->SetRot(D3DXVECTOR3(m_OffsetRot[nCntPart] + DestRot));
		}
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
void CMotion::SetInfo(CInfo** pInfo)
{
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		if (pInfo[nCnt] != NULL)
		{
			m_apInfo[nCnt] = pInfo[nCnt];
		}
	}
}

//====================================================
// モデルの設定
//====================================================
void CMotion::SetModel(CModel** pModel)
{
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		if (pModel != NULL)
		{
			m_apModel[nCnt] = pModel[nCnt];
		}
	}
}

// テキスト(スクリプト)読込-------------------------------------------------------------------------------------------------

//====================================================
// コンストラクタ
//====================================================
CLoadMotion::CLoadMotion()
{
	// 値をクリア,初期化
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		m_PartPath[nCnt][0] = {};	// モデルファイルパス
	}

	m_pLoadtxt = { NULL };			// テキスト読込へのポインタ
	m_nNumParts = 0;				// パーツ数
	m_nModelCount = 0;
	m_nKeyCount = 0;				// キーのカウンタ
	m_nKeyInfoCount = 0;			// キー情報のカウンタ
	m_nInfoCount = 0;				// モーション情報のカウンタ
	m_fJump = 0.0f;
	m_fSpeed = 0.0f;
	m_fRadiusShaow = 0.0f;
}

//====================================================
// デストラクタ
//====================================================
CLoadMotion::~CLoadMotion()
{
	// なし
}


//====================================================
// スクリプトの最初の読込
//====================================================
void CLoadMotion::LoadMotionTXT(const char* pFileName, CMotion* pMotion)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };

	// 外部ファイルを開く
	FILE* pFile = fopen(pFileName, "r");

	// メモリの確保
	m_pLoadtxt = new CLoadtxt;

	if (pFile != NULL)
	{
		while (1)
		{
			fgets(cData, 2, pFile);

			if (*cData != '#')
			{
				strcat(cData1, cData);

				if (strcmp(&cData1[0], "SCRIPT") == 0)// SCRIPTなら
				{
					// コメントを読み飛ばす
					m_pLoadtxt->SkipComment(pFile);

					// 文字列の初期化
					cData1[0] = { NULL };
					break;
				}
			}
			else
			{
				// コメントを読み飛ばす
				m_pLoadtxt->SkipComment(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
		}

		// 続きを読込む
		LoadMotion(pFile, pMotion);
		fclose(pFile);
	}

	if (m_pLoadtxt != NULL)// 中身があるなら
	{
		// メモリの開放
		delete m_pLoadtxt;
		m_pLoadtxt = NULL;
	}
}

//====================================================
// スクリプトの読込
//====================================================
void CLoadMotion::LoadMotion(FILE* pFile, CMotion* pMotion)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	char* ModelPath[32] = { NULL };
	int nData = 0;
	CInfo* apInfo[MAX_MOTION] = {NULL};

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
			
			if (strcmp(&cData1[0], "NUM_MODEL") == 0)// NUM_MODELなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の取得
				nData = m_pLoadtxt->LoadInt(pFile);

				// パーツモデル数の設定
				pMotion->SetNumModel(nData);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "MODEL_FILENAME") == 0)// MODEL_FILENAMEなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 文字列の取得
				ModelPath[0] = m_pLoadtxt->LoadPath(pFile, ModelPath[0]);

				// パスの設定
				strcpy(&m_PartPath[m_nKeyCount][0], ModelPath[0]);
				
				// パーツのインデックスカウント
				m_nKeyCount++;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "CHARACTERSET") == 0)// CHARACTERSETなら
			{
				// キャラクター情報の読込
				LoadCharacterInfo(pFile, pMotion);

				// カウンターの初期化
				m_nKeyCount = 0;

				//文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "MOTIONSET") == 0)// MOTIONSETなら
			{
				// モーション情報の読込
				apInfo[m_nInfoCount] = LoadInfo(pFile);

				m_nInfoCount++;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_SCRIPT") == 0)
			{
				pMotion->SetInfo(apInfo);
				m_nInfoCount = 0;
				break;
			}
		}
		else
		{
			// 文字列の初期化
			cData1[0] = { NULL };

			if (cData[0] == '#')// #なら
			{
				// コメントを読み飛ばす
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
}

//====================================================
// キャラクター情報の読込
//====================================================
void CLoadMotion::LoadCharacterInfo(FILE* pFile, CMotion* pMotion)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	int nData = 0;
	float fData = 0.0f;
	CModel* apModel[MAX_PART];

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "NUM_PARTS") == 0)// NUM_PARTSなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				nData = m_pLoadtxt->LoadInt(pFile);

				// パーツ数の設定
				m_nNumParts = nData;

				// 文字列の初期化
				cData[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "MOVE") == 0)// MOVEなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				fData = m_pLoadtxt->LoadFloat(pFile);

				// 移動量の設定
				m_fSpeed = fData;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "JUMP") == 0)// JUMPなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				fData = m_pLoadtxt->LoadFloat(pFile);

				// 移動量の設定
				m_fJump = fData;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "RADIUS") == 0)// RADIUSなら
			{
				// =の読み飛ばし
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				fData = m_pLoadtxt->LoadFloat(pFile);

				// 移動量の設定
				m_fRadiusShaow = fData;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "PARTSSET") == 0)// PARTSETなら
			{
				// パーツ情報の読込
				apModel[m_nModelCount] = LoadModel(pFile, pMotion);

				pMotion->SetModel(apModel);

				// 文字列の初期化
				cData1[0] = { NULL };

				m_nModelCount++;
			}
			else if (strcmp(&cData1[0], "END_CHARACTERSET") == 0)// END_CHARACTERSETなら
			{
				// 文字列の初期化
				cData1[0] = { NULL };

				m_nModelCount = 0;
				break;
			}
		}
		else
		{
			// 文字列の初期化
			cData1[0] = { NULL };

			if (cData[0] == '#')// #なら
			{
				// コメントを読み飛ばす
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
}

//====================================================
// モデル情報の読込
//====================================================
CModel* CLoadMotion::LoadModel(FILE* pFile, CMotion* pMotion)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	int nParent = 0;
	int nData = 0;
	D3DXVECTOR3 pos = {};
	D3DXVECTOR3 rot = {};
	CModel* pModel = NULL;

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "INDEX") == 0)// INDEXなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				nData = m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "PARENT") == 0)// PARENTなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				nParent = m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "POS") == 0)// POSなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				pos.x = m_pLoadtxt->LoadFloat(pFile);
				pos.y = m_pLoadtxt->LoadFloat(pFile);
				pos.z = m_pLoadtxt->LoadFloat(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "ROT") == 0)// ROTなら
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				rot.x = m_pLoadtxt->LoadFloat(pFile);
				rot.y = m_pLoadtxt->LoadFloat(pFile);
				rot.z = m_pLoadtxt->LoadFloat(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_PARTSSET") == 0)// END_PARTSSETなら
			{
				// 文字列の初期化
				cData1[0] = { NULL };

				// 格納用モデルポインタ
				CModel* pParent = NULL;

				// モデルの生成処理
				pModel = CModel::Create(pos, rot, (const char*)m_PartPath[m_nModelCount]);

				// 親モデルがあるなら
				if (nParent > -1 && nParent < m_nKeyCount)
				{
					// モデルの取得
					pParent = pMotion->GetModel()[nParent];
				}

				// 親モデルの設定
				pModel->CModel::SetParent(pParent);

				break;
			}
		}
		else
		{
			// 文字列の初期化
			cData1[0] = { NULL };

			if (cData[0] == '#')// #なら
			{
				// コメントを読み飛ばす
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
	return pModel;
}

//====================================================
// モーション情報の取得
//====================================================
CInfo* CLoadMotion::LoadInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	int nNumKay = 0;
	bool bLoop = false;
	CInfo* pInfo = { NULL };
	CKeyInfo* apKeyInfo[MAX_KEY_INFO] = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "LOOP") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				bLoop = (bool)m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "NUM_KEY") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値の読込
				nNumKay = m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "KEYSET") == 0)
			{
				// キー情報の読込
				apKeyInfo[m_nKeyInfoCount] = LoadKeyInfo(pFile);

				m_nKeyInfoCount++;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_MOTIONSET") == 0)
			{
				pInfo = CInfo::Create(bLoop, nNumKay);

				pInfo->SetKeyInfo(apKeyInfo);

				m_nKeyInfoCount = 0;

				// 文字列の初期化
				cData1[0] = { NULL };
				break;
			}
		}
		else
		{
			// 文字列の初期化
			cData1[0] = { NULL };

			if (cData[0] == '#')// #なら
			{
				// コメントを読み飛ばす
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
	return pInfo;
}

//====================================================
// キー情報の取得
//====================================================
CKeyInfo* CLoadMotion::LoadKeyInfo(FILE*pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	int nFream = 0;
	CKEY* apKey[MAX_KEY] = { NULL };
	CKeyInfo* pKeyInfo = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "FRAME") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				nFream = m_pLoadtxt->LoadInt(pFile);

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "KEY") == 0)
			{
				// キーの読込
				apKey[m_nKeyCount] = LoadKey(pFile);

				m_nKeyCount++;

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_KEYSET") == 0)
			{
				// キー情報の生成
				pKeyInfo = CKeyInfo::Create(nFream);

				// キーの設定
				pKeyInfo->SetKey(apKey);

				m_nKeyCount = 0;

				// 文字列の初期化
				cData1[0] = { NULL };
				break;
			}
		}
		else
		{
			// 文字列の初期化
			cData1[0] = { NULL };

			if (cData[0] == '#')// #なら
			{
				// コメントを読み飛ばす
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
	return pKeyInfo;
}

//====================================================
// キーの読込処理
//====================================================
CKEY* CLoadMotion::LoadKey(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	float afPos[3] = {};
	float afRot[3] = {};
	CKEY* pKey = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);

		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);

			if (strcmp(&cData1[0], "POS") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					afPos[nCnt] = m_pLoadtxt->LoadFloat(pFile);
				}

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				// =を読み飛ばす
				m_pLoadtxt->SkipEqual(pFile);

				// 数値を読込む
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					afRot[nCnt] = m_pLoadtxt->LoadFloat(pFile);
				}

				// 文字列の初期化
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_KEY") == 0)
			{
				// キーの生成
				pKey = CKEY::Create(afPos[0], afPos[1], afPos[2], afRot[0], afRot[1], afRot[2]);

				// 文字列の初期化
				cData1[0] = { NULL };

				break;
			}
		}
		else
		{
			// 文字列の初期化
			cData1[0] = { NULL };

			if (cData[0] == '#')// #なら
			{
				// コメントを読み飛ばす
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}

	return pKey;
}

//====================================================
// 読込した情報を返す
//====================================================
CMotion* CLoadMotion::Load(const char* pFileName, CMotion* pMotion)
{
	CLoadMotion* pLoad = NULL;

	pLoad = new CLoadMotion;

	// テキスト読込
	pLoad->LoadMotionTXT(pFileName, pMotion);

	// メモリの開放
	delete pLoad;
	pLoad = NULL;

	return pMotion;
}

//====================================================
// モーション情報クラスのコンストラクタ
//====================================================
CMotionInfo::CMotionInfo()
{
	// 値をクリア,初期化
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		m_apModel[nCnt] = { nullptr };	// モデルへのポインタ

		m_OffsetPos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_OffsetRot[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_apInfo[nCnt] = { nullptr };	// モーション情報へのポインタ
	}
	
	m_nNumModel = 0;
}

//====================================================
// モーション情報クラスのコピーコンストラクタ
//====================================================
CMotionInfo::CMotionInfo(const CMotionInfo& other)
{
	memcpy(this->m_apInfo, other.m_apInfo, sizeof(this->m_apInfo));
	memcpy(this->m_apModel, other.m_apModel, sizeof(this->m_apModel));
	memcpy(this->m_OffsetPos, other.m_OffsetPos, sizeof(this->m_OffsetPos));
	memcpy(this->m_OffsetRot, other.m_OffsetRot, sizeof(this->m_OffsetRot));
	this->m_nNumModel = other.m_nNumModel;
}

//====================================================
// モーション情報クラスの終了処理
//====================================================
void CMotionInfo::Uninit(void)
{
	// モーション情報の破棄
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
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
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
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
void CMotionInfo::SetInfo(CInfo** pInfo)
{
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		if (pInfo[nCnt] != nullptr)
		{
			m_apInfo[nCnt] = pInfo[nCnt];
		}
	}
}

//====================================================
// モデル情報の設定処理
//====================================================
void CMotionInfo::SetModel(CModel** pModel)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt] = pModel[nCnt];

		m_OffsetPos[nCnt] = m_apModel[nCnt]->GetPos();
		m_OffsetRot[nCnt] = m_apModel[nCnt]->GetRot();
	}
}