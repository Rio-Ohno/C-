//====================================================
//
// 影[shadow.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

// インクルード
#include"main.h"
#include"object3D.h"

class CShadow:public CObject3D
{
public:
	CShadow();
	~CShadow();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);

private:
	static int m_nTexture;
};

#endif // !_SHADOW_H_
