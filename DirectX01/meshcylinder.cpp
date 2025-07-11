//====================================================
//
// ���b�V���V�����_�[ [meshcylinder.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include "meshcylinder.h"
#include"manager.h"
#include <cassert>

//====================================================
// �R���X�g���N�^
//====================================================
CMeshCylinder::CMeshCylinder()
{
	// �e�ϐ�������
	m_pVtxBuff = { NULL };
	m_pIdxBuff = { NULL };
	m_mtxWorld = {};

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nTexindx = -1;
	m_nDiviX = 0;
	m_nDiviY = 0;
	m_nMaxVtx = 0;
	m_nPolyNum = 0;
	m_fHeight = 0.0f;
	m_fRadius = 0.0f;
	m_bCulling = true;
}

//====================================================
// �f�X�g���N�^
//====================================================
CMeshCylinder::~CMeshCylinder()
{
	// �Ȃ�
}

//====================================================
//����������
//====================================================
HRESULT CMeshCylinder::Init(D3DXVECTOR3 pos,float fWidth,float fHeight)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//�C���f�b�N�X�ւ̃|�C���^
	WORD* pIdx = NULL;

	int flindexNum = (2 * (m_nDiviY * (2 + m_nDiviX) - 1));	//�C���f�b�N�X��

	//�C���f�b�N�X�J�E���^�[
	int indx = 0;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nMaxVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY <= m_nDiviY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//�p�x�Z�o
			float fAngle = ((D3DX_PI * 2.0f / m_nDiviX) * nCntX);

			//�����̊i�[
			float fHeight = (m_fHeight / m_nDiviY) * (m_nDiviY - nCntY);

			//���_�̐ݒ�
			pVtx[indx].pos = D3DXVECTOR3(m_fRadius * sinf(fAngle), fHeight, m_fRadius * cosf(fAngle));

			//���S�ւ̃x�N�g��
			D3DXVECTOR3 vec = m_pos - pVtx[indx].pos;

			//�x�N�g���̐��K��,�e���_�̖@���̐ݒ�
			D3DXVec3Normalize(&pVtx[indx].nor, &vec);

			//���_�J���[�̐ݒ�
			pVtx[indx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[indx].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntY);
			indx++;
		}
	}
	assert(indx <= m_nMaxVtx);

	//���_�o�b�t�@���A�����b�N�@
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * flindexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nCntX = 0;
	int Indx = 0;
	for (int nCntY = 0; nCntY < m_nDiviY; nCntY++)
	{
		for (nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (m_nDiviX + 1) * (nCntY + 1) + nCntX;
			pIdx[1] = nCntX + (nCntY * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}

		//���ރ|���S����
		if (nCntY < m_nDiviY - 1)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (nCntX - 1) + (nCntY * (m_nDiviX + 1));
			pIdx[1] = nCntX + ((nCntY + 1) * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}
	}
	assert(indx <= m_nMaxVtx);

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CMeshCylinder::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CMeshCylinder::Update(void)
{
	// �Ȃ�
}

//====================================================
// �`�揈��
//====================================================
void CMeshCylinder::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���N���X�ւ̃|�C���^�̎擾
	CTexture* pTexture = CManager::GetTexture();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	//���C�g��؂�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	if (m_bCulling == true)
	{
		//�J�����O������
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
	else
	{
		//�J�����O��؂�
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X����f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexindx));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMaxVtx, 0, m_nPolyNum);

	//���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�J�����O������
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//====================================================
// ��������
//====================================================
CMeshCylinder* CMeshCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int DiviX, int DiviY, float fHeight, float fRadius)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//�C���f�b�N�X�ւ̃|�C���^
	WORD* pIdx = NULL;

	CMeshCylinder* pCylinder = NULL;

	// �������̊m��
	pCylinder = new CMeshCylinder;

	//�e�ϐ��̐ݒ�
	pCylinder->m_pos = pos;												// �ʒu
	pCylinder->m_rot = rot;												// ����
	pCylinder->m_nDiviX = DiviX;										// ������(x��)
	pCylinder->m_nDiviY = DiviY;										// ������(y��)
	pCylinder->m_fHeight = fHeight;										// ����
	pCylinder->m_fRadius = fRadius;										// ���a
	pCylinder->m_nMaxVtx = (DiviX + 1) * (DiviY + 1);					// �ő咸�_��
	pCylinder->m_nPolyNum = (2 * DiviX * DiviY + (DiviY - 1) * 4);		// �|���S����

	// ����������
	pCylinder->Init(pos, 0.0f, fHeight);

	return pCylinder;
}

//====================================================
// �F�̐ݒ菈��
//====================================================
void CMeshCylinder::SetColor(D3DXCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//�C���f�b�N�X�J�E���^�[
	int indx = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY <= m_nDiviY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//���_�J���[�̐ݒ�
			pVtx[indx].col = col;

			// �J�E���g�A�b�v
			indx++;
		}
	}
	assert(indx <= m_nMaxVtx);

	//���_�o�b�t�@���A�����b�N�@
	m_pVtxBuff->Unlock();
}