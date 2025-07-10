//====================================================
//
// �w�i[BG.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include "BG.h"
#include"manager.h"


// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBG::m_pTexture = NULL;
LPDIRECT3DTEXTURE9 CBGManager::m_pTexture[MAX_BG] = { NULL };
CBG* CBGManager::m_apBG[MAX_BG] = { NULL };

////====================================================
//// �R���X�g���N�^
////====================================================
//CBG::CBG()
//{
//	// �l���N���A�ɂ���
//	m_fScroll = 0;
//}

//====================================================
// �R���X�g���N�^
//====================================================
CBG::CBG(int nPriority) :CObject2D(nPriority)
{
	// �l���N���A�ɂ���
	m_fScroll = 0;
	m_fMemScroll = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CBG::~CBG()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CBG::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �|���S���̏�����
	CObject2D::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CBG::Uninit()
{
	// �|���S���̏I������
	CObject2D::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CBG::Update()
{
	if (m_fScroll != 0)
	{
		m_fMemScroll -= m_fScroll;

		// �o�b�t�@�[�̎擾
		LPDIRECT3DVERTEXBUFFER9 pBuff = this->GetBuffer();

		//���_���ւ̃|�C���^
		VERTEX_2D* pVtx = NULL;

		//���_�o�b�t�@�����b�N
		pBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(m_fMemScroll, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f + m_fMemScroll, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_fMemScroll, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f + m_fMemScroll, 1.0f);

		//���_�o�b�t�@�̃A�����b�N
		pBuff->Unlock();

		if (m_fMemScroll > 1.0f)
		{// 1���傫���Ȃ�
			m_fMemScroll -= 1.0f;
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CBG::Draw()
{
	// �|���S���̕`�揈��
	CObject2D::Draw();
}

//====================================================
// �e�N�X�`���̓ǂݍ���
//====================================================
HRESULT CBG::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓Ǎ�
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\BG.jpg",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;
}

//====================================================
// �e�N�X�`���̔j��
//====================================================
void CBG::UnLoad()
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
CBG* CBG::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fScroll)
{
	CBG* pBG = NULL;

	// �������̊m��
	pBG = new CBG;

	// ����������
	pBG->Init(pos, fWidth, fHeight);

	pBG->m_fScroll = fScroll;

	// �e�N�X�`���̊���
	pBG->BindTex(m_pTexture);

	// ��ނ̐ݒ�
	pBG->SetType(CObject::TYPE_BG);

	return pBG;
}

//CBGManager***************************************************************************************************************************************************************

//====================================================
// �R���X�g���N�^
//====================================================
CBGManager::CBGManager(int nPriority):CObject(nPriority)
{
	//�@�Ȃ�
}

//====================================================
// �f�X�g���N�^
//====================================================
CBGManager::~CBGManager()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CBGManager::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apBG[nCnt] = CBG::Create(pos, SCREEN_WIDTH, SCREEN_HEIGHT, Scroll_SPEED * (nCnt + 1));
		m_apBG[nCnt]->BindTex(m_pTexture[nCnt]);
	}
	return S_OK;
}

//====================================================
// �I������
//====================================================
void CBGManager::Uninit()
{
	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CBGManager::Update()
{
}

//====================================================
// �`�揈��
//====================================================
void CBGManager::Draw()
{
}

//====================================================
// �e�N�X�`���̓ǂݍ���
//====================================================
HRESULT CBGManager::Load()
{
	//�e�N�X�`��
	static const char* BG_TEXTURE[MAX_BG] =
	{
		"data\\TEXTURE\\BG001.jpg",
		"data\\TEXTURE\\bg101.png",
		"data\\TEXTURE\\bg102.png",
	};

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//�e�N�X�`���̓Ǎ�
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			BG_TEXTURE[nCnt],
			&m_pTexture[nCnt])))
		{
			return -1;
		}
	}

	return S_OK;
}

//====================================================
// �e�N�X�`���̔j��
//====================================================
void CBGManager::UnLoad()
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{			  
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//====================================================
// ��������
//====================================================
CBGManager* CBGManager::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CBGManager* pBGScroll = NULL;

	 //�������̊m��
	pBGScroll = new CBGManager;

	// ����������
	pBGScroll->Init(pos, fWidth, fHeight);

	// ��ނ̐ݒ�
	pBGScroll->SetType(CObject::TYPE_BG);

	return pBGScroll;
}
