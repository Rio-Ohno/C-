//====================================================
//
// ��[wall.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _WALL_H_
#define _WALL_H_

// �C���N���[�h
#include"main.h"
#include"object.h"

// �ǃN���X
class CWall :public CObject
{
public:
	CWall();
	~CWall();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DCOLOR col);
	void BindTexIndex(int indx) { m_nTexindx = indx; };
	void SetDisp(bool bDisp) { m_bDisp = bDisp; };
	void SetTexUV(float minU, float maxU, float minV, float maxV);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return m_fWidth; };
	float GetLength(void) { return m_fLength; };
	float GetHeight(void) { return m_fHeight; };

	bool isColision(D3DXVECTOR3 pos);
	D3DXVECTOR3 Reflect(D3DXVECTOR3 pos, D3DXVECTOR3 posOld);

	static CWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, bool bCollision, bool bDisp);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	int m_nTexindx;								// �e�N�X�`���C���f�b�N�X
	float m_fLength;							// ����
	float m_fWidth;								// ��
	float m_fHeight;							// ����
	bool m_bCollision;							// �����蔻����Ƃ邩�ǂ���
	bool m_bDisp;								// �\�����邩�ǂ���
};

#endif // !_WALL_H_
