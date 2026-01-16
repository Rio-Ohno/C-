//==============================================
// 
// 熊 [bear.cpp]
// Author:Rio Ohno
// 
//==============================================

// インクルード
#include "bear.h"
#include "stateEnemy.h"
#include "motion.h"
#include "manager.h"
#include "collider.h"

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
	pBear->m_pMotion->SetModel(pMotion->GetModel());	// モデルの取得
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
	CEnemyBase::ChangeState(std::make_shared<CEnemyStateNone>());

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

	// モーションの更新処理
	m_pMotion->Update();

	// コライダーの位置更新処理
	UpdateColliderPos();

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

// くま専用ステートクラス------------------------------------------------------------------------------------------------------

//==============================================
// 逃げる状態クラスのコンストラクタ
//==============================================
CBearStateRun::CBearStateRun()
{
}

//==============================================
// 逃げる状態クラスのデストラクタ
//==============================================
CBearStateRun::~CBearStateRun()
{
}

//==============================================
// 逃げる状態クラスの初期化処理
//==============================================
void CBearStateRun::Init(void)
{
	// 敵情報取得
	CEnemyBase* pEnemy = GetEnemy();

	// 重力の係数再設定
	pEnemy->SetGravity(GRAVITY);
	pEnemy->SetGravity(true);// 重力をかける
}

//==============================================
// 逃げる状態クラスの更新処理
//==============================================
void CBearStateRun::Update(void)
{
}