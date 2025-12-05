//============================================================
//
//メッシュスフィア[meshSphere.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

// インクルード
#include "main.h"
#include"object.h"
																												   
class CMeshSphere :public CObject
{
public:
	CMeshSphere();
	~CMeshSphere();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DXCOLOR col);
	void BindTexIndex(int indx) { m_nTexindx = indx; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return m_fRadius; };
	float GetHeight(void) { return m_fRadius; };

	static CMeshSphere* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDiviX, int nDiviY, float fRadius, bool bHalf,bool bFront);

private:
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_rot;									// 向き
	D3DXCOLOR m_col;									// 色
	D3DXMATRIX m_mtxWorld;								// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIndxBuff;					// インデクスバッファへのポインタ
	int m_nTexindx;										// テクスチャインデックス
	int m_nDiviX;										// 分割数
	int m_nDiviY;										// 分割数
	int m_nMaxVtx;										// 頂点数 
	int m_nPolyNum;										// ポリゴン数
	float  m_fRadius;									// 半径
	bool m_bHalf;										// 半球かどうか
	bool m_bFront;										// 表向きかどうか
};
#endif // !_MESHSPHERE_H_
