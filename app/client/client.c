#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define SIZE_BUFFER 140
#define PIPE_NAME "\\\\.\\pipe\\MyPipe"//имя канала (такое же, как и на сервере)

int main()
{
	system("chcp 1251");
	CHAR inBuffer[SIZE_BUFFER];//буфер на чтение
	CHAR outBuffer[SIZE_BUFFER];//буфер на запись
	while (TRUE)
	{
		HANDLE hNamedPipe = CreateFileA(//открываем канал. по аналогии с открытием файла
			PIPE_NAME, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
		DWORD dwMode = PIPE_READMODE_MESSAGE;//Текстовый режим работы канала
		BOOL isSuccess = SetNamedPipeHandleState(hNamedPipe, &dwMode, NULL, NULL);//задает режим блокировки канала. если канал существует, изменяет его статус
		if (!isSuccess)
		{
			printf("сервер не отвечает\n");
		}
		else
		{
			printf("введите сообщение для сервера:\n");
			gets(outBuffer);
			WriteFile(hNamedPipe, outBuffer, SIZE_BUFFER, NULL, NULL);//пишем в канал		
			ReadFile(hNamedPipe, inBuffer, SIZE_BUFFER, NULL, NULL);//ждем ответ от сервера и читаем его
			printf("\nСервер пишет: %s \n", inBuffer);
		}
		CloseHandle(hNamedPipe);
	}
}