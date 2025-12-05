//====================================================
// 
// ゲームシーン[game.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _GAME_H_
#define _GAME_H_

// インクルード
#include"scene.h"

// 前方宣言
class CMeshField;		// メッシュフィールド
class CFiledManager;	// フィールドマネージャー
class CPlayer;			// プレイヤー

// テストシーンクラス
class CGame :public CScene
{
public:

	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshField* GetField(void) { return m_pFiled; }
	static CFiledManager* GetFieldManager(void) { return m_FieldManager; }

private:
	static CPlayer* m_pPlayer;
	static CMeshField* m_pFiled;
	static CFiledManager* m_FieldManager;
};
#endif