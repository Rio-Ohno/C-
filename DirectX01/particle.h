//====================================================
//
// �p�[�e�B�N��[particle.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

// �C���N���[�h
#include "main.h"
#include"object.h"
#include"effect.h"

// �}�N����`
#define MAX_EFFECT (16)

class  CParticle :public CObject
{
public:
	CParticle(int nPriority = 2);
	~CParticle();

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

	static CParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fSpeed, int nLife, int nLifeEffect, int NumEffect);

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
#endif // !_PARTICLE_H_
