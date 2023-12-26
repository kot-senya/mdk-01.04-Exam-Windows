#include <stdio.h>
#include <Windows.h>

int clipboardUsually()
{
	LPWSTR mess = L"Сообщение из буфера";

}
int clipboardInput(LPWORD buf)
{
	DWORD lenBuf = wcslen(buf) + 1; //длина строки
	HANDLE hMem;

	hMem = GlobalAlloc(GMEM_MOVEABLE, lenBuf * sizeof(LPWSTR));	//выделение памятив глобальной области видимости
	memcpy(GlobalLock(hMem), buf, lenBuf * sizeof(LPWSTR));		//копирование областипамяти из buf в hmem
	GlobalUnlock(hMem); //разблокировать содержимое памяти
	OpenClipboard(0);	//открыть буфер обмена - стандартный
	EmptyClipboard();	//очистить буфер обмена
	SetClipboardData(CF_UNICODETEXT, hMem); //запись в буфер обмена данные соответствующего типа
	CloseClipboard();	//закрыть буфер
	return 0;
}

int clipboardOutput()
{
	return 0;
}