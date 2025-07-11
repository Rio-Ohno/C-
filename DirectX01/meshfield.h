//====================================================
//
// ���b�V���t�B�[���h[meshfield.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _MESHFIELD_H
#define _MESHFIELD_H_

// �C���N���[�h
#include "main.h"
#include "object.h"

//�}�N����`
#define MESH_NUM_MAX (32)//���b�V���t�B�[���h�̐�
#define MAX_TEX_FIELD (64)//�e�N�X�`���̍ő吔

// ���b�V���t�B�[���h�N���X
class CMeshField:public CObject
{
public:
	CMeshField();
	~CMeshField();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return (float)m_nWidth; };
	float GetHeight(void) { return (float)m_nHeight; };
	void BindTexIndex(int indx) { m_nTexIndx = indx; };

	static CMeshField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int textype, int nDiviX, int nDiviZ, int nWidth, int nHeight);

private:
	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR3 m_rot;											// ����
	D3DXMATRIX m_mtxWorld;										// ���[���h�}�g���b�N�X
	LPDIRECT3DINDEXBUFFER9 m_IdxBuff;							// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// ���_���ւ̃|�C���^
	int m_nTexIndx;												// �e�N�X�`���C���f�b�N�X
	int	m_nDiviX;												// ������(x��)
	int	m_nDiviZ;												// ������(z��)
	int	m_nWidth;												// ��
	int	m_nHeight;												// ����
	int m_nMaxVtx;												// �ő咸�_��
	int m_nPolyNum;												// �|���S����
};
#endif