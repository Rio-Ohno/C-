//==================================================== 
// 
// �X�R�A�@[score.cpp]
// Author: Rio Ohno
// 
//==================================================== 

// �C���N���[�h
#include"score.h"
#include"manager.h"
#include"input.h"

// �ÓI�����o�ϐ�
int CScore::m_nScore = 0;

//==================================================== 
// �R���X�g���N�^
//==================================================== 
CScore::CScore(int nPriority) :CObject(nPriority)
{
	// �l���N���A����
	m_nScore = 0;
	m_Texindx = -1;
}

//==================================================== 
// �f�X�g���N�^
//==================================================== 
CScore::~CScore()
{
	//�@�Ȃ�
}

//==================================================== 
// ����������
//==================================================== 
HRESULT CScore::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGHT; nCnt++)
	{
		pos.x -= (fWidth + nCnt);

		// �����̐����A�e�N�X�`���̊���
		m_apNumber[nCnt] = CNumber::Create(pos, fWidth, fHeight);
		m_apNumber[nCnt]->CNumber::BindTexindx(m_Texindx);
	}
	return S_OK;
}

//==================================================== 
// �I������
//==================================================== 
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGHT; nCnt++)
	{
		// �����̏I������
		m_apNumber[nCnt]->CNumber::Uninit();
	}
	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//==================================================== 
// �X�V����
//==================================================== 
void CScore::Update(void)
{
#if _DEBUG
	//�L�[�{�[�h�̎擾
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetPress(DIK_UP) == true)
	{
		// �X�R�A���Z
		CScore::Add(5);
	}
	else if (pKeyboard->GetPress(DIK_DOWN) == true)
	{
		// �X�R�A���Z
		CScore::Diff(5);
	}

#endif
	// �X�R�A�̐ݒ�
	CScore::SetScore();
}

//==================================================== 
// �`�揈��
//==================================================== 
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGHT; nCnt++)
	{
		// �����̕`�揈��
		m_apNumber[nCnt]->Draw();
	}
}

//==================================================== 
// ��������
//==================================================== 
CScore* CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScore* pScore = NULL;

	// �������̊m��
	pScore = new CScore;

	// �e�N�X�`���C���f�b�N�X�̐ݒ�
	pScore->m_Texindx = CTexture::TYPE_SCORENUMBER;

	// ����������
	pScore->Init(pos, fWidth, fHeight);

	// ��ނ̐ݒ�
	pScore->SetType(TYPE_UI);

	return pScore;
}

//==================================================== 
// �X�R�A�̐ݒ菈��
//==================================================== 
void CScore::SetScore(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGHT; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_nScore,nCnt);
	}

	CDebugProc::Print("score�F%d\n", m_nScore);
}

//==================================================== 
// �X�R�A���Z����
//==================================================== 
void CScore::Add(const int nAdd)
{
	m_nScore += nAdd;
}

//==================================================== 
// �X�R�A���Z����
//==================================================== 
void CScore::Diff(const int nDiff)
{
	if ((m_nScore - nDiff) >= 0)
	{
		m_nScore -= nDiff;
	}
}