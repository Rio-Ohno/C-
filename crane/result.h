//====================================================
// 
// リザルトシーン[result.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _RESULT_H_
#define _RESULT_H_

// インクルード
#include "scene.h"

// 前方宣言
class CObject2D;	// 2Dポリゴン
class CScore;		// スコア
class CMeshSphere;	// メッシュスフィア(球)

// リザルトクラス
class CResult :public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static CScore* m_pScore;		// スコア
	static CMeshSphere* m_pSphere;	// 空
	CObject2D* m_pObject2D;
};
#endif