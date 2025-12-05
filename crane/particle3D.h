//====================================================
//
// パーティクル[particle3D.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _PARTICLE3D_H_
#define _PARTICLE3D_H_

// インクルード
#include "main.h"
#include"object.h"

// マクロ定義
#define MAX_EFFECT (16)

class  CParticle3D :public CObject
{
public:
	CParticle3D(int nPriority = 4);
	~CParticle3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos);
	void SetRot(const D3DXVECTOR3 rot) {};
	void SetColor(D3DXCOLOR col);

	D3DXVECTOR3 GetPos(void) { return m_pos; };

	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CParticle3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fSpeed, int nLife, int nLifeEffect, int NumEffect);

private:
	D3DXVECTOR3 m_pos;							// 角度
	D3DXVECTOR3 m_rot;							// 角度
	D3DXCOLOR m_col;							// 色
	float m_fRadius;							// 幅
	float m_fSpeed;								// スピード
	int m_nLife;								// 寿命(パーティクル)エフェクトを呼ぶフレーム数
	int m_nLifeEffect;							// 寿命(エフェクト)
	int m_nNumEffect;							// 1Fに呼ぶエフェクトの数
};
#endif