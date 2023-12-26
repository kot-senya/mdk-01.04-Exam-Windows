#include "Header.h"

#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK LogKeyN(int iCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_KEYDOWN)
	{
		PKBDLLHOOKSTRUCT pHook = (PKBDLLHOOKSTRUCT)lParam;
		DWORD iKey = MapVirtualKeyW(pHook->vkCode, NULL);
		LPWSTR code[256];
		wsprintfW(code, L"%d", iKey);
		MessageBox(NULL, code, L"ИНФОРМАЦИЯ", MB_OK);
	}
	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

VOID WINAPI keyboardASCII()
{
	HHOOK hHook = SetWindowsHookExW(WH_KEYBOARD_LL, LogKeyN, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))//функция ожидает системного сообщения
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hHook);
	return 0;
}
