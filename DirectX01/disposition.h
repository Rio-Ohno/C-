//====================================================
//
// �z�u�G�f�B�^���� [disposition.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _DISPOSITION_H_
#define _DISPOSITION_H_

#define NUM_OBJECT (30)

// �C���N���[�h
#include"main.h"
#include"scene.h"
#include"object3D.h"

class CDisposition :public CScene
{
public:

	CDisposition();
	~CDisposition();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void Save(void);
	static void Load(void);

private:

	static CObject3D* m_pObjecct3D;
};

#endif // !_DISPOSITION_H_