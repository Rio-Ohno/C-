//====================================================
//
// メッシュフィールド[meshfield.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _MESHFIELD_H
#define _MESHFIELD_H_

// インクルード
#include "main.h"
#include "object.h"

//マクロ定義
#define MESH_NUM_MAX (32)//メッシュフィールドの数
#define MAX_TEX_FIELD (64)//テクスチャの最大数

// メッシュフィールドクラス
class CMeshField:public CObject
{
public:
	CMeshField();
	~CMeshField();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return (float)m_nWidth; };
	float GetHeight(void) { return (float)m_nHeight; };
	void BindTexIndex(int indx) { m_nTexIndx = indx; };

	static CMeshField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int textype, int nDiviX, int nDiviZ, int nWidth, int nHeight);

private:
	D3DXVECTOR3 m_pos;											// 位置
	D3DXVECTOR3 m_rot;											// 向き
	D3DXMATRIX m_mtxWorld;										// ワールドマトリックス
	LPDIRECT3DINDEXBUFFER9 m_IdxBuff;							// インデックスバッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// 頂点情報へのポインタ
	int m_nTexIndx;												// テクスチャインデックス
	int	m_nDiviX;												// 分割数(x軸)
	int	m_nDiviZ;												// 分割数(z軸)
	int	m_nWidth;												// 幅
	int	m_nHeight;												// 高さ
	int m_nMaxVtx;												// 最大頂点数
	int m_nPolyNum;												// ポリゴン数
};
#endif