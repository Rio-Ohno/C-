//====================================================
//
//���b�V���X�t�B�A[meshSphere.cpp]
//Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include "meshSphere.h"
#include "manager.h"
#include <cassert>

//====================================================
// �R���X�g���N�^
//====================================================
CMeshSphere::CMeshSphere()
{
	// �e�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	//D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_pVtxBuff = { NULL };					// ���_�o�b�t�@�ւ̃|�C���^
	m_pIndxBuff = { NULL };					// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_nTexindx = -1;						// �e�N�X�`���C���f�b�N�X
	m_nDiviX = 0;							// ������
	m_nDiviY = 0;							// ������
	m_nMaxVtx = 0;							// ���_��
	m_nPolyNum = 0;							// �|���S����
	m_fRadius = 0.0f;						// ���a
	m_bFront = true;
	m_bHalf = true;							// �������ǂ���(�����̏�Ԃ�)
}

//====================================================
// �f�X�g���N�^
//====================================================
CMeshSphere::~CMeshSphere()
{
	// �Ȃ�
}

//====================================================
// ��������
//====================================================
CMeshSphere* CMeshSphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDiviX, int nDiviY, float fRadius, bool bHalf, bool bFront)
{
	CMeshSphere* pSphere = NULL;

	// �������̊m��
	pSphere = new CMeshSphere;

	// �e�ϐ��̐ݒ�
	pSphere->m_nDiviX = nDiviX;
	pSphere->m_nDiviY = nDiviY;
	pSphere->m_fRadius = fRadius;
	pSphere->m_nMaxVtx = (nDiviX + 1) * nDiviY + 1;// ���_��
	pSphere->m_bHalf = bHalf;
	pSphere->m_bFront = bFront;

	// ����������
	pSphere->Init(pos, fRadius, fRadius);

	return pSphere;
}

//====================================================
// ����������
//====================================================
HRESULT CMeshSphere::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D* pVtx = NULL;
	int indx = 0;//���_�C���f�b�N�X
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �x�N�g���̕ۑ��p

	//���_�o�b�t�@�̐���
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
			int i = nCntX;

			if (m_bFront == false)
			{
				i = m_nDiviX - nCntX;
			}

			//�p�x�i�[
			float fAngle = ((D3DX_PI * 2 / m_nDiviX) * i);						//y��
			float fAngle2 = (D3DX_PI / m_nDiviY) * nCntY;		//z��

			//�����Ȃ�
			if (m_bHalf == true)
			{
				fAngle2 = (((D3DX_PI * 0.5f) / m_nDiviY) * nCntY);
			}

			//���_�̈ʒu�̐ݒ�
			pVtx[indx].pos.x = (float)m_fRadius * sinf(fAngle2) * sinf(fAngle);
			pVtx[indx].pos.y = (float)m_fRadius * cosf(fAngle2);
			pVtx[indx].pos.z = (float)m_fRadius * sinf(fAngle2) * cosf(fAngle);

			//�O���ւ̃x�N�g��
			vec = pVtx[indx].pos - m_pos;

			//�x�N�g���̐��K��,�e���_�̖@���̐ݒ�
			D3DXVec3Normalize(&pVtx[indx].nor, &vec);

			//���_�J���[�̐ݒ�
			pVtx[indx].col = m_col;

			//�e�N�X�`�����W�̐ݒ�
			if (indx == 0)
			{
				pVtx[indx].tex = D3DXVECTOR2(0.5f, 0.0f);
			}
			else if (indx >= 1 && indx <= (m_nDiviX + 1))
			{
				pVtx[indx].tex = D3DXVECTOR2(1.0f - (float)nCntX / m_nDiviX, 1.0f / m_nDiviY);
			}
			else
			{
				pVtx[indx].tex = D3DXVECTOR2(1.0f - (float)nCntX / m_nDiviX, (float)nCntY / m_nDiviY);
			}

			//���_�C���f�b�N�X��i�߂�
			indx++;
			assert(indx >= 0 && indx <= m_nMaxVtx);

			if ((indx - 1) == 0)
			{// 1���_�ڂȂ�
				break;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�ւ̃|�C���^
	WORD* pIdx = NULL;
	int indexNum = (2 * ((m_nDiviY /*- 1*/) * (2 + m_nDiviX) - 1));													// �C���f�b�N�X
	m_nPolyNum = (2 * m_nDiviX * (m_nDiviY-1) + (m_nDiviY-2) * 4);					// �|���S����

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * indexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIndxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nCntX = 0;
	int Indx = 0;

	for (int nCntY = 0; nCntY < m_nDiviY; nCntY++)
	{
		for (nCntX = m_nDiviX; nCntX >= 0; nCntX--)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (m_nDiviX + 1) * (nCntY + 1) + nCntX;
			pIdx[1] = nCntX + (nCntY * (m_nDiviX + 1));

			pIdx += 2;
			Indx += 2;
		}

		//���ރ|���S����
		if (nCntY < m_nDiviY - 2)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (nCntX + 1) + (nCntY * (m_nDiviX + 1));
			pIdx[1] = (m_nDiviX + 1) * (nCntY + 2) + m_nDiviX;

			pIdx += 2;
			Indx += 2;
		}

		assert(Indx <= indexNum);
		assert(nCntY >= 0 && nCntY <= m_nDiviY);
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIndxBuff->Unlock();

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CMeshSphere::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIndxBuff != NULL)
	{
		m_pIndxBuff->Release();
		m_pIndxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CMeshSphere::Update(void)
{
	// �Ȃ�

		// �p�x�̋ߓ�
	if ((m_rot.y + 0.0005f) >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if ((m_rot.y + 0.0005f) <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_rot.y += 0.0005f;
}

//====================================================
// �`�揈��
//====================================================
void CMeshSphere::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���N���X�ւ̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g��؂�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);   // �������F�J��Ԃ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);  // �c�����F�[�~��

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexindx));

	// �|���S����`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_nDiviX);

	if (m_nDiviY >= 2)
	{
		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(m_pIndxBuff);

		// ���b�V���ǂ�`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 1, 0, m_nMaxVtx, 0, m_nPolyNum);
	}

	//���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//====================================================
// �F�̐ݒ�
//====================================================
void CMeshSphere::SetColor(D3DXCOLOR col)
{
	VERTEX_3D* pVtx = NULL;
	int indx = 0;//���_�C���f�b�N�X

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntY = 0; nCntY <= m_nDiviY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			// �F�̐ݒ�
			pVtx[indx].col = col;
			m_col = col;

			//���_�C���f�b�N�X��i�߂�
			indx++;
			assert(indx >= 0 && indx <= m_nMaxVtx);

			if ((indx - 1) == 0)
			{// 1���_�ڂȂ�
				break;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}