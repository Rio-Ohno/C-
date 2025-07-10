//====================================================
//
// エフェクト[effect.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

// インクルード
#include"main.h"
#include"object2D.h"

// エフェクトクラス
class CEffect :public CObject2D
{
public:
	CEffect(int nPriority = 2);
	~CEffect();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static HRESULT Load(void);
	static void UnLoad(void);

	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius, int nLife, float fDelSize);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				// テクスチャへのポインタ
	D3DXVECTOR3 m_move;									// 移動値
	int m_nLife;										// 寿命
	float m_fDelSize;									// サイズを小さくする係数
};
#endif