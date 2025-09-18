//====================================================
//
// �����i�A�C�e���j�Ǘ����� [noteManager.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _NOTEMANAGER_H_
#define _NOTEMANAGER_H_

// �C���N���[�h
#include"main.h"
#include"object.h"
#include"notePattern.h"
#include"note.h"

// �����̊Ǘ��N���X
class CNoteManager
{
public:
	CNoteManager();
	~CNoteManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Load(void);
	void Spawn(void);

	static void AddNum(void) { m_nNumNote++; };
	static void DefNum(void) { m_nNumNote--; };
	static int GetNum(void) { return m_nNumNote; };

	static CNoteManager* Create(void);

private:
	static int m_nNumNote;// ����
	static CNote* m_apNote[NUM_NOTE];
	static CNotePattern* m_pPattern;
};
#endif // !_NOTEMANAGER_H_

