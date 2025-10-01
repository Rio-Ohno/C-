//====================================================
//
//ライト[light.cpp]
//Author:Rio Ohno
//
//====================================================

// インクルード
#include"light.h"
#include"manager.h"

//====================================================
// コンストラクタ
//====================================================
CLight::CLight()
{
	// なし
}

//====================================================
// デストラクタ
//====================================================
CLight::~CLight()
{
	// なし
}

//====================================================
// ライトの初期化処理
//====================================================
HRESULT CLight::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];//ライトの方向ベクトル
	D3DXCOLOR vecDif[MAX_LIGHT];//ライトの方向ベクトル

	//ライトをクリア
	ZeroMemory(&m_light, sizeof(m_light));

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトの種類を設定
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;//平行光源
	}

	//ライトの拡散光を設定
	//vecDif[0] = D3DXCOLOR(1.0f, 1.0f, 0.8f, 1.0f);
	//vecDif[1] = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	//vecDif[2] = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	//ライトの方向を設定
	vecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	vecDir[1] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	vecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトの拡散光を設定
		m_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//正視化する
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		m_light[nCnt].Direction = vecDir[nCnt];

		//ライトを設定する
		pDevice->SetLight(nCnt, &m_light[nCnt]);

	}

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	return S_OK;
}

//====================================================
// ライトの終了処理
//====================================================
void CLight::Uninit(void)
{

}

//====================================================
// ライトの更新処理
//====================================================
void CLight::Update(void)
{

}
