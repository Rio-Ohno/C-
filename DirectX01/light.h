//====================================================
//
//���C�g[light.h]
//Author:Rio Ohno
//
//====================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

// �C���N���[�h
#include"main.h"

//�}�N����`
#define MAX_LIGHT (3)			// ���C�g�̐�

//�v���g�^�C�v�錾
void InitLight();
void UninitLight();
void UpdateLight();

class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	D3DLIGHT9 m_light[MAX_LIGHT];//���C�g���
};

#endif // !_LIGHT_H_
