#include "Header.h"

#include <stdio.h>
#include <Windows.h>

int clipboardProcessParent()
{
	LPWSTR mess = L"HI WORLD!";
	DWORD lenMes = wcslen(mess) + 1;
	HANDLE hMess = GlobalAlloc(GMEM_MOVEABLE, lenMes * sizeof(LPWSTR));
	memcpy(GlobalLock(hMess), mess, lenMes * sizeof(LPWSTR));
	OpenClipboard(0); //��������� �����
	EmptyClipboard(); //������ �����
	SetClipboardData(CF_UNICODETEXT, hMess);//������ � �����
	CloseClipboard(1);
}