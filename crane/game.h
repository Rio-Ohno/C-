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
class CPlayer;			// プレイヤー
class CTimeManager;
class CPrizemanager;	// プライズマネージャー
class CHole;			// ゲットホール

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
	static CPrizemanager* GetPrizeManager(void) { return m_PrizeManager; }

	static void AddFunction(std::unique_ptr<CFunctionBase> function) { m_apFunction.push_back(std::move(function)); }

private:
	static CPlayer* m_pPlayer;
	static CMeshField* m_pFiled;
	static CFiledManager* m_FieldManager;
	static CTimeManager* m_pTimeM;
	static CPrizemanager* m_PrizeManager;
	static CHole* m_pHole;
	static std::vector<std::unique_ptr<CFunctionBase>> m_apFunction;
};
#endif