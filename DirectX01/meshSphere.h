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
																												   
//���̍\����																									 �@ 
typedef struct																									   
{																												   
	D3DXVECTOR3 pos;																							// �ʒu
	D3DXVECTOR3 rot;																							// ����
	D3DXCOLOR col;																								// �F
	D3DXMATRIX mtxWorld;																						// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;																			// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIndxBuff;																			// �C���f�N�X�o�b�t�@�ւ̃|�C���^
	int textype;																								// �e�N�X�`���̎��
	int DiviX;																									// ������
	int DiviY;																									// ������
	int nMaxVtx;																								// ���_�� 
	int nPolyNum;																								// �|���S����
	float  fRadius;																								// ���a
	bool bHalf;																									// �������ǂ���
	bool bHead;																									// �\���ǂ���
	bool bUse;																									// �g�p���Ă��邩�ǂ���
}MeshSphere;																									   
																												   
//�v���g�^�C�v�錾																								   
void InitSphere(void);																							// ����������
void UninitSphere(void);																						// �I������
void UpdateSphere(void);																						// �X�V����
void DrawSphere(void);																							// �`�揈��
int SetSphere(D3DXVECTOR3 pos, int textype, int DiviX, int DiviY, float fRadius, bool bHead, bool bHalf);		// �ݒ菈��
void SetSpherePos(int indx,D3DXVECTOR3 pos);																	// �ʒu�̐ݒ菈��
void SetSphereTexture(int indx);																				// �e�N�X�`���̐ݒ菈��
//void DeleteSphere(int indx);																					// ��������

class CMeshSphere :public CObject
{
public:
	CMeshSphere();
	~CMeshSphere();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetColor(D3DXCOLOR col);
	void BindTexIndex(int indx);

	D3DXVECTOR3 GetPos(void);

	static CMeshSphere* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDiviX, int nDiviY, float fRadius, bool bHalf);

private:
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_rot;								// ����
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIndxBuff;				// �C���f�N�X�o�b�t�@�ւ̃|�C���^
	int m_nTexindx;									// �e�N�X�`���C���f�b�N�X
	int m_nDiviX;									// ������
	int m_nDiviY;									// ������
	int m_nMaxVtx;									// ���_�� 
	int m_nPolyNum;									// �|���S����
	float  m_fRadius;								// ���a
	bool m_bHalf;									// �������ǂ���
	bool m_bFront;									// �\�������ǂ���
};
#endif // !_MESHSPHERE_H_
