//====================================================
//
// タイトルシーン処理 [title.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _TITLE_H_
#define _TITLE_H_

// インクルード
#include"main.h"
#include"scene.h"

class CTitle :public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};
#endif // !_TITLE_H_
