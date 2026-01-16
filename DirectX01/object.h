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

//マクロ定義
#define PRIORITY (8)					// オブジェクトの描画優先順位
#define MAX_OBJECT (256)

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

	//CObject();
	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	virtual void SetPos(const D3DXVECTOR3 pos) = 0;
	virtual void SetRot(const D3DXVECTOR3 rot) = 0;

	virtual D3DXVECTOR3 GetPos(void) = 0;
	virtual float GetWidth(void) = 0;
	virtual float GetHeight(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetType(TYPE type);
	void SetPriority(int nPriority) { m_nPriority = nPriority; };

	TYPE GetType(void);
	int GetPriority(void) { return m_nPriority; };

	static void SetPause(bool bPause) { m_bPause = bPause; };
	static bool GetPause(void) { return m_bPause; };

	static CObject* GetObject(int nPriority, int nindx);
	static int GetNumAll(void);

protected:
	void Release(void);

private:

	static void Delete(int nPriority);


	static CObject* m_pTop[PRIORITY];
	static CObject* m_pCur[PRIORITY];
	static int m_nNumAll;					// オブジェクト総数
	static bool m_bPause;					// ポーズフラグ
	CObject* m_pPrev;
	CObject* m_pNext;
	TYPE m_type;							// 種類
	int m_nPriority;						// 優先順位
	bool m_bDeath;							// 死亡フラグ
};

#endif // !_OBJECT_H_
