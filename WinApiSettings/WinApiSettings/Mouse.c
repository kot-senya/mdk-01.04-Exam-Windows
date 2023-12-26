#include "Header.h"

#include <Windows.h>
#include <stdio.h>

DWORD left = 0;
DWORD right = 0;
DWORD center = 0;

LPWSTR answer;

LRESULT CALLBACK LogMouse(int iCode, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case WM_LBUTTONDOWN:
	{
		left++;
		wsprintfW(answer, L"Ћева€ кнопка мыши нажата %d раз", left);
		MessageBoxW(NULL, answer, L"»Ќ‘ќ–ћј÷»я", MB_OK);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		right++;
		wsprintfW(answer, L"ѕрава€ кнопка мыши нажата %d раз", right);
		MessageBoxW(NULL, answer, L"»Ќ‘ќ–ћј÷»я", MB_OK);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		center++;
		wsprintfW(answer, L"—редн€€ кнопка мыши нажата %d раз", center);
		MessageBoxW(NULL, answer, L"»Ќ‘ќ–ћј÷»я", MB_OK);
		break;
	}
	}
	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

VOID WINAPI mouse()
{
	answer = calloc(256, sizeof(WCHAR));
	HHOOK hHook = SetWindowsHookExW(WH_MOUSE_LL, LogMouse, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hHook);
	return 0;
}