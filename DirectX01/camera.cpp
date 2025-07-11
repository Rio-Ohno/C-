//====================================================
//
//カメラ[camera.cpp]
//Author:Rio Ohno
//
//====================================================

// インクルード
#include"camera.h"
#include"manager.h"
#include"input.h"
#include"player.h"

//====================================================
// コンストラクタ
//====================================================
CCamera::CCamera()
{
	// 各値の初期化
	m_posV = D3DXVECTOR3(0.0f, 70.0f, -200.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NOMAL;
	m_fDistance = 0;
	m_bAssent = false;
}

//====================================================
// デストラクタ
//====================================================
CCamera::~CCamera()
{
	// なし
}

//====================================================
// カメラの初期化処理
//====================================================
HRESULT CCamera::Init(void)
{
	//各種初期化
	m_posV = D3DXVECTOR3(0.0f, 200.0f,-300.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bAssent = false;
	m_type = TYPE_NOMAL;

	////ビューポートの設定
	//m_viewport.X = (DWORD)0.0f;
	//m_viewport.Y = (DWORD)0.0f;
	//m_viewport.Width = 1280;
	//m_viewport.Height = 720;

	//視点から注視点の距離計算
	float fDisX = m_posR.x - m_posV.x;
	float fDisY = m_posR.y - m_posV.y;
	float fDisZ = m_posR.z - m_posV.z;

	// 角度を求める
	float fRotX = atan2f(m_posV.z, m_posV.y);;

	//対角線の長さを算出する
	m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

	// 角度の設定
	m_rot.x = (float)fRotX + D3DX_PI;

	return S_OK;
}

//====================================================
// カメラの終了処理
//====================================================
void CCamera::Uninit(void)
{

}

//====================================================
//カメラの更新処理
//====================================================
void CCamera::Update(void)
{
	//キーボードの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	//リセット================================================================================
	if (pKeyboard->GetTrigger(DIK_R) == true)
	{
		// 初期化処理
		CCamera::Init();
	}

	//追従のオンオフ
	if (pKeyboard->GetTrigger(DIK_F) == true)
	{
		m_bAssent = m_bAssent ? false : true;
	}

	if (m_bAssent == false)
	{
		m_type = TYPE_NOMAL;
	}
	else if (m_bAssent == true)
	{
		m_type = TYPE_ASSENT;
	}

#ifdef _DEBUG

	if (m_type == TYPE_NOMAL)
	{
		//注視点の旋回============================================================================
		if (pKeyboard->GetPress(DIK_LEFT) == true)
		{
			m_rot.y -= 0.01f;

			//目標の移動方向（角度）の補正
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
		}
		else if (pKeyboard->GetPress(DIK_RIGHT) == true)
		{
			m_rot.y += 0.01f;

			//目標の移動方向（角度）の補正
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
		}

		//カメラの移動============================================================================
		if (pKeyboard->GetPress(DIK_I) == true)
		{
			m_posV.x += sinf(m_rot.y) * 1.0f;
			m_posV.z += cosf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
		}
		else if (pKeyboard->GetPress(DIK_K) == true)
		{
			m_posV.x -= sinf(m_rot.y) * 1.0f;
			m_posV.z -= cosf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;

		}
		else if (pKeyboard->GetPress(DIK_J) == true)
		{

			m_posV.x -= sinf(m_rot.y + D3DX_PI / 2.0f) * 1.0f;
			m_posV.z -= cosf(m_rot.y + D3DX_PI / 2.0f) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;

		}
		else if (pKeyboard->GetPress(DIK_L) == true)
		{

			m_posV.x += sinf(m_rot.y + D3DX_PI / 2.0f) * 1.0f;
			m_posV.z += cosf(m_rot.y + D3DX_PI / 2.0f) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;

		}
		//else if (GetKeyboardPress(DIK_T) == true)
		//{
		//	m_.posV.y += 0.05f;
		//	m_.posR.y = m_.posV.y;
		//}
		//else if (GetKeyboardPress(DIK_G) == true)
		//{
		//	m_.posV.y -= 0.05f;
		//	m_.posR.y = m_.posV.y;
		//}
	}
#endif // DEBUG
	//追従====================================================================================
	
	if (m_type == TYPE_ASSENT)
	{
		//プレイヤーの情報取得
		CPlayer* pPlayer = CManager::GetPlayer();

		//目的の値
		m_posRDest.x = pPlayer->GetPos().x + sinf(pPlayer->GetRot().y);
		m_posRDest.y = pPlayer->GetPos().y;				   
		m_posRDest.z = pPlayer->GetPos().z + cosf(pPlayer->GetRot().y);
							 
		m_posVDest.x = pPlayer->GetPos().x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
		m_posVDest.y = pPlayer->GetPos().y - (float)(cosf(m_rot.x) * m_fDistance);
		m_posVDest.z = pPlayer->GetPos().z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

		//
		m_posR.x += (m_posRDest.x - m_posR.x) * 0.09f;
		m_posR.y += (m_posRDest.y - m_posR.y) * 0.09f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 0.09f;
												   
		m_posV.x += (m_posVDest.x - m_posV.x) * 0.09f;
		m_posV.y += (m_posVDest.y - m_posV.y) * 0.09f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 0.09f;

	}

	//視点の旋回============================================================================
	if (pKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y -= 0.01f;

		//目標の移動方向（角度）の補正
		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}

		m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
		m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
		m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

	}
	else if (pKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y += 0.01f;

		//目標の移動方向（角度）の補正
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}

		m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
		m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
		m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

	}
	else if (pKeyboard->GetPress(DIK_Y) == true)
	{

		if (m_rot.x + 0.01f <= D3DX_PI)
		{
			m_rot.x += 0.01f;
		}

		m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
		m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
		m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
	}
	else if (pKeyboard->GetPress(DIK_H) == true)
	{
		if (m_rot.x - 0.01f >= 0.0f)
		{
			m_rot.x -= 0.01f;
		}

		m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
		m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
		m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
	}
}

//====================================================
// カメラの設定処理
//====================================================
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(40.0f),
														(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
														10.0f,
														2000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//====================================================
//// カメラの情報取得
//====================================================
//Camera*GetCamera()
//{
//	return &m_;
//}