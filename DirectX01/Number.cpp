//==================================================== 
// 
// ���l�̊Ǘ��@[Number.cpp]
// Author: Rio Ohno
// 
//==================================================== 

// �C���N���[�h
#include"Number.h"
#include"manager.h"

//==================================================== 
// �R���X�g���N�^
//==================================================== 
CNumber::CNumber()
{
	// �e������
	m_pVtxBuff = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_Texindx = -1;								// �e�N�X�`���C���f�b�N�X
	m_fWidth = 0;								// ��
	m_fHeight = 0;								// ����
}

//==================================================== 
// �f�X�g���N�^
//==================================================== 
CNumber::~CNumber()
{
	// �Ȃ�
}

//==================================================== 
// ����������
//==================================================== 
void CNumber::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�ϐ��̏�����
	m_pos = pos;// �ʒu
	m_fWidth = fWidth;// ��
	m_fHeight = fHeight;// ����

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

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//rhw�̐ݒ�
		pVtx[nCnt].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//==================================================== 
// �I������
//==================================================== 
void CNumber::Uninit(void)
{
	//�o�b�t�@�[�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �������̔j��
	delete this;
}

//==================================================== 
// �X�V����
//==================================================== 
void CNumber::Update(void)
{

}

//==================================================== 
// �`�揈��
//==================================================== 
void CNumber::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���N���X�ւ̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	//�|���S���̕`�揈��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_Texindx));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==================================================== 
// �F�̎擾����
//==================================================== 
D3DXCOLOR CNumber::GetColor(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	D3DXCOLOR col = {};

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
	col = pVtx[0].col;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return col;
}

//==================================================== 
// �F�̐ݒ�
//==================================================== 
void CNumber::SetColor(D3DXCOLOR col)
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

//==================================================== 
// ��������
//==================================================== 
CNumber* CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CNumber* pNumber = NULL;
	pNumber = new CNumber;

	pNumber->Init(pos,fWidth,fHeight);

	return pNumber;
}

//==================================================== 
// �e���̐��l��ݒ�
//==================================================== 
int CNumber::SetNum(int nNumber,int nDight)
{
	int nNum = 0;// �e���̐��l�i�[�p
	int nDiffDight = 10;

	for (int nCnt = 0; nCnt < nDight; nCnt++)
	{
		nNumber /= 10;
	}

	// ���l�̓���
	nNum = nNumber % 10;

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
		//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f * nNum, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (nNum + 1.0f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * nNum, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (nNum + 1.0f), 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return nNum;
}