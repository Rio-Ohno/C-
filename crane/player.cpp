//====================================================
//
// プレイヤー　[player.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "player.h"
#include "manager.h"
#include "input.h"
#include "meshcylinder.h"
#include "statePlayer.h"

// 静的メンバ変数
CMotion* CPlayer::m_pMotion = nullptr;				// モーションへのポインタ
CLoadMotion* CPlayer::m_pLoadMotion = nullptr;		// モーション読込クラスへのポインタ
CMeshCylinder* CPlayer::m_pCylinder = nullptr;		// シリンダーへのポインタ

//====================================================
// コンストラクタ
//====================================================
CPlayer::CPlayer()
{
	// 各メンバ変数の初期化処理
	m_pMotion = nullptr;			// モーションへのポインタ
	m_pLoadMotion = nullptr;		// モーション読込クラスへのポインタ
	m_pCylinder = nullptr;			// シリンダーへのポインタ

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_posBase = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 最初の位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 前フレームの位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
}

//====================================================
// デストラクタ
//====================================================
CPlayer::~CPlayer()
{
	// なし
}

//====================================================
// 生成処理
//====================================================
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	// ポインタの作成
	CPlayer* pPlayer = nullptr;

	// メモリの確保
	pPlayer = new CPlayer;

	// 各メンバ変数の設定
	pPlayer->m_pos = pos;			// 位置
	pPlayer->m_rot = rot;			// 向き
	pPlayer->m_posBase = pos;		// 最初の位置保存

	// 初期化処理
	pPlayer->Init();

	return pPlayer;
}

//====================================================
// 初期化処理
//====================================================
HRESULT CPlayer::Init(void)
{
	// 状態管理クラス
	if (m_statePlayer == nullptr)
	{
		m_statePlayer = std::make_unique< CStateMachine>();
		ChangeState(std::make_shared<CStatePlayerNone>());
	}

	// モーションの設定
	CPlayer::SetMotion(MOTION_FILE_NAME);

	// モーションの初期化
	m_pMotion->Init(m_pMotion);
	m_pMotion->Set(MOTION_NEUTRAL);

	// シリンダーの生成
	m_pCylinder = CMeshCylinder::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 65.0f, m_pos.z), D3DXVECTOR3(m_rot.x, m_rot.y - D3DX_PI * 0.55f, m_rot.z), 16, 1, 100.0f, 35.0f);
	m_pCylinder->SetCulling(false);								// カリングを切る
	m_pCylinder->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f));	// 色の設定

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CPlayer::Uninit(void)
{
	// モーションの破棄
	if (m_pMotion != nullptr)
	{
		// 終了処理
		m_pMotion->Uninit();

		// メモリの破棄
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// シリンダーの破棄
	if (m_pCylinder != nullptr)
	{
		// 終了処理
		m_pCylinder->Uninit();

		// メモリの破棄
		m_pCylinder = nullptr;
	}

	// 自身の破棄フラグを建てる
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CPlayer::Update(void)
{
	// デバック表示
	CDebugProc::Print("Player pos：x: %f y: %f z: %f\n", m_pos.x, m_pos.y, m_pos.z);

	// 状態管理の更新処理
	m_statePlayer->Update();

	// モーションの更新処理
	m_pMotion->Update();

	if (m_pCylinder != nullptr)
	{
		// シリンダーの位置更新
		m_pCylinder->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y - 65.0f, m_pos.z));
	}
}

//====================================================
// 描画処理
//====================================================
void CPlayer::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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

	int NumModel = m_pMotion->GetNumModel();

	for (int nCnt = 0; nCnt < NumModel; nCnt++)
	{
		// modelの描画処理
		m_pMotion->GetModel()[nCnt]->Draw();
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================
// プレイヤーステート変更処理
//====================================================
void CPlayer::ChangeState(std::shared_ptr<CStatePlayerBase> stateBasePlayer)
{
	// 自身のポインタを設定
	stateBasePlayer->SetPlayer(this);

	// 状態を変更
	m_statePlayer->Change(stateBasePlayer);
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
// 何もない状態の時
//====================================================
void CPlayer::None(void)
{
	// 入力ポインタの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();
	CJoypad* pJoypad /*= CManager::GetJoypad()*/;

	if (pKeyboard->GetTrigger(DIK_W) ||
		pKeyboard->GetTrigger(DIK_A) ||
		pKeyboard->GetTrigger(DIK_S) ||
		pKeyboard->GetTrigger(DIK_D))// 移動キーを押されたら
	{
		// 移動状態にする
		ChangeState(std::make_shared<CStatePlayerMove>());
	}
	else if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		// 下げる状態にする
		ChangeState(std::make_shared<CStatePlayerDown>());
	}
}

//====================================================
// 移動関連
//====================================================
void CPlayer::Move(void)
{
	// 前フレームの位置を保存
	m_posOld = m_pos;

	// 入力ポインタの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();
	CJoypad* pJoypad /*= CManager::GetJoypad()*/;

	// カメラの取得
	CCamera* pCamera = CManager::GetCamera();

	if (pKeyboard->GetPress(DIK_W) == true)
	{// Wを押されたら
	
		if (pKeyboard->GetPress(DIK_A) == true)
		{// Aも押されてるなら
			m_move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SPEED;
			m_move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SPEED;
		}
		else if (pKeyboard->GetPress(DIK_D) == true)
		{// Dも押されてるなら
			m_move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SPEED;
			m_move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SPEED;
		}
		else if (pKeyboard->GetPress(DIK_W) == true)
		{// Wのみなら
			m_move.x += sinf(pCamera->GetRot().y) * SPEED;
			m_move.z += cosf(pCamera->GetRot().y) * SPEED;
		}
	}
	else if (pKeyboard->GetPress(DIK_A) == true)
	{// Aが押されたら
	
		m_move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.5f) * SPEED;
		m_move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.5f) * SPEED;
	}
	else if (pKeyboard->GetPress(DIK_S) == true)
	{// Sが押されているとき
	
		if (pKeyboard->GetPress(DIK_A) == true)
		{// Aも押されてるなら
			m_move.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SPEED;
			m_move.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * SPEED;
		}
		else if (pKeyboard->GetPress(DIK_D) == true)
		{// Dも押されてるなら
			m_move.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SPEED;
			m_move.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * SPEED;
		}
		else if (pKeyboard->GetPress(DIK_S) == true)
		{// Sのみなら
			m_move.x -= sinf(pCamera->GetRot().y) * SPEED;
			m_move.z -= cosf(pCamera->GetRot().y) * SPEED;
		}
	}
	else if (pKeyboard->GetPress(DIK_D) == true)
	{// Dが押されたら
	
		m_move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED ;
		m_move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED ;
	}

	// 位置を更新
	m_pos += m_move;

	//移動量を更新（減衰）
	m_move.x += (0.0f - m_move.x) * 0.095f;
	m_move.z += (0.0f - m_move.z) * 0.095f;//あんまりいらないから数字でかめにしてる

	if (m_move.x <= MOVE_LIMIT && m_move.x >= -MOVE_LIMIT &&
		m_move.z <= MOVE_LIMIT && m_move.z >= -MOVE_LIMIT)// 移動量が限界範囲内なら
	{
		// 何もしない状態へ
		ChangeState(std::make_shared<CStatePlayerNone>());
	}
	else if (pKeyboard->GetTrigger(DIK_RETURN))// Enterキー入力で
	{
		// アームを下げる状態へ
		ChangeState(std::make_shared<CStatePlayerDown>());
	}
}