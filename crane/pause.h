//====================================================
//
//ポーズ処理[pause.h]
//Author:Rio Ohno
//
//====================================================

#ifndef _PAUSE_H_
#define _PAUSE_H_

// インクルード
#include "main.h"
#include "object2D.h"

// ポーズ
class CPause
{
public:

	//ポーズメニュー
	typedef enum
	{
		MENU_CONTINUE = 0,	// ゲームに戻る
		MENU_RETRY,			// ゲームをやり直す
		MENU_QUIT,			// タイトルに戻る
		MENU_MAX
	}MENU;

	CPause();
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause* Create(void);

private:

	// constexpr
	static constexpr int NUM_POLY = 4;

	static CObject2D* m_apObject2D[NUM_POLY];
	MENU m_mode;
	int m_nCntMenu;
};

// ポーズマネージャー
class CPauseManager
{
public:
	CPauseManager();
	~CPauseManager();

	void Init(void);
	void Uninit(void);
	void Update(void);

	void isPause(void);

	static bool GetPause(void) { return m_bPause; }
	static void SetPause(bool bPause) { m_bPause = bPause; }

private:
	static CPause* m_pPause;	// ポーズフラグ
	static bool m_bPause;		// ポーズポインタ
};

#endif // !PAUSE_H_