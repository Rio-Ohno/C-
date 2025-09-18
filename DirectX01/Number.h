//==================================================== 
// 
// 数値の管理　[Number.h]
// Author: Rio Ohno
// 
//==================================================== 
#ifndef _NUMBER_H_
#define _NUMBER_H_

// インクルード
#include"main.h"

// 数字クラス
class CNumber
{
public:

	CNumber();
	~CNumber();

	void Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXCOLOR GetColor(void);
	float GetWidth(void) { return m_fWidth; };
	float GetHeight(void) { return m_fHeight; };

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetColor(D3DXCOLOR col);

	static CNumber* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

	void BindTexindx(int indx) { m_Texindx = indx; };
	int SetNum(int nNumber, int nDight);

private:
	int m_Texindx;								// テクスチャインデックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;							// 位置
	float m_fWidth;								// 幅
	float m_fHeight;							// 高さ
};

#endif