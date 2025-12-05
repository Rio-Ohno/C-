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
	m_posV = D3DXVECTOR3(0.0f, 175.0f,-300.0f);		// 視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 注視点
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
	float fRotX = atan2f(-fDisZ, -fDisY);

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
	// なし
}

//====================================================
//カメラの更新処理
//====================================================
void CCamera::Update(void)
{
	// デバック表示
	CDebugProc::Print("Camera PosR：{%f, %f, %f}\n", m_posR.x, m_posR.y, m_posR.z);
	CDebugProc::Print("Camera PosV：{%f, %f, %f}\n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("Camera rot：{%f, %f, %f}\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("Camera Distance：%f\n", m_fDistance);

	//キーボードの取得
	CKeyboard* pKeyboard = CManager::GetKeyboard();

#ifdef _DEBUG 
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
#endif

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

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
		}
		else if (pKeyboard->GetPress(DIK_RIGHT) == true)
		{
			m_rot.y += 0.01f;

			//目標の移動方向（角度）の補正
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
		}

		//カメラの移動============================================================================
		if (pKeyboard->GetPress(DIK_I) == true)
		{
			m_posV.x += (float)(sinf(m_rot.x) * sinf(m_rot.y) * 1.0f);
			m_posV.z += (float)(sinf(m_rot.x) * cosf(m_rot.y) * 1.0f);

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
		}
		else if (pKeyboard->GetPress(DIK_K) == true)
		{
			m_posV.x -= (float)(sinf(m_rot.x) * sinf(m_rot.y) * 1.0f);
			m_posV.z -= (float)(sinf(m_rot.x) * cosf(m_rot.y) * 1.0f);

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

		}
		else if (pKeyboard->GetPress(DIK_J) == true)
		{

			m_posV.x -= (float)(sinf(m_rot.x) * sinf(m_rot.y + D3DX_PI / 2.0f) * 1.0f);
			m_posV.z -= (float)(sinf(m_rot.x) * cosf(m_rot.y + D3DX_PI / 2.0f) * 1.0f);

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

		}
		else if (pKeyboard->GetPress(DIK_L) == true)
		{

			m_posV.x += (float)(sinf(m_rot.x) * sinf(m_rot.y + D3DX_PI / 2.0f) * 1.0f);
			m_posV.z += (float)(sinf(m_rot.x) * cosf(m_rot.y + D3DX_PI / 2.0f) * 1.0f);

			m_posR.x = m_posV.x + (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
			m_posR.z = m_posV.z + (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

		}
	}
#endif // DEBUG
	//追従====================================================================================
	
	if (m_type == TYPE_ASSENT)
	{
		Follow();
	}

	//視点の旋回（Y軸）============================================================================
	if (pKeyboard->GetPress(DIK_Q) == true)
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
	else if (pKeyboard->GetPress(DIK_E) == true)
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

#ifdef _DEBUG
	//視点の旋回（X軸）============================================================================
	if (pKeyboard->GetPress(DIK_Y) == true)
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

	//視点のY軸移動============================================================================
	if (pKeyboard->GetPress(DIK_T) == true)
	{
		m_posV.y += 0.5f;

		//視点から注視点の距離計算
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//対角線の長さを算出する
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// 角度を求める
		float fRotX = atan2f(-fDisZ, -fDisY);

		// 角度の設定
		m_rot.x = (float)fRotX + D3DX_PI;
	}
	else if (pKeyboard->GetPress(DIK_G) == true)
	{
		m_posV.y -= 0.5f;

		//視点から注視点の距離計算
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//対角線の長さを算出する
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// 角度を求める
		float fRotX = atan2f(-fDisZ, -fDisY);

		// 角度の設定
		m_rot.x = (float)fRotX + D3DX_PI;
	}

	//視点のZ軸移動============================================================================
	if (pKeyboard->GetPress(DIK_0) == true)
	{
		m_posV.z += 0.5f;

		//視点から注視点の距離計算
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//対角線の長さを算出する
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// 角度を求める
		float fRotX = atan2f(-fDisZ, -fDisY);

		// 角度の設定
		m_rot.x = (float)fRotX + D3DX_PI;
	}
	else if(pKeyboard->GetPress(DIK_P) == true)
	{
		m_posV.z -= 0.5f;

		//視点から注視点の距離計算
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//対角線の長さを算出する
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// 角度を求める
		float fRotX = atan2f(-fDisZ, -fDisY);

		// 角度の設定
		m_rot.x = (float)fRotX + D3DX_PI;
	}

	//注視点のY軸移動============================================================================
	if (pKeyboard->GetPress(DIK_7) == true)
	{
		m_posR.y += 0.5f;

		//視点から注視点の距離計算
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//対角線の長さを算出する
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// 角度を求める
		float fRotX = atan2f(-fDisZ, -fDisY);

		// 角度の設定
		m_rot.x = (float)fRotX + D3DX_PI;
	}
	else if (pKeyboard->GetPress(DIK_U) == true)
	{
		m_posR.y -= 0.5f;

		//視点から注視点の距離計算
		float fDisX = m_posR.x - m_posV.x;
		float fDisY = m_posR.y - m_posV.y;
		float fDisZ = m_posR.z - m_posV.z;

		//対角線の長さを算出する
		m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

		// 角度を求める
		float fRotX = atan2f(-fDisZ, -fDisY);

		// 角度の設定
		m_rot.x = (float)fRotX + D3DX_PI;
	}
#endif
}

//====================================================
// 追従処理
//====================================================
void CCamera::Follow(void)
{
	//目的の値
	m_posRDest.x = m_posTarget.x + sinf(m_rotTarget.y);
	m_posRDest.y = m_posTarget.y * 0.5f;
	m_posRDest.z = m_posTarget.z + cosf(m_rotTarget.y);

	m_posVDest.x = m_posTarget.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
	m_posVDest.y = m_posTarget.y * 0.5f - (float)(cosf(m_rot.x) * m_fDistance);
	m_posVDest.z = m_posTarget.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

	//
	m_posR.x += (m_posRDest.x - m_posR.x) * 0.09f;
	m_posR.y += (m_posRDest.y - m_posR.y) * 0.09f;
	m_posR.z += (m_posRDest.z - m_posR.z) * 0.09f;

	m_posV.x += (m_posVDest.x - m_posV.x) * 0.09f;
	m_posV.y += (m_posVDest.y - m_posV.y) * 0.09f;
	m_posV.z += (m_posVDest.z - m_posV.z) * 0.09f;
}

//====================================================
// 追従処理
//====================================================
void CCamera::Follow(const D3DXVECTOR3 TargetPos, const D3DXVECTOR3 TargetRot)
{
	//目的の値
	m_posRDest.x = TargetPos.x + sinf(TargetRot.y);
	m_posRDest.y = TargetPos.y * 0.5f;
	m_posRDest.z = TargetPos.z + cosf(TargetRot.y);

	m_posVDest.x = TargetPos.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
	m_posVDest.y = TargetPos.y * 0.5f - (float)(cosf(m_rot.x) * m_fDistance);
	m_posVDest.z = TargetPos.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);

	//
	m_posR.x += (m_posRDest.x - m_posR.x) * 0.09f;
	m_posR.y += (m_posRDest.y - m_posR.y) * 0.09f;
	m_posR.z += (m_posRDest.z - m_posR.z) * 0.09f;

	m_posV.x += (m_posVDest.x - m_posV.x) * 0.09f;
	m_posV.y += (m_posVDest.y - m_posV.y) * 0.09f;
	m_posV.z += (m_posVDest.z - m_posV.z) * 0.09f;
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
// カメラの種類設定
//====================================================
void CCamera::SetType(TYPE type)
{
	m_type = type;

	if (type == TYPE_ASSENT)
	{
		m_bAssent = true;
	}
	else
	{
		m_bAssent = false;
	}
}

//====================================================
// カメラのPos設定
//====================================================
void CCamera::SetCameraPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	//視点から注視点の距離計算
	float fDisX = posR.x - posV.x;
	float fDisY = posR.y - posV.y;
	float fDisZ = posR.z - posV.z;

	//対角線の長さを算出する
	m_fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);

	// 角度を求める
	float fRotX = atan2f(-fDisZ, -fDisY);

	// 角度の設定
	m_rot.x = (float)fRotX + D3DX_PI;

	m_posR = posR;

	m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
	m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
	m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
}

//====================================================
// カメラのRot設定
//====================================================
void CCamera::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;

	//目標の移動方向（角度）の補正
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - (float)(sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance);
	m_posV.y = m_posR.y - (float)(cosf(m_rot.x) * m_fDistance);
	m_posV.z = m_posR.z - (float)(sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance);
}