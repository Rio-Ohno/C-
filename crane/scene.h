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

	void SetPos(const D3DXVECTOR3 pos) {};
	void SetRot(const D3DXVECTOR3 rot) {};

	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	MODE GetMode(void) { return m_mode; };

	static CScene* Create(MODE mode);

private:
	MODE m_mode;
};
#endif // !_SCENE_H_
