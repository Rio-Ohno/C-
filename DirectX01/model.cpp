//====================================================
//
// ���f��(�K�w�\���O��)[model.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"model.h"
#include"manager.h"
#include <stdio.h>
#include <string.h>

//====================================================
// �R���X�g���N�^
//====================================================
CModel::CModel()
{
	// �l��������
	m_pMesh = { NULL };
	m_pBuffMat = { NULL };
	m_dwNumMat = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = {};
	m_pParent = { NULL };
}

//====================================================
// �f�X�g���N�^
//====================================================
CModel::~CModel()
{
	// �Ȃ�
}

//====================================================
// ��������
//====================================================
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	CModel* pModel = NULL;

	// �������̊m��
	pModel = new CModel;

	// ����������
	if (FAILED(pModel->Init(pos, rot, pFilename)))
	{// ���s������

		// ���������j��
		delete pModel;
		pModel = NULL;

		return NULL;
	}

	return pModel;
}

//====================================================
// ����������
//====================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//D3DXMATERIAL* pMat;			// �}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//X�t�@�C���̓Ǎ�
	if (FAILED(D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh)))
	{
		return -1;
	}

	// �e�ϐ��̐ݒ�
	m_pos = pos;		// �ʒu
	m_rot = rot;		// ����

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CModel::Uninit(void)
{
	// ���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//====================================================
// �`�揈��
//====================================================
void CModel::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMATRIX mtxParent;// �e���f���}�g���b�N�X

	if (m_pParent != NULL)
	{// �e������Ȃ�
		// �e�̃}�g���b�N�X�擾
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// �e���Ȃ�
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �e�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
	{
		if (m_col != NULL)
		{
			D3DXMATERIAL DamageColor = pMat[nCnt];
			DamageColor.MatD3D.Diffuse = m_col;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&DamageColor.MatD3D);
		}
		else
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		}

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL/*apTextureModel[nCnt]*/);

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCnt);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================
// �e���f���̐ݒ菈��
//====================================================
void CModel::SetParent(CModel* pModel)
{
	// �e���f���̐ݒ�
	m_pParent = pModel;
}

//====================================================
// �ʒu�̐ݒ菈��
//====================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu�̐ݒ�
	m_pos = pos;
}


//====================================================
// �����̐ݒ菈��
//====================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	// �ʒu�̐ݒ�
	m_rot = rot;
}

//====================================================
// ���[���h�}�g���b�N�X�̎擾����
//====================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}