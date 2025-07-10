//====================================================
// 
// 弾 [bullet.h]
// Author:Rio Ohno
// 
//====================================================
#ifndef _BULLET_H_
#define _BULLET_H_

// インクルード
#include"main.h"
#include"object2D.h"

// マクロ定義
#define MAX_BULLET (128)
#define BULLET_SPEED ((float)12.0f)

// 弾クラス
class CBullet :public CObject2D
{
public:
	CBullet();
	//CBullet(int nPriority);
	~CBullet();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static HRESULT Load(void);
	static void UnLoad(void);

	static CBullet* Create(D3DXVECTOR3 pos, float fRadius,int nLife);

	bool CollisionEnemy(D3DXVECTOR3 pos);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;					// テクスチャへのポインタ

	D3DXVECTOR3 m_move;										// 移動値
	int m_nLife;											// 寿命
};

#endif // !_BULLET_H_
