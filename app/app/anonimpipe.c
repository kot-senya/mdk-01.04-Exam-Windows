#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <Windows.h>

#define PATH "proc.exe"//имя запускаемого дочернего процесса
#define BUF_SIZE 256

HANDLE hRead, hWrite;//дескрипторы чтения и записи в анонимный канал
SECURITY_ATTRIBUTES sa = { sizeof(sa),NULL,TRUE };//структура безопасности, в которой разрешено наследование дескрипторов

int anonim()
{
	system("chcp 1251>nul");
	CreatePipe(//создаем анонимный канал
		&hRead,//ссылка на дескриптор для чтения
		&hWrite,//ссылка на дескриптор для записи
		&sa, //указатель на структуру безопасности (должно быть разрешено наследование дескрипторов)
		0);	//размер буфера канала (0 - по умолчанию)

	printf("Дескриптор для чтения у родителя: %d \n", hRead);// выводим дескрипторы для сравнения
	printf("Дескриптор для записи у родителя: %d \n", hWrite);

	//блок создания дочернего процесса
	LPSTR str = calloc(100, 1);//для аргументов командной строки
	sprintf(str, "%d %d", hWrite, hRead);//переводим дескриптор для записи в строку

	STARTUPINFO* sti = calloc(1, sizeof(STARTUPINFO));				// структура
	sti->cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION* pi = calloc(1, sizeof(PROCESS_INFORMATION));

	if (!CreateProcessA(PATH,//путь к файлу
		str,//агрументы командной строки
		NULL,//структура безопасности процесса
		NULL,//структура безопасности потока
		TRUE,//наследовать дескриптор нового процесса от старого?
		0,//флаги приоритета процессов CREATE_NEW_CONSOLE
		NULL,//среда окружения процесса ANSI или UNICODE
		NULL,//консольный путь к каталогу, из которого вызывается процесс
		sti,//указатель на структуру STARTUPINFO
		pi))//указатель на структуру PROCESS_INFORMATION
	{
		printf("Не удалось создать процесс. Код ошибки: %d.\n", GetLastError());
	}
	free(str);
	CloseHandle(hRead);//Закрываем дескриптор для чтения
	WriteFile(hWrite, "Сообщение для благодарных потомков", 67, NULL, NULL);	//пишем в канал
	CloseHandle(hWrite);
	WaitForSingleObject(pi->hProcess, INFINITE);//ожидание завершения дочернего процесса
	DWORD dw;
	GetExitCodeProcess(pi->hProcess, &dw);//получаем код выхода дочернего процесса
	CloseHandle(pi->hThread);
	CloseHandle(pi->hProcess);
	printf("Я дождался завершения процесса %d\n", dw);
	system("pause");
	return 0;
}