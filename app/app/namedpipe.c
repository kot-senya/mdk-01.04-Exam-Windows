#include <stdio.h>
#include <Windows.h>

#define SIZE_BUFFER 140
#define PIPE_NAME "\\\\.\\pipe\\MyPipe"//��� ������

int namedpipe()
{
    system("chcp 1251");
    CHAR inBuffer[SIZE_BUFFER];//����� �� ������
    CHAR outBuffer[SIZE_BUFFER];//����� �� ������
    DWORD actual_readen; //������� �� ����� ���� ���� ��������� ����       

    while (TRUE)
    {
        HANDLE hNamedPipe = CreateNamedPipeA( //�������� ������
            PIPE_NAME, //��� ������
            PIPE_ACCESS_DUPLEX, //����� ������� � ������ (�������������/������������)
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, //������ ������ ������: ���������� ���������|������ ���������|�����
            PIPE_UNLIMITED_INSTANCES, //���������� �������� ���������� � ������. � ������ ������ ������������
            SIZE_BUFFER, // ����� ������ �� ������ (����)
            SIZE_BUFFER, // ����� ������ �� ������ (����)
            INFINITE, // ������������ ����� �������� ���������
            NULL); //��������� �� ��������� ������������

        ConnectNamedPipe(hNamedPipe, NULL); //������� ���������� ������� � �������    
        ReadFile(hNamedPipe, inBuffer, SIZE_BUFFER, NULL, NULL);
        printf("\n������ �����: %s \n\n������� ��������� ��� �������:\n", inBuffer);//������ ��������� ������� � �������� ���
        gets(outBuffer);
        WriteFile(hNamedPipe, outBuffer, SIZE_BUFFER, NULL, NULL);
        CloseHandle(hNamedPipe);//��������� �����
    }
}