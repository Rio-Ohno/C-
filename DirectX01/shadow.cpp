//====================================================
//
// �e[shadow.h]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"shadow.h"
#include"manager.h"
#include"texture.h"

// �ÓI�����o�ϐ�
int CShadow::m_nTexture = { NULL };

//====================================================
// �R���X�g���N�^
//====================================================
CShadow::CShadow()
{
	// �Ȃ�
}

//====================================================
// �f�X�g���N�^
//====================================================
CShadow::~CShadow()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CShadow::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �|���S���̏���������
	CObject3D::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CShadow::Uninit(void)
{
	// �|���S���̏I������
	CObject3D::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CShadow::Update(void)
{
	// �Ȃ�
}

//====================================================
// �`�揈��
//====================================================
void CShadow::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//// �A���t�@�e�X�g
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0.05f);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �|���S���̕`�揈��
	CObject3D::Draw();

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//// �A���t�@�e�X�g�𖳌���
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//====================================================
// ��������
//====================================================
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CShadow* pShadow = NULL;

	// �������̊m��
	pShadow = new CShadow;

	// ����������
	pShadow->Init(pos, fRadius, fRadius);

	// �e�N�X�`���|�C���^
	CTexture* pTexture = CManager::GetTexture();

	m_nTexture = pTexture->Register("data/TEXTURE/shadow000.jpg");

	// �e�N�X�`���̊���
	pShadow->BindTexture(pTexture->GetAddress(m_nTexture));

	return pShadow;
}