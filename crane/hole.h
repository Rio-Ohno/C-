//====================================================
//
// ホール　[hole.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _HOLE_H_
#define _HOLE_H_

// インクルード
#include "meshcylinder.h"

// 前方宣言
class CColliderCylinder;// コライダー(円柱)

class CHole:public CMeshCylinder
{
public:
	CHole(int nPriority = 4) :CMeshCylinder(nPriority) { m_collider = nullptr; };
	~CHole();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	CColliderCylinder* GetCollider(void) { return m_collider; }

	static CHole* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY, float fHeight, float fRadius);

private:
	// contexpr
	static constexpr float COLLIDER_SCALE_RADIUS = 0.9f;// 当たり判定のスケール(半径)
	static constexpr float COLLIDER_SCALE_HEIGHT = 0.1f;// 当たり判定のスケール(高さ)
	

	CColliderCylinder* m_collider;// コライダー
};
#endif // !_HOLE_H_