// TestConsole.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <iostream>
#include <cstdio>
#include <Windows.h>
#include <detours.h>

#pragma comment(lib, "detours.lib")

int main(int argc, char* argv[])
{
	std::cout << "Hello World!\n"; //���
	if (argc != 2) {
		MessageBox(NULL, L"too many or less args", NULL, NULL);
		return 0;
	}
	STARTUPINFO si;		//STARTUPINFO����ָ���½��̵����������Ե�һ���ṹ��
	PROCESS_INFORMATION pi;	//PROCESS_INFORMATION �ṹ�����й��½��̼������̵߳���Ϣ
	ZeroMemory(&si, sizeof(STARTUPINFO)); //ZeroMemory��0���һ��������ڴ�
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	//����STARTUPINFO�ṹ�е��ֽ���.���Microsoft������չ�ýṹ
	//,���������汾�����ֶΣ�
	//Ӧ�ó�����뽫cb��ʼ��Ϊsizeof(STARTUPINFO)��
	//char moduleFileName[MAX_PATH];
	//GetCurrentDirectoryA(MAX_PATH, moduleFileName);
	//printf("%s", moduleFileName);
	WCHAR DirPath[MAX_PATH + 1];	//WCHAR��չ���ַ����� MAX_PATHΪ260
	wcscpy_s(DirPath, MAX_PATH, L".\\x64\\Debug"); //Dll���ļ���
			//wcscpy_s���ڿ������ַ������ַ�����Ŀ�ģ�Ŀ�Ĵ�С��Դָ�룩
	char DLLPath[MAX_PATH + 1] = "injected_dll.dll";//dll�ĵ�ַ
	WCHAR EXE[MAX_PATH + 1] = { 0 };
	//wcscpy_s(EXE, MAX_PATH, L".\\x64\\Debug\\test_program.exe
	wchar_t fileName[256] = L"";
	MultiByteToWideChar(CP_ACP, 0, argv[1], strlen(argv[1]), fileName, sizeof(fileName));
	//MessageBox(NULL, fileName, NULL, 0);
	wcscpy_s(EXE, MAX_PATH, fileName);
	//  C:\\Users\\fine\\Desktop\\softwaresafty\\InjectDll\\Debug
//DetourCreateProcessWithDllEx������������һ�����̼�������ע���dll

/*
	wcscpy_s(DirPath, MAX_PATH, L"C:\\softwareSecurity\\TestInitialNullForStudent\\InjectDll\\Debug"); //Dll���ļ���
	char DLLPath[MAX_PATH + 1] = "C:\\softwareSecurity\\TestInitialNullForStudent\\InjectDll\\Debug\\InnjectDll.dll";//Dll�ĵ�ַ x64
	WCHAR EXE[MAX_PATH + 1] = { 0 };
	//wcscpy_s(EXE, MAX_PATH, L"C:\\Windows\\System32\\notepad.exe");//��Ҫע�����ĵ�ַSystem32
	//wcscpy_s(EXE, MAX_PATH, L"C:\\softwareSecurity\\APP\\Debug\\APP.exe");
	//wcscpy_s(EXE, MAX_PATH, L"C:\\softwareSecurity\\APP\\Debug\\FindFilesApp.exe");
	wcscpy_s(EXE, MAX_PATH,     L"C:\\softwareSecurity\\TestInitialNullForStudent\\InjectDll\\Debug\\TestApp.exe");//��Ҫע�����ĵ�ַSystem32
	*/

	if (DetourCreateProcessWithDllEx(EXE, NULL, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED, NULL, DirPath, &si, &pi, DLLPath, NULL))
	{
		//MessageBox& (NULL����INJECT������INJECT����NULL);
		ResumeThread(pi.hThread);//ʹ�̵߳Ĺ���ʱ�������һ
		WaitForSingleObject(pi.hProcess, INFINITE);
		//���dwMillisecondsΪINFINITE�����󱻴����źź󣬺����Ż᷵�ء�
		//hHandle[in]������������ָ��һϵ�еĶ���
	}
	else
	{
		char error[100];
		sprintf_s(error, "%d", GetLastError()); //MessageBoxA(NULL�� error��NULL��NULL);
				//GetLastError�����߳�����Ĵ������ֵ
	}
	return 0;

}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
