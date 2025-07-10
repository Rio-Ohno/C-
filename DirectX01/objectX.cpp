//====================================================
//
// X�t�@�C��[objectX.h]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"objectX.h"
#include"manager.h"

//====================================================
// �R���X�g���N�^
//====================================================
CObjectX::CObjectX()
{
	// �ϐ���������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < MAX_MAT; nCnt++)
	{
		m_anTexIndx[nCnt] = { -1 };
	}
}

//====================================================
// �f�X�g���N�^
//====================================================
CObjectX::~CObjectX()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CObjectX::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL* pMat;			// �}�e���A���f�[�^�ւ̃|�C���^

	// �ʒu�̑��
	m_pos = pos;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bExistence == false)
	{
		//X�t�@�C���̓Ǎ�
		D3DXLoadMeshFromX("data\\MODEL\\box000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
	{

		if (pMat[nCnt].pTextureFilename != NULL)
		{
			m_anTexIndx[nCnt] = CManager::GetTexture()->Register(pMat[nCnt].pTextureFilename);
		}
	}

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CObjectX::Uninit(void)
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

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CObjectX::Update(void)
{

}

//====================================================
// �`�揈��
//====================================================
void CObjectX::Draw(void)
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

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(m_anTexIndx[nCnt]));

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCnt);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================
// ��������
//====================================================
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObjectX* pObjectX = NULL;

	// �������̊m��
	pObjectX = new CObjectX;

	// ����������
	pObjectX->Init(pos, 0.0f, 0.0f);

	pObjectX->m_rot = rot;

	return pObjectX;
}

//====================================================
// ���f���̊���
//====================================================
void CObjectX::BindModel(const char* pFileName)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXLoadMeshFromX(pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh)))
	{
		m_bExistence = false;
	}
	else
	{
		m_bExistence = true;
	}
}
