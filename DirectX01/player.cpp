//====================================================
//
// �v���C���[[player.cpp]
// Author:Rio Ohno
//
//====================================================

//�C���N���[�h
#include"player.h"
#include"manager.h"
#include"object.h"
#include"input.h"
#include"effect3D.h"
#include"particle3D.h"
#include"object3D.h"

//�ÓI�����o�ϐ�
CMotion* CPlayer::m_pMotion = NULL;
CLoadMotion* CPlayer::m_pLoadMotion = NULL;

////====================================================
//// �R���X�g���N�^
////====================================================
//CPlayer::CPlayer()
//{
//	//�l���N���A
//	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_nCntAnim = 0;
//	m_nCntNumAnim = 0;
//
//	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
//	{
//		m_apBullet[nCnt] = NULL;
//	}
//}

//====================================================
// �R���X�g���N�^
//====================================================
CPlayer::CPlayer(int nPriority) :CObject(nPriority)
{
	//�l���N���A
	m_state = STATE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DestRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pShadow = { NULL };
}

//====================================================
// �f�X�g���N�^
//====================================================
CPlayer::~CPlayer()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ���[�V�����̏�����
	m_pMotion->Init(m_pMotion);

	for (int nCntModel = 0; nCntModel < m_pMotion->GetNumModel(); nCntModel++)
	{
		// ���_���̎擾
		int nNumVtx = m_pMotion->GetModel()[nCntModel]->GetMesh()->GetNumVertices();
		DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBUff;			// ���_�o�b�t�@�ւ̃|�C���^

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(m_pMotion->GetModel()[nCntModel]->GetMesh()->GetFVF());

		//���_�o�b�t�@�̃��b�N
		m_pMotion->GetModel()[nCntModel]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

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

			if (vtx.z >  m_vtxMax.z)//z�ő�l
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
		m_pMotion->GetModel()[nCntModel]->GetMesh()->UnlockVertexBuffer();
	}

	//�T�C�Y�̏�����
	m_size = m_vtxMax - m_vtxMin;

	//// �e�̐���
	//m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z), m_rot, 40.0f);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CPlayer::Uninit(void)
{
	if (m_pMotion != NULL)
	{
		// ���[�V�����̏I������
		m_pMotion->Uninit();

		// �������̊J��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CPlayer::Update(void)
{
	// ���[�V����
	m_pMotion->Update();

	//�v���C���[�̍s��
	Action();

	// // �e�̈ʒu�X�V
	//m_pShadow->CObject3D::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));
}

//====================================================
// �`�揈��
//====================================================
void CPlayer::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// // ���݂̂��̂�ۑ�
	//LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;		// �����_�����O�^�[�Q�b�g�Az�o�b�t�@
	//D3DVIEWPORT9 viewportDef;						// �r���[�|�[�g
	//D3DXMATRIX mtxViewDef, mtxProjectionDef;		// �r���[�}�g���b�N�X�A�v���W�F�N�V�����}�g���b�N�X

	//// ���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
	//pDevice->GetRenderTarget(0, &pRenderDef);

	//// ���݂�z�o�b�t�@���擾(�ۑ�)
	//pDevice->GetDepthStencilSurface(&pZBuffDef);

	//// ���݂̃r���[�|�[�g���擾(�ۑ�)
	//pDevice->GetViewport(&viewportDef);

	//// ���݂̃r���[�}�g���b�N�X���擾(�ۑ�)
	//pDevice->GetTransform(D3DTS_VIEW, &mtxViewDef);

	//// ���݂̃v���W�F�N�V�����}�g���b�N�X���擾(�ۑ�)
	//pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjectionDef);

	//// �����_�����O�^�[�Q�b�g�̕ύX
	//CManager::GetRenderer()->ChangeTarget(D3DXVECTOR3(0.0f, 100.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̃N���A
	//pDevice->Clear(0,
	//				NULL,
	//				(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	//				D3DCOLOR_RGBA(100, 255, 220, 255),
	//				1.0f,
	//				0);


	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

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

	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		// model�̕`�揈��
		m_pMotion->GetModel()[nCnt]->Draw();
	}

	////�ۑ����Ă����}�e���A����߂�
	//pDevice->SetMaterial(&matDef);

	//// �����_�����O�^�[�Q�b�g�����ɖ߂�
	//pDevice->SetRenderTarget(0, pRenderDef);

	//// z�o�b�t�@�����ɖ߂�
	//pDevice->SetDepthStencilSurface(pZBuffDef);

	//// �r���[�|�[�g�����ɖ߂�
	//pDevice->SetViewport(&viewportDef);

	//// �r���[�}�g���b�N�X�����ɖ߂�
	//pDevice->SetTransform(D3DTS_VIEW, &mtxViewDef);

	//// �v���W�F�N�V�����}�g���b�N�X�����ɖ߂�
	//pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjectionDef);
}

//====================================================
// ���[�V�����̐ݒ菈��
//====================================================
void CPlayer::SetMotion(const char* pFileName)
{
	m_pMotion = new CMotion;

	// ���[�V�����̓Ǎ�
	CLoadMotion::Load(pFileName, m_pMotion);
}

//====================================================
// ��������
//====================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer = NULL;

	//�������̊m��
	pPlayer = new CPlayer;

	// �ϐ��̐ݒ�
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;

	//����������
	pPlayer->Init(pos, 0.0f, 0.0f);

	// ��ނ̐ݒ�
	pPlayer->SetType(CObject::TYPE_PLAYER);

	return pPlayer;
}

//====================================================
// �s������
//====================================================
void CPlayer::Action(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	// �I�u�W�F�N�g3D�̎擾
	CObject3D* pObject3D = CManager::GetObject3D();

	// �J�����̎擾
	CCamera* pCamera = CManager::GetCamera();

	// �O�t���[���̈ʒu�ۑ�
	m_posOld = m_pos;

	if (pKeyboard->GetPress(DIK_W) == true)
	{// W�������ꂽ��

		m_move.x += sinf(pCamera->GetRot().y) * PLAYER_SPEED;
		m_move.z += cosf(pCamera->GetRot().y) * PLAYER_SPEED;
		m_DestRot.y = pCamera->GetRot().y + D3DX_PI;
	}
	if (pKeyboard->GetPress(DIK_A) == true)
	{// A�������ꂽ��
		m_move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_DestRot.y = pCamera->GetRot().y + D3DX_PI * 0.5f;
	}
	if (pKeyboard->GetPress(DIK_S) == true)
	{// S��������Ă���Ƃ�
		m_move.x -= sinf(pCamera->GetRot().y) * PLAYER_SPEED;
		m_move.z -= cosf(pCamera->GetRot().y) * PLAYER_SPEED;
		m_DestRot.y = pCamera->GetRot().y;
	}
	if (pKeyboard->GetPress(DIK_D) == true)
	{// D�������ꂽ��
		m_move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_DestRot.y = pCamera->GetRot().y - D3DX_PI * 0.5f;
	}

#if _DEBUG

	if (pKeyboard->GetTrigger(DIK_R) == true)
	{// ENTER�������ꂽ��

		// �ʒu�̐ݒ�
		CPlayer::SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{// SPACE�������ꂽ��
		//CEffect3D::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 120, 1.0f);
		CParticle3D::Create(m_pos, D3DXVECTOR3(D3DX_PI * 2.0f, D3DX_PI * 2.0f, D3DX_PI * 2.0f), 20.0f, 1.0f, 600, 120, 20);
	}
#endif

	// �ʒu���X�V
	m_pos += m_move;

	// �����̎擾
	m_move.y = pObject3D->GetHeight();

	//�ړ��ʂ��X�V�i�����j
	m_move.x += (0.0f - m_move.x) * 0.09f;
	m_move.y += (0.0f - m_move.y) * 0.09f;
	m_move.z += (0.0f - m_move.z) * 0.09f;//����܂肢��Ȃ����琔���ł��߂ɂ��Ă�

	//if (m_posOld.x-m_pos.x!=0.0f|| m_posOld.z - m_pos.z != 0.0f)
	//{
	//	CManager::GetRenderer()->SetFeedbackEffect(true);
	//}
	//else
	//{
	//	CManager::GetRenderer()->SetFeedbackEffect(false);
	//}

	// �p�x�̋ߓ�
	if ((m_DestRot.y - m_rot.y) >= D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if ((m_DestRot.y - m_rot.y) <= -D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// ���X�ɖڕW��
	m_rot += (m_DestRot - m_rot) * 0.1f;
}