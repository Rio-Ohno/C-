//====================================================
//
// 箱(プライズ)　[box.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _BOX_X_
#define _BOX_H_

// インクルード
#include "enemy.h"

// 前方宣言
class CObjectX;
class CColliderSphere;

// 箱クラス
class CPrizeBox :public CEnemyBase
{
public:
	CPrizeBox();
	~CPrizeBox();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	static CPrizeBox* Create(D3DXVECTOR3 pos);

private:

	// constexpr
	static constexpr const char* FILE_NAME = "data/MODEL/prize/PrizeBox001.x";

	CObjectX* m_model;				// モデル情報
	CColliderSphere* m_collider;	// コライダー
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
};
#endif