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
#include "function.h"
#include <vector>
#include <memory>

// 前方宣言
class CMeshField;		// メッシュフィールド
class CFiledManager;	// フィールドマネージャー
class CWall;			// 壁
class CPlayer;			// プレイヤー
class CTimeManager;		// タイムマネージャー
class CPrizemanager;	// プライズマネージャー
class CHole;			// ゲットホール
class CPauseManager;	// ポーズマネージャー
class CScore;			// スコア

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

	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CMeshField* GetField(void) { return m_pFiled; }
	static CHole* GetHole(void) { return m_pHole; }
	static CFiledManager* GetFieldManager(void) { return m_FieldManager; }
	static CScore* GetScore(void) { return m_pScore; }
	static CPrizemanager* GetPrizeManager(void) { return m_PrizeManager; }
	static CWall** GetApWall(void) { return m_apWall; }

	static void AddFunction(std::unique_ptr<CFunctionBase> function) { m_apFunction.push_back(std::move(function)); }

	// constexpr
	static constexpr int NUM_WALL = 5;// 壁の数

private:

	static CWall* m_apWall[NUM_WALL];									// 壁
	static CPlayer* m_pPlayer;											// プレイヤー
	static CMeshField* m_pFiled;										// フィールド
	static CFiledManager* m_FieldManager;								// フィールドマネージャー
	static CTimeManager* m_pTimeM;										// タイムマネージャー
	static CScore* m_pScore;											// スコア
	static CPrizemanager* m_PrizeManager;								// プライズ(敵)マネージャー
	static CHole* m_pHole;												// ゲットホール
	static CPauseManager* m_pPause;										// ポーズマネージャー
	static std::vector<std::unique_ptr<CFunctionBase>> m_apFunction;	// ファンクション
};
#endif