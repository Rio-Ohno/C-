//====================================================
//
// �����_���[[renderer.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//�C���N���[�h
#include "main.h"
#include"sound.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Draw(void);
	void Uninit(void);
	void Update(void);

	LPDIRECT3DDEVICE9 GetDevice(void)const;
	CSound* GetSound(void)const { return m_pSound; };

	void onWireFrame(void) { m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); };
	void offWireFrame(void) { m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); };

	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);
	LPDIRECT3DTEXTURE9 GetTextureMT(void) { return m_pTexMT; };
	bool isFeedbackEffect(void) { return m_bFeedbackEffect; };
	void SetFeedbackEffect(bool bUse) { m_bFeedbackEffect = bUse; };

private:
	static CSound* m_pSound;
	LPDIRECT3D9 m_pD3D;						// DirectX3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;         // DirectX3D�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexMT;			// �����_�����O�^�[�Q�b�g�p�e�N�X�`���|�C���^
	LPDIRECT3DTEXTURE9 m_apTexMT[2];		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���|�C���^(�t�B�[�h�o�b�N�G�t�F�N�g�p)
	LPDIRECT3DSURFACE9 m_pRenderMT;			// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X
	LPDIRECT3DSURFACE9 m_apRenderMT[2];		// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X(�t�B�[�h�o�b�N�G�t�F�N�g�p)
	LPDIRECT3DSURFACE9 m_pZBuffMT;			// �e�N�X�`�������_�����O�pz�o�b�t�@
	D3DVIEWPORT9 m_viewportMT;				// �e�N�X�`�������_�����O�p�r���[�|�[�g

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;	// �t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@
	bool m_bFeedbackEffect;
};

#endif // !_RENDERER_H_

