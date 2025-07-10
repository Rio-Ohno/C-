//====================================================
//
// エフェクト[effect3D.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

// インクルード
#include"main.h"
#include"objectBillboard.h"

class CEffect3D :public CObjectBillboard
{
public:
	CEffect3D();
	~CEffect3D();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius, int nLife, float fDelSize);

private:
	static int m_Texindx;								// テクスチャインデックス
	D3DXVECTOR3 m_move;									// 移動値
	int m_nLife;										// 寿命
	float m_fDelSize;									// サイズを小さくする係数
};

#endif // !_EFFECT3D_H_