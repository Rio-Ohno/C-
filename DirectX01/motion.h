//====================================================
//
// ���[�V����[motion.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _MOTION_H_
#define _MOTION_H_

// �C���N���[�h
#include "main.h"
#include"loadtxt.h"
#include"key.h"
#include"model.h"
#include <string.h>
#include <stdio.h>

// �}�N����`
#define MAX_PART (20)
#define MAX_MOTION (8)

// ���[�V�����N���X
class CMotion
{
public:
	CMotion();
	~CMotion();

	HRESULT Init(CMotion* pMotion);
	void Uninit(void);
	void Set(int nType);
	void Update(void);
	bool isFinish(void);

	CModel** GetModel(void) { return m_apModel; };
	CInfo** GetInfo(void) { return m_apInfo; };
	int GetNumModel(void) { return m_nNumModel; };
	int GetNumKey(void) { return m_nNumKey; };

	void SetInfo(CInfo** pInfo);
	void SetModel(CModel** pModel);
	void SetNumModel(int NumModel) { m_nNumModel = NumModel; };
	void SetNumKey(int NumKey) { m_nNumKey = NumKey; };

private:
	CModel* m_apModel[MAX_PART];					// �p�[�c�̃��f���ւ̃|�C���^
	CInfo* m_apInfo[MAX_MOTION];					// ���[�V�������ւ̃|�C���^
	D3DXVECTOR3 m_OffsetPos[MAX_PART];
	D3DXVECTOR3 m_OffsetRot[MAX_PART];
	int m_nNumModel;								// �p�[�c���f����
	int m_nNumKey;									// �L�[��
	bool m_bFinish;									// �I���������ǂ���

	int m_nType;									// ��ނ̐ݒ�
	int m_nKey;										// ���݂̃L�[
	int m_nNextKey;									// �O�̃L�[
	int m_nCounter;
};

// ���[�V�����Ǎ��N���X
class CLoadMotion
{
public:
	CLoadMotion();
	~CLoadMotion();

	void LoadMotionTXT(const char* pFileName, CMotion* pMotion);
	void LoadMotion(FILE* pFile, CMotion* pMotion);
	void LoadCharacterInfo(FILE* pFile, CMotion* pMotion);
	CModel* LoadModel(FILE* pFile, CMotion* pMotion);
	CInfo* LoadInfo(FILE* pFile);
	CKeyInfo* LoadKeyInfo(FILE* pFile);
	CKEY* LoadKey(FILE* pFile);

	static CMotion* Load(const char* pFileName, CMotion* pMotion);

private:
	static CLoadtxt* m_pLoadtxt;					// �e�L�X�g�Ǎ��ւ̃|�C���^

	int m_nNumParts;								// �p�[�c��

	int m_nModelCount;
	int m_nKeyCount;								// �p�[�c�̃J�E���g
	int m_nKeyInfoCount;							// �L�[���̃J�E���g
	int m_nInfoCount;								// ���[�V�������̃J�E���g
	char m_PartPath[MAX_PART][64];					// �p�[�c���f���̃p�X

	float m_fSpeed;									// �ړ���
	float m_fJump;									// �W�����v��
	float m_fRadiusShaow;							// �e�̔��a
};
#endif // !_MOTION_H_
