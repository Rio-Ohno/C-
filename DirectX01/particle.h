//====================================================
//
// パーティクル[particle.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

// インクルード
#include "main.h"
#include"object.h"
#include"effect.h"

// マクロ定義
#define MAX_EFFECT (16)

class  CParticle :public CObject
{
public:
	CParticle(int nPriority = 2);
	~CParticle();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void SetPos(const D3DXVECTOR3 pos);
	void SetRot(const D3DXVECTOR3 rot) {};
	void SetColor(D3DXCOLOR col);

	D3DXVECTOR3 GetPos(void) { return m_pos; };

	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fSpeed, int nLife, int nLifeEffect, int NumEffect);

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
#endif // !_PARTICLE_H_
