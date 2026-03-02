//====================================================
//
// ライト[light.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

// インクルード
#include"main.h"

// ライトのクラス
class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	// constexpr
	static constexpr int NUM_LIGHT = 3;// ライトの数

	D3DLIGHT9 m_light[NUM_LIGHT];//ライト情報
};

#endif // !_LIGHT_H_
