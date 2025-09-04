//============================================================
//
//���b�V���X�t�B�A[meshSphere.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

// �C���N���[�h
#include "main.h"
#include"object.h"
																												   
class CMeshSphere :public CObject
{
public:
	CMeshSphere();
	~CMeshSphere();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DXCOLOR col);
	void BindTexIndex(int indx) { m_nTexindx = indx; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return m_fRadius; };
	float GetHeight(void) { return m_fRadius; };

	static CMeshSphere* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDiviX, int nDiviY, float fRadius, bool bHalf,bool bFront);

private:
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_rot;									// ����
	D3DXCOLOR m_col;									// �F
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIndxBuff;					// �C���f�N�X�o�b�t�@�ւ̃|�C���^
	int m_nTexindx;										// �e�N�X�`���C���f�b�N�X
	int m_nDiviX;										// ������
	int m_nDiviY;										// ������
	int m_nMaxVtx;										// ���_�� 
	int m_nPolyNum;										// �|���S����
	float  m_fRadius;									// ���a
	bool m_bHalf;										// �������ǂ���
	bool m_bFront;										// �\�������ǂ���
};
#endif // !_MESHSPHERE_H_
