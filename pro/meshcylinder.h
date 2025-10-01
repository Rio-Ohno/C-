//==============================================
//
// メッシュシリンダー [meshcylinder.h]
// Author:Rio Ohno
//
//==============================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

// インクルード
#include "main.h"
#include"object.h"

// メッシュシリンダークラス
class CMeshCylinder:public CObject
{
public:
	CMeshCylinder();
	~CMeshCylinder();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetColor(D3DXCOLOR col);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetCulling(bool bUse) { m_bCulling = bUse; };
	void BindTexIndx(int indx) { m_nTexindx = indx; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	bool isCulling(void) { return m_bCulling; };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CMeshCylinder* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY, float fHeight, float fRadius);

private:
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// インデックスバッファ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	int m_nTexindx;							// テクスチャインデックス
	int m_nDiviX;							// 分割数(x軸)
	int m_nDiviY;							// 分割数(y軸)
	int m_nMaxVtx;							// 最大頂点数
	int m_nPolyNum;							// ポリゴン数
	float m_fHeight;						// 高さ
	float m_fRadius;						// 半径
	bool m_bCulling;						// カリングするかどうか
};
#endif