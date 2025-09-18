//====================================================
//
// 壁[wall.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _WALL_H_
#define _WALL_H_

// インクルード
#include"main.h"
#include"object.h"

// 壁クラス
class CWall :public CObject
{
public:
	CWall();
	~CWall();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DCOLOR col);
	void BindTexIndex(int indx) { m_nTexindx = indx; };
	void SetDisp(bool bDisp) { m_bDisp = bDisp; };
	void SetTexUV(float minU, float maxU, float minV, float maxV);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return m_fWidth; };
	float GetLength(void) { return m_fLength; };
	float GetHeight(void) { return m_fHeight; };

	bool isColision(D3DXVECTOR3 pos);
	D3DXVECTOR3 Reflect(D3DXVECTOR3 pos, D3DXVECTOR3 posOld);

	static CWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, bool bCollision, bool bDisp);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 向き
	int m_nTexindx;								// テクスチャインデックス
	float m_fLength;							// 長さ
	float m_fWidth;								// 幅
	float m_fHeight;							// 高さ
	bool m_bCollision;							// 当たり判定をとるかどうか
	bool m_bDisp;								// 表示するかどうか
};

#endif // !_WALL_H_
