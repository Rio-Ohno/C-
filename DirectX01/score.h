//==================================================== 
// 
// スコア　[score.h]
// Author: Rio Ohno
// 
//==================================================== 
#ifndef _SCORE_H_
#define _SCORE_H_

// マクロ定義
#define MAX_SCOREDIGHT (6)		// 最大桁数

// インクルード
#include"main.h"
#include"Number.h"
#include"object.h"

class CScore:public CObject
{
public:
	CScore(int nPriority = 7);
	~CScore();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos) {};
	void SetRot(const D3DXVECTOR3 rot) {};
	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3(); };

	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static HRESULT Load(void);
	static void UnLoad(void);

	static CScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

	void SetScore(void);
	static void Add(const int nAdd);
	static void Diff(const int nDiff);

private:
	 CNumber* m_apNumber[MAX_SCOREDIGHT];
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static int m_nScore;// スコア
};
#endif // !_SCORE_H_

