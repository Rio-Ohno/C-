//====================================================
//
// ����[explosion.h]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"explosion.h"
#include"manager.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

////====================================================
//// �R���X�g���N�^
////====================================================
//CExplosion::CExplosion()
//{
//	// �l���N���A
//	m_nCntAnime = 0;
//	m_nPatternAnime = 0;
//}

//====================================================
// �R���X�g���N�^
//====================================================
CExplosion::CExplosion(int nPriority) :CObject2D(nPriority)
{
	// �l���N���A
	m_nCntAnime = 0;
	m_nPatternAnime = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CExplosion::~CExplosion()
{

}

//====================================================
// ����������
//====================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �|���S���̏���������
	CObject2D::Init(pos, fWidth, fHeight);

	// �e�N�X�`�����W�̐ݒ�
	SetTexUV(8.0f, 1.0f);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CExplosion::Uninit(void)
{
	// �|���S���̏I������
	CObject2D::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CExplosion::Update(void)
{
	// �A�j���[�V����
	Anime(8, 1);
}

//====================================================
// �`�揈��
//====================================================
void CExplosion::Draw(void)
{
	// �|���S���̕`�揈��
	CObject2D::Draw();
}

//====================================================
// �A�j���[�V��������
//====================================================
void CExplosion::Anime(int nDiviX, int nDiviY)
{
	//�J�E���g�A�b�v
	m_nCntAnime++;

	if (((m_nCntAnime + 1) % EXPLOSION_ANIME_SPAN) == 0)
	{
		// 0�ɖ߂�
		m_nCntAnime = 0;

		// �A�j���J�E���^�[�J�E���g�A�b�v
		m_nPatternAnime = (m_nPatternAnime + 1) % nDiviX * nDiviY;

		// �o�b�t�@�[�̎擾
		LPDIRECT3DVERTEXBUFFER9 pBuff = GetBuffer();

		//���_���ւ̃|�C���^
		VERTEX_2D* pVtx = NULL;

		//���_�o�b�t�@�����b�N
		pBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((1.0f / nDiviX) * m_nPatternAnime, (1.0f / nDiviY) * (m_nPatternAnime / nDiviX));
		pVtx[1].tex = D3DXVECTOR2((1.0f / nDiviX) * (m_nPatternAnime + 1), (1.0f / nDiviY) * (m_nPatternAnime / nDiviX));
		pVtx[2].tex = D3DXVECTOR2((1.0f / nDiviX) * m_nPatternAnime, (1.0f / nDiviY) * ((m_nPatternAnime / nDiviX) + 1));
		pVtx[3].tex = D3DXVECTOR2((1.0f / nDiviX) * (m_nPatternAnime + 1), (1.0f / nDiviY) * ((m_nPatternAnime / nDiviX) + 1));

		//���_�o�b�t�@�̃A�����b�N
		pBuff->Unlock();

		if (m_nPatternAnime >= nDiviX * nDiviY - 1)
		{
			// �I������
			Uninit();
		}
	}
}

//====================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//====================================================
HRESULT CExplosion::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓Ǎ�
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;

}

//====================================================
// �e�N�X�`���̔j��
//====================================================
void CExplosion::UnLoad(void)
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
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, float fRadius)
{
	CExplosion* pExplosion = NULL;

	// �������̊m��
	pExplosion = new CExplosion;

	// ����������
	pExplosion->Init(pos, fRadius, fRadius);

	//�e�N�X�`���̊���
	pExplosion->BindTex(m_pTexture);

	// ��ނ̐ݒ�
	pExplosion->SetType(CObject::TYPE_EXPLOSION);

	return pExplosion;
}
