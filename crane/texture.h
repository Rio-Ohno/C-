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
#include <vector>

// テクスチャクラス
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
		TYPE_POP,
		TYPE_TITLE,
		TYPE_PRESS,
		TYPE_SCORENUMBER,
		TYPE_TIMENUMBER,
		TYPE_COLON,
		TYPE_FILED,
		TYPE_SKY,
		TYPE_PAUSE,
		TYPE_CONTEINUE,
		TYPE_RETRY,
		TYPE_QUIT,
		TYPE_RESULT,
		TYPE_MAX
	}TYPE;

	// テクスチャパス
	std::vector<const char*> PassList =
	{
		"data\\TEXTURE\\effect000.jpg",
		"data\\TEXTURE\\shadow000.jpg",
		"data\\TEXTURE\\pop.png",
		"data\\TEXTURE\\TryCatch002.png",
		"data\\TEXTURE\\Press001.png",					// 仮
		"data\\TEXTURE\\number001.png",
		"data\\TEXTURE\\number003.png",
		"data\\TEXTURE\\colon.png",
		"data\\TEXTURE\\non.png",
		"data\\TEXTURE\\sky000.jpg",					// 空
		"data\\TEXTURE\\pause001.png",					// pause背景
		"data\\TEXTURE\\Continue001.png",				// Continue
		"data\\TEXTURE\\Retry001.png",					// Retry
		"data\\TEXTURE\\Quit001.png",					// Quit
		"data\\TEXTURE\\result004.png",
	};

	LPDIRECT3DTEXTURE9 GetAddress(int nindx);
	HRESULT Load(void);
	void UnLoad(void);
	int Register(const char* pFilename);

private:
	static std::vector<LPDIRECT3DTEXTURE9> m_apTexture;
	static int m_nNumAll;
};

#endif