//====================================================
//
// �T�E���h���� [sound.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _SOUND_H_
#define _SOUND_H_

// �C���N���[�h
#include "main.h"

// �T�E���h�N���X
class CSound
{
public:

	// �T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// �T�E���h���̍\���̒�`
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
	} SOUNDINFO;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	static void StopAll(void);


private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);		// �`�����N�̃`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);		// �`�����N�f�[�^�̓ǂݍ���

	static IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];										// �\�[�X�{�C�X
	IXAudio2* m_pXAudio2;																				// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;															// �}�X�^�[�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];																// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];																// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
