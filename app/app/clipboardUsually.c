#include <stdio.h>
#include <Windows.h>

int clipboardInput(LPWORD buf)
{
	DWORD lenBuf = wcslen(buf) + 1; //����� ������
	HANDLE hMem;

	hMem = GlobalAlloc(GMEM_MOVEABLE, lenBuf * sizeof(LPWSTR));	//��������� ������� ���������� ������� ���������
	memcpy(GlobalLock(hMem), buf, lenBuf * sizeof(LPWSTR));		//����������� ������������� �� buf � hmem
	GlobalUnlock(hMem); //�������������� ���������� ������
	OpenClipboard(0);	//������� ����� ������ - �����������
	EmptyClipboard();	//�������� ����� ������
	SetClipboardData(CF_UNICODETEXT, hMem); //������ � ����� ������ ������ ���������������� ����
	CloseClipboard();	//������� �����
	return 0;
}

int clipboardOutput()
{
	LPWSTR mess;
	OpenClipboard(NULL);
	HANDLE hMess = GetClipboardData(CF_UNICODETEXT);
	mess = (LPWSTR)GlobalLock(hMess);
	CloseClipboard();
	MessageBox(NULL, mess, L"�������� ������", MB_OK);
	return 0;
}

int clipboardUsually()
{
	LPWSTR mess = L"��������� �� ������";

	clipboardInput(mess);
	clipboardOutput();
}