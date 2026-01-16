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
		SOUND_LABEL_TEST = 0,
		SOUND_LABEL_WAVE,
		SOUND_LABEL_DEBUG,
		SOUND_LABEL_GAME,
		SOUND_LABEL_RESULT,
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// サウンド情報の構造体定義
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
		float fBPM;				// テンポ
		float fCurrentBeat;		// 現在の拍
	} SOUNDINFO;


	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	/*static*/ void StopAll(void);

	float GetPlaybackTempo(SOUND_LABEL label);
	bool isBeatTrigger(SOUND_LABEL label, float fBeatInterval);


private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);		// チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);		// チャンクデータの読み込み
	bool GetLooped(SOUND_LABEL label);																	// ループ再生をしているときに終わったかどうか

	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];										// ソースボイス
	IXAudio2MasteringVoice* m_pMasteringVoice;													// マスターボイス
	IXAudio2* m_pXAudio2;																		// XAudio2オブジェクトへのインターフェイス

	BYTE* m_apDataAudio[SOUND_LABEL_MAX];														// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];														// オーディオデータサイズ
	UINT32 m_aPrevSamplesPlayed[SOUND_LABEL_MAX];												// 前回の再生サンプル数
	UINT32 m_aPrevBeatIndex[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX];
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data\\SOUND\\BGM\\matsurinohi.wav", -1, 0.0f, 0.0f},	// テスト

		{"data\\SOUND\\SE\\pi001.wav", 0, 0.0f, 0.0f},			// 波発生時
		{"data\\SOUND\\SE\\pi002.wav",0,0.0f,0.0f},				// デバック用効果音

		{"data\\SOUND\\BGM\\BGM001.wav", -1, 135.0f, 0.0f},		// ゲームBGM
		{"data\\SOUND\\BGM\\memento.wav", -1, 0.0f, 0.0f},		// リザルトBGM
	};

	int m_nCntLoop[SOUND_LABEL_MAX];															// ループ回数
};

#endif
