//====================================================
//
// 敵[enemy.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

// インクルード
#include"main.h"
#include"object2D.h"

#define MAX_ENEMY (3)

class CEnemy :public CObject2D
{
public:

	//typedef enum
	//{
	//	TYPE_NONE = 0,
	//	TYPE_BLACK,
	//	TYPE_WHITH,
	//	TYPE_MAX
	//};

	CEnemy(int nPriority = 4);
	~CEnemy();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static HRESULT Load(void);
	static void UnLoad(void);

	static CEnemy*Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_move;
	float m_fLife;
};

#endif // !_ENEMY_H_
