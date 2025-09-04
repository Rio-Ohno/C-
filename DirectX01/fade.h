//====================================================
//
//�t�F�[�h����[fade.h]
//Author:Rio Ohno
//
//====================================================

#ifndef _FADE_H_
#define _FADE_H_

// �C���N���[�h
#include"main.h"
#include"scene.h"

// �t�F�[�h�N���X
class CFade
{
public:

	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,//�^����
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;

	CFade();
	~CFade();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(CScene::MODE modeNext);
	FADE Get(void);
	
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;              // ���_�o�b�t�@�ւ̃|�C���^
	FADE m_fade;                                     // �t�F�[�h�̏��
	CScene::MODE m_modeNext;                         // ���̉�ʁi���[�h�j
	D3DXCOLOR m_colorFade;                           // �|���S���i�t�F�[�h�j�̐F
};
#endif // !_FADE_H_

