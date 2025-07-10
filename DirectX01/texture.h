//====================================================
// 
// �e�N�X�`�� [texture.h]
// Author:Rio Ohno
// 
//====================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

// �C���N���[�h
#include"main.h"

// �}�N����`
#define MAX_TEX (32)

class CTexture
{
public:
	CTexture();
	~CTexture();

	// �e�N�X�`���̎��
	typedef  enum
	{
		TYPE_EFFECT = 0,
		TYPE_SHADOW,
		TYPE_SCORENUMBER,
		TYPE_FILED,
		TYPE_MAX
	}TYPE;

	// �e�N�X�`���p�X
	const char* TexturePass[TYPE_MAX] =
	{
		"data\\TEXTURE\\effect000.jpg",
		"data\\TEXTURE\\shadow000.jpg",
		"data\\TEXTURE\\number001.png",
		"data\\TEXTURE\\field000.jpg"
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