//====================================================
// 
// �Ռ��g[shockwave.cpp]
// Author:Rio Ohno
// 
//==================================================== 

// �C���N���[�h
#include"shockwave.h"
#include"manager.h"
#include"game.h"
#include <cassert>

//==================================================== 
// �R���X�g���N�^
//==================================================== 
CShockwave::CShockwave()
{
	// �e�ϐ�������
	m_pVtxBuff = { NULL };					// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = { NULL };					// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_mtxWorld = {};						// ���[���h�}�g���b�N�X

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����

	m_nTexindx = -1;						// �e�N�X�`���C���f�b�N�X
	m_nDiviX = 0;							// ����������
	m_nDiviY = 0;							// �c��������
	m_nMaxVtx = 0;							// �ő咸�_��
	m_nPolyNum = 0;							// �|���S����
	m_nLife = 0;							// ����
	m_nVanishFream = 0;						// ������t���[����
	m_nVanishCnt = 0;						// ������t���[���J�E���^�[
	m_fHeight = 0.0f;						// ����
	m_fWidth = 0.0f;						// ��
	m_fRadius = 0.0f;						// ���a
	m_fSpeed = 0.0f;						// �L����X�s�[�h
	m_bCulling = true;						// �J�����O���邩�ǂ���
	m_bCollision = false;					// �����蔻����Ƃ邩�ǂ���
	m_bVanish = false;						// �����鉉�o������邩�ǂ���
}

//==================================================== 
// �f�X�g���N�^
//==================================================== 
CShockwave::~CShockwave()
{
	// �Ȃ�
}

//====================================================
// ��������
//====================================================
CShockwave* CShockwave::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY,int nLife, float fWidth, float fHeight, float fRadius, float fSpeed, bool bCulling, bool bCollision)
{
	CShockwave* pwave = NULL;

	// �������̊m��
	pwave = new CShockwave;

	//�e�ϐ��̐ݒ�
	pwave->m_pos = pos;												// �ʒu
	pwave->m_rot = rot;												// ����
	pwave->m_nDiviX = DiviX;										// ������(x��)
	pwave->m_nDiviY = DiviY;										// ������(y��)
	pwave->m_nLife = nLife;											// ����
	pwave->m_fHeight = fHeight;										// ����
	pwave->m_fWidth = fWidth;										// ��
	pwave->m_fRadius = fRadius;										// ���a
	pwave->m_fSpeed = fSpeed;										// �L����X�s�[�h
	pwave->m_nMaxVtx = (DiviX + 1) * (DiviY + 1);					// �ő咸�_��
	pwave->m_nPolyNum = (2 * DiviX * DiviY + (DiviY - 1) * 4);		// �|���S����
	pwave->m_bCulling = bCulling;
	pwave->m_bCollision = bCollision;

	// ����������
	pwave->Init(pos, fWidth, fHeight);

	return pwave;
}

//==================================================== 
// ����������
//==================================================== 
HRESULT CShockwave::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
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
			float fAngle = ((D3DX_PI * 2.0f / m_nDiviX) * (m_nDiviX - nCntX));

			//�����̊i�[
			float fHeight = (m_fHeight / m_nDiviY) * (m_nDiviY - nCntY);

			// ���̎Z�o
			float fWidth = (m_fWidth / m_nDiviY) * nCntY;

			//���_�̐ݒ�
			pVtx[indx].pos = D3DXVECTOR3((m_fRadius+fWidth) * sinf(fAngle), fHeight, (m_fRadius + fWidth) * cosf(fAngle));

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
	int Indx = 0;	// �C���f�b�N�X�J�E���^

	for (int nCntY = 0; nCntY < m_nDiviY; nCntY++)
	{
		for (nCntX = 0; nCntX <= m_nDiviX; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (m_nDiviX + 1) * (nCntY + 1) + nCntX;
			pIdx[1] = nCntX + (nCntY * (m_nDiviX + 1));

			// �|�C���^�ƃC���f�b�N�X�J�E���^��i�߂�
			pIdx += 2;
			Indx += 2;
		}

		//���ރ|���S����
		if (nCntY < m_nDiviY - 1)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (nCntX - 1) + (nCntY * (m_nDiviX + 1));
			pIdx[1] = nCntX + ((nCntY + 1) * (m_nDiviX + 1));

			// �|�C���^�ƃC���f�b�N�X�J�E���^��i�߂�
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
void CShockwave::Uninit(void)
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
void CShockwave::Update(void)
{
	// ���������炷
	--m_nLife;

	// �������c���Ă�Ȃ�
	if (m_nLife > 0)
	{
		// �����蔻����Ƃ�Ȃ�
		if (m_bCollision)
		{
			// �v���C���[�̏��擾
			CPlayer* pPlayer = CGame::GetPlayer();

			// �v���C���[�̏�񂪂���Ȃ�
			if (pPlayer != NULL)
			{
				// �v���C���[�Ƃ̓����蔻��
				if (isCollision(pPlayer->GetPos(), 6.0f,0.0f,pPlayer->GetSize().y) == true)
				{
					// �v���C���[��e����
					pPlayer->Hit();
				}
			}
		}

		// �L���鏈��
		Spread();
	}
	// �������s�����Ȃ�
	else
	{
		// �����鉉�o�����Ȃ��Ȃ�
		if (m_bVanish == false)
		{
			// �I������
			Uninit();
		}
		// �����鉉�o������Ȃ�
		else
		{
			// �L���鏈��
			Spread();

			// �����鉉�o
			Vanish();
		}
	}
}

//==================================================== 
// �`�揈��
//==================================================== 
void CShockwave::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���N���X�ւ̃|�C���^�̎擾
	CTexture* pTexture = CManager::GetTexture();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	//���C�g��؂�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �J�����O�����Ȃ��Ȃ�
	if (m_bCulling == false)
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
// �F�̐ݒ�
//==================================================== 
void CShockwave::SetColor(D3DXCOLOR col, bool bTransparent)
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
			if (bTransparent == true)
			{
				float a = col.a;

				float alpha = ((a+0.1f) / m_nDiviY) * (m_nDiviY - nCntY);

				col.a = alpha;
			}

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

//==================================================== 
// �����蔻��
//==================================================== 
bool CShockwave::isCollision(D3DXVECTOR3 pos, float fRadius, float fUnder, float fTop)
{
	// �������͈͂Ȃ�
	if (pos.y - fUnder <= m_pos.y + m_fHeight && pos.y + fTop >= m_pos.y)
	{
		float fDistance = (pos.x - m_pos.x) * (pos.x - m_pos.x) +
			(pos.z - m_pos.z) * (pos.z - m_pos.z);	// ����(2D��)

		// ������
		fDistance = sqrtf(fDistance);

		if (fDistance <= (m_fRadius + m_fWidth + fRadius) && fDistance >= m_fRadius)
		{
			return true;
		}
	}
	return false;
}

//==================================================== 
// �����鉉�o�̐ݒ菈��
//==================================================== 
void CShockwave::SetVanish(int nFream)
{
	if (nFream > 0)
	{
		// �����鉉�o�̃t���O�𗧂Ă�
		m_bVanish = true;

		// ���o�̃t���[���ݒ�(�ۑ�)
		m_nVanishFream = nFream;

		// �t���[���J�E���^�̏�����
		m_nVanishCnt = nFream;
	}
}

//==================================================== 
// �L���鏈��
//==================================================== 
void CShockwave::Spread(void)
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
			//�p�x�Z�o
			float fAngle = ((D3DX_PI * 2.0f / m_nDiviX) * (m_nDiviX - nCntX));

			// �ړ��ʎZ�o
			D3DXVECTOR3 move = D3DXVECTOR3(m_fSpeed * sinf(fAngle), 0.0f, m_fSpeed * cosf(fAngle));

			// ���_�̈ʒu�ݒ�
			pVtx[indx].pos += move;

			// �J�E���g�A�b�v
			indx++;
		}
	}
	assert(indx <= m_nMaxVtx);

	// ���a�ɉ��Z
	m_fRadius += m_fSpeed;

	//���_�o�b�t�@���A�����b�N�@
	m_pVtxBuff->Unlock();
}

//====================================================
// �����鉉�o���� 
//==================================================== 
void CShockwave::Vanish(void)
{
	// �J�E���^�[�����炷
	--m_nVanishCnt;

	// �J�E���^�[������؂�����
	if (m_nVanishCnt < 0)
	{
		// �I������
		Uninit();

		return;
	}

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
			D3DXCOLOR col = pVtx[indx].col;

			float alpha = (((col.a + 0.1f) / m_nDiviY) / m_nVanishFream) * (m_nDiviY - nCntY) * m_nVanishCnt;

			col.a = alpha;

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