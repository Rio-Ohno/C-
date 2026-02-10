//====================================================
//
// タイトルシーン　[title.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _TITLE_H_
#define _TITLE_H_

// インクルード
#include "scene.h"
#include "function.h"
#include <vector>
#include <memory>

// 前方宣言
class CMeshSphere;		// 球体メッシュ
class CMeshField;		// メッシュフィールド
class CObject2D;		// ポリゴン
class CPrizemanager;	// プライズマネージャー
class CFunctionBase;	// ファンクション基底クラス
class CPlayer;			// プレイヤー

// タイトルシーンクラス
class CTitle :public CScene
{
public:
	CTitle();
	~CTitle();

	typedef enum
	{
		UI_POP = 0,
		UI_TITLE,
		UI_ENTER,
		UI_MAX
	}UI;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	static CPrizemanager* GetPrizemanager(void) { return m_pPrizeManager; }
	static CMeshField* GetField(void) { return m_pField; }

private:

	static void AddFunction(std::unique_ptr<CFunctionBase> function) { m_apFunction.push_back(std::move(function)); }
	void UpdateUI_ENTER(void);

	// constexpr
	static constexpr float CAMERA_TURN = 0.0009f;	// 回転量
	static constexpr int NUM_POLY = 3;				// ポリゴン数
	static constexpr int BLINKING_FREAM = 120;		// 点滅にかかるフレーム

	static CMeshSphere* m_pSphere;			// 空
	static CMeshField* m_pField;			// メッシュフィールド
	static CPrizemanager* m_pPrizeManager;	// プライズマネージャー
	static CPlayer* m_pPlayer;				// プレイヤー

	static std::vector<std::unique_ptr<CFunctionBase>> m_apFunction;	// ファンクション
	CObject2D* m_pObject2D[NUM_POLY];		// UIポリゴン数
	int m_nCntFream;						// フレームカウンタ
};

#endif