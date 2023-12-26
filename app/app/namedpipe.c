#include <stdio.h>
#include <Windows.h>

#define SIZE_BUFFER 140
#define PIPE_NAME "\\\\.\\pipe\\MyPipe"//имя канала

int namedpipe()
{
    system("chcp 1251");
    CHAR inBuffer[SIZE_BUFFER];//буфер на чтение
    CHAR outBuffer[SIZE_BUFFER];//буфер на запись
    DWORD actual_readen; //сколько на самом деле было прочитано байт       

    while (TRUE)
    {
        HANDLE hNamedPipe = CreateNamedPipeA( //создание канала
            PIPE_NAME, //имя канала
            PIPE_ACCESS_DUPLEX, //режим доступа к каналу (односторонний/двусторонний)
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, //режимы работы канала: передавать сообщения|читать сообщения|ждать
            PIPE_UNLIMITED_INSTANCES, //количество входящих соединений к каналу. в данном случае неограничено
            SIZE_BUFFER, // объем буфера на чтение (байт)
            SIZE_BUFFER, // объем буфера на запись (байт)
            INFINITE, // максимальное время ожидания сообщения
            NULL); //указатель на структуру безопасности

        ConnectNamedPipe(hNamedPipe, NULL); //ожидаем соединения клиента с каналом    
        ReadFile(hNamedPipe, inBuffer, SIZE_BUFFER, NULL, NULL);
        printf("\nКлиент пишет: %s \n\nвведите сообщение для клиента:\n", inBuffer);//читаем сообщение клиента и отвечаем ему
        gets(outBuffer);
        WriteFile(hNamedPipe, outBuffer, SIZE_BUFFER, NULL, NULL);
        CloseHandle(hNamedPipe);//закрываем канал
    }
}