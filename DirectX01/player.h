//====================================================
//
// �v���C���[[player.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�C���N���[�h
#include"main.h"
#include"object.h"
#include"model.h"
#include"shadow.h"
#include"motion.h"

// �}�N����`
#define ANIME_SPAN (40)					// �X�v���C�g��؂�ւ��銴�o(�t���[��)
#define PLAYER_SPEED ((float)0.5f)
#define NUM_MODEL (15)
#define MOTIONFILE_PLAYER ((const char*)"data/MODEL/player/motion.txt")

//�v���C���[�N���X
class CPlayer:public CObject
{
public:

	typedef enum
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_INVINCIBLE,
		STATE_MAX
	}State;

	//CPlayer();
	CPlayer(int nPriority = 3);
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//void SetState(State state);
	//State GetState(void);

	void Action(void);

	static HRESULT Load(void);
	static void UnLoad(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetMotion(const char* pFileName);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };
	D3DXVECTOR3 GetSize(void) { return m_size; };

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	static CMotion* m_pMotion;				// ���[�V�����ւ̃|�C���^
	static CLoadMotion* m_pLoadMotion;
	//static int m_nIndxTex;				// �e�N�X�`���ւ̃C���f�b�N�X
	D3DXVECTOR3 m_move;						// �ړ���
	State m_state;							// ���
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_posOld;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_DestRot;					// �����̖ڕW
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXVECTOR3 m_vtxMax;					// �ő�̒��_�ʒu
	D3DXVECTOR3 m_vtxMin;					// �ŏ��̒��_�ʒu
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	CShadow* m_pShadow;						// �e�ւ̃|�C���^
	int nNumModel;							// ���f���̑���
	float m_fSpeed;

};

#endif // !_PLAYER_H_
