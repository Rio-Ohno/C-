//====================================================
//
// ��[wall.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"wall.h"
#include"manager.h"
#include"tutorial.h"
#include"game.h"

//====================================================
// �R���X�g���N�^
//====================================================
CWall::CWall()
{
	// �e�ϐ��̏�����
	m_pVtxBuff = { NULL };
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTexindx = -1;
	m_fLength = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_bCollision = false;
	m_bDisp = true;
}

//====================================================
// �f�X�g���N�^
//====================================================
CWall::~CWall()
{
	// �Ȃ�
}

//====================================================
// ��������
//====================================================
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight,bool bCollision,bool bDisp)
{
	CWall* pWall = NULL;

	// �������̊m��
	pWall = new CWall;

	pWall->m_pos = pos;
	pWall->m_rot = rot;
	pWall->m_fWidth = fWidth;
	pWall->m_fHeight = fHeight;
	pWall->m_bCollision = bCollision;
	pWall->m_bDisp = bDisp;

	// ����������
	pWall->Init(pos, fWidth, fHeight);

	return pWall;
}

//====================================================
// ����������
//====================================================
HRESULT CWall::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�ւ̃|�C���^�Ǝ擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth * 0.5f, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth * 0.5f, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth * 0.5f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, 0.0f);

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
void CWall::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
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
void CWall::Update(void)
{
	if (m_bCollision == true)// �����蔻����Ƃ�Ȃ�
	{
		// �v���C���[�|�C���^
		CPlayer* pPlayer = NULL;

		if (CManager::GetMode() == CScene::MODE_TUTORIAL)
		{
			// �`���[�g���A���̃v���C���[�擾
			pPlayer = CTutorial::GetPlayer();
		}
		else if (CManager::GetMode() == CScene::MODE_GAME)
		{
			// �Q�[���̃v���C���[�擾
			pPlayer = CGame::GetPlayer();
		}

		if (pPlayer != NULL)
		{
			D3DXVECTOR3 pos = pPlayer->GetPos();
			if (isColision(pos) == true)// �����������Ă�����
			{

				// �O�̈ʒu�̎擾
				D3DXVECTOR3 oldpos = pPlayer->GetOldPos();

				// �O�̈ʒu�ɖ߂�(�����ȊO)
				pPlayer->SetPos(D3DXVECTOR3(oldpos.x, pos.y, oldpos.z));

				// �ړ��ʂ̃��Z�b�g
				pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CWall::Draw(void)
{
		//�f�o�C�X�ւ̃|�C���^�Ǝ擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���|�C���^�̎擾
		CTexture* pTexture = CManager::GetTexture();

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

		if (m_bDisp == true)// �\������Ȃ�
		{
			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

			//�e�N�X�`�����W�̐ݒ�
			pDevice->SetTexture(0, pTexture->GetAddress(m_nTexindx));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
}

//====================================================
// �����蔻�菈��
//====================================================
bool CWall::isColision(D3DXVECTOR3 pos)
{
	if (m_pos.x + m_fWidth * 0.5f >= pos.x && m_pos.x - m_fWidth * 0.5f <= pos.x && m_pos.y + m_fHeight * 0.5f >= pos.y && m_pos.y <= pos.y)
	{
		D3DXVECTOR3 VecWall, VecTarget, cross;
		D3DXVECTOR3 pos1, pos2;

		pos1.x = m_pos.x - cosf(m_rot.y) * (m_fWidth * 0.5f);
		pos1.y = 0.0f;
		pos1.z = m_pos.z + sinf(m_rot.y) * (m_fWidth * 0.5f);

		pos2.x = m_pos.x + cosf(m_rot.y) * (m_fWidth * 0.5f);
		pos2.y = 0.0f;
		pos2.z = m_pos.z - sinf(m_rot.y) * (m_fWidth * 0.5f);

		VecWall = pos2 - pos1;
		VecTarget = pos - pos1;

		// �O��
		D3DXVec3Cross(&cross, &VecWall, &VecTarget);

		if (cross.y < 0.0f)
		{
			return true;
		}
	}

	return false;
}

//====================================================
// ���ˏ���
//====================================================
D3DXVECTOR3 CWall::Reflect(D3DXVECTOR3 pos, D3DXVECTOR3 posOld)
{
	D3DXVECTOR3 VecWall, VecTarget, cross;
	D3DXVECTOR3 pos1, pos2;
	D3DXVECTOR3 nor,reflect;
	float Dot;

	pos1.x = m_pos.x - cosf(m_rot.y) * (m_fWidth * 0.5f);
	pos1.y = 0.0f;
	pos1.z = m_pos.z + sinf(m_rot.y) * (m_fWidth * 0.5f);

	pos2.x = m_pos.x + cosf(m_rot.y) * (m_fWidth * 0.5f);
	pos2.y = 0.0f;
	pos2.z = m_pos.z - sinf(m_rot.y) * (m_fWidth * 0.5f);

	VecWall = pos2 - pos1;
	VecTarget = pos - posOld;

	// �O��
	D3DXVec3Cross(&nor, &VecWall, &VecTarget);

	// �t�x�N�g���ɂ���
	VecTarget *= -1.0f;

	// ����
	Dot = D3DXVec3Dot(&VecTarget, &nor);
	reflect = VecTarget + 2.0f * Dot * nor;

	return reflect;
}

//====================================================
// �F�̐ݒ�
//====================================================
void CWall::SetColor(D3DCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//====================================================
// �e�N�X�`�����W�̐ݒ�
//====================================================
void CWall::SetTexUV(float minU, float maxU, float minV, float maxV)
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(minU,minV);
	pVtx[1].tex = D3DXVECTOR2(maxU,minV);
	pVtx[2].tex = D3DXVECTOR2(minU,maxV);
	pVtx[3].tex = D3DXVECTOR2(maxU,maxV);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
