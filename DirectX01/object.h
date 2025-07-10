//====================================================
//
// �I�u�W�F�N�g[object.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//�C���N���[�h
#include"main.h"

//�}�N����`
#define PRIORITY (8)					// �I�u�W�F�N�g�̕`��D�揇��
#define MAX_OBJECT (256)

class CObject
{
public:

	typedef enum
	{
		TYPE_NONE=0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_EXPLOSION,
		TYPE_BG,
		TYPE_UI,
		TYPE_MAX
	}TYPE;

	//CObject();
	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	virtual void SetPos(const D3DXVECTOR3 pos) = 0;
	virtual void SetRot(const D3DXVECTOR3 rot) = 0;

	virtual D3DXVECTOR3 GetPos(void) = 0;
	virtual float GetWidth(void) = 0;
	virtual float GetHeight(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static void Delete(int nPriority);

	void SetType(TYPE type);
	TYPE GetType(void);

	static CObject* GetObject(int nPriority, int nindx);
	static int GetNumAll(void);

protected:
	void Release(void);

private:
	static CObject* m_pTop[PRIORITY];
	static CObject* m_pCur[PRIORITY];
	static int m_nNumAll;					// �I�u�W�F�N�g����
	CObject* m_pPrev;
	CObject* m_pNext;
	TYPE m_type;							// ���
	int m_nPriority;						// �D�揇��
	bool m_bDeath;							// ���S�t���O
};

#endif // !_OBJECT_H_
