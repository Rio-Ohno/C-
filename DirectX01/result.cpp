//====================================================
//
// リザルトシーン処理 [result.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"result.h"
#include"manager.h"
#include"ranking.h"

// 静的メンバ変数
CMeshSphere* CResult::m_pSphere = NULL;
CScore* CResult::m_pScore = NULL;

//====================================================
// コンストラクタ
//====================================================
CResult::CResult() :CScene(CScene::MODE_TITLE)
{
	CObject::SetType(CObject::TYPE_SCENE);
}

//====================================================
// デストラクタ
//====================================================
CResult::~CResult()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// カメラ位置の設定
	CManager::GetCamera()->SetType(CCamera::TYPE_NOMAL);
	CManager::GetCamera()->SetCameraPos(D3DXVECTOR3(0.0f, 90.0f, -190.0f), D3DXVECTOR3(0.0f, 0.0f, 270.0f));

	// スコアの読込と生成処理
	int nScore = CScore::Load(SAVEFILE_SCORE);
	m_pScore = CScore::Create(D3DXVECTOR3(960.0f, 360.0f, 0.0f), 7, 75.0f, 150.0f);
	m_pScore->BindTexIndx(CTexture::TYPE_TIMENUMBER);
	m_pScore->Add(nScore);

	// 球体(空)の生成処理
	m_pSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 600.0f, false, false);
	m_pSphere->BindTexIndex(CTexture::TYPE_SKY);

	// 2Dポリゴン
	CObject2D* pResult = CObject2D::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), 720.0f, 150.0f);
	pResult->BindTexIndx(CTexture::TYPE_RESULT);

	// BGMの再生
	CManager::GetSound()->Play(CSound::SOUND_LABEL_RESULT);
	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CResult::Uninit(void)
{
	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CResult::Update(void)
{
	// スペースを押したらタイトルへ
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) == true)
	{
		CRanking::SetMode(CRanking::MODE::MODE_GAME);
		CManager::GetFade()->Set(CScene::MODE_RANKING);
	}
}

//====================================================
// 描画処理
//====================================================
void CResult::Draw(void)
{
	// なし
}