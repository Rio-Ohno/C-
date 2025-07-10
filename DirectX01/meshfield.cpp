//====================================================
//
// ���b�V���t�B�[���h[meshfield.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include "meshfield.h"
#include "manager.h"
#include "texture.h"
#include <cassert>

//====================================================
// �R���X�g���N�^
//====================================================
CMeshField::CMeshField()
{
	// �e�����o�ϐ��̏�����
	m_IdxBuff = { NULL };
	m_pVtxBuff = { NULL };

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// ����

	m_TexIndx = -1;	// �e�N�X�`���C���f�b�N�X
	m_nDiviX = 0;	// ������(x��)
	m_nDiviZ = 0;	// ������(z��)
	m_nWidth = 0;	// ��
	m_nHeight = 0;	// ����
	m_nMaxVtx = 0;	// �ő咸�_��
	m_nPolyNum = 0;	// �|���S����
}

//====================================================
// �f�X�g���N�^
//====================================================
CMeshField::~CMeshField()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//�C���f�b�N�X�ւ̃|�C���^
	WORD* pIdx = NULL;

	// �e�����o�ϐ��̐ݒ�
	m_pos = pos;				// �ʒu
	m_nWidth = (int)fWidth;		// ��
	m_nHeight = (int)fHeight;	// ����

	// �C���f�b�N�X��
	int flindexNum = (2 * (m_nDiviZ * (2 + m_nDiviX) - 1));

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nMaxVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;

	//�����ւ��炷
	float centerX = m_nWidth * (m_nDiviX - 2) * 0.5f;
	float centerY = m_nHeight * (m_nDiviZ - 2) * 0.5f;

	//���_���̐ݒ�
	for (int nCntZ = 0; nCntZ <= m_nDiviZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//���_���W�̐ݒ�
			pVtx[nCntVtx].pos = D3DXVECTOR3((float)(-m_nWidth + (m_nWidth * nCntX) - centerX), 0.0f, (float)(m_nHeight - (m_nHeight * nCntZ) + centerY));

			//�@���x�N�g���̐ݒ�
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);

			nCntVtx++;
		}
	}

	// max�𒴂����Ƃ��ɋ����I��
	assert(nCntVtx <= m_nMaxVtx);

	//���_�o�b�t�@���A�����b�N�@
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * flindexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_IdxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_IdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nCntX;
	int Indx = 0;
	for (int nCntZ = 0; nCntZ < m_nDiviZ; nCntZ++)
	{
		for (nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (m_nDiviX + 1) * (nCntZ + 1) + nCntX;
			pIdx[1] = nCntX + (nCntZ * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}

		if (nCntZ < m_nDiviZ - 1)
		{
			pIdx[0] = (nCntX - 1) + (nCntZ * (m_nDiviX + 1));
			pIdx[1] = nCntX + ((nCntZ + 1) * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}
	}
	assert(Indx <= flindexNum);

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_IdxBuff->Unlock();

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CMeshField::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_IdxBuff != NULL)
	{
		m_IdxBuff->Release();
		m_IdxBuff = NULL;
	}

	// ���g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CMeshField::Update(void)
{
	// �Ȃ�
}

//====================================================
// �`�揈��
//====================================================
void CMeshField::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�̎擾
	CTexture* pTexture = CManager::GetTexture();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_IdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_TexIndx));

	//���b�V������`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMaxVtx, 0, m_nPolyNum);
}

//====================================================
// ��������
//====================================================
CMeshField* CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int textype, int nDiviX, int nDiviZ, int nWidth, int nHeight)
{
	CMeshField* pMeshField = NULL;

	// �������̊m��
	pMeshField = new CMeshField;

	// �e�����o�ϐ��̐ݒ�
	pMeshField->m_rot = rot;												// ����
	pMeshField->m_TexIndx = textype;										// �e�N�X�`���C���f�b�N�X
	pMeshField->m_nDiviX = nDiviX;											// ������(x��)
	pMeshField->m_nDiviZ = nDiviZ;											// ������(z��)
	pMeshField->m_nMaxVtx = (nDiviX + 1) * (nDiviZ + 1);					// �ő咸�_��
	pMeshField->m_nPolyNum = (2 * nDiviX * nDiviZ + (nDiviZ - 1) * 4);		// �|���S����

	// ����������
	pMeshField->Init(pos, (float)nWidth, (float)nHeight);

	return pMeshField;
}