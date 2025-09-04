//====================================================
//
// �e[shadowS.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _SHADOWS_H_
#define _SHADOWS_H_

// �C���N���[�h
#include"main.h"
#include"objectX.h"

class CShadowS :public CObjectX
{
public:
	CShadowS(int nPriority = 4);
	~CShadowS();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetColor(D3DXCOLOR col) { m_col = col; };

	static CShadowS* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_scale;
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	static bool m_bmodel;						// �e���f����\�����邩�ǂ���
};

#endif
