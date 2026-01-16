//====================================================
// 
// リザルトシーン[result.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _RESULT_H_
#define _RESULT_H_

// インクルード
#include "scene.h"

// 前方宣言
class CObject2D;

// リザルトクラス
class CResult :public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CObject2D* m_pObject2D;
};

#endif