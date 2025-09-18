//====================================================
//
// �e[shadowS.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"shadowS.h"
#include"manager.h"
#include"input.h"

// �ÓI�����o�ϐ�
bool CShadowS::m_bmodel = false;

//====================================================
// �R���X�g���N�^
//====================================================
CShadowS::CShadowS(int nPriority):CObjectX(nPriority)
{
	m_pVtxBuff = { NULL };
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//====================================================
// �f�X�g���N�^
//====================================================
CShadowS::~CShadowS()
{
	// �Ȃ�
}

//====================================================
// ��������
//====================================================
CShadowS* CShadowS::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CShadowS* pShadowS = NULL;

	// �������̊m��
	pShadowS = new CShadowS;

	// ���f���̃t�@�C���p�X�̊���
	pShadowS->BindModel("data\\MODEL\\shadow.x");

	// ����������
	pShadowS->Init(pos, 0.0f, 0.0f);

	return pShadowS;
}

//====================================================
// ����������
//====================================================
HRESULT CShadowS::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ���f���̏���������
	CObjectX::Init(pos, 0.0f, 0.0f);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�ϐ��̏�����
	m_pos = pos;// �ʒu

	//�|���S���̏���������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//rhw�̐ݒ�
		pVtx[nCnt].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DCOLOR_RGBA(0, 0, 0, 200);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CShadowS::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̏I������
	CObjectX::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CShadowS::Update(void)
{
	// �I�u�W�F�N�g�̍X�V
	CObjectX::Update();

#ifdef _DEBUG

	// ����
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	// �e���f����\�����邩�ǂ���
	if (pKeyboard->GetTrigger(DIK_F3) == true)
	{
		m_bmodel = m_bmodel ? false : true;
	}
#endif // _DEBUG
}

//====================================================
// �`�揈��
//====================================================
void CShadowS::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

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

	if (m_bmodel == false)
	{
		// �X�e���V���e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// Z�o�b�t�@�ւ̏������݂𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		// �J���[�o�b�t�@�ւ̏������݂𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

		// �X�e���V���o�b�t�@�̔�r�p�����[�^��ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);

		//�\�ʂ��J�����O
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}

	 //�e���f���̕`�揈��
	CObjectX::Draw();

	if (m_bmodel == false)
	{
		// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("1"�ɂ���)
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		// �X�e���V���o�b�t�@�̔�r�p�����[�^��ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);

		// �\�ʂ��J�����O
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// �e���f���̕`�揈��
		CObjectX::Draw();
	}
		// �J���[�o�b�t�@�ւ̏������݂�L���ɂ���
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);

	if (m_bmodel == false)
	{
		// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("2"�ɂ���)
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

		// �X�e���V���o�b�t�@�̔�r�p�����[�^��ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);


		// ��ʃT�C�Y�̍��|���S���`��
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// �S�Č��ɖ߂�
	
	// �X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�J�����O������
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}