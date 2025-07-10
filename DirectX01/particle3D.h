//====================================================
//
// �p�[�e�B�N��[particle3D.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _PARTICLE3D_H_
#define _PARTICLE3D_H_

// �C���N���[�h
#include "main.h"
#include"object.h"

// �}�N����`
#define MAX_EFFECT (16)

class  CParticle3D :public CObject
{
public:
	CParticle3D(int nPriority = 4);
	~CParticle3D();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos);
	void SetRot(const D3DXVECTOR3 rot) {};
	void SetColor(D3DXCOLOR col);

	D3DXVECTOR3 GetPos(void) { return m_pos; };

	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CParticle3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fSpeed, int nLife, int nLifeEffect, int NumEffect);

private:
	D3DXVECTOR3 m_pos;							// �p�x
	D3DXVECTOR3 m_rot;							// �p�x
	D3DXCOLOR m_col;							// �F
	float m_fRadius;							// ��
	float m_fSpeed;								// �X�s�[�h
	int m_nLife;								// ����(�p�[�e�B�N��)�G�t�F�N�g���Ăԃt���[����
	int m_nLifeEffect;							// ����(�G�t�F�N�g)
	int m_nNumEffect;							// 1F�ɌĂԃG�t�F�N�g�̐�
};
#endif