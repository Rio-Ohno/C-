//==================================================== 
// 
// ���l�̊Ǘ��@[Number.h]
// Author: Rio Ohno
// 
//==================================================== 
#ifndef _NUMBER_H_
#define _NUMBER_H_

// �C���N���[�h
#include"main.h"

class CNumber
{
public:

	CNumber();
	~CNumber();

	void Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return m_fWidth; };
	float GetHeight(void) { return m_fHeight; };

	static CNumber* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

	void BindTex(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; };
	int SetNum(int nNumber, int nDight);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							// �ʒu
	float m_fWidth;								// ��
	float m_fHeight;							// ����
};

#endif