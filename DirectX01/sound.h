//====================================================
//
// サウンド処理 [sound.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _SOUND_H_
#define _SOUND_H_

// インクルード
#include "main.h"

// サウンドクラス
class CSound
{
public:

	// サウンド一覧
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// サウンド情報の構造体定義
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
	} SOUNDINFO;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	static void StopAll(void);


private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);		// チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);		// チャンクデータの読み込み

	static IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];										// ソースボイス
	IXAudio2* m_pXAudio2;																				// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;															// マスターボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];																// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];																// オーディオデータサイズ
};

#endif
