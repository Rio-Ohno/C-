//====================================================
//
//ポーズ処理[pause.h]
//Author:Rio Ohno
//
//====================================================

#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "object2D.h"

// マクロ定義
#define NUM_POLY (4)		// ポリゴン数

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

	static CObject2D* m_apObject2D[NUM_POLY];
	MENU m_mode;
	int m_nCntMenu;
};
#endif // !PAUSE_H_

