#include "Header.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ReestSTR(HKEY hKey)
{
	HKEY tmp = NULL;

	if (RegCreateKey(hKey, L"MyKey", &tmp) == ERROR_SUCCESS) //создаем ключ
	{
		MessageBox(NULL, L"Ключ успешно создан", L"Информация", MB_OK);
	}
	LPWSTR d = L"Hello world";
	if (RegSetValueExW(tmp, L"MyStrParam",NULL, REG_SZ,  d, 13 * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"Строковой параметр успешно создан и ему присвоено значение по умолчанию", L"Информация", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Строковой параметр не был создан", L"Информация", MB_OK);
		return -1;
	}

	LPWSTR DataType = 0;
	DWORD DataLen = 512 * sizeof(char);
	LPWSTR StrValue = malloc(512);

	if (RegGetValueW(hKey, L"Mykey", L"MyStrParam", RRF_RT_ANY, &DataType, StrValue, &DataLen) == ERROR_SUCCESS)
	{
		MessageBox(NULL, StrValue, L"Значение параметра", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Что-то пошло не так", L"Информация", MB_OK);
	}

	RegCloseKey(tmp);
}

void ReestNUM(HKEY hKey)
{
	HKEY tmp = NULL;

	if (RegCreateKey(hKey, L"MyKey", &tmp) != ERROR_SUCCESS) //создаем ключ
	{
		MessageBox(NULL, L"Ключ успешно создан", L"Информация", MB_OK);
	}

	DWORD DataType = 0;
	DWORD DataLen = 512;
	DWORD d = 123;

	//создаем параметр типа DWORD 
	if (RegSetValueExW(tmp, L"MyDwordParam", NULL, REG_DWORD, &d, 4) == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"Числовой параметр успешно создан и ему присвоено значение по умолчанию", L"Информация", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Числовой параметр не был создан", L"Информация", MB_OK);
		return -1;
	}

	DWORD DWValue = 0;
	if (RegGetValueW(hKey, L"Mykey", L"MyDwordParam", RRF_RT_ANY, &DataType, &DWValue, &DataLen) == ERROR_SUCCESS)
	{
		LPWSTR OutputString = malloc(512);
		swprintf(OutputString, 512, TEXT("%d"), DWValue);
		MessageBox(NULL, OutputString, L"Значение параметра", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Что-то пошло не так", L"Информация", MB_OK);
	}

	RegCloseKey(tmp); //закрываем дискриптор
}

int reestr()
{
	HKEY hKey = NULL;//дескриптор ключа реестра (он является структурой)

	if (RegOpenKey(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS) //открываем раздел HKEY_CURRENT_USER
		return 1;	

	//создаем подраздел + значение по умолчанию
	if (RegSetValueW(hKey, L"Mykey", REG_SZ, L"Значение по умолчанию", 22 * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"Ключ успешно создан и ему присвоено значение по умолчанию", L"Информация", MB_OK);
	}

	ReestSTR(hKey);
	ReestNUM(hKey);	

	/*
	if (RegDeleteValue(hKey, L"MyDwordParam") == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"Параметр успешно удален", L"Информация", MB_OK);
	}

	if (RegDeleteKey(hKey, L"MyKey") == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"Ключ успешно удален", L"Информация", MB_OK);
	}
	*/

	RegCloseKey(hKey); //закрываем дискриптор
}