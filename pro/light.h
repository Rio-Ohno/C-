//====================================================
//
//ライト[light.h]
//Author:Rio Ohno
//
//====================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

// インクルード
#include"main.h"

//マクロ定義
#define MAX_LIGHT (3)			// ライトの数

//プロトタイプ宣言
void InitLight();
void UninitLight();
void UpdateLight();

class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DLIGHT9 m_light[MAX_LIGHT];//ライト情報
};

#endif // !_LIGHT_H_
