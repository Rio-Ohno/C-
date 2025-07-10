//====================================================
// 
// �e [bullet.h]
// Author:Rio Ohno
// 
//====================================================

// �C���N���[�h
#include "bullet.h"
#include"manager.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"score.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//====================================================
// �R���X�g���N�^
//====================================================
CBullet::CBullet()
{
	//�l���N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CBullet::~CBullet()
{

}

//====================================================
// ����������
//====================================================
HRESULT CBullet:: Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �|���S���̏�����
	CObject2D::Init(pos, fWidth, fHeight);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CBullet::Uninit(void)
{
	// �|���S���̏I������
	CObject2D::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CBullet::Update(void)
{
	m_move.x = -BULLET_SPEED;

	// �ʒu���X�V
	D3DXVECTOR3 pos = CObject2D::GetPos() + m_move;

	// �ʒu�̐ݒ�
	CObject2D::SetPos(pos);

	// �G�t�F�N�g�̐���
	CEffect* pEffect = CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20, 0.97f);
	pEffect->SetColor(D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f));

	// �����̃J�E���g�_�E��
	m_nLife--;

	// �������ĂȂ��Ȃ�
	if (CollisionEnemy(pos) == false)
	{
		if (m_nLife <= 0)
		{// �������s������

			// �e�̔����̐���
			CExplosion::Create(CObject2D::GetPos(), 50.0f);

			// �I������
			Uninit();
		}
		else if (pos.x <= 0.0f ||
			pos.x >= SCREEN_WIDTH ||
			pos.y <= 0.0f ||
			pos.y >= SCREEN_HEIGHT)
		{// ��ʊO�ɏo����

			// �I������
			Uninit();
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CBullet::Draw(void)
{
	// �|���S���̕`�揈��
	CObject2D::Draw();
}

//====================================================
// ��������
//====================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, float fRadius,int nLife)
{
	int nNumAll = CObject::GetNumAll();

	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// �e�ւ̃|�C���^
	CBullet* pBullet = NULL;

	// �������̊m��
	pBullet = new CBullet;

	// ����������
	pBullet->Init(pos, fRadius, fRadius);

	// �����̐ݒ�
	pBullet->m_nLife = nLife;

	//�e�N�X�`���̊���
	pBullet->BindTex(m_pTexture);

	// ��ނ̐ݒ�
	pBullet->SetType(TYPE_BULLET);

	return pBullet;
}

//====================================================
// �e�N�X�`���̓Ǎ�
//====================================================
HRESULT CBullet::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓Ǎ�
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\fish.png",
		&m_pTexture)))
	{
		return -1;
	}
	
	return S_OK;
}

//====================================================
// �e�N�X�`���̔j��
//====================================================
void CBullet::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//====================================================
// �e�N�X�`���̔j��
//====================================================
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			// �I�u�W�F�N�g�̎擾
			CObject* pObj = CObject::GetObject(nPriority, nCnt);

			if (pObj != NULL)
			{
				// ��ނ̎擾
				CObject::TYPE type = pObj->GetType();

				if (type == CObject::TYPE_ENEMY)
				{// �G�Ȃ�

					// �����蔻����Ƃ�
					if (pos.x >= pObj->GetPos().x - pObj->GetWidth() * 0.5f &&
						pos.x <= pObj->GetPos().x + pObj->GetWidth() * 0.5f &&
						pos.y >= pObj->GetPos().y - pObj->GetHeight() * 0.5f &&
						pos.y <= pObj->GetPos().y + pObj->GetHeight() * 0.5f)// ����������
					{
						// �e�̔����̐���
						CExplosion::Create(CObject2D::GetPos(), 50.0f);

						CScore::Add(5);

						//// �G�̔����̐���
						//CExplosion* pExplosion = CExplosion::Create(pObj->GetPos(), 100.0f);
						//pExplosion->SetColor(D3DXCOLOR(1.0f, 0.8f, 0.5f, 1.0f));

						// �p�[�e�B�N���̐���
						CParticle* pParticle = CParticle::Create(pObj->GetPos(), D3DXVECTOR3(0.0f, 0.0f, 6.28f), 30.0f, 8.0f, 8, 15, 6);
						pParticle->SetColor(D3DXCOLOR(1.0f, 0.8f, 0.5f, 0.5f));// �F�̐ݒ�

						// �G�̔j��
						pObj->Uninit();

						// �e�̔j��
						CBullet::Uninit();

						return true;
					}
				}
			}
		}
	}
	return false;
}
