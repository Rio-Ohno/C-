//====================================================
// 
// �r���{�[�h�I�u�W�F�N�g [objectBillboard.cpp]
// Author:Rio Ohno
// 
//====================================================

// �C���N���[�h
#include"objectBillboard.h"
#include"manager.h"

//====================================================
// �R���X�g���N�^
//====================================================
CObjectBillboard::CObjectBillboard()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_indxTexture = -1;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
}

//====================================================
// �f�X�g���N�^
//====================================================
CObjectBillboard::~CObjectBillboard()
{
	// �Ȃ�
}

//====================================================
// �r���{�[�h�̏���������
//====================================================
HRESULT CObjectBillboard::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�ւ̃|�C���^�Ǝ擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

		m_pos = pos;
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fHeight = fHeight;
		m_fWidth = fWidth;

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(m_origin.x), (m_fHeight - m_origin.y), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(m_fWidth - m_origin.x), (m_fHeight - m_origin.y), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_origin.x), (-m_origin.y), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(m_fWidth - m_origin.x), (-m_origin.y), 0.0f);

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================================
// �r���{�[�h�̏I������
//============================================================
void CObjectBillboard::Uninit(void)
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

//============================================================
// �r���{�[�h�̍X�V����
//============================================================
void CObjectBillboard::Update(void)
{

}

//============================================================
// �r���{�[�h�̕`�揈��
//============================================================
void CObjectBillboard::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// �e�N�X�`���N���X�ւ̃|�C���^�̎擾
	CTexture* pTexture = CManager::GetTexture();

	//���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X

	//�r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`�����W�̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_indxTexture));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================================
// ��������
//============================================================
CObjectBillboard* CObjectBillboard::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXVECTOR3 origin)
{
	CObjectBillboard* pBillboard = NULL;

	pBillboard = new CObjectBillboard;

	// �ʒu����̋���
	pBillboard->m_origin = origin;

	// ����������
	pBillboard->Init(pos, fWidth, fHeight);

	return pBillboard;
}

//============================================================
// �T�C�Y�̐ݒ�
//============================================================
void CObjectBillboard::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
}

//============================================================
// �F�̐ݒ�
//============================================================
void CObjectBillboard::SetColor(D3DXCOLOR col)
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