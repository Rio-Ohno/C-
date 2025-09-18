//====================================================
//
// シーン処理 [scene.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _SCENE_H_
#define _SCENE_H_

// インクルード
#include "main.h"
#include "object.h"

// シーンクラス
class CScene :public CObject
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_EDIT_DISPOSITION,
		MODE_MAX
	}MODE;

	CScene();
	CScene(MODE mode);
	virtual ~CScene();

	virtual HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight) = 0;
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
