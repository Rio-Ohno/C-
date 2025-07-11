//====================================================
// 
// 3D�I�u�W�F�N�g [object3D.cpp]
// Author:Rio Ohno
// 
//====================================================

// �C���N���[�h
#include"object3D.h"
#include"manager.h"
#include"player.h"

//====================================================
// �R���X�g���N�^
//====================================================
CObject3D::CObject3D()
{
	// �e�ϐ��̏�����
	m_pVtxBuff = { NULL };
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTexindx = -1;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fLength = 0.0f;
}

//====================================================
// �f�X�g���N�^
//====================================================
CObject3D::~CObject3D()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CObject3D::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�ϐ��̐ݒ�
	m_pos = pos;				// �ʒu
	m_fWidth = fWidth;			// ��
	m_fLength = fHeight;		// ����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth * 0.5f, 0.0f, m_fLength * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, m_fLength * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth * 0.5f, 0.0f, -m_fLength * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, -m_fLength * 0.5f);

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̉��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CObject3D::Update(void)
{ 
	// �Ȃ�
}

//====================================================
// �`�揈��
//====================================================
void CObject3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���N���X�ւ̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	LPDIRECT3DTEXTURE9 pTexMT;// �}���`�^�[�Q�b�g�p�e�N�X�`��

	// �}���`�^�[�Q�b�g�p�e�N�X�`���̎擾
	pTexMT = CManager::GetRenderer()->GetTextureMT();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexindx));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//====================================================
// ��������
//====================================================
CObject3D* CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fLength)
{
	CObject3D* pObject3D = NULL;

	// �������̊m��
	pObject3D = new CObject3D;

	// ����������
	pObject3D->Init(pos, fWidth, fLength);

	// �����̐ݒ�
	pObject3D->m_rot = rot;

	return pObject3D;
}

//====================================================
// �����蔻��
//====================================================
void CObject3D::isColision(void)
{
	// ���_�ʒu
	D3DXVECTOR3 pos[4] = {};
	D3DXVECTOR3 Vec[3], Vec1, Vec2;
	D3DXVECTOR3 nor[3];

	// �v���C���[�̎擾
	CPlayer* pPlayer = CManager::GetPlayer();
	
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pos[nCnt] = pVtx[nCnt].pos;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	for (int nCnt = 0; nCnt < 2; nCnt++)//012321
	{
		// �x�N�g���v�Z
		Vec[0] = pos[nCnt + 1] - pos[nCnt * 3];
		Vec[1] = pos[2 - nCnt] - pos[nCnt + 1];
		Vec[2] = pos[nCnt * 3] - pos[2 - nCnt];

		D3DXVECTOR3 vecPlayer;

		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{
			int VecIndx = 0;

			// �v���C���[�Ƃ̃x�N�g��
			vecPlayer = pPlayer->GetPos() - pos[nCntVtx + nCnt];

			if (nCnt == 1)
			{
				VecIndx = 2 - nCntVtx;
			}
			else
			{
				VecIndx = nCntVtx;
			}

			D3DXVec3Cross(&nor[nCntVtx], &vecPlayer, &Vec[VecIndx]);

			// �@���𐳋K��
			D3DXVec3Normalize(&nor[nCntVtx], &nor[nCntVtx]);
		}

		if (0.0f >= nor[0].y && 0.0f >= nor[1].y && 0.0f >= nor[2].y)
		{
			D3DXVECTOR3 nor;
			float dot = 0.0f;

			Vec1 = pos[nCnt + 1] - pos[nCnt * 3];
			Vec2 = pos[2 - nCnt] - pos[nCnt * 3];

			// 2�̃x�N�g������@�������߂�
			D3DXVec3Cross(&nor, &Vec1, &Vec2);

			// �@���𐳋K��
			D3DXVec3Normalize(&nor, &nor);

			// ����
			dot = D3DXVec3Dot(&vecPlayer, &nor);

			if (nor.y != 0.0f)
			{
				// ������ς���
				m_fHeight = -dot;
				return;
			}
		}
	}
}

//====================================================
// �����̎擾
//====================================================
float CObject3D::GetHeight(void)
{
	// �Փ˔���
	isColision();

	return m_fHeight;
}