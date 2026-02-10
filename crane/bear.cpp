//==============================================
// 
// 熊 [bear.cpp]
// Author:Rio Ohno
// 
//==============================================

// インクルード
#include "bear.h"
#include "stateEnemy.h"
#include "stateBear.h"
#include "motion.h"
#include "manager.h"
#include "collider.h"
#include "effect3D.h"

//==============================================
// コンストラクタ
//==============================================
CBear::CBear()
{
	// 各変数の初期化処理
	m_pMotion = nullptr;	// モーションへのポインタ
	m_collider = nullptr;	// コライダーへのポインタ
	m_nCntFream = 0;		// フレームカウンタ

	// 種類の設定
	SetEnemyActionType(CEnemyBase::ACTION_MOVE);
	SetPrize(CEnemyBase::PRIZE_BEAR);
}

//==============================================
// デストラクタ
//==============================================
CBear::~CBear()
{
	// 基盤クラスの終了処理
	CEnemyBase::Uninit();

	// モーションの破棄
	if (m_pMotion != nullptr)
	{
		m_pMotion->UninitModel();

		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// コライダーの破棄
	if (m_collider != nullptr)
	{
		// 終了処理
		m_collider->Uninit();

		CEnemyBase::SetCollider(nullptr);
		m_collider = nullptr;
	}
}

//==============================================
// 生成処理
//==============================================
CBear* CBear::Create(D3DXVECTOR3 pos, std::shared_ptr<CMotionInfo> pMotion)
{
	CBear* pBear = nullptr;
	pBear = new CBear;

	// 各変数の設定
	pBear->SetPos(pos);									// 位置
	pBear->m_pMotion = new CMotion;						// モーションポインタの生成
	pBear->m_pMotion->Init(
		pMotion->GetInfo(),
		pMotion->GetModel(),
		pMotion->GetNumModel(),
		pMotion->GetOffsetPos(),
		pMotion->GetOffsetRot());						// モーション情報の取得
	pBear->m_pMotion->Set(MOTION_NEUTRAL);				// モーション種類の設定
	pBear->CEnemyBase::SetGravity(0.9f);				// 重力の設定

	// 初期化処理
	pBear->Init();

	return pBear;
}

//==============================================
// 初期化処理
//==============================================
HRESULT CBear::Init(void)
{
	// 基盤クラスの初期化処理
	CEnemyBase::Init();

	// 当たり判定のポインタ生成
	m_collider = new CColliderSphere;
	m_collider->Init();
	m_collider->SetParameter(CEnemyBase::GetPos(), 30.0f);

	// 基盤クラスへ割当
	CEnemyBase::SetCollider(m_collider);

	// 状態の設定
	CEnemyBase::ChangeState(std::make_shared<CEnemyStateSpawn>());

	return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CBear::Uninit(void)
{
	// オブジェクトの破棄
	CObject::Release();
}

//==============================================
// 更新処理
//==============================================
void CBear::Update(void)
{
	// 基盤クラスの更新処理
	CEnemyBase::Update();

	if (CEnemyBase::GetNowStateID() == CStateEnemyBase::STATE_NONE)// 何もしていない状態なら
	{
		// ニュートラル状態へ
		CEnemyBase::ChangeState(std::make_shared<CBearStateNeutral>());
	}

	// モーションの更新処理
	m_pMotion->Update();

	// コライダーの位置更新処理
	UpdateColliderPos();

	// モーションの設定処理
	SetMotion();

	CManager::GetDebug()->Print("Bear fream:%d\n", m_pMotion->GetFream());
}

//==============================================
// 描画処理
//==============================================
void CBear::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, CEnemyBase::GetRot().y, CEnemyBase::GetRot().x, CEnemyBase::GetRot().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, CEnemyBase::GetPos().x, CEnemyBase::GetPos().y, CEnemyBase::GetPos().z);
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

//==============================================
// 歩く処理
//==============================================
void CBear::Walk(float rotY)
{
	// 現在の移動量取得
	D3DXVECTOR3 move = CEnemyBase::GetMove();

	move.x += sinf(rotY) * WALK_SPEED;
	move.z += cosf(rotY) * WALK_SPEED;

	// 移動量の設定
	CEnemyBase::SetMove(move);
}

//==============================================
// 読込処理
//==============================================
CMotion* CBear::Load(void)
{
	// メモリの確保
	CMotion* pMotion = nullptr;
	pMotion = new CMotion;

	// 読込
	CLoadMotion::Load(MOTIONFILE_NAME, pMotion);

	if (pMotion == nullptr)
	{
		delete pMotion;
		return nullptr;
	}
	return pMotion;
}

//==============================================
// コライダーの位置更新処理
//==============================================
void CBear::UpdateColliderPos(void)
{
	D3DXVECTOR3 Body = m_pMotion->GetModelPos(BODY_INDEX) + CEnemyBase::GetPos();
	D3DXVECTOR3 Head = m_pMotion->GetModelPos(HEAD_INDEX) + CEnemyBase::GetPos();

	// 中心の割り出し
	D3DXVECTOR3 Center = (Body + Head) * 0.5f;

	// コライダーの位置更新
	m_collider->SetPos(Center);

//#ifdef _DEBUG
//
//	CEffect3D::Create(D3DXVECTOR3(Center.x + m_collider->GetRadius(), Center.y, Center.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5.0f, 10, 0.7f);
//	CEffect3D::Create(D3DXVECTOR3(Center.x - m_collider->GetRadius(), Center.y, Center.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5.0f, 10, 0.7f);
//	CEffect3D::Create(D3DXVECTOR3(Center.x, Center.y + m_collider->GetRadius(), Center.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5.0f, 10, 0.7f);
//	CEffect3D::Create(D3DXVECTOR3(Center.x, Center.y - m_collider->GetRadius(), Center.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5.0f, 10, 0.7f);
//	CEffect3D::Create(D3DXVECTOR3(Center.x, Center.y, Center.z + m_collider->GetRadius()), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5.0f, 10, 0.7f);
//	CEffect3D::Create(D3DXVECTOR3(Center.x, Center.y, Center.z - m_collider->GetRadius()), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5.0f, 10, 0.7f);
//
//#endif
}

//==============================================
// モーションの設定
//==============================================
void CBear::SetMotion(void)
{
	int stateID = CEnemyBase::GetNowStateID();	// 現在のステートIDを取得

	switch (stateID)
	{
	case CStateEnemyBase::STATE_CAUGHT:// 捕まった状態
		m_pMotion->Set(MOTION_FLUTTER);
		break;

	case CStateEnemyBase::STATE_NEUTRAL:// ニュートラル
		m_pMotion->Set(MOTION_NEUTRAL);
		break;

	case CStateEnemyBase::STATE_WALK:// 歩く
		m_pMotion->Set(MOTION_RUN);
		break;

	case CStateEnemyBase::STATE_RUN:// 逃げる
		m_pMotion->Set(MOTION_RUN);
		break;

	case CStateEnemyBase::STATE_FLUTTER:// じたばた
		m_pMotion->Set(MOTION_FLUTTER);
		break;

	default:
		m_pMotion->Set(MOTION_NEUTRAL);
		break;
	}
}