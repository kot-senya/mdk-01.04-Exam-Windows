#include <stdio.h>
#include <Windows.h>

#define BUF_SIZE 256

HANDLE hRead, hWrite;//дескрипторы чтения и записи в анонимный канал


int main(int argc, char* argv[])
{
	//получаем дескрипторы для чтения и записи из аргументов командной строки
	hWrite = (HANDLE)atoi(argv[0]);
	hRead = (HANDLE)atoi(argv[1]);
	system("chcp 1251>nul");

	printf("Дескриптор для чтения у потомка: %d \n", hRead);
	printf("Дескриптор для записи у потомка: %d \n", hWrite);
	system("pause");
	CloseHandle(hWrite);//закрываем дескриптор для записи у потомка
	char buffer[BUF_SIZE];
	ReadFile(hRead, buffer, BUF_SIZE, NULL, NULL);//читаем данные из канала
	printf("Ребенок прочитал: %s и завершил работу \n", buffer);//выводим на экран и завершаем работу
	return(0);
}