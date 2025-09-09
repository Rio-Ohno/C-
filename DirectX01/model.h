//====================================================
//
// ���f��(�K�w�\���O��)[model.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _MODEL_H_
#define _MODEL_H_

// �C���N���[�h
#include "main.h"

// ���f���N���X
class CModel
{
public:
	CModel();
	~CModel();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);
	void Uninit(void);
	void Draw(void);

	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

	void SetParent(CModel* pModel);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetColor(D3DXCOLOR col) { m_col = col; };
	void ColorReset(void) { m_col = {}; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	LPD3DXMESH GetMesh(void) { return m_pMesh; };
	LPD3DXBUFFER GetBuffMat(void) { return m_pBuffMat; };
	DWORD GetdwNumMat(void) { return m_dwNumMat; };
	D3DXMATRIX GetMtxWorld(void);
private:
	LPD3DXMESH m_pMesh;			// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	// �}�e���A���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	DWORD m_dwNumMat;			// �}�e���A���̐�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXCOLOR m_col;			// �F
	CModel* m_pParent;			// �e���f���ւ̃|�C���^
};

#endif // !_MODEL_H_
