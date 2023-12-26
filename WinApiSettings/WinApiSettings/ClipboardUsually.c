#include <stdio.h>
#include <Windows.h>

int clipboardUsually()
{
	LPWSTR mess = L"��������� �� ������";

}
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
	return 0;
}