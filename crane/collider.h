//====================================================
// 
//  当たり判定（コライダー）[collider.h]
// Author：Rio Ohno
// 
//====================================================
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

// インクルード
#include "main.h"

// ---------------------------------------------------
// コライダー基底クラス
// ---------------------------------------------------
class CColliderBase
{
public:
	CColliderBase() { m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); };
	virtual ~CColliderBase() {};

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };

private:
	D3DXVECTOR3 m_pos;
};

// ---------------------------------------------------
// 球のコライダー
// ---------------------------------------------------
class CColliderSphere :public CColliderBase
{
public:
	CColliderSphere();
	~CColliderSphere() {};

	void Init(void) {};
	void Uninit(void) { delete this; };

	// ゲッター
	D3DXVECTOR3 GetCenter(void) { return CColliderBase::GetPos(); }
	float GetRadius(void) { return m_fRadius; }

	void SetParameter(D3DXVECTOR3 pos, float fRadius);
	void SetParameter(D3DXVECTOR3 pos) { CColliderBase::SetPos(pos); }
	void SetParameter(float fRadius) { m_fRadius = fRadius; };

private:
	float m_fRadius;		// 半径
};

// ---------------------------------------------------
// 円柱のコライダー
// ---------------------------------------------------
class CColliderCylinder :public CColliderBase
{
public:
	CColliderCylinder();
	~CColliderCylinder() {};

	void Init(void) {};
	void Uninit(void) { delete this; }

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return CColliderBase::GetPos(); }
	float GetRadius(void) { return m_fRadius; }
	float GetHeight(void) { return m_fHeight; }

	// セッター
	void SetParameter(D3DXVECTOR3 pos, float fRadius, float fHeight);

	void SetParameter(D3DXVECTOR3 pos) { CColliderBase::SetPos(pos); }
	void SetRadius(float fRadius) { m_fRadius = fRadius; };
	void SetHeight(float fHeight) { m_fHeight = fHeight; };

private:
	float m_fRadius;	// 半径
	float m_fHeight;	// 高さ
};

#endif // !_COLLISION_H_
