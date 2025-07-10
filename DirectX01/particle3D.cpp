//====================================================
//
// �p�[�e�B�N��[particle.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"particle3D.h"
#include"effect3D.h"
#include"manager.h"

//====================================================
// �R���X�g���N�^
//====================================================
CParticle3D::CParticle3D(int nPriority) :CObject(nPriority)
{
	// �l���N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fRadius = 0;
	m_fSpeed = 0;
	m_nLife = 0;
	m_nLifeEffect = 0;
	m_nNumEffect = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CParticle3D::~CParticle3D()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CParticle3D::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	return S_OK;
}

//====================================================
// �I������
//====================================================
void CParticle3D::Uninit(void)
{
	// �������g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CParticle3D::Update(void)
{
	// ����(�p�[�e�B�N��)�����炷
	m_nLife--;

	if (m_nLife > 0)
	{
		for (int nNumEffect = 0; nNumEffect < m_nNumEffect; nNumEffect++)
		{
			D3DXVECTOR3 Rot, tenRot, move;
			int nLife = 0;
			float fRadius = m_fRadius;

			tenRot = m_rot * 100.0f;

			// �p�x�̐ݒ�
			Rot.x = (float)(rand() % (int)tenRot.x - 314) * 0.01f;
			Rot.y = (float)(rand() % (int)tenRot.y - 314) * 0.01f;

			// �ړ��ʂ̐ݒ�
			move.x = (float)sinf(Rot.x) * cosf(Rot.y) * m_fSpeed;
			move.y = (float)sinf(Rot.x) * sinf(Rot.y) * m_fSpeed;
			move.z = (float)cosf(Rot.x) * m_fSpeed;

			// �T�C�Y�̐ݒ�
			fRadius = (float)(rand() % (int)m_fRadius + 1.0f);

			// �����̐ݒ�
			nLife = rand() % m_nLifeEffect + 1;

			// �G�t�F�N�g�̐���
			CEffect3D* pEffect = CEffect3D::Create(m_pos, move, fRadius, nLife, 0.0f);
			pEffect->SetColor(m_col);
		}
	}
	else
	{
		CParticle3D::Uninit();
	}
}

//====================================================
// �`�揈��
//====================================================
void CParticle3D::Draw(void)
{

}

//====================================================
// �ʒu�̐ݒ�
//====================================================
void CParticle3D::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//====================================================
// �F�̐ݒ�
//====================================================
void CParticle3D::SetColor(D3DXCOLOR col)
{
	this->m_col = col;
}

//====================================================
// ��������(�ݒ菈��)
//====================================================
CParticle3D* CParticle3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fSpeed, int nLife, int nLifeEffect, int NumEffect)
{
	CParticle3D* pParticle = NULL;

	pParticle = new CParticle3D;

	// �e�ϐ��̐ݒ�
	pParticle->m_pos = pos;						// �ʒu
	pParticle->m_rot = rot;						// ����
	pParticle->m_fRadius = fRadius;				// ���a
	pParticle->m_fSpeed = fSpeed;				// �X�s�[�h
	pParticle->m_nLife = nLife;					// ����(�p�[�e�B�N��)
	pParticle->m_nLifeEffect = nLifeEffect;		// ����(�G�t�F�N�g)

	// 1F�ɌĂԃG�t�F�N�g�̐�
	if (NumEffect <= MAX_EFFECT)
	{
		pParticle->m_nNumEffect = NumEffect;
	}
	else
	{
		pParticle->m_nNumEffect = MAX_EFFECT;
	}

	return pParticle;
}