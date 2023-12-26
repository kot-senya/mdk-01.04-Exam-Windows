#include "Header.h"

#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT pHook = (PKBDLLHOOKSTRUCT)lParam;
	while (wParam == WM_KEYDOWN)
	{
		DWORD iKey = MapVirtualKeyW(pHook->vkCode, NULL) << 16; //виртуальный код клавиши
		if (!(pHook->vkCode <= 1 << 5))	// сдвигаем тк первые 32 символа не читаютс€
			iKey |= 0x1 << 24;			//истина дл€ 24 бит
		wchar_t* name = calloc(256, sizeof(wchar_t));
		GetKeyNameTextW(iKey, name, 256);
		MessageBox(NULL, name, L"»Ќ‘ќ–ћј÷»я", MB_OK);
	}
	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

VOID WINAPI keyboardName()
{
	HHOOK hHook = SetWindowsHookExW(WH_KEYBOARD_LL, LogKey, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))//функци€ ожидает системного сообщени€
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hHook);
	return 0;
}