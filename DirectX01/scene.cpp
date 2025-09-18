//====================================================
//
// �V�[������ [scene.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"scene.h"
#include"disposition.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"ranking.h"
#include"tutorial.h"

//====================================================
// �R���X�g���N�^
//====================================================
CScene::CScene():CObject(0)
{

}

//====================================================
// �R���X�g���N�^
//====================================================
CScene::CScene(MODE mode) :CObject(0)
{
	// �ϐ��̏�����
	m_mode = mode;
}

//====================================================
// �f�X�g���N�^
//====================================================
CScene::~CScene()
{
	// �Ȃ�
}

//====================================================
// ��������
//====================================================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = NULL;

	// �������̊m��
	switch (mode)
	{
	case MODE_TITLE:

		pScene = new CTitle;

		break;

	case MODE_GAME:

		pScene = new CGame;

		break;

	case MODE_RESULT:

		pScene = new CResult;

		break;

	case MODE_RANKING:

		pScene = new CRanking;
		break;

	case MODE_TUTORIAL:

		pScene = new CTutorial;
		break;

	case MODE_EDIT_DISPOSITION:

#ifdef _DEBUG
		//pScene = new CDisposition;
#endif // _DEBUG

		break;

	default:
		break;
	}

	// ���[�h�̐ݒ�
	if (pScene != NULL)
	{
		pScene->m_mode = mode;

		// ����������
		pScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
	}

	return pScene;
}