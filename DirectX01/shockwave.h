//====================================================
// 
// 衝撃波[shockwave.h]
// Author:Rio Ohno
// 
//==================================================== 

#ifndef _SHOCKWAVE_H_
#define _SHOCKWAVE_H_

// インクルード
#include"main.h"
#include"object.h"

class CShockwave:public CObject
{
public:
	CShockwave();
	~CShockwave();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DXCOLOR col,bool bTransparent);
	void SetVanish(int nfream);
	void SetCulling(bool bUse) { m_bCulling = bUse; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };
	bool isCulling(void) { return m_bCulling; };
	bool isCollision(D3DXVECTOR3 pos, float fRadius, float fUnder, float fTop);

	void Spread(void);						// 広げる演出処理
	void Vanish(void);						// 消える演出処理

	static CShockwave* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY,int nLife, float fWidth, float fHeight, float fRadius, float fSpeed, bool bCulling, bool bCollision);

private:

	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// インデックスバッファ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	int m_nTexindx;							// テクスチャインデックス
	int m_nDiviX;							// 分割数(x軸)
	int m_nDiviY;							// 分割数(y軸)
	int m_nMaxVtx;							// 最大頂点数
	int m_nPolyNum;							// ポリゴン数
	int m_nLife;							// 寿命
	int m_nVanishFream;						// 消えるフレーム数(保存用)
	int m_nVanishCnt;						// 消えるフレームカウンター
	float m_fHeight;						// 高さ
	float m_fWidth;							// 幅
	float m_fRadius;						// 半径
	float m_fSpeed;							// 広がるスピード
	bool m_bCulling;						// カリングするかどうか
	bool m_bCollision;						// 当たり判定をとるかどうか
	bool m_bVanish;							// 消える演出を入れるかどうか
};

#endif // !_SHOCKWAVE_H_