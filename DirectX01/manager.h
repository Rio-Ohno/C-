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
#include"player.h"
#include"BG.h"
#include"enemy.h"
#include"light.h"
#include"camera.h"
#include"texture.h"
#include"motion.h"
#include"score.h"
#include"object3D.h"

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

	static CRenderer* GetRenderer(void);
	static CKeyboard* GetKeyboard(void);
	static CPlayer* GetPlayer(void);
	static CEnemy* GetEnemy(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);
	static CTexture* GetTexture(void);
	static CLoadMotion* GetLoadMotion(void);
	static CScore* GetScore(void);
	static CObject3D* GetObject3D(void);

private:
	static CRenderer* m_pRenderer;			// �����_���[�ւ̃|�C���^
	static CKeyboard* m_pKeyboard;			// �L�[�{�[�h�ւ̃|�C���^
	static CBGManager* m_BGManager;
	static CPlayer* m_pPlayer;				// �v���C���[�ւ̃|�C���^
	static CEnemy* m_pEnemy[MAX_ENEMY];
	static CCamera* m_pCamera;				// �J�����ւ̃|�C���^
	static CLight* m_pLight;				// ���C�g�ւ̃|�C���^
	static CTexture* m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	static CLoadMotion* m_pLoadMotion;		// ���[�V�����Ǎ��ւ̃|�C���^
	static CScore* m_pScore;				// �X�R�A�ւ̃|�C���^
	static CObject3D* m_pObjecct3D;
};

#endif // !_MANAGER_H_
