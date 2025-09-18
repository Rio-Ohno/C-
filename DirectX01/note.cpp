//====================================================
//
// �A�C�e��[item.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"note.h"
#include"noteManager.h"
#include"manager.h"
#include"game.h"
#include"tutorial.h"
#include"particle3D.h"

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

	m_pShadow = { NULL };
}

//====================================================
// �f�X�g���N�^
//====================================================
CNote::~CNote()
{
	// �����̑��������炷
	CNoteManager::DefNum();
}

//====================================================
// ��������
//====================================================
CNote* CNote::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CNote* pItem = NULL;

	// �������̊m��
	pItem = new CNote;

	// �����̑����𑝂₷
	CNoteManager::AddNum();

	// ���f���̊���
	pItem->BindModel("data/MODEL/note001.x");

	// ����������
	pItem->Init(pos, 0.0f, 0.0f);

	// �����̐ݒ�
	pItem->CObjectX::SetRot(rot);

	return pItem;
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

	// �e�̐���
	m_pShadow = CShadow::Create(D3DXVECTOR3(pos.x, pos.y + 0.3f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CNote::Uninit(void)
{
	if (m_pShadow != NULL)
	{
		// �I������
		m_pShadow->Uninit();
	}

	// �I�u�W�F�N�g�̏I������
	CObjectX::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CNote::Update(void)
{
	// �v���C���[�|�C���^
	CPlayer* pPlayer = NULL;

	// �X�R�A�|�C���^
	CScore* pScore = NULL;

	// �v���C���[�̏��擾
	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		// �v���C���[�̎擾
		pPlayer = CTutorial::GetPlayer();

		// �X�R�A�̎擾
		pScore = CTutorial::GetScore();
	}
	else if (CManager::GetMode() == CScene::MODE_GAME)
	{
		// �v���C���[�̎擾
		pPlayer = CGame::GetPlayer();

		// �X�R�A�̎擾
		pScore = CGame::GetScore();
	}

	// �v���C���[�ƃX�R�A��NULL����Ȃ��Ȃ�
	if (pPlayer != NULL)
	{
		// �v���C���[�ƏՓ˂����Ȃ�
		if (isColision(pPlayer->GetPos(), pPlayer->GetSize(), pPlayer->GetSize().x * 0.5f) == true)
		{
			if (pScore != NULL)
			{
				// �X�R�A���Z
				pScore->Add(1000);
			}

			// �p�[�e�B�N���̐ݒ�
			CParticle3D::Create(CObjectX::GetPos(), 
								D3DXVECTOR3(D3DX_PI * 0.25f, D3DX_PI * 2.0f, 0.0f),
								10.0f, 0.8f, 10, 60, 6);

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
// �����蔻��
//====================================================
bool CNote::isColision(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRadius)
{
	D3DXVECTOR3 apos = CObjectX::GetPos();// ���g�̈ʒu

	if (pos.y >= CObjectX::GetPos().y && pos.y <= CObjectX::GetPos().y + m_size.y ||
		pos.y + size.y >= CObjectX::GetPos().y && pos.y + size.y <= CObjectX::GetPos().y + m_size.y ||
		pos.y <= CObjectX::GetPos().y && pos.y + size.y <= CObjectX::GetPos().y)	// �A�C�e���̍����͈̔͂Ȃ�
	{
		float fDistance = (pos.x - CObjectX::GetPos().x) * (pos.x - CObjectX::GetPos().x) +
			(pos.z - CObjectX::GetPos().z) * (pos.z - CObjectX::GetPos().z);// ����(2D��)

		// ������
		fDistance = (float)sqrt(fDistance);

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