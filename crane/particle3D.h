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
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DXCOLOR col);
	void SetColorRandom(D3DXCOLOR Maxcol);
	void SetRadius(float fRadius) { m_fRadius = fRadius; };
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; };
	void SetLife(int nLife) { m_nLife = nLife; };
	void SetLifeEffect(int nLife) { m_nLifeEffect = nLife; };
	void SetNumEffect(int nNum) { m_nNumEffect = nNum; };
	void SetSpan(int nSpan) { m_nSpan = nSpan; };
	void SetRandMode(bool bRandom) { m_bColorRandom = bRandom; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXCOLOR GetColor(void) { return m_col; };
	int GetSpan(void) { return m_nSpan; };

	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CParticle3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fSpeed, int nLife, int nLifeEffect, int NumEffect,int nSpan);

private:
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 角度
	D3DXCOLOR m_col;							// 色
	float m_fRadius;							// 半径(エフェクトポリゴン)
	float m_fSpeed;								// スピード
	int m_nLife;								// 寿命(パーティクル)エフェクトを呼ぶフレーム数
	int m_nLifeEffect;							// 寿命(エフェクト)
	int m_nNumEffect;							// 一回に呼ぶエフェクトの数
	int m_nSpan;								// エフェクトを呼ぶ間隔
	int m_nCntFream;							// フレームカウンタ
	bool m_bColorRandom;						// 色をランダムにするかどうか
};
#endif