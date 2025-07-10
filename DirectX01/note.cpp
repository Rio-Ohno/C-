//====================================================
//
// �A�C�e��[item.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"note.h"
#include"manager.h"
#include"player.h"
#include"score.h"

//====================================================
// �R���X�g���N�^
//====================================================
CNote::CNote()
{
	// �����o�ϐ��̏�����
	m_nCounter = 0;

	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = {};
}

//====================================================
// �f�X�g���N�^
//====================================================
CNote::~CNote()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CNote::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �I�u�W�F�N�g�̏�����
	if (FAILED(CObjectX::Init(pos, 0.0f, 0.0f)))
	{
		return -1;
	}

	int nNumVtx = CObjectX::GetMesh()->GetNumVertices();//�ő咸�_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBUff;//���_�o�b�t�@�ւ̃|�C���^

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(CObjectX::GetMesh()->GetFVF());

	//���_�o�b�t�@�̃��b�N
	CObjectX::GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

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
	CObjectX::GetMesh()->UnlockVertexBuffer();

	//�T�C�Y�̏�����
	m_size = m_vtxMax - m_vtxMin;

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CNote::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	CObjectX::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CNote::Update(void)
{
	// �v���C���[�|�C���^�̎擾
	CPlayer* pPlayer = CManager::GetPlayer();

	// �X�R�A�|�C���^�̎擾
	CScore* pScore = CManager::GetScore();

	// �v���C���[�ƃX�R�A��NULL����Ȃ��Ȃ�
	if (pPlayer != NULL && pScore != NULL)
	{
		// �v���C���[�ƏՓ˂����Ȃ�
		if (isColision(pPlayer->GetPos(), pPlayer->GetSize().x) == true)
		{
			// �X�R�A���Z
			pScore->Add(1000);

			// �I������
			Uninit();
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CNote::Draw(void)
{
	// �I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//====================================================
// ��������
//====================================================
CNote* CNote::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CNote* pItem = NULL;

	// �������̊m��
	pItem = new CNote;

	// ���f���̊���
	pItem->BindModel("data/MODEL/note001.x");

	// ����������
	pItem->Init(pos, 0.0f, 0.0f);

	// �����̐ݒ�
	pItem->CObjectX::SetRot(rot);

	return pItem;
}

//====================================================
// �����蔻��
//====================================================
bool CNote::isColision(D3DXVECTOR3 pos, float fRadius)
{
	D3DXVECTOR3 apos = CObjectX::GetPos();// ���g�̈ʒu

	if (pos.y >= CObjectX::GetPos().y && pos.y < CObjectX::GetPos().y + m_size.y)	// �A�C�e���̍����͈̔͂Ȃ�
	{
		float fDistance = (pos.x - CObjectX::GetPos().x) * (pos.x - CObjectX::GetPos().x) +
			(pos.z - CObjectX::GetPos().z) * (pos.z - CObjectX::GetPos().z);// ����(2D��)

		if (fDistance <= (fRadius + m_size.x * 0.5f))
		{
			// �������Ă���
			return true;
		}
		else
		{
			// �������Ă��Ȃ�
			return false;
		}
	}

	// �������Ă��Ȃ�
	return false;
}