#include "Header.h"

#include <Windows.h>
#include <stdio.h>

#define PATH "messege.txt"

VOID WINAPI unicodToMessage()
{
	HANDLE File = CreateFile(PATH, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	wchar_t* info_buf = calloc(512, sizeof(wchar_t));
	File = OpenFile(PATH, info_buf, OF_READ);
	wchar_t* buf = calloc(512, sizeof(wchar_t));
	ReadFile(File, buf, 512 * sizeof(wchar_t), NULL, NULL);
	MessageBoxW(NULL, buf, L"Соообщение из файла", MB_OK);
}