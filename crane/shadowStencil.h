//====================================================
//
// 影 [shadowStencil.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _SHADOWS_H_
#define _SHADOWS_H_

// インクルード
#include"main.h"
#include"objectX.h"

class CShadowS :public CObjectX
{
public:
	CShadowS(int nPriority = 4);
	~CShadowS();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetColor(D3DXCOLOR col);

	static CShadowS* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:

	// constexpr
	static constexpr const char* MODEL_FILEPASS = "data\\MODEL\\shadow.x";// モデルファイルパス
	static constexpr int NUM_VTX = 4;			// 頂点数


	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXCOLOR m_col;							// 色
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	static bool m_bmodel;						// 影モデルを表示するかどうか
};

#endif
