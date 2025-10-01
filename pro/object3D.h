//====================================================
// 
// 3Dオブジェクト [object3D.h]
// Author:Rio Ohno
// 
//====================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

// インクルード
#include"main.h"
#include"object.h"

// 3Dポリゴンのクラス
class CObject3D :public CObject
{
public:
	CObject3D();
	virtual ~CObject3D();

	virtual HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DCOLOR col);
	void BindTexIndex(int indx) { m_nTexindx = indx; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	void isColision(void);
	float GetWidth(void) { return m_fWidth; };
	float GetLength(void) { return m_fLength; };
	float GetHeight(void);

	static CObject3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fLength);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 向き
	int m_nTexindx;								// テクスチャインデックス
	float m_fLength;							// 長さ
	float m_fWidth;								// 幅
	float m_fHeight;							// 高さ
}; 
#endif