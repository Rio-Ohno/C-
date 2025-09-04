//====================================================
//
// �����̏o���p�^�[�����[notePattern.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"notePattern.h"

// �ÓI�����o�ϐ�
int CNotePattern::m_nMaxNum = 0;
int CNotePattern::m_nNumInfo = 0;

//====================================================
// �����̈ʒu���̃R���X�g���N�^
//====================================================
CNotePos::CNotePos()
{
	// �e�ϐ��̏���������
	m_PosX = 0.0f;
	m_PosY = 0.0f;
	m_PosZ = 0.0f;
}

//====================================================
// �����̈ʒu���̃f�X�g���N�^
//====================================================
CNotePos::~CNotePos()
{
	// �Ȃ�
}

//====================================================
// �����̈ʒu���̈ʒu�擾����
//====================================================
D3DXVECTOR3 CNotePos::GetPos(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(m_PosX, m_PosY, m_PosZ);

	return pos;
}

//====================================================
// �����̈ʒu���̐�������
//====================================================
CNotePos* CNotePos::Create(float posX, float posY, float posZ)
{
	CNotePos* pPos = NULL;

	// �������̊m��
	pPos = new CNotePos;

	// �e�ϐ��̐ݒ�
	pPos->m_PosX = posX;
	pPos->m_PosY = posY;
	pPos->m_PosZ = posZ;

	return pPos;
}

//====================================================
// �����̃p�^�[�����̃R���X�g���N�^
//====================================================
CNoteInfo::CNoteInfo()
{
	// �e�ϐ��̏�����
	m_nNum = 0;

	for (int nCnt = 0; nCnt < NUM_NOTE; nCnt++)
	{
		m_apPos[nCnt] = { NULL };
	}
}

//====================================================
// �����̃p�^�[�����̃f�X�g���N�^
//====================================================
CNoteInfo::~CNoteInfo()
{
	// �Ȃ�
}

//====================================================
// �����̃p�^�[�����̏I������
//====================================================
void CNoteInfo::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_NOTE; nCnt++)
	{
		if (m_apPos[nCnt] != NULL)
		{
			// �������̔j��
			delete m_apPos[nCnt];
			m_apPos[nCnt] = { NULL };
		}
	}
}

//====================================================
// �����̈ʒu���̐ݒ菈��
//====================================================
void CNoteInfo::SetNotePos(CNotePos** pNotePos)
{
	for (int nCnt = 0; nCnt < NUM_NOTE; nCnt++)
	{
		if (pNotePos[nCnt] != NULL)
		{
			m_apPos[nCnt] = pNotePos[nCnt];
		}
	}
}

//====================================================
// �����̃p�^�[�����̐�������
//====================================================
CNoteInfo* CNoteInfo::Create(int nNum)
{
	CNoteInfo* pInfo = NULL;

	// �������̊m��
	pInfo = new CNoteInfo;

	// �e�ϐ��̐ݒ�
	pInfo->m_nNum = nNum;

	return pInfo;
}

//====================================================
// �p�^�[�����̃R���X�g���N�^
//====================================================
CNotePattern::CNotePattern()
{
	// �e�ϐ��̏�����
	m_nMaxNum = 0;
	m_nNumInfo = 0;

	for (int nCnt = 0; nCnt < NUM_PATTERN_NOTE; nCnt++)
	{
		m_apInfo[nCnt] = { NULL };
	}
}

//====================================================
// �p�^�[�����̃f�X�g���N�^
//====================================================
CNotePattern::~CNotePattern()
{
	// �Ȃ�
}

//====================================================
// �p�^�[�����̏I������
//====================================================
void CNotePattern::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PATTERN_NOTE; nCnt++)
	{
		if (m_apInfo[nCnt] != NULL)
		{
			// �I������
			m_apInfo[nCnt]->Uninit();

			// �������̔j��
			delete m_apInfo[nCnt];
			m_apInfo[nCnt] = NULL;
		}
	}
}

//====================================================
// �����̃p�^�[�����̐ݒ菈��
//====================================================
void CNotePattern::SetNoteInfo(CNoteInfo** pNoteInfo)
{
	for (int nCnt = 0; nCnt < NUM_PATTERN_NOTE; nCnt++)
	{
		if (pNoteInfo[nCnt] != NULL)
		{
			m_apInfo[nCnt] = pNoteInfo[nCnt];
		}
	}
}

//====================================================
// �p�^�[�����̐�������
//====================================================
CNotePattern* CNotePattern::Create(const int nMaxNum)
{
	CNotePattern* pPattern = NULL;

	// �������̊m��
	pPattern->m_nMaxNum = nMaxNum;

	return pPattern;
}