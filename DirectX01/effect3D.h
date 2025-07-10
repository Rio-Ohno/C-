//====================================================
//
// �G�t�F�N�g[effect3D.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

// �C���N���[�h
#include"main.h"
#include"objectBillboard.h"

class CEffect3D :public CObjectBillboard
{
public:
	CEffect3D();
	~CEffect3D();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius, int nLife, float fDelSize);

private:
	static int m_Texindx;								// �e�N�X�`���C���f�b�N�X
	D3DXVECTOR3 m_move;									// �ړ��l
	int m_nLife;										// ����
	float m_fDelSize;									// �T�C�Y������������W��
};

#endif // !_EFFECT3D_H_