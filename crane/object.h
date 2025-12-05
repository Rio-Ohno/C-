//====================================================
//
// オブジェクト[object.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//インクルード
#include"main.h"

class CObject
{
public:

	typedef enum
	{
		TYPE_NONE=0,
		TYPE_SCENE,
		TYPE_MANAGER,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_EXPLOSION,
		TYPE_EFFECT,
		TYPE_BG,
		TYPE_UI,
		TYPE_PAUSE,
		TYPE_MAX
	}TYPE;

	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	// セッター
	void SetType(TYPE type) { m_type = type; };
	void SetPriority(int nPriority) { m_nPriority = nPriority; }

	// ゲッター
	TYPE GetType(void) { return m_type; };
	int GetPriority(void) { return m_nPriority; }
	static int GetNumAll(void) { return m_nNumAll; };

	static void SetPause(bool bPause) { m_bPause = bPause; };
	static bool GetPause(void) { return m_bPause; };

protected:
	void Release(void);

	// constexpr
	static constexpr int MAX_OBJECT = 256;	// 最大オブジェクト数

private:

	// constexpr
	static constexpr int PRIORITY = 8;		// 描画順

	static void Delete(int nPriority);		// オブジェクトの破棄

	static CObject* m_pTop[PRIORITY];
	static CObject* m_pCur[PRIORITY];
	static int m_nNumAll;					// オブジェクト総数
	static bool m_bPause;					// ポーズフラグ
	CObject* m_pPrev;						// 前のオブジェクト
	CObject* m_pNext;						// 次のオブジェクト
	TYPE m_type;							// 種類
	int m_nPriority;						// 優先順位
	bool m_bDeath;							// 死亡フラグ
};

#endif // !_OBJECT_H_
