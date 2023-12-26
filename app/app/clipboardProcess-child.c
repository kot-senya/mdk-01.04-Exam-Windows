
#include <Windows.h>
#include <stdio.h>

int clipboardProcessChild()
{
	
	OpenClipboard(0);
	LPWSTR mess = (LPWSTR) GetClipboardData(CF_UNICODETEXT);
	CloseClipboard();
	MessageBoxW(NULL, mess, L"Значение буфера", MB_OK);
}