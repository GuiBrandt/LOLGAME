//=============================================================================
// lolgame.cpp
//
//      A game engine for creating real games with LOLCODE :D
//
//  @author     Brandt
//  @version    1.0
//  @date       2018-06-23
//=============================================================================
#ifndef UNICODE
	#define UNICODE
#endif

#include <windows.h>
#include <shlwapi.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <string>

#include "include/Scene.hpp"
#include "include/BitmapManager.hpp"
#include "include/LOLCODE.hpp"

#pragma comment(lib, "ole32")
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "kernel32")
#pragma comment(lib, "shlwapi")
#pragma comment(lib, "windowscodecs")

using namespace std;
//=============================================================================
// Constants
//=============================================================================
#define WINDOW_CLASS_NAME   TEXT("LOLGAMEWindow")
#define WINDOW_TITLE        TEXT("LOLGAME")
#define WINDOW_STYLEEX      WS_EX_LEFT
#define WINDOW_STYLE        WS_OVERLAPPEDWINDOW & (~WS_SIZEBOX)
#define WINDOW_WIDTH        640
#define WINDOW_HEIGHT       480
//=============================================================================
// Prototypes
//=============================================================================

// Game main procedure
DWORD WINAPI LolGameMain ( LPVOID );

// Main window message handling procedure
LRESULT CALLBACK WindowProc ( HWND, UINT, WPARAM, LPARAM );

//=============================================================================
// WinMain
//
//      Application entry point
//
// hInstance        {HINSTANCE} : Current module instance handle
// hPrevInstance    {HINSTANCE} : Caller module instance handle
// lpCmdLine        {LPTSTR}    : The calling command line
// nCmdShow         {int}       : Whether the window should be visible or not
//=============================================================================
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	cout << "I DOINGS LOLGAME SETUP!" << endl;

	// Seeds rand() with the current time
	cout << "GETTIN' RANDOM SEEDZ..." << endl;
	srand (time(NULL));

	// Registers the Window Class
	cout << "WINDOWZ CLAS IS BEIN MAEK..." << endl;
	LPTSTR class_name = WINDOW_CLASS_NAME;

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));
	wc.style = CS_OWNDC;
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = class_name;

	BOOL result = RegisterClass(&wc);

	if (!result)
	{
		cerr << "FML WINDOWZ CLAS GONE BAD: " << GetLastError() << endl;

		LPTSTR errorMessage;
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&errorMessage,
			0,
			NULL
		);

		cerr << errorMessage;

		return -1;
	}

	// Creates the window
	cout << "I CREATES WINDOW..." << endl;
	HWND hwnd = CreateWindowEx(
		WINDOW_STYLEEX,

		class_name,
		WINDOW_TITLE,
		WINDOW_STYLE,

		CW_USEDEFAULT, CW_USEDEFAULT, 
		WINDOW_WIDTH, WINDOW_HEIGHT,

		NULL, NULL,
		hInstance, NULL
	);

	// Checks for errors
	if (hwnd == NULL)
	{
		cerr << "FML WINDOW GONE BAD: " << GetLastError() << endl;

		LPTSTR errorMessage;
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&errorMessage,
			0,
			NULL
		);

		cerr << errorMessage;

		return -1;
	}

	// Shows or hides the window, depending on the nCmdShow parameter
	ShowWindow(hwnd, nCmdShow);

	// Message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
//=============================================================================
// WindowProc
//
//      Main window message handling procedure
//
// hWnd     {HWND} 		: Window handle
// uMsg     {UINT} 		: Message code
// wParam   {WPARAM}    : Wide parameter
// lParam   {LPARAM}    : Long parameter
//=============================================================================
LRESULT CALLBACK WindowProc(
	HWND hWnd, 
	UINT uMsg, 
	WPARAM wParam, 
	LPARAM lParam
)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			CreateThread(
				NULL,
				0,
				LolGameMain,
				0,
				0,
				NULL
			);

			break;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			if (LolGame::Scene::current != NULL)
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);

				LolGame::Scene::current->render(hdc);

				EndPaint(hWnd, &ps);
			}

			InvalidateRect(hWnd, NULL, TRUE);
		}

		return 0;
	}

	// Uses the default procedure handler
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//=============================================================================
// LolGameMain
//
//		Main procedure for the game handling thread
//=============================================================================
DWORD WINAPI LolGameMain ( LPVOID param )
{
	cout << "GAEM THREAD UP, LOADIN' GAEM!" << endl;

	ifstream file;
	file.open("main.lol");

	string script;

	while (!file.eof())
		script.push_back((char)file.get());

	LolGame::LOLCODE::run(script);

	return -1;
}