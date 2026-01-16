//====================================================
//
// 箱(プライズ)　[box.cpp]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "box.h"
#include "objectX.h"
#include "collider.h"
#include "manager.h"
#include "stateEnemy.h"
#include "shadowS.h"

//====================================================
// コンストラクタ
//====================================================
CPrizeBox::CPrizeBox()
{
	// 各メンバ変数の初期化
	m_model = nullptr;		// モデル
	m_collider = nullptr;	// コライダー

	// 種類の設定
	SetEnemyActionType(CEnemyBase::ACTION_NONE);
	SetPrize(CEnemyBase::PRIZE_BOX);
}

//====================================================
// デストラクタ
//====================================================
CPrizeBox::~CPrizeBox()
{
	// 基盤クラスの終了処理
	CEnemyBase::Uninit();

	if (m_model != nullptr)
	{
		// 終了処理
		m_model->Uninit();

		m_model = nullptr;
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

//====================================================
// 生成処理
//====================================================
CPrizeBox* CPrizeBox::Create(D3DXVECTOR3 pos)
{
	CPrizeBox* pBox = nullptr;

	// メモリの確保
	pBox = new CPrizeBox;

	// メンバ変数
	pBox->m_model = CObjectX::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// モデルの生成
	pBox->m_model->BindModel(FILE_NAME);									// モデルの割当
	pBox->CEnemyBase::SetPos(pos);											// 位置の設定
	pBox->CEnemyBase::SetGravity(0.9f);										// 重力の設定

	// 初期化処理
	pBox->Init();

	if (pBox != nullptr &&
		pBox->m_model != nullptr)
	{
		return pBox;
	}
	else
	{
		return nullptr;
	}
}

//====================================================
// 初期化処理
//====================================================
HRESULT CPrizeBox::Init(void)
{
	// 基盤クラスの初期化処理
	CEnemyBase::Init();

	// コライダーの生成
	m_collider = new CColliderSphere;
	m_collider->Init();
	m_collider->SetParameter(m_model->GetPos(), 38.0f);

	// 基盤クラスへ割当
	CEnemyBase::SetCollider(m_collider);

	// 影のサイズ設定
	CEnemyBase::GetShadow()->SetScale(D3DXVECTOR3(2.0f, 1.1f, 2.0f));

	// 状態クラス
	CEnemyBase::ChangeState(std::make_shared<CEnemyStateNone>());

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CPrizeBox::Uninit(void)
{
	// 自身の破棄
	CObject::Release();
}

//====================================================
// 更新処理
//====================================================
void CPrizeBox::Update(void)
{
	// 基盤クラスの更新処理
	CEnemyBase::Update();

	// コライダーの位置更新
	m_collider->SetParameter(CEnemyBase::GetPos());

	// モデルの位置更新
	m_model->SetPos(CEnemyBase::GetPos());
}

//====================================================
// 描画処理
//====================================================
void CPrizeBox::Draw(void)
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

	// モデルの描画処理
	m_model->Draw();

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}