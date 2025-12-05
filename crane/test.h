//====================================================
// 
// テストシーン[test.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _TEST_H_
#define _TEST_H_

// インクルード
#include"scene.h"

// 前方宣言
class CMeshField;		// メッシュフィールド
class CFiledManager;	// フィールドマネージャー

// テストシーンクラス
class CTest :public CScene
{
public:

	CTest();
	~CTest();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshField* GetField(void) { return m_pFiled; }
	static CFiledManager* GetFieldManager(void) { return m_FieldManager; }

private:
	static CMeshField* m_pFiled;
	static CFiledManager* m_FieldManager;
};
#endif