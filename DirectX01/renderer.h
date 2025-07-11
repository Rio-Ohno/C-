//====================================================
//
// レンダラー[renderer.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//インクルード
#include "main.h"
#include"sound.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Draw(void);
	void Uninit(void);
	void Update(void);

	LPDIRECT3DDEVICE9 GetDevice(void)const;
	CSound* GetSound(void)const { return m_pSound; };

	void onWireFrame(void) { m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); };
	void offWireFrame(void) { m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); };

	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);
	LPDIRECT3DTEXTURE9 GetTextureMT(void) { return m_pTexMT; };
	bool isFeedbackEffect(void) { return m_bFeedbackEffect; };
	void SetFeedbackEffect(bool bUse) { m_bFeedbackEffect = bUse; };

private:
	static CSound* m_pSound;
	LPDIRECT3D9 m_pD3D;						// DirectX3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;         // DirectX3Dデバイスへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexMT;			// レンダリングターゲット用テクスチャポインタ
	LPDIRECT3DTEXTURE9 m_apTexMT[2];		// レンダリングターゲット用テクスチャポインタ(フィードバックエフェクト用)
	LPDIRECT3DSURFACE9 m_pRenderMT;			// テクスチャレンダリング用インターフェース
	LPDIRECT3DSURFACE9 m_apRenderMT[2];		// テクスチャレンダリング用インターフェース(フィードバックエフェクト用)
	LPDIRECT3DSURFACE9 m_pZBuffMT;			// テクスチャレンダリング用zバッファ
	D3DVIEWPORT9 m_viewportMT;				// テクスチャレンダリング用ビューポート

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;	// フィードバック用ポリゴンの頂点バッファ
	bool m_bFeedbackEffect;
};

#endif // !_RENDERER_H_

