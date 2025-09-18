//====================================================
//
// ���U���g�V�[������ [result.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"result.h"
#include"manager.h"
#include"ranking.h"

// �ÓI�����o�ϐ�
CMeshSphere* CResult::m_pSphere = NULL;
CScore* CResult::m_pScore = NULL;

//====================================================
// �R���X�g���N�^
//====================================================
CResult::CResult() :CScene(CScene::MODE_TITLE)
{
	CObject::SetType(CObject::TYPE_SCENE);
}

//====================================================
// �f�X�g���N�^
//====================================================
CResult::~CResult()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �J�����ʒu�̐ݒ�
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 90.0f, -190.0f), D3DXVECTOR3(0.0f, 0.0f, 270.0f));

	// �X�R�A�̓Ǎ��Ɛ�������
	int nScore = CScore::Load(SAVEFILE_SCORE);
	m_pScore = CScore::Create(D3DXVECTOR3(960.0f, 360.0f, 0.0f), 7, 75.0f, 150.0f);
	m_pScore->BindTexIndx(CTexture::TYPE_TIMENUMBER);
	m_pScore->Add(nScore);

	// ����(��)�̐�������
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);

	// 2D�|���S��
	CObject2D* pResult = CObject2D::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), 720.0f, 150.0f);
	pResult->BindTexIndx(CTexture::TYPE_RESULT);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CResult::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CResult::Update(void)
{
	// �X�y�[�X����������^�C�g����
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) == true)
	{
		CRanking::SetMode(CRanking::MODE::MODE_GAME);
		CManager::GetFade()->Set(CScene::MODE_RANKING);
	}
}

//====================================================
// �`�揈��
//====================================================
void CResult::Draw(void)
{
	// �Ȃ�
}