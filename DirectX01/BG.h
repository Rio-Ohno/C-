//====================================================
//
// 背景[BG.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _BG_H_
#define _BG_H_

// インクルード
#include"main.h"
#include"object.h"
#include"object2D.h"

// マクロ定義
#define MAX_BG (3)							// 背景の最大数
#define Scroll_SPEED ((float)0.001f)				// 一番早いスクロール

// 背景クラス
class CBG :public CObject2D
{
public:

	//CBG();
	CBG(int nPriority = 2);
	~CBG();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static HRESULT Load(void);
	static void UnLoad(void);

	static CBG* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fScroll);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	float m_fScroll;// スクロールのスピード
	float m_fMemScroll;// 今までのスクロール移動量
};

// 背景マネージャークラス
class CBGManager :public CObject
{
public:
	CBGManager(int nPriority = 1);
	~CBGManager();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Draw(void);
	void Update(void);

	void SetPos(const D3DXVECTOR3 pos) {};
	void SetRot(const D3DXVECTOR3 rot) {};

	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3(); };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };


	static HRESULT Load(void);
	static void UnLoad(void);

	static CBGManager* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	static CBG* m_apBG[MAX_BG];
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BG];
};


#endif // !_BG_H_
