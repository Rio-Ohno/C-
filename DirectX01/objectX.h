//====================================================
//
// X�t�@�C��[objectX.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

// �C���N���[�h
#include"main.h"
#include"object.h"

// �}�N����`
#define MAX_MAT (512) 

// X�t�@�C���N���X
class CObjectX :public CObject
{
public:
	CObjectX();
	virtual ~CObjectX();

	virtual HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void BindModel(const char* pFileName);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };

	LPD3DXMESH GetMesh(void) { return m_pMesh; };
	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CObjectX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:
	int m_anTexIndx[MAX_MAT];					// �e�N�X�`���|�C���^�̃C���f�b�N�X�ۑ��p
	LPD3DXMESH m_pMesh;							// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;					// �}�e���A���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	DWORD m_dwNumMat;							// �}�e���A���̐�
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	bool m_bExistence = false;					// ���f���̗L��
};

#endif
