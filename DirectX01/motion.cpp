//====================================================
//
// ���[�V����[motion.h]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"motion.h"

// �ÓI�����o�ϐ�
CLoadtxt* CLoadMotion::m_pLoadtxt = NULL;

//====================================================
// �R���X�g���N�^
//====================================================
CMotion::CMotion()
{
	// �l���N���A,������
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		m_apModel[nCnt] = { NULL };	// ���f���ւ̃|�C���^

		m_OffsetPos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_OffsetRot[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_apInfo[nCnt] = { NULL };	// ���[�V�������ւ̃|�C���^
	}

	m_nNumKey = 0;
	m_nNumModel = 0;				// ���f����
	m_bFinish = false;				// �I���������ǂ���

	m_nType = 0;									// ��ނ̐ݒ�
	m_nKey = 0;										// ���݂̃L�[
	m_nNextKey = 0;									// �O�̃L�[
	m_nCounter = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CMotion::~CMotion()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CMotion::Init(CMotion* Motion)
{
	m_nNumModel = Motion->GetNumModel();

	m_nNumKey = Motion->GetNumKey();

	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_apInfo[nCnt] = Motion->GetInfo()[nCnt];
	}
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt] = Motion->GetModel()[nCnt];

		m_OffsetPos[nCnt] = m_apModel[nCnt]->GetPos();
		m_OffsetRot[nCnt] = m_apModel[nCnt]->GetRot();
	}

	m_nNextKey = m_nKey + 1;

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CMotion::Uninit(void)
{
	// ���f���ւ̃|�C���^�̔j��
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			// �I������
			m_apModel[nCnt]->Uninit();

			// �������̊J��
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}

	// ���[�V�������̔j��
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		if (m_apInfo[nCnt] != NULL)
		{
			// �I������
			m_apInfo[nCnt]->Uninit();

			// �������̊J��
			delete m_apInfo[nCnt];
			m_apInfo[nCnt] = NULL;
		}
	}
}

//====================================================
// �ݒ菈��
//====================================================
void CMotion::Set(int nType)
{
	m_nType = nType;
	m_nCounter = 0;

	m_nKey = 0;
	m_nNextKey = 0;

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{// �p�[�c�̈ʒu�E������ݒ�

	}
}

//====================================================
// �X�V����
//====================================================
void CMotion::Update(void)
{
	CKeyInfo* pKeyInfo = m_apInfo[m_nType]->GetKeyInfo(m_nKey);
	CKeyInfo* pNextKeyInfo = m_apInfo[m_nType]->GetKeyInfo(m_nNextKey);

	// ���[�V�����J�E���^�[
	m_nCounter++;

	if (m_nCounter >= m_apInfo[m_nType]->GetKeyInfo(m_nKey)->GetFream())
	{
		m_nCounter = 0;

		if (m_bFinish == false)
		{
			m_nKey++;
			m_nNextKey++;
		}
		if (m_apInfo[m_nType]->isLoop() == true)
		{
			if (m_nKey >= m_nNumKey - 1)
			{// ���̃L�[���L�[�̍ő吔��������
				if (m_nKey > m_nNextKey)
				{// ���̃L�[�����̃L�[�ȏゾ������
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
			if (m_nKey >= m_nNumKey - 1)
			{// ���̃L�[���L�[�̍ő吔��������
				m_bFinish = true;
				m_nNextKey = m_nKey;
				m_nType = 0;
			}
			else if (m_nKey > m_nNextKey)
			{// ���̃L�[�����̃L�[�ȏゾ������
				m_nKey = 0;
			}
		}
	}

	// �S�p�[�c�̍X�V
	for (int nCntPart = 0; nCntPart < m_nNumModel; nCntPart++)
	{
		// �����i�[�p
		D3DXVECTOR3 DiffPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �ʒu
		D3DXVECTOR3 DiffRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// ����

		// �v�Z���ʊi�[�p
		D3DXVECTOR3 DestPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �ʒu
		D3DXVECTOR3 DestRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// ����

		// ����
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

		// �ʒu���X�V
		m_apModel[nCntPart]->SetPos(D3DXVECTOR3(m_OffsetPos[nCntPart] + DestPos));

		// �������X�V
		m_apModel[nCntPart]->SetRot(D3DXVECTOR3(m_OffsetRot[nCntPart] + DestRot));
	}
}

//====================================================
// �I�����邩�ǂ���
//====================================================
bool CMotion::isFinish(void)
{
	if (m_apInfo[m_nType]->isLoop() == true)	// �������[�v������Ȃ�
	{
		return false;
	}
	else										// ���[�v���Ȃ��Ȃ�
	{
		return true;
	}
}

//====================================================
// ���[�V�������̐ݒ�
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
// ���f���̐ݒ�
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

// �e�L�X�g(�X�N���v�g)�Ǎ�-------------------------------------------------------------------------------------------------

//====================================================
// �R���X�g���N�^
//====================================================
CLoadMotion::CLoadMotion()
{
	// �l���N���A,������
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		m_PartPath[nCnt][0] = {};	// ���f���t�@�C���p�X
	}

	m_pLoadtxt = { NULL };			// �e�L�X�g�Ǎ��ւ̃|�C���^
	m_nNumParts = 0;				// �p�[�c��
	m_nModelCount = 0;
	m_nKeyCount = 0;				// �L�[�̃J�E���^
	m_nKeyInfoCount = 0;			// �L�[���̃J�E���^
	m_nInfoCount = 0;				// ���[�V�������̃J�E���^
}

//====================================================
// �f�X�g���N�^
//====================================================
CLoadMotion::~CLoadMotion()
{
	// �Ȃ�
}


//====================================================
// �X�N���v�g�̍ŏ��̓Ǎ�
//====================================================
void CLoadMotion::LoadMotionTXT(const char* pFileName, CMotion* pMotion)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };

	// �O���t�@�C�����J��
	FILE* pFile = fopen(pFileName, "r");

	// �������̊m��
	m_pLoadtxt = new CLoadtxt;

	if (pFile != NULL)
	{
		while (1)
		{
			fgets(cData, 2, pFile);

			if (*cData != '#')
			{
				strcat(cData1, cData);

				if (strcmp(&cData1[0], "SCRIPT") == 0)// SCRIPT�Ȃ�
				{
					// �R�����g��ǂݔ�΂�
					m_pLoadtxt->SkipComment(pFile);

					// ������̏�����
					cData1[0] = { NULL };
					break;
				}
			}
			else
			{
				// �R�����g��ǂݔ�΂�
				m_pLoadtxt->SkipComment(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
		}

		// ������Ǎ���
		LoadMotion(pFile, pMotion);
		fclose(pFile);
	}

	if (m_pLoadtxt != NULL)// ���g������Ȃ�
	{
		// �������̊J��
		delete m_pLoadtxt;
		m_pLoadtxt = NULL;
	}
}

//====================================================
// �X�N���v�g�̓Ǎ�
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
			
			if (strcmp(&cData1[0], "NUM_MODEL") == 0)// NUM_MODEL�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				// ���l�̎擾
				nData = m_pLoadtxt->LoadInt(pFile);

				// �p�[�c���f�����̐ݒ�
				pMotion->SetNumModel(nData);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "MODEL_FILENAME") == 0)// MODEL_FILENAME�Ȃ�
			{
				// =��ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				// ������̎擾
				ModelPath[0] = m_pLoadtxt->LoadPath(pFile, ModelPath[0]);

				// �p�X�̐ݒ�
				strcpy(&m_PartPath[m_nKeyCount][0], ModelPath[0]);
				
				// �p�[�c�̃C���f�b�N�X�J�E���g
				m_nKeyCount++;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "CHARACTERSET") == 0)// CHARACTERSET�Ȃ�
			{
				// �L�����N�^�[���̓Ǎ�
				LoadCharacterInfo(pFile, pMotion);

				// �J�E���^�[�̏�����
				m_nKeyCount = 0;

				//������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "MOTIONSET") == 0)// MOTIONSET�Ȃ�
			{
				// ���[�V�������̓Ǎ�
				apInfo[m_nInfoCount] = LoadInfo(pFile);

				m_nInfoCount++;

				// ������̏�����
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
			// ������̏�����
			cData1[0] = { NULL };

			if (cData[0] == '#')// #�Ȃ�
			{
				// �R�����g��ǂݔ�΂�
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
}

//====================================================
// �L�����N�^�[���̓Ǎ�
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

			if (strcmp(&cData1[0], "NUM_PARTS") == 0)// NUM_PARTS�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				// ���l�̓Ǎ�
				nData = m_pLoadtxt->LoadInt(pFile);

				// �p�[�c���̐ݒ�
				m_nNumParts = nData;

				// ������̏�����
				cData[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "MOVE") == 0)// MOVE�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				// ���l�̓Ǎ�
				fData = m_pLoadtxt->LoadFloat(pFile);

				// �ړ��ʂ̐ݒ�
				m_fSpeed = fData;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "JUMP") == 0)// JUMP�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				// ���l�̓Ǎ�
				fData = m_pLoadtxt->LoadFloat(pFile);

				// �ړ��ʂ̐ݒ�
				m_fJump = fData;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "RADIUS") == 0)// RADIUS�Ȃ�
			{
				// =�̓ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				// ���l�̓Ǎ�
				fData = m_pLoadtxt->LoadFloat(pFile);

				// �ړ��ʂ̐ݒ�
				m_fRadiusShaow = fData;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "PARTSSET") == 0)// PARTSET�Ȃ�
			{
				// �p�[�c���̓Ǎ�
				apModel[m_nModelCount] = LoadModel(pFile, pMotion);

				pMotion->SetModel(apModel);

				// ������̏�����
				cData1[0] = { NULL };

				m_nModelCount++;
			}
			else if (strcmp(&cData1[0], "END_CHARACTERSET") == 0)// END_CHARACTERSET�Ȃ�
			{
				// ������̏�����
				cData1[0] = { NULL };

				m_nModelCount = 0;
				break;
			}
		}
		else
		{
			// ������̏�����
			cData1[0] = { NULL };

			if (cData[0] == '#')// #�Ȃ�
			{
				// �R�����g��ǂݔ�΂�
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
}

//====================================================
// ���f�����̓Ǎ�
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

			if (strcmp(&cData1[0], "INDEX") == 0)// INDEX�Ȃ�
			{
				// =��ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				nData = m_pLoadtxt->LoadInt(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "PARENT") == 0)// PARENT�Ȃ�
			{
				// =��ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				// ���l��Ǎ���
				nParent = m_pLoadtxt->LoadInt(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "POS") == 0)// POS�Ȃ�
			{
				// =��ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				// ���l�̓Ǎ�
				pos.x = m_pLoadtxt->LoadFloat(pFile);
				pos.y = m_pLoadtxt->LoadFloat(pFile);
				pos.z= m_pLoadtxt->LoadFloat(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "ROT") == 0)// ROT�Ȃ�
			{
				// =��ǂݔ�΂�
				m_pLoadtxt->SkipEqual(pFile);

				// ���l�̓Ǎ�
				rot.x = m_pLoadtxt->LoadFloat(pFile);
				rot.y = m_pLoadtxt->LoadFloat(pFile);
				rot.z= m_pLoadtxt->LoadFloat(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_PARTSSET") == 0)// END_PARTSSET�Ȃ�
			{
				// ������̏�����
				cData1[0] = { NULL };

				// �i�[�p���f���|�C���^
				CModel* pParent = NULL;

				// ���f���̐�������
				pModel = CModel::Create(pos, rot, (const char*)m_PartPath[m_nModelCount]);

				// �e���f��������Ȃ�
				if (nParent > -1 && nParent < m_nKeyCount)
				{
					// ���f���̎擾
					pParent = pMotion->GetModel()[nParent];
				}

				// �e���f���̐ݒ�
				pModel->CModel::SetParent(pParent);

				break;
			}
		}
		else
		{
			// ������̏�����
			cData1[0] = { NULL };

			if (cData[0] == '#')// #�Ȃ�
			{
				// �R�����g��ǂݔ�΂�
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
	return pModel;
}

//====================================================
// ���[�V�������̎擾
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
				// �󔒂�ǂݔ�΂�
				m_pLoadtxt->SkipBlank(pFile);

				// ���l��Ǎ���
				bLoop = (bool)m_pLoadtxt->LoadInt(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "NUM_KEY") == 0)
			{
				// �󔒂�ǂݔ�΂�
				m_pLoadtxt->SkipBlank(pFile);

				// ���l�̓Ǎ�
				nNumKay = m_pLoadtxt->LoadInt(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "KEYSET") == 0)
			{
				// �L�[���̓Ǎ�
				apKeyInfo[m_nKeyInfoCount] = LoadKeyInfo(pFile);

				m_nKeyInfoCount++;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_MOTIONSET") == 0)
			{
				pInfo = CInfo::Create(bLoop, nNumKay);

				pInfo->SetKeyInfo(apKeyInfo);

				m_nKeyInfoCount = 0;

				// ������̏�����
				cData1[0] = { NULL };
				break;
			}
		}
		else
		{
			// ������̏�����
			cData1[0] = { NULL };

			if (cData[0] == '#')// #�Ȃ�
			{
				// �R�����g��ǂݔ�΂�
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
	return pInfo;
}

//====================================================
// �L�[���̎擾
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
				// �󔒂�ǂݔ�΂�
				m_pLoadtxt->SkipBlank(pFile);

				// ���l��Ǎ���
				nFream = m_pLoadtxt->LoadInt(pFile);

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "KEY") == 0)
			{
				// �L�[�̓Ǎ�
				apKey[m_nKeyCount] = LoadKey(pFile);

				m_nKeyCount++;

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_KEYSET") == 0)
			{
				// �L�[���̐���
				pKeyInfo = CKeyInfo::Create(nFream);

				// �L�[�̐ݒ�
				pKeyInfo->SetKey(apKey);

				m_nKeyCount = 0;

				// ������̏�����
				cData1[0] = { NULL };
				break;
			}
		}
		else
		{
			// ������̏�����
			cData1[0] = { NULL };

			if (cData[0] == '#')// #�Ȃ�
			{
				// �R�����g��ǂݔ�΂�
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}
	return pKeyInfo;
}

//====================================================
// �L�[�̓Ǎ�����
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
				// �󔒂�ǂݔ�΂�
				m_pLoadtxt->SkipBlank(pFile);

				// ���l��Ǎ���
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					afPos[nCnt] = m_pLoadtxt->LoadFloat(pFile);
				}

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				// �󔒂�ǂݔ�΂�
				m_pLoadtxt->SkipBlank(pFile);

				// ���l��Ǎ���
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					afRot[nCnt] = m_pLoadtxt->LoadFloat(pFile);
				}

				// ������̏�����
				cData1[0] = { NULL };
			}
			else if (strcmp(&cData1[0], "END_KEY") == 0)
			{
				// �L�[�̐���
				pKey = CKEY::Create(afPos[0], afPos[1], afPos[2], afRot[0], afRot[1], afRot[2]);

				// ������̏�����
				cData1[0] = { NULL };

				break;
			}
		}
		else
		{
			// ������̏�����
			cData1[0] = { NULL };

			if (cData[0] == '#')// #�Ȃ�
			{
				// �R�����g��ǂݔ�΂�
				m_pLoadtxt->SkipComment(pFile);
			}
		}
	}

	return pKey;
}

//====================================================
// �Ǎ���������Ԃ�
//====================================================
CMotion* CLoadMotion::Load(const char* pFileName, CMotion* pMotion)
{
	CLoadMotion* pLoad = NULL;

	pLoad = new CLoadMotion;

	// �e�L�X�g�Ǎ�
	pLoad->LoadMotionTXT(pFileName, pMotion);

	// �������̊J��
	delete pLoad;
	pLoad = NULL;

	return pMotion;
}