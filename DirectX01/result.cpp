//====================================================
//
// ���U���g�V�[������ [result.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"result.h"
#include"manager.h"

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
	// �e�N�X�`���̎擾
	CTexture* pTexture = CManager::GetTexture();

	CObject2D* poly = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	poly->BindTexIndx(pTexture->Register("data\\TEXTURE\\Result000.png"));

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
		CManager::GetFade()->Set(CScene::MODE_TITLE);
	}
}

//====================================================
// �`�揈��
//====================================================
void CResult::Draw(void)
{
	// �Ȃ�
}