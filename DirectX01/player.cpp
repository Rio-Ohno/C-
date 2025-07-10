//====================================================
//
// プレイヤー[player.cpp]
// Author:Rio Ohno
//
//====================================================

//インクルード
#include"player.h"
#include"manager.h"
#include"object.h"
#include"input.h"
#include"effect3D.h"
#include"particle3D.h"
#include"object3D.h"

//静的メンバ変数
CMotion* CPlayer::m_pMotion = NULL;
CLoadMotion* CPlayer::m_pLoadMotion = NULL;

////====================================================
//// コンストラクタ
////====================================================
//CPlayer::CPlayer()
//{
//	//値をクリア
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
// コンストラクタ
//====================================================
CPlayer::CPlayer(int nPriority) :CObject(nPriority)
{
	//値をクリア
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
// デストラクタ
//====================================================
CPlayer::~CPlayer()
{
	// なし
}

//====================================================
// 初期化処理
//====================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// モーションの初期化
	m_pMotion->Init(m_pMotion);

	for (int nCntModel = 0; nCntModel < m_pMotion->GetNumModel(); nCntModel++)
	{
		// 頂点数の取得
		int nNumVtx = m_pMotion->GetModel()[nCntModel]->GetMesh()->GetNumVertices();
		DWORD sizeFVF;			// 頂点フォーマットのサイズ
		BYTE* pVtxBUff;			// 頂点バッファへのポインタ

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_pMotion->GetModel()[nCntModel]->GetMesh()->GetFVF());

		//頂点バッファのロック
		m_pMotion->GetModel()[nCntModel]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

		for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

			//頂点座標を比較してモデルの最大最小を取得

			if (vtx.x > m_vtxMax.x)//x最大値
			{
				m_vtxMax.x = vtx.x;
			}
			else if (vtx.x < m_vtxMin.x)//x最小値
			{
				m_vtxMin.x = vtx.x;
			}

			if (vtx.y > m_vtxMax.y)//y最大値
			{
				m_vtxMax.y = vtx.y;
			}
			else if (vtx.y < m_vtxMin.y)//y最小値
			{
				m_vtxMin.y = vtx.y;
			}

			if (vtx.z >  m_vtxMax.z)//z最大値
			{
				m_vtxMax.z = vtx.z;
			}
			else if (vtx.z < m_vtxMin.z)//z最小値
			{
				m_vtxMin.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBUff += sizeFVF;
		}

		//頂点バッファのアンロック
		m_pMotion->GetModel()[nCntModel]->GetMesh()->UnlockVertexBuffer();
	}

	//サイズの初期化
	m_size = m_vtxMax - m_vtxMin;

	//// 影の生成
	//m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z), m_rot, 40.0f);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CPlayer::Uninit(void)
{
	if (m_pMotion != NULL)
	{
		// モーションの終了処理
		m_pMotion->Uninit();

		// メモリの開放
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// オブジェクトの破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CPlayer::Update(void)
{
	// モーション
	m_pMotion->Update();

	//プレイヤーの行動
	Action();

	// // 影の位置更新
	//m_pShadow->CObject3D::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));
}

//====================================================
// 描画処理
//====================================================
void CPlayer::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// // 現在のものを保存
	//LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;		// レンダリングターゲット、zバッファ
	//D3DVIEWPORT9 viewportDef;						// ビューポート
	//D3DXMATRIX mtxViewDef, mtxProjectionDef;		// ビューマトリックス、プロジェクションマトリックス

	//// 現在のレンダリングターゲットを取得(保存)
	//pDevice->GetRenderTarget(0, &pRenderDef);

	//// 現在のzバッファを取得(保存)
	//pDevice->GetDepthStencilSurface(&pZBuffDef);

	//// 現在のビューポートを取得(保存)
	//pDevice->GetViewport(&viewportDef);

	//// 現在のビューマトリックスを取得(保存)
	//pDevice->GetTransform(D3DTS_VIEW, &mtxViewDef);

	//// 現在のプロジェクションマトリックスを取得(保存)
	//pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjectionDef);

	//// レンダリングターゲットの変更
	//CManager::GetRenderer()->ChangeTarget(D3DXVECTOR3(0.0f, 100.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//// レンダリングターゲット用テクスチャのクリア
	//pDevice->Clear(0,
	//				NULL,
	//				(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	//				D3DCOLOR_RGBA(100, 255, 220, 255),
	//				1.0f,
	//				0);


	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		// modelの描画処理
		m_pMotion->GetModel()[nCnt]->Draw();
	}

	////保存していたマテリアルを戻す
	//pDevice->SetMaterial(&matDef);

	//// レンダリングターゲットを元に戻す
	//pDevice->SetRenderTarget(0, pRenderDef);

	//// zバッファを元に戻す
	//pDevice->SetDepthStencilSurface(pZBuffDef);

	//// ビューポートを元に戻す
	//pDevice->SetViewport(&viewportDef);

	//// ビューマトリックスを元に戻す
	//pDevice->SetTransform(D3DTS_VIEW, &mtxViewDef);

	//// プロジェクションマトリックスを元に戻す
	//pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjectionDef);
}

//====================================================
// モーションの設定処理
//====================================================
void CPlayer::SetMotion(const char* pFileName)
{
	m_pMotion = new CMotion;

	// モーションの読込
	CLoadMotion::Load(pFileName, m_pMotion);
}

//====================================================
// 生成処理
//====================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer = NULL;

	//メモリの確保
	pPlayer = new CPlayer;

	// 変数の設定
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;

	//初期化処理
	pPlayer->Init(pos, 0.0f, 0.0f);

	// 種類の設定
	pPlayer->SetType(CObject::TYPE_PLAYER);

	return pPlayer;
}

//====================================================
// 行動処理
//====================================================
void CPlayer::Action(void)
{
	//キーボードの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	// オブジェクト3Dの取得
	CObject3D* pObject3D = CManager::GetObject3D();

	// カメラの取得
	CCamera* pCamera = CManager::GetCamera();

	// 前フレームの位置保存
	m_posOld = m_pos;

	if (pKeyboard->GetPress(DIK_W) == true)
	{// Wを押されたら

		m_move.x += sinf(pCamera->GetRot().y) * PLAYER_SPEED;
		m_move.z += cosf(pCamera->GetRot().y) * PLAYER_SPEED;
		m_DestRot.y = pCamera->GetRot().y + D3DX_PI;
	}
	if (pKeyboard->GetPress(DIK_A) == true)
	{// Aが押されたら
		m_move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_DestRot.y = pCamera->GetRot().y + D3DX_PI * 0.5f;
	}
	if (pKeyboard->GetPress(DIK_S) == true)
	{// Sが押されているとき
		m_move.x -= sinf(pCamera->GetRot().y) * PLAYER_SPEED;
		m_move.z -= cosf(pCamera->GetRot().y) * PLAYER_SPEED;
		m_DestRot.y = pCamera->GetRot().y;
	}
	if (pKeyboard->GetPress(DIK_D) == true)
	{// Dが押されたら
		m_move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_DestRot.y = pCamera->GetRot().y - D3DX_PI * 0.5f;
	}

#if _DEBUG

	if (pKeyboard->GetTrigger(DIK_R) == true)
	{// ENTERを押されたら

		// 位置の設定
		CPlayer::SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{// SPACEが押されたら
		//CEffect3D::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 120, 1.0f);
		CParticle3D::Create(m_pos, D3DXVECTOR3(D3DX_PI * 2.0f, D3DX_PI * 2.0f, D3DX_PI * 2.0f), 20.0f, 1.0f, 600, 120, 20);
	}
#endif

	// 位置を更新
	m_pos += m_move;

	// 高さの取得
	m_move.y = pObject3D->GetHeight();

	//移動量を更新（減衰）
	m_move.x += (0.0f - m_move.x) * 0.09f;
	m_move.y += (0.0f - m_move.y) * 0.09f;
	m_move.z += (0.0f - m_move.z) * 0.09f;//あんまりいらないから数字でかめにしてる

	//if (m_posOld.x-m_pos.x!=0.0f|| m_posOld.z - m_pos.z != 0.0f)
	//{
	//	CManager::GetRenderer()->SetFeedbackEffect(true);
	//}
	//else
	//{
	//	CManager::GetRenderer()->SetFeedbackEffect(false);
	//}

	// 角度の近道
	if ((m_DestRot.y - m_rot.y) >= D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if ((m_DestRot.y - m_rot.y) <= -D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// 徐々に目標へ
	m_rot += (m_DestRot - m_rot) * 0.1f;
}