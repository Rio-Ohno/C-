//====================================================
//
// ゲームシーン処理 [game.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _GAME_H_
#define _GAME_H_

// インクルード
#include "main.h"
#include"scene.h"
#include"Time.h"
#include"player.h"
#include"object3D.h"
#include"pause.h"
#include"score.h"
#include"wall.h"
#include"meshSphere.h"
#include"noteManager.h"
#include"shockManager.h"

// マクロ定義
#define NOTE_SPAWN (90)
#define WAVE_SPAWN (1800)
#define START_FREAM (180)
#define FINISH_REAM (120)

// ゲームシーンクラス
class CGame :public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Start(void);
	void Finish(void);
	void NoteSpawm(void);
	void WaveSpawn(void);

	static CPlayer* GetPlayer(void);
	static CObject3D* GetObject3D(void);
	static CScore* GetScore(void);
	static CTime* GetTime(void);
	static CNoteManager* GetNoteManager(void) { return m_pNoteManager; };
	static CShockManager* GetShockManager(void) { return m_pShockManager; }
	static bool GetPause(void) { return m_bPause; };
	static void SetPause(bool Use);

	bool isPause(void);

private:
	static CPlayer* m_pPlayer;				// プレイヤーへのポインタ
	static CObject3D* m_pObjecct3D;
	static CScore* m_pScore;				// スコアへのポインタ
	static CTime* m_pTime;
	static CTime* m_pStartTime;
	static CPause* m_pPause;
	static CNoteManager* m_pNoteManager;
	static CShockManager* m_pShockManager;
	CMeshSphere* m_pSphere;
	CWall* m_apWall[8];

	static bool m_bFinish;					// ゲーム終了フラグ
	static bool m_bStart;					// ゲーム開始フラグ
	static bool m_bPause;					// ポーズフラグ
	int m_nCntFreamFin;						// ゲーム終了からフェードが始まるまでのフレーム
	int m_nCntFreamTimeUP;					// 色変えフレームカウンタ
	int m_nCntNoteSpan;						// 音符が呼び出されるまでのフレーム
	int m_nCntWaveSpan;						// 衝撃波が設定されるまでのフレーム
};
#endif // !_GAME_H_

