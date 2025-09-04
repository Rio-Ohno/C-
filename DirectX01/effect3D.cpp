//====================================================
//
// �G�t�F�N�g[effect3D.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"effect3D.h"
#include"manager.h"

// �ÓI�����o�ϐ�
int CEffect3D::m_Texindx = -1;

//====================================================
// �R���X�g���N�^
//====================================================
CEffect3D::CEffect3D()
{
	m_nLife = 0;
	m_fDelSize = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================================
// �f�X�g���N�^
//====================================================
CEffect3D::~CEffect3D()
{
	// �Ȃ�
}

//====================================================
// ��������
//====================================================
CEffect3D* CEffect3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius, int nLife, float fDelSize)
{
	CEffect3D* pEffect = NULL;

	// �������̊m��
	pEffect = new CEffect3D;

	pEffect->m_nLife = nLife;
	pEffect->m_fDelSize = fDelSize;
	pEffect->m_move = move;
	pEffect->m_Texindx = CTexture::TYPE_EFFECT;

	// ��]���̐ݒ�
	pEffect->SetOriogin(D3DXVECTOR3(fRadius * 0.5f, fRadius * 0.5f, 0.0f));

	// ����������
	pEffect->Init(pos, fRadius, fRadius);

	// �e�N�X�`���̊���
	pEffect->BindTexindx(m_Texindx);

	return pEffect;
}

//====================================================
// ����������
//====================================================
HRESULT CEffect3D::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ����������
	CObjectBillboard::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CEffect3D::Uninit(void)
{
	// �I������
	CObjectBillboard::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CEffect3D::Update(void)
{
	// ���������炷
	m_nLife--;

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObjectBillboard::GetPos();

	if (m_nLife <= 0)
	{
		// �G�t�F�N�g�̏I������
		CEffect3D::Uninit();
	}
	else
	{
		if (m_fDelSize != 0.0f)
		{// �T�C�Y������������W��������Ȃ�
			// ���a�̎擾
			float fRadius = CObjectBillboard::GetWidth();

			// ���a������������
			fRadius *= m_fDelSize;

			// �T�C�Y�̐ݒ�
			CObjectBillboard::SetSize(fRadius, fRadius);
		}

		// �ʒu�̍X�V
		pos += m_move;
		CObjectBillboard::SetPos(pos);
	}
}

//====================================================
// �`�揈��
//====================================================
void CEffect3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// Z�o�b�t�@�ɂ͏������܂Ȃ�

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CObjectBillboard::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}