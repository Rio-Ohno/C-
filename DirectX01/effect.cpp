//====================================================
//
// �G�t�F�N�g[effect.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"effect.h"
#include"manager.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//====================================================
// �R���X�g���N�^
//====================================================
CEffect::CEffect(int nPriority):CObject2D(nPriority)
{
	// �l���N���A
	m_nLife = 0;
	m_fDelSize = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CEffect::~CEffect()
{

}

//====================================================
// ��������
//====================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius, int nLife, float fDelSize)
{
	// ���݂̃I�u�W�F�N�g�����擾
	int nNumAll = CObject::GetNumAll();

	if (nNumAll >= MAX_OBJECT || nLife <= 0)
	{// ����ȏ�Ȃ�
		return NULL;
	}

	// �G�t�F�N�g�ւ̃|�C���^
	CEffect* pEffect = NULL;

	// �������̊m��
	pEffect = new CEffect;

	// �G�t�F�N�g�̏���������
	pEffect->Init(pos, fRadius, fRadius);

	//�e�N�X�`���̊���
	pEffect->BindTex(m_pTexture);

	// �����o�ϐ��̐ݒ�
	pEffect->m_nLife = nLife;
	pEffect->m_move = move;

	// �T�C�Y������������W���̐ݒ�
	pEffect->m_fDelSize = fDelSize;

	return pEffect;
}

//====================================================
// ����������
//====================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �|���S���̏���������
	CObject2D::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CEffect::Uninit(void)
{
	// �|���S���̏I������
	CObject2D::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CEffect::Update(void)
{
	// ���������炷
	m_nLife--;

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObject2D::GetPos();

	if (m_nLife <= 0)
	{
		// �G�t�F�N�g�̏I������
		CEffect::Uninit();
	}
	else if (pos.x <= 0.0f ||
		pos.x >= SCREEN_WIDTH ||
		pos.y <= 0.0f ||
		pos.y >= SCREEN_HEIGHT)
	{// ��ʊO�ɏo����

		// �G�t�F�N�g�̏I������
		CEffect::Uninit();
	}
	else
	{
		if (m_fDelSize != 0)
		{// �T�C�Y������������W��������Ȃ�
			// ���a�̎擾
			float fRadius = CObject2D::GetWidth();

			// ���a������������
			fRadius *= m_fDelSize;

			// �T�C�Y�̐ݒ�
			CObject2D::SetSize(fRadius, fRadius);
		}

		// �ʒu�̍X�V
		pos += m_move;
		CObject2D::SetPos(pos);
	}
}

//====================================================
// �`�揈��
//====================================================
void CEffect::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �|���S���̕`�揈��
	CObject2D::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//====================================================
// �e�N�X�`���̓Ǎ�
//====================================================
HRESULT CEffect::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓Ǎ�
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&m_pTexture)))
	{
		return -1;
	}

	return S_OK;
}

//====================================================
// �e�N�X�`���̔j��
//====================================================
void CEffect::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}