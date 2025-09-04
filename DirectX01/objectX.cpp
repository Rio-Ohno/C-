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
CObjectX::CObjectX(int nPriority):CObject(nPriority)
{
	// �ϐ���������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bExistence = false;

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

	// ���_���̎擾
	int nNumVtx = m_pMesh->GetNumVertices();
	DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBUff;			// ���_�o�b�t�@�ւ̃|�C���^

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

	for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

		//���_���W���r���ă��f���̍ő�ŏ����擾

		if (vtx.x > m_vtxMax.x)//x�ő�l
		{
			m_vtxMax.x = vtx.x;
		}
		else if (vtx.x < m_vtxMin.x)//x�ŏ��l
		{
			m_vtxMin.x = vtx.x;
		}

		if (vtx.y > m_vtxMax.y)//y�ő�l
		{
			m_vtxMax.y = vtx.y;
		}
		else if (vtx.y < m_vtxMin.y)//y�ŏ��l
		{
			m_vtxMin.y = vtx.y;
		}

		if (vtx.z > m_vtxMax.z)//z�ő�l
		{
			m_vtxMax.z = vtx.z;
		}
		else if (vtx.z < m_vtxMin.z)//z�ŏ��l
		{
			m_vtxMin.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBUff += sizeFVF;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();

	//�T�C�Y�̏�����
	m_size = m_vtxMax - m_vtxMin;

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
