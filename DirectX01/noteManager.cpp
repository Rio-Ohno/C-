//====================================================
//
// �����i�A�C�e���j�Ǘ����� [noteManager.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"noteManager.h"
#include"DebugProc.h"
#include"loadnote.h"

// �ÓI�����o�ϐ�
int CNoteManager::m_nNumNote = 0;
CNote* CNoteManager::m_apNote[NUM_NOTE] = { NULL };
CNotePattern* CNoteManager::m_pPattern = { NULL };

//====================================================
// �R���X�g���N�^
//====================================================
CNoteManager::CNoteManager()
{
	// �e�ϐ�������
	m_nNumNote = 0;
	m_pPattern = { NULL };

	for (int nCnt = 0; nCnt < NUM_NOTE; nCnt++)
	{
		m_apNote[nCnt] = { NULL };
	}
}

//====================================================
// �f�X�g���N�^
//====================================================
CNoteManager::~CNoteManager()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CNoteManager::Init(void)
{
	// �X�N���v�g�Ǎ�
	CNoteManager::Load();

	if (m_pPattern == NULL)
	{
		return 0;
	}

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CNoteManager::Uninit(void)
{
	// �p�^�[���̔j��
	if (m_pPattern != NULL)
	{
		// �I������
		m_pPattern->Uninit();

		delete m_pPattern;
		m_pPattern = NULL;
	}

	// �����͎����j��
}

//====================================================
// �X�V����
//====================================================
void CNoteManager::Update(void)
{
	// �Ȃ�
}

//====================================================
// �`�揈��
//====================================================
void CNoteManager::Draw(void)
{
	// �Ȃ�
}

//====================================================
// �p�^�[���Ǎ������̌Ăяo������
//====================================================
void CNoteManager::Load(void)
{
	// �������̊m��
	m_pPattern = new CNotePattern;

	if (m_pPattern != NULL)
	{
		// �e�L�X�g�Ǎ�����
		CLoadNote::Load("data/SCRIPT/NotePattern.txt", m_pPattern);
	}
}

//====================================================
// �����̐�������
//====================================================
void CNoteManager::Spawn()
{
	CNoteInfo* pInfo = { NULL };
	CNotePos* pPos[NUM_NOTE] = { NULL };
	int nPattern = rand() % m_pPattern->GetNumInfo();

	// �ő�p�^�[�����𒴂��Ă��Ȃ��Ȃ�
	if (nPattern <= NUM_PATTERN_NOTE && nPattern >= 0)
	{
		pInfo = m_pPattern->GetNoteInfo()[nPattern];
		
		for (int nCnt = 0; nCnt < pInfo->GetNum(); nCnt++)
		{
			pPos[nCnt] = pInfo->GetNotePos()[nCnt];
		}
	}
	else
	{
		return;
	}

	for (int nCnt = 0; nCnt < pInfo->GetNum(); nCnt++)
	{
		// �����̐���
		m_apNote[nCnt] = CNote::Create(pPos[nCnt]->GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	int i = 0;
}

//====================================================
// ��������
//====================================================
CNoteManager* CNoteManager::Create(void)
{
	CNoteManager* pManager = NULL;

	// �������̊m��
	pManager = new CNoteManager;

	// ����������
	pManager->Init();

	return pManager;
}