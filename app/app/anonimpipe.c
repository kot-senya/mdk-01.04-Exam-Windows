#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <Windows.h>

#define PATH "proc.exe"//��� ������������ ��������� ��������
#define BUF_SIZE 256

HANDLE hRead, hWrite;//����������� ������ � ������ � ��������� �����
SECURITY_ATTRIBUTES sa = { sizeof(sa),NULL,TRUE };//��������� ������������, � ������� ��������� ������������ ������������

int anonim()
{
	system("chcp 1251>nul");
	CreatePipe(//������� ��������� �����
		&hRead,//������ �� ���������� ��� ������
		&hWrite,//������ �� ���������� ��� ������
		&sa, //��������� �� ��������� ������������ (������ ���� ��������� ������������ ������������)
		0);	//������ ������ ������ (0 - �� ���������)

	printf("���������� ��� ������ � ��������: %d \n", hRead);// ������� ����������� ��� ���������
	printf("���������� ��� ������ � ��������: %d \n", hWrite);

	//���� �������� ��������� ��������
	LPSTR str = calloc(100, 1);//��� ���������� ��������� ������
	sprintf(str, "%d %d", hWrite, hRead);//��������� ���������� ��� ������ � ������

	STARTUPINFO* sti = calloc(1, sizeof(STARTUPINFO));				// ���������
	sti->cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION* pi = calloc(1, sizeof(PROCESS_INFORMATION));

	if (!CreateProcessA(PATH,//���� � �����
		str,//��������� ��������� ������
		NULL,//��������� ������������ ��������
		NULL,//��������� ������������ ������
		TRUE,//����������� ���������� ������ �������� �� �������?
		0,//����� ���������� ��������� CREATE_NEW_CONSOLE
		NULL,//����� ��������� �������� ANSI ��� UNICODE
		NULL,//���������� ���� � ��������, �� �������� ���������� �������
		sti,//��������� �� ��������� STARTUPINFO
		pi))//��������� �� ��������� PROCESS_INFORMATION
	{
		printf("�� ������� ������� �������. ��� ������: %d.\n", GetLastError());
	}
	free(str);
	CloseHandle(hRead);//��������� ���������� ��� ������
	WriteFile(hWrite, "��������� ��� ����������� ��������", 67, NULL, NULL);	//����� � �����
	CloseHandle(hWrite);
	WaitForSingleObject(pi->hProcess, INFINITE);//�������� ���������� ��������� ��������
	DWORD dw;
	GetExitCodeProcess(pi->hProcess, &dw);//�������� ��� ������ ��������� ��������
	CloseHandle(pi->hThread);
	CloseHandle(pi->hProcess);
	printf("� �������� ���������� �������� %d\n", dw);
	system("pause");
	return 0;
}