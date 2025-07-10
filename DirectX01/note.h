//====================================================
//
// 音符[note.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include"main.h"
#include"objectX.h"

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

	bool isColision(D3DXVECTOR3 pos, float fRadius);

private:
	int m_nCounter;
	D3DXVECTOR3 m_vtxMax;
	D3DXVECTOR3 m_vtxMin;
	D3DXVECTOR3 m_size;
};