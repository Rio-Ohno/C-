//====================================================
//
// �p�[�e�B�N��[particle.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"particle.h"
#include"manager.h"

//====================================================
// �R���X�g���N�^
//====================================================
CParticle::CParticle(int nPriority) :CObject(nPriority)
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
CParticle::~CParticle()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	return S_OK;
}

//====================================================
// �I������
//====================================================
void CParticle::Uninit(void)
{
	// �������g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CParticle::Update(void)
{
	// ����(�p�[�e�B�N��)�����炷
	m_nLife--;

	if (m_nLife > 0)
	{
		for (int nNumEffect = 0; nNumEffect < m_nNumEffect; nNumEffect++)
		{
			D3DXVECTOR3 Rot, tenRot, move;
			int nLife = 0;

			tenRot = m_rot * 100.0f;

			// �p�x�̐ݒ�
			Rot.z = (float)(rand() % (int)tenRot.z - 314) * 0.01f;

			// �ړ��ʂ̐ݒ�
			move.x = (float)sinf(Rot.z) * m_fSpeed;
			move.y = (float)cosf(Rot.z) * m_fSpeed;
			move.z = 0.0f;

			// �����̐ݒ�
			nLife = rand() % m_nLifeEffect + 1;

			// �G�t�F�N�g�̐���
			CEffect*pEffect = CEffect::Create(m_pos, move, m_fRadius, nLife, 0.0f);
			pEffect->SetColor(m_col);
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CParticle::Draw(void)
{

}

//====================================================
// �ʒu�̐ݒ�
//====================================================
void CParticle::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//====================================================
// �F�̐ݒ�
//====================================================
void CParticle::SetColor(D3DXCOLOR col)
{
	this->m_col = col;
}

//====================================================
// ��������(�ݒ菈��)
//====================================================
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fSpeed, int nLife, int nLifeEffect, int NumEffect)
{
	CParticle* pParticle = NULL;

	pParticle = new CParticle;

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