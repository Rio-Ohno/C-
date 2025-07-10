//====================================================
// 
// �e [bullet.h]
// Author:Rio Ohno
// 
//====================================================
#ifndef _BULLET_H_
#define _BULLET_H_

// �C���N���[�h
#include"main.h"
#include"object2D.h"

// �}�N����`
#define MAX_BULLET (128)
#define BULLET_SPEED ((float)12.0f)

// �e�N���X
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
	static LPDIRECT3DTEXTURE9 m_pTexture;					// �e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3 m_move;										// �ړ��l
	int m_nLife;											// ����
};

#endif // !_BULLET_H_
