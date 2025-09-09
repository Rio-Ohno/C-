//====================================================
// 
// テクスチャ [texture.h]
// Author:Rio Ohno
// 
//====================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

// インクルード
#include"main.h"

// マクロ定義
#define MAX_TEX (32)

class CTexture
{
public:
	CTexture();
	~CTexture();

	// テクスチャの種類
	typedef  enum
	{
		TYPE_EFFECT = 0,
		TYPE_SHADOW,
		TYPE_SCORENUMBER,
		TYPE_TIMENUMBER,
		TYPE_FILED,
		TYPE_SKY,
		TYPE_SKY_RANKING,
		TYPE_PAUSE,
		TYPE_CONTEINUE,
		TYPE_RETRY,
		TYPE_QUIT,
		TYPE_MAX
	}TYPE;

	// テクスチャパス
	const char* TexturePass[TYPE_MAX] =
	{
		"data\\TEXTURE\\effect000.jpg",
		"data\\TEXTURE\\shadow000.jpg",
		"data\\TEXTURE\\number001.png",
		"data\\TEXTURE\\number003.png",
		"data\\TEXTURE\\non.png",
		"data\\TEXTURE\\BG001.jpg",
		"data\\TEXTURE\\BG000.jpg",
		"data\\TEXTURE\\pause001.png",							//pause背景
		"data\\TEXTURE\\Continue001.png",						//Continue
		"data\\TEXTURE\\Retry001.png",							//Retry
		"data\\TEXTURE\\Quit001.png",							//Quit
	};

	LPDIRECT3DTEXTURE9 GetAddress(int nindx);
	HRESULT Load(void);
	void UnLoad(void);
	int Register(const char* pFilename);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEX];
	static int m_nNumAll;
};

#endif