//====================================================
//
// �^�C�g���V�[������ [title.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"title.h"
#include"object2D.h"
#include"manager.h"

//====================================================
// �R���X�g���N�^
//====================================================
CTitle::CTitle() :CScene(CScene::MODE_TITLE)
{
	CObject::SetType(CObject::TYPE_SCENE);
}

//====================================================
// �f�X�g���N�^
//====================================================
CTitle::~CTitle()
{

}

//====================================================
// ����������
//====================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �e�N�X�`���̎擾
	CTexture* pTexture = CManager::GetTexture();

	CObject2D* poly = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	poly->BindTexIndx(pTexture->Register("data\\TEXTURE\\Title000.png"));

	// �J�����̐ݒ�
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CTitle::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V����
//====================================================
void CTitle::Update(void)
{
	// �X�y�[�X����������Q�[����
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) == true)
	{
		CManager::GetFade()->Set(CScene::MODE_GAME);
	}
}

//====================================================
// �`�揈��
//====================================================
void CTitle::Draw(void)
{
	// �Ȃ�
}