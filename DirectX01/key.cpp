//====================================================
//
// ���[�V�����̃L�[[key.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"key.h"
#include<string.h>

//====================================================
// �p�[�c�̃R���X�g���N�^
//====================================================
CKEY::CKEY()
{
	// �e�ϐ����N���A
	m_fposX = 0;
	m_fposY = 0;
	m_fposZ = 0;

	m_frotX = 0;
	m_frotY = 0;
	m_frotZ = 0;
}

//====================================================
// �p�[�c�̃f�X�g���N�^
//====================================================
CKEY::~CKEY()
{
	// �Ȃ�
}

//====================================================
// �p�[�c�̐�������
//====================================================
CKEY* CKEY::Create(float fposX, float fposY, float fposZ, float frotX, float frotY, float frotZ)
{
	CKEY* pKey = NULL;

	// �������̊m��
	pKey = new CKEY;

	// �e�ϐ��̐ݒ�
	pKey->m_fposX = fposX;
	pKey->m_fposY = fposY;
	pKey->m_fposZ = fposZ;

	pKey->m_frotX = frotX;
	pKey->m_frotY = frotY;
	pKey->m_frotZ = frotZ;

	return pKey;
}

//====================================================
// �p�[�c�̈ʒu�̎擾����
//====================================================
float CKEY::GetPos(const char* Axis)
{
	float pos = 0.0f;

	if (strcmp(Axis, "X") == 0 || strcmp(Axis, "x") == 0)// X�Ȃ�
	{
		// �ʒu(X��)����
		pos = this->m_fposX;
	}
	else if (strcmp(Axis, "Y") == 0 || strcmp(Axis, "y") == 0)// Y�Ȃ�
	{
		// �ʒu(Y��)����
		pos = this->m_fposY;
	}
	else if (strcmp(Axis, "Z") == 0 || strcmp(Axis, "z") == 0)// Z�Ȃ�
	{
		// �ʒu(Z��)����
		pos = this->m_fposZ;
	}

	return pos;
}

//====================================================
// �p�[�c�̌����̎擾����
//====================================================
float CKEY::GetRot(const char* Axis)
{
	float rot = 0.0f;

	if (strcmp(Axis, "X") == 0 || strcmp(Axis, "x") == 0)// X�Ȃ�
	{
		// �ʒu(X��)����
		rot = this->m_frotX;
	}
	else if (strcmp(Axis, "Y") == 0 || strcmp(Axis, "y") == 0)// Y�Ȃ�
	{
		// �ʒu(Y��)����
		rot = this->m_frotY;
	}
	else if (strcmp(Axis, "Z") == 0 || strcmp(Axis, "z") == 0)// Z�Ȃ�
	{
		// �ʒu(Z��)����
		rot = this->m_frotZ;
	}

	return rot;
}

//====================================================
// �L�[�̃R���X�g���N�^
//====================================================
CKeyInfo::CKeyInfo()
{
	// �l���N���A
	for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
	{
		m_apKey[nCnt] = { NULL };
	}
	m_nFream = 0;
}

//====================================================
// �L�[�̃f�X�g���N�^
//====================================================
CKeyInfo::~CKeyInfo()
{
	// �Ȃ�
}

//====================================================
// �L�[�̐�������
//====================================================
CKeyInfo* CKeyInfo::Create(int nFream)
{
	CKeyInfo* pKeyInfo = NULL;

	// �������̊m��
	pKeyInfo = new CKeyInfo;

	// �ϐ��̐ݒ�
	pKeyInfo->m_nFream = nFream;

	return pKeyInfo;
}

//====================================================
// �p�[�c�̐ݒ菈��
//====================================================
void CKeyInfo::SetKey(CKEY** pKey)
{
	for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
	{
		if (pKey[nCnt] != NULL)
		{
			m_apKey[nCnt] = pKey[nCnt];
		}
	}
}

//====================================================
// �L�[�̐�������
//====================================================
void CKeyInfo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
	{
		if (m_apKey[nCnt] != NULL)
		{
			delete m_apKey[nCnt];
			m_apKey[nCnt] = NULL;
		}
	}
}

//====================================================
// ���[�V�������̃R���X�g���N�^
//====================================================
CInfo::CInfo()
{
	// �l���N���A�ɂ���
	for (int nCnt = 0; nCnt < MAX_KEY_INFO; nCnt++)
	{
		m_apKeyInfo[nCnt] = { NULL };
	}
	m_bLoop = 0;
	m_nNumKey = 0;
}

//====================================================
// ���[�V�������̃f�X�g���N�^
//====================================================
CInfo::~CInfo()
{
	// �Ȃ�
}

//====================================================
// ���[�V�������̐�������
//====================================================
CInfo* CInfo::Create(bool Loop, int nNumKey)
{
	CInfo* pInfo = NULL;

	// �������̊m��
	pInfo = new CInfo;

	// �e�ϐ��̐ݒ�
	pInfo->m_bLoop = Loop;
	pInfo->m_nNumKey = nNumKey;

	return pInfo;
}

//====================================================
// �L�[����ݒ肷�鏈��
//====================================================
void CInfo::SetKeyInfo(CKeyInfo** pKeyInfo)
{
	for (int nCnt = 0; nCnt < MAX_KEY_INFO; nCnt++)
	{
		// �L�[���̐�������
		m_apKeyInfo[nCnt] = pKeyInfo[nCnt];
	}
}

//====================================================
// ���[�V�������̏I������
//====================================================
void CInfo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_KEY_INFO; nCnt++)
	{
		if (m_apKeyInfo[nCnt] != NULL)
		{
			m_apKeyInfo[nCnt]->Uninit();

			// �������̊J��
			delete m_apKeyInfo[nCnt];
			m_apKeyInfo[nCnt] = NULL;
		}
	}
}