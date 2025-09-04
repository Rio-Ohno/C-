//====================================================
//
// 音符[note.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _NOTE_H_
#define _NOTE_H_

// インクルード
#include"main.h"
#include"objectX.h"

// 音符のクラス
class CNote :public CObjectX
{
public:
	CNote();
	~CNote();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNote* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	bool isColision(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRadius);

private:
	int m_nCounter;
	D3DXVECTOR3 m_vtxMax;
	D3DXVECTOR3 m_vtxMin;
	D3DXVECTOR3 m_size;
};

#endif // !_NOTE_H_