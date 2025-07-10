//====================================================
//
// �G[enemy.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"enemy.h"
#include"manager.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;

////====================================================
//// �R���X�g���N�^
////====================================================
//CEnemy::CEnemy()
//{
//	//�l���N���A
//	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_fLife = 0;
//}

//====================================================
// �R���X�g���N�^
//====================================================
CEnemy::CEnemy(int nPriority) :CObject2D(nPriority)
{
	//�l���N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLife = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CEnemy::~CEnemy()
{

}

//====================================================
// ����������
//====================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �|���S���̏�����
	CObject2D::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CEnemy::Uninit(void)
{
	// �|���S���̏I������
	CObject2D::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CEnemy::Update(void)
{
}

//====================================================
// �`�揈��
//====================================================
void CEnemy::Draw(void)
{
	// �|���S���̕`�揈��
	CObject2D::Draw();
}

//====================================================
// ��������
//====================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �e�ւ̃|�C���^
	CEnemy* pEnemy = NULL;

	// �������̊m��
	pEnemy = new CEnemy;

	// ����������
	pEnemy->Init(pos, fWidth, fHeight);

	//�e�N�X�`���̊���
	pEnemy->BindTex(m_pTexture);

	// ��ނ̐ݒ�
	pEnemy->SetType(CObject::TYPE_ENEMY);

	return pEnemy;
}

//====================================================
// �e�N�X�`���̓Ǎ�
//====================================================
HRESULT CEnemy::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓Ǎ�
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cat001.png",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;
}

//====================================================
// �e�N�X�`���̔j��
//====================================================
void CEnemy::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}