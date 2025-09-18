//====================================================
//
// シーン処理 [scene.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"scene.h"
#include"disposition.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"ranking.h"
#include"tutorial.h"

//====================================================
// コンストラクタ
//====================================================
CScene::CScene():CObject(0)
{

}

//====================================================
// コンストラクタ
//====================================================
CScene::CScene(MODE mode) :CObject(0)
{
	// 変数の初期化
	m_mode = mode;
}

//====================================================
// デストラクタ
//====================================================
CScene::~CScene()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = NULL;

	// メモリの確保
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

	// モードの設定
	if (pScene != NULL)
	{
		pScene->m_mode = mode;

		// 初期化処理
		pScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
	}

	return pScene;
}