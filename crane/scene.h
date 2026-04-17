//====================================================
//
// シーン処理 [scene.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _SCENE_H_
#define _SCENE_H_

// インクルード
#include "object.h"

// シーンクラス
class CScene :public CObject
{
public:
	typedef enum
	{
		MODE_TEST = 0,
		MODE_TITLE,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	CScene();
	CScene(MODE mode);
	virtual ~CScene();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static  MODE GetMode(void) { return m_mode; };

	static CScene* Create(MODE mode);

private:
	static MODE m_mode;
};
#endif // !_SCENE_H_
