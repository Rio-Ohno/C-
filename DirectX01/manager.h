//====================================================
// 
// マネジャー[manager.h]
// Author:RioOhno
// 
//====================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//インクルード
#include"main.h"
#include"input.h"
#include"renderer.h"
#include"player.h"
#include"BG.h"
#include"enemy.h"
#include"light.h"
#include"camera.h"
#include"texture.h"
#include"motion.h"
#include"score.h"
#include"object3D.h"

//マネージャークラス
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer* GetRenderer(void);
	static CKeyboard* GetKeyboard(void);
	static CPlayer* GetPlayer(void);
	static CEnemy* GetEnemy(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);
	static CTexture* GetTexture(void);
	static CLoadMotion* GetLoadMotion(void);
	static CScore* GetScore(void);
	static CObject3D* GetObject3D(void);

private:
	static CRenderer* m_pRenderer;			// レンダラーへのポインタ
	static CKeyboard* m_pKeyboard;			// キーボードへのポインタ
	static CBGManager* m_BGManager;
	static CPlayer* m_pPlayer;				// プレイヤーへのポインタ
	static CEnemy* m_pEnemy[MAX_ENEMY];
	static CCamera* m_pCamera;				// カメラへのポインタ
	static CLight* m_pLight;				// ライトへのポインタ
	static CTexture* m_pTexture;			// テクスチャへのポインタ
	static CLoadMotion* m_pLoadMotion;		// モーション読込へのポインタ
	static CScore* m_pScore;				// スコアへのポインタ
	static CObject3D* m_pObjecct3D;
};

#endif // !_MANAGER_H_
