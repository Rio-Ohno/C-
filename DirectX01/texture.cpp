//====================================================
// 
// テクスチャ [texture.h]
// Author:Rio Ohno
// 
//====================================================

// インクルード
#include"texture.h"
#include"manager.h"

// 静的メンバ変数
int CTexture::m_nNumAll = 0;
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[MAX_TEX] = { NULL };

//====================================================
// コンストラクタ
//====================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
	}
}

//====================================================
// デストラクタ
//====================================================
CTexture::~CTexture()
{
	// なし
}

//====================================================
// テクスチャの読込
//====================================================
HRESULT CTexture::Load(void)// 最初に割当てindex決め打ちするためのもの
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < CTexture::TYPE_MAX; nCnt++)
	{
		//テクスチャの読込
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			TexturePass[nCnt],
			&m_apTexture[nCnt])))
		{
			return -1;
		}

		// 総数カウントアップ
		m_nNumAll++;
	}
	int i = 0;
	return S_OK;
}

//====================================================
// テクスチャの破棄
//====================================================
void CTexture::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// テクスチャポインタの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//====================================================
// 指定のテクスチャ読込(登録)
//====================================================
int CTexture::Register(const char* pFilename)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_nNumAll < MAX_TEX)
	{
		if (pFilename != NULL)
		{
			for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
			{
				if (m_apTexture[nCnt] == NULL)
				{
					if(FAILED(D3DXCreateTextureFromFile(pDevice,
						pFilename,
						&m_apTexture[nCnt])))
					{
						return -1;
					}

					// 総数カウントアップ
					m_nNumAll++;

					// インデックスを返す
					return nCnt;
				}
			}
		}
		else
		{
			return -1;
		}

	}
	return -1;
}

//====================================================
// テクスチャポインタの取得
//====================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIndx)
{
	// インデックスが0より小さいなら
	if (nIndx < 0)
	{
		return NULL;
	}
	else
	{
		return m_apTexture[nIndx];
	}
}