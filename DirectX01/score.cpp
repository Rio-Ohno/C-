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
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;
int CScore::m_nScore = 0;

//==================================================== 
// �R���X�g���N�^
//==================================================== 
CScore::CScore(int nPriority) :CObject(nPriority)
{
	// �l���N���A����
	m_nScore = 0;
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
		m_apNumber[nCnt]->CNumber::BindTex(m_pTexture);
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
// �e�N�X�`���̓Ǎ�
//==================================================== 
HRESULT CScore::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓Ǎ�
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;
}

//==================================================== 
// �e�N�X�`���̔j��
//==================================================== 
void CScore::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
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