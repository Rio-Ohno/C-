//====================================================
// 
// ビルボードオブジェクト [objectBillboard.cpp]
// Author:Rio Ohno
// 
//====================================================
#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_

// インクルード
#include"main.h"
#include"object.h"

class CObjectBillboard:public CObject
{
public:
	CObjectBillboard();
	~CObjectBillboard();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetSize(float fWidth, float fHeight);
	void SetOriogin(D3DXVECTOR3 origin) { m_origin = origin; };
	void SetColor(D3DXCOLOR col);
	void Bindtexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return m_fWidth; };
	float GetHeight(void) { return m_fHeight; };

	static CObjectBillboard* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXVECTOR3 origin);
private:
	int m_indxTexture;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 向き
	D3DXVECTOR3 m_dir;							//方向ベクトル(move?)
	D3DXVECTOR3 m_origin;							// 回転軸の位置
	float m_fWidth;								// 幅
	float m_fHeight;							// 高さ
};

#endif