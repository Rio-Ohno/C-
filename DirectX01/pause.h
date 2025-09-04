//====================================================
//
//�|�[�Y����[pause.h]
//Author:Rio Ohno
//
//====================================================

#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "object2D.h"

// �}�N����`
#define NUM_POLY (4)		// �|���S����

class CPause
{
public:

	//�|�[�Y���j���[
	typedef enum
	{
		MENU_CONTINUE = 0,	// �Q�[���ɖ߂�
		MENU_RETRY,			// �Q�[������蒼��
		MENU_QUIT,			// �^�C�g���ɖ߂�
		MENU_MAX
	}MENU;

	CPause();
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause* Create(void);

private:

	static CObject2D* m_apObject2D[NUM_POLY];
	MENU m_mode;
	int m_nCntMenu;
};
#endif // !PAUSE_H_

