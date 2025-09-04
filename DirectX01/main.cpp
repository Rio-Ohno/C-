//============================================================
//
//render[main.cpp]
//Author:Rio Ohno
//
//============================================================

//インクルード
#include"main.h"
#include"manager.h"
#include <crtdbg.h>

// グローバル変数宣言
int g_nCountFPS = 0;

//=========================================================
//メイン関数
//=========================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//メモリーリーク検知用フラグ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	CManager* pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),              //WNDCLASSEXのメモリーサイズ
		CS_CLASSDC,                      //ウィンドウのスタイル
		WindowProc,                      //ウィンドウプロシージャ
		0,                               //0にする（通常はしない）
		0,                               //0にする（通常はしない）
		hInstance,                       //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),  //タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),      //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),        //クライアント領域の背景色
		NULL,                            //メニューバー
		CLASS_NAME,                      //ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),  //ファイルのアイコン
	};

	HWND hWnd;//ウィンドウハンドル
	MSG msg;//メッセージを格納する

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//画面サイズの構造体

	DWORD dwCurrentTime;//現在時刻
	DWORD dwExecLastTime;//最後に処理した時刻
	DWORD dwFrameCount;												//フレームカウント
	DWORD dwFPSLastTime;											//最後に計測した時刻

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成 
	hWnd = CreateWindowEx
	   (0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right-rect.left),
		(rect.bottom-rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//マネージャの生成
	pManager = new CManager;

	//マネージャの初期化処理
	pManager->Init(hInstance,hWnd, TRUE);

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwFrameCount = 0;
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd,nCmdShow);//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);       //クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();         //現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを加算
				g_nCountFPS = ((dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime));
				dwFPSLastTime = dwCurrentTime;							//FPSを計測した時刻を保存

				dwFrameCount = 0;										//フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;    //処理開始の時刻[現在時刻]を保存

				//更新処理
				pManager->Update();

				//描画処理
				pManager->Draw();
			}
		}
	}

	//マネージャの破棄
	if (pManager != NULL)
	{
		//マネージャの終了処理
		pManager->Uninit();

		delete pManager;
		pManager = NULL;
	}

	//分解脳を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch(uMsg)
	{
	case WM_DESTROY://ウィンドウ破棄のメッセージ

		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			nID = MessageBox(hWnd, "終了しますか?", "", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}

			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=========================================================
// FPSの取得
//=========================================================
int GetFPS(void)
{
	return g_nCountFPS;
}