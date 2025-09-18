//====================================================
//
// チュートリアルシーン処理 [tutorial.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

// インクルード
#include"main.h"
#include"wall.h"
#include"scene.h"
#include"score.h"
#include"player.h"
#include"object2D.h"
#include"object3D.h"
#include"meshSphere.h"
#include"noteManager.h"
#include"shockManager.h"

// マクロ定義
#define FREAM_MOVE (1200)

// チュートリアルクラス
class CTutorial :public CScene
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos) {};
	void SetRot(const D3DXVECTOR3 rot) {};

	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CPlayer* GetPlayer(void) { return m_pPlayer; };
	static CScore* GetScore(void) { return m_pScore; };
	static CObject3D* GetObject3D(void) { return m_pObject3D; };

private:
	static CPlayer* m_pPlayer;
	static CObject3D* m_pObject3D;
	static CScore* m_pScore;				// スコアへのポインタ
	static CNoteManager* m_pNoteManager;
	static CShockManager* m_pShockManager;
	static CMeshSphere* m_pSphere;
	CWall* m_apWall[8];

	int m_nCntFream;
	int m_nCntNoteSpan;
	bool m_bMove;
};
#endif 