//====================================================
//
// タイトルシーン　[title.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _TITLE_H_
#define _TITLE_H_

// インクルード
#include "scene.h"

// 前方宣言
class CObject2D;

// タイトルシーンクラス
class CTitle :public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObject2D* m_pObject2D;
};

#endif