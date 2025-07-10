//============================================================
//
//render[main.cpp]
//Author:Rio Ohno
//
//============================================================

//�C���N���[�h
#include"main.h"
#include"manager.h"
#include <crtdbg.h>

//=========================================================
//���C���֐�
//=========================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//�������[���[�N���m�p�t���O
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	CManager* pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),              //WNDCLASSEX�̃������[�T�C�Y
		CS_CLASSDC,                      //�E�B���h�E�̃X�^�C��
		WindowProc,                      //�E�B���h�E�v���V�[�W��
		0,                               //0�ɂ���i�ʏ�͂��Ȃ��j
		0,                               //0�ɂ���i�ʏ�͂��Ȃ��j
		hInstance,                       //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),  //�^�X�N�o�[�A�C�R��
		LoadCursor(NULL,IDC_ARROW),      //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),        //�N���C�A���g�̈�̔w�i�F
		NULL,                            //���j���[�o�[
		CLASS_NAME,                      //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),  //�t�@�C���̃A�C�R��
	};

	HWND hWnd;//�E�B���h�E�n���h��
	MSG msg;//���b�Z�[�W���i�[����

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//��ʃT�C�Y�̍\����

	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExecLastTime;//�Ō�ɏ�����������

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐� 
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

	//�}�l�[�W���̐���
	pManager = new CManager;

	//�}�l�[�W���̏���������
	pManager->Init(hInstance,hWnd, TRUE);

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	
	//�E�B���h�E�̕\��
	ShowWindow(hWnd,nCmdShow);//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);       //�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();         //���ݎ������擾

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;    //�����J�n�̎���[���ݎ���]��ۑ�

				//�X�V����
				pManager->Update();

				//�`�揈��
				pManager->Draw();
			}
		}
	}

	//�}�l�[�W���̔j��
	if (pManager != NULL)
	{
		//�}�l�[�W���̏I������
		pManager->Uninit();

		delete pManager;
		pManager = NULL;
	}

	//����]��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY://�E�B���h�E�j���̃��b�Z�[�W

		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(hWnd);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}