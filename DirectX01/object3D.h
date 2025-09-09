//====================================================
// 
// 3D�I�u�W�F�N�g [object3D.h]
// Author:Rio Ohno
// 
//====================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

// �C���N���[�h
#include"main.h"
#include"object.h"

// 3D�|���S���̃N���X
class CObject3D :public CObject
{
public:
	CObject3D();
	virtual ~CObject3D();

	virtual HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DCOLOR col);
	void BindTexIndex(int indx) { m_nTexindx = indx; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	void isColision(void);
	float GetWidth(void) { return m_fWidth; };
	float GetLength(void) { return m_fLength; };
	float GetHeight(void);

	static CObject3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fLength);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	int m_nTexindx;								// �e�N�X�`���C���f�b�N�X
	float m_fLength;							// ����
	float m_fWidth;								// ��
	float m_fHeight;							// ����
}; 
#endif