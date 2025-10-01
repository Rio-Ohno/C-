//====================================================
// 
// テストシーン[test.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _TEST_H_
#define _TEST_H_

// インクルード
#include "main.h"
#include"scene.h"

// テストシーンクラス
class CTest :public CScene
{
public:

	CTest();
	~CTest();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};
#endif