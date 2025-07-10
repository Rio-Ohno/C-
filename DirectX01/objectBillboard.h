//====================================================
// 
// �r���{�[�h�I�u�W�F�N�g [objectBillboard.cpp]
// Author:Rio Ohno
// 
//====================================================
#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_

// �C���N���[�h
#include"main.h"
#include"object.h"

class CObjectBillboard:public CObject
{
public:
	CObjectBillboard();
	~CObjectBillboard();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetSize(float fWidth, float fHeight);
	void SetOriogin(D3DXVECTOR3 origin) { m_origin = origin; };
	void SetColor(D3DXCOLOR col);
	void Bindtexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return m_fWidth; };
	float GetHeight(void) { return m_fHeight; };

	static CObjectBillboard* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXVECTOR3 origin);
private:
	int m_indxTexture;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXVECTOR3 m_dir;							//�����x�N�g��(move?)
	D3DXVECTOR3 m_origin;							// ��]���̈ʒu
	float m_fWidth;								// ��
	float m_fHeight;							// ����
};

#endif