//====================================================
//
// �G�t�F�N�g[effect.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

// �C���N���[�h
#include"main.h"
#include"object2D.h"

// �G�t�F�N�g�N���X
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
	static LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_move;									// �ړ��l
	int m_nLife;										// ����
	float m_fDelSize;									// �T�C�Y������������W��
};
#endif