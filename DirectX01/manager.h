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
#include"light.h"
#include"camera.h"
#include"texture.h"
#include"scene.h"
#include"sound.h"
#include"fade.h"
#include"DebugProc.h"

#include"BG.h"

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

	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void);
	static CRenderer* GetRenderer(void);
	static CKeyboard* GetKeyboard(void);
	static CSound* GetSound(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);
	static CTexture* GetTexture(void);
	static CFade* GetFade(void);
	static CDebugProc* GetDebug(void);

private:
	static CScene* m_pScene;
	static CRenderer* m_pRenderer;			// レンダラーへのポインタ
	static CKeyboard* m_pKeyboard;			// キーボードへのポインタ
	static CCamera* m_pCamera;				// カメラへのポインタ
	static CLight* m_pLight;				// ライトへのポインタ
	static CTexture* m_pTexture;			// テクスチャへのポインタ
	static CSound* m_pSound;				// サウンドへのポインタ
	static CFade* m_pFade;					// フェードへのポインタ
	static CDebugProc* m_pDebug;			// デバック表示へのポインタ
};

#endif // !_MANAGER_H_
