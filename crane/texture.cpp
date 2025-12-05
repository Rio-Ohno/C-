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
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apTexture = {};

//====================================================
// コンストラクタ
//====================================================
CTexture::CTexture()
{
	// なし
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
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	for (int nCnt = 0; nCnt < CTexture::TYPE_MAX; nCnt++)
	{
		//テクスチャの読込
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			PassList.at(nCnt),
			&pTexture)))
		{
			return -1;
		}

		// テクスチャリストに追加
		m_apTexture.push_back(pTexture);

		// 総数カウントアップ
		m_nNumAll++;
	}
	return S_OK;
}

//====================================================
// テクスチャの破棄
//====================================================
void CTexture::UnLoad(void)
{
	int nCntTex = 0;
	for (auto& iterObj : m_apTexture)
	{
		// テクスチャポインタの破棄
		if (m_apTexture.at(nCntTex) != nullptr)
		{
			m_apTexture.at(nCntTex)->Release();
			m_apTexture.at(nCntTex) = nullptr;

			++nCntTex;
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
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		if (strcmp(PassList.at(nCnt), pFilename) == 0)
		{
			return nCnt;
		}
	}

	if (pFilename != nullptr)
	{
		for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
		{
			if (m_apTexture.at(nCnt) == nullptr)
			{
				if(FAILED(D3DXCreateTextureFromFile(pDevice,
					pFilename,
					&pTexture)))
				{
					return -1;
				}

				// テクスチャリストに追加
				m_apTexture.push_back(pTexture);

				// パスリストに追加
				PassList.push_back(pFilename);

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
		return m_apTexture.at(nIndx);
	}
}