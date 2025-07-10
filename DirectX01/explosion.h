//====================================================
//
// 爆発[explosion.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

// インクルード
#include"main.h"
#include"object2D.h"

// マクロ定義
#define EXPLOSION_ANIME_SPAN (4)

// 爆発クラス
class CExplosion :public  CObject2D
{
public:
	//CExplosion();
	CExplosion(int nPriority = 4);
	~CExplosion();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Anime(int nDiviX, int nDiviY);

	static HRESULT Load(void);
	static void UnLoad(void);

	static CExplosion* Create(D3DXVECTOR3 pos, float fRadius);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nCntAnime;			// フレームカウンター
	int m_nPatternAnime;		// パターンカウンター
};

#endif // !_EXPLOSION_H_
