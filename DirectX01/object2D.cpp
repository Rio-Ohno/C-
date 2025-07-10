//====================================================
//
// �I�u�W�F�N�g[object.h]
// Author:Rio Ohno
//
//====================================================

//�C���N���[�h
#include"object2D.h"
#include"renderer.h"
#include"manager.h"

////====================================================
//// �R���X�g���N�^
////====================================================
//CObject2D::CObject2D()
//{
//	//�l���N���A����
//	m_pTexture = NULL;
//	m_pVtxBuff = NULL;
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_fWidth = 0;
//	m_fHeight = 0;
//}

//====================================================
// �R���X�g���N�^
//====================================================
CObject2D::CObject2D(int nPriority) :CObject(nPriority)
{
	//�l���N���A����
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0;
	m_fHeight = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CObject2D::~CObject2D()
{
}

//====================================================
// ����������
//====================================================
HRESULT CObject2D::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�����_���[�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�ϐ��̏�����
	m_pos = pos;// �ʒu
	m_fWidth = fWidth;// ��
	m_fHeight = fHeight;// ����

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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, 
							  m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/,
							  m_pos.z);

	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/,
							  m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/,
							  m_pos.z);

	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/,
							  m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/,
		                      m_pos.z);

	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/,
							  m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/,
							  m_pos.z);

	//int i = 0;

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
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CObject2D::Uninit(void)
{
	//�|���S���̏I������
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}

	//�o�b�t�@�[�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CObject2D::Update(void)
{
	//�|���S���̍X�V����
}

//====================================================
// �`�揈��
//====================================================
void CObject2D::Draw(void)
{
	//�����_���[�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�|���S���̕`�揈��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//====================================================
// �ʒu�̐ݒ�
//====================================================
void CObject2D::SetPos(const D3DXVECTOR3 pos)
{
	CObject2D::m_pos = pos;

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//====================================================
// �����̐ݒ�
//====================================================
void CObject2D::SetRot(const D3DXVECTOR3 rot)
{
	CObject2D::m_rot = rot;
}

//====================================================
// �T�C�Y�̐ݒ�
//====================================================
void CObject2D::SetSize(const float fWidth,const float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y - m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f /** sinf(m_rot.z)*/, m_pos.y + m_fHeight * 0.5f /** cosf(m_rot.z)*/, m_pos.z);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//====================================================
// �e�N�X�`���̐ݒ菈��
//====================================================
void CObject2D::BindTex(LPDIRECT3DTEXTURE9 pTexture)
{
	// �e�N�X�`���̐ݒ�
	m_pTexture = pTexture;
}

//====================================================
// �e�N�X�`���̐ݒ菈��
//====================================================
void CObject2D::BindTex2(int nTextureIndx)
{
	// �e�N�X�`���C���f�b�N�X�̐ݒ�
	m_nIndxTex = nTextureIndx;
}

//====================================================
// ��������
//====================================================
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CObject2D* pObject2D = NULL;

	//�I�u�W�F�N�g�̐���
	pObject2D = new CObject2D;

	//����������
	pObject2D->Init(pos, fWidth, fHeight);

	return pObject2D;
}

//====================================================
// �e�N�X�`����UV�ݒ菈��
//====================================================
void CObject2D::SetTexUV(float fDiviX, float fDiviY)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
		//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / fDiviX), (1.0f / fDiviY) - 1);
	pVtx[1].tex = D3DXVECTOR2((1.0f / fDiviX) * 2.0f, (1.0f / fDiviY) - 1);
	pVtx[2].tex = D3DXVECTOR2((1.0f / fDiviX), (1.0f / fDiviY));
	pVtx[3].tex = D3DXVECTOR2((1.0f / fDiviX) * 2.0f, (1.0f / fDiviY));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//====================================================
// ���_�o�b�t�@�̐ݒ菈��
//====================================================
void CObject2D::SetBuffer(LPDIRECT3DVERTEXBUFFER9 pVtxBuff)
{
	// ���_�o�b�t�@�̐ݒ�
	m_pVtxBuff = pVtxBuff;
}

//====================================================
// ���_�J���[�̐ݒ菈��
//====================================================
void CObject2D::SetColor(D3DXCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = col;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}
