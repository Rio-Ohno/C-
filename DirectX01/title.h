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
#include"wall.h"
#include"scene.h"
#include"object3D.h"
#include"object2D.h"
#include"meshSphere.h"
#include"noteManager.h"
#include"shockManager.h"

// マクロ定義
#define CAMERA_SPEED ((float)0.0004f)
#define NUM_POLYGON (4)

class CTitle :public CScene
{
public:

	typedef enum
	{
		MENU_GAME = 0,
		MENU_TUTORIAL,
		MENU_MAX
	}Menu;

	CTitle();
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SelectMode(void);

	static CObject3D* GetObject3D(void) { return m_pObjecct3D; };
	static CNoteManager* GetNoteManager(void) { return m_pNoteManager; };
	static CShockManager* GetShockManager(void) { return m_pShockManager; }
	static CObject2D** GetObject2D(void){ return m_apObject2D; };

private:
	static CObject3D* m_pObjecct3D;
	static CNoteManager* m_pNoteManager;
	static CShockManager* m_pShockManager;
	static CObject2D* m_apObject2D[NUM_POLYGON];
	CMeshSphere* m_pSphere;
	CWall* m_apWall[4];

	Menu m_Menu;
	int m_nCntFream;
	int m_nCntMenu;// 0：game 1：tutorial
};
#endif // !_TITLE_H_
