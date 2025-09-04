//====================================================
//
// �Q�[���V�[������ [game.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _GAME_H_
#define _GAME_H_

// �C���N���[�h
#include "main.h"
#include"scene.h"
#include"Time.h"
#include"player.h"
#include"score.h"
#include"object3D.h"
#include"pause.h"
#include"noteManager.h"
#include"shockManager.h"

// �}�N����`
#define NOTE_SPAWN (90)

class CGame :public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer* GetPlayer(void);
	static CScore* GetScore(void);
	static CObject3D* GetObject3D(void);
	static CTime* GetTime(void);
	static CNoteManager* GetNoteManager(void) { return m_pNoteManager; };
	static CShockManager* GetShockManager(void) { return m_pShockManager; }
	static bool GetPause(void) { return m_bPause; };
	static void SetPause(bool Use);

	bool isPause(void);

private:
	static CPlayer* m_pPlayer;				// �v���C���[�ւ̃|�C���^
	static CScore* m_pScore;				// �X�R�A�ւ̃|�C���^
	static CObject3D* m_pObjecct3D;
	static CTime* m_pTime;
	static CPause* m_pPause;
	static CNoteManager* m_pNoteManager;
	static CShockManager* m_pShockManager;

	static bool m_bFinish;					// �Q�[���I���t���O
	static bool m_bPause;					// �|�[�Y�t���O
	int m_nCntFinFream;						// �Q�[���I������t�F�[�h���n�܂�܂ł̃t���[��
	int m_nCntNoteSpan;						// �������Ăяo�����܂ł̃t���[��
};
#endif // !_GAME_H_

