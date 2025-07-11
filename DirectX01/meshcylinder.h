//==============================================
//
// ���b�V���V�����_�[ [meshcylinder.h]
// Author:Rio Ohno
//
//==============================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

// �C���N���[�h
#include "main.h"
#include"object.h"

// ���b�V���V�����_�[�N���X
class CMeshCylinder:public CObject
{
public:
	CMeshCylinder();
	~CMeshCylinder();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetColor(D3DXCOLOR col);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetCulling(bool bUse) { m_bCulling = bUse; };
	void BindTexIndx(int indx) { m_nTexindx = indx; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	bool isCulling(void) { return m_bCulling; };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CMeshCylinder* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY, float fHeight, float fRadius);

private:
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	int m_nTexindx;							// �e�N�X�`���C���f�b�N�X
	int m_nDiviX;							// ������(x��)
	int m_nDiviY;							// ������(y��)
	int m_nMaxVtx;							// �ő咸�_��
	int m_nPolyNum;							// �|���S����
	float m_fHeight;						// ����
	float m_fRadius;						// ���a
	bool m_bCulling;						// �J�����O���邩�ǂ���
};
#endif