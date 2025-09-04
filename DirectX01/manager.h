//====================================================
// 
// �}�l�W���[[manager.h]
// Author:RioOhno
// 
//====================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//�C���N���[�h
#include"main.h"
#include"input.h"
#include"renderer.h"
#include"light.h"
#include"camera.h"
#include"texture.h"
#include"scene.h"
#include"sound.h"
#include"fade.h"
#include"DebugProc.h"

#include"BG.h"

//�}�l�[�W���[�N���X
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void);
	static CRenderer* GetRenderer(void);
	static CKeyboard* GetKeyboard(void);
	static CSound* GetSound(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);
	static CTexture* GetTexture(void);
	static CFade* GetFade(void);
	static CDebugProc* GetDebug(void);

private:
	static CScene* m_pScene;
	static CRenderer* m_pRenderer;			// �����_���[�ւ̃|�C���^
	static CKeyboard* m_pKeyboard;			// �L�[�{�[�h�ւ̃|�C���^
	static CCamera* m_pCamera;				// �J�����ւ̃|�C���^
	static CLight* m_pLight;				// ���C�g�ւ̃|�C���^
	static CTexture* m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	static CSound* m_pSound;				// �T�E���h�ւ̃|�C���^
	static CFade* m_pFade;					// �t�F�[�h�ւ̃|�C���^
	static CDebugProc* m_pDebug;			// �f�o�b�N�\���ւ̃|�C���^
};

#endif // !_MANAGER_H_
