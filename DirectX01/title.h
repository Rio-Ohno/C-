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
#include"player.h"
#include"object3D.h"
#include"object2D.h"
#include"meshSphere.h"
#include"noteManager.h"
#include"shockManager.h"

// マクロ定義
#define CAMERA_SPEED ((float)0.0004f)

class CTitle :public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer* GetPlayer(void) { return m_pPlayer; };
	static CObject3D* GetObject3D(void) { return m_pObjecct3D; };
	static CNoteManager* GetNoteManager(void) { return m_pNoteManager; };
	static CShockManager* GetShockManager(void) { return m_pShockManager; }
	static CObject2D* GetObject2D(void){ return m_apObject2D; };

private:
	static CPlayer* m_pPlayer;				// プレイヤーへのポインタ
	static CObject3D* m_pObjecct3D;
	static CNoteManager* m_pNoteManager;
	static CShockManager* m_pShockManager;
	static CMeshSphere* m_pSphere;
	static CObject2D* m_apObject2D;

	int m_nCntFream;
};
#endif // !_TITLE_H_
