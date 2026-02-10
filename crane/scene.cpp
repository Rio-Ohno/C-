//====================================================
//
// シーン処理 [scene.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "scene.h"
#include "test.h"
#include "title.h"
#include "game.h"
#include "result.h"

// 静的メンバ変数
CScene::MODE CScene::m_mode;

//====================================================
// コンストラクタ
//====================================================
CScene::CScene():CObject(0)
{
	// なし
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
	CScene* pScene = nullptr;

	// メモリの確保
	switch (mode)
	{
	case MODE_TEST:
		pScene = new CTest;
		break;

	case MODE_TITLE:
		pScene = new CTitle;
		break;

	case MODE_GAME:
		pScene = new CGame;
		break;

	case MODE_RESULT:
		pScene = new CResult;
		break;

	default:
		break;
	}

	// モードの設定
	if (pScene != nullptr)
	{
		pScene->m_mode = mode;

		// 初期化処理
		pScene->Init();
	}

	return pScene;
}