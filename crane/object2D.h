//====================================================
//
// オブジェクト2D[object2D.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//インクルード
#include"main.h"
#include"object.h"

class CObject2D:public CObject
{
public:
	CObject2D(int nPriority = 3);
	~CObject2D();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
		    
	virtual void SetPos(const D3DXVECTOR3 pos);
	virtual void SetRot(const D3DXVECTOR3 rot);
	void SetSize(const float fWidth,const float fHeight);
	void BindTex(LPDIRECT3DTEXTURE9 pTexture);
	void BindTexIndx(int nTextureIndx);
	void SetTexUV(float fDiviX, float fDiviY);
	void SetBuffer(LPDIRECT3DVERTEXBUFFER9 pVtxBuff);
	void SetColor(D3DXCOLOR col);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	float GetWidth(void) { return m_fWidth; };
	float GetHeight(void) { return m_fHeight; };
	LPDIRECT3DTEXTURE9 GetTex(void) { return m_pTexture; };
	LPDIRECT3DVERTEXBUFFER9 GetBuffer(void) { return m_pVtxBuff; };

	static CObject2D* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	// constexpr
	static constexpr int NUM_VTX = 4;			// 頂点数

	LPDIRECT3DTEXTURE9 m_pTexture;				// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 向き
	int m_nIndxTex;								// テクスチャポインタのインデックス
	float m_fWidth;								// 幅
	float m_fHeight;							// 高さ
};
#endif