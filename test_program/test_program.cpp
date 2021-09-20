#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")

#define PAGE_SIZE	4096

void menu();
void heap_create_destroy();
void create_and_write_file();
void read_file();
void reg_create_and_set_value();
void reg_open_and_del_value();
void heap_repeated_release();
void change_executable_program();
void self_replication();
void open_another_folder();
void modify_startup_registry();
void socket_recv_data();
void socket_send_data();

int main() {
	int choice;
	int mark = 0;
	while (true)
	{
		menu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			MessageBoxA(NULL, "I'm your father!", "wsxk", MB_OK);
			break;
		case 2:
			MessageBoxW(NULL, L"I'm your father!", L"wsxk", MB_OK);
			break;
		case 3:
			heap_create_destroy();
			break;
		case 4:
			create_and_write_file();
			break;
		case 5:
			read_file();
			break;
		case 6:
			reg_create_and_set_value();
			break;
		case 7:
			reg_open_and_del_value();
			break;
		case 8:
			heap_repeated_release();
			break;
		case 9:
			change_executable_program();
			break;
		case 10:
			self_replication();
			break;
		case 11:
			open_another_folder();
			break;
		case 12:
			modify_startup_registry();
			break;
		case 13:
			socket_recv_data();
			break;
		case 14:
			socket_send_data();
			break;
		case 15:
			mark = 1;
			break;
		default:
			break;
		}
		if (mark)
			break;
	}
	printf("See you!\n");
	return 0;
}

void menu() {
	printf("--------------------------------please enter your choice--------------------------------\n");
	printf("---operations---:\n");
	printf("1.MessageBoxA      2.MessageBoxW            3.HeapCreateAndDestory   4.CreateAndWriteFile\n");
	printf("5.ReadFileString   6.RegCreateAndSetValue   7.RegOpenAndDelValue     8.HeapRepeatedRelease\n");
	printf("9.ChangeExecutableProgram   10.SelfReplication   11.OpenAnotherFolder\n");
	printf("12.ModifyStartupRegistry 13.SocketRecvData 14.SocketSendData\n");
	printf("15: exit\n");
}

void heap_create_destroy() {
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);
	if (!hHeap) {
		printf("create error!\n");
		return;
	}
	int* heap =(int *)HeapAlloc(hHeap, 0, sizeof(int) * 10);
	if (!heap) {
		printf("alloc error!\n");
		return;
	}
	for (int i = 0; i < 10; i++) {
		heap[i] = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", heap[i]);
	}
	printf("\n");
	HeapFree(hHeap, 0, heap);
	HeapDestroy(hHeap);
}

void create_and_write_file() {
	HANDLE hOpenFile = (HANDLE)CreateFile(L"wsxk.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hOpenFile ==INVALID_HANDLE_VALUE) {
		printf("create error!\n");
		return;
	}
	printf("just for for convenience,we put string 'wsxk' into file\n");
	char write_string[5] = "wsxk";
	int flag;
	flag=WriteFile(hOpenFile, write_string, sizeof(write_string), NULL, NULL);
	FlushFileBuffers(hOpenFile);
	CloseHandle(hOpenFile);
	return;
}

void read_file() {
	HANDLE hOpenFile = (HANDLE)CreateFile(L"wsxk.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		hOpenFile = NULL;
		printf("Can not open the file\n");
		return;
	}
	int file_size = GetFileSize(hOpenFile, NULL);
	char* file_buffer = (char*)malloc((long long)(file_size + 1) * sizeof(char));
	int flag = ReadFile(hOpenFile, file_buffer, file_size, NULL, NULL);
	file_buffer[file_size] = 0;
	if (flag) {
		printf("%s\n", file_buffer);
	}
	free(file_buffer);
	CloseHandle(hOpenFile);
}

void reg_create_and_set_value() {
	HKEY hKey = NULL;
	size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"wsxk", 0, NULL, REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (lRet != ERROR_SUCCESS) {
		printf("create reg error!\n");
		return;
	}
	TCHAR value[255] = L"https://github.com/wsxk";
	size_t size = wcslen(value);
	lRet = RegSetValueEx(hKey, L"wxk", 0, REG_SZ, (CONST BYTE*)value, sizeof(TCHAR) * size);
	if (lRet == ERROR_SUCCESS)
	{
		printf("set value successfully!\n");
		return;
	}
	else {
		printf("failed to set value!\n");
	}
	RegCloseKey(hKey);
}

void reg_open_and_del_value() {
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"wsxk", 0, KEY_ALL_ACCESS, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("open successfully!\n");
	}
	else {
		printf("open failed\n");
		return;
	}
	lRet = RegDeleteValue(hKey, L"wxk");
	if (lRet == ERROR_SUCCESS) {
		printf("delete success!\n");
	}
	else {
		printf("delete fail!\n");
	}
	RegCloseKey(hKey);
	return;
}

void heap_repeated_release() {
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);
	if (!hHeap) {
		printf("create error!\n");
		return;
	}
	int* heap = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 10);
	if (!heap) {
		printf("alloc error!\n");
		return;
	}
	for (int i = 0; i < 10; i++) {
		heap[i] = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", heap[i]);
	}
	printf("\n");
	printf("first free!\n");
	HeapFree(hHeap, 0, heap);
	printf("second free!\n");
	HeapFree(hHeap, 0, heap);
	HeapDestroy(hHeap);
	return;
}

void change_executable_program() {
	HANDLE hOpenFile = (HANDLE)CreateFile(L"fun.exe", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	CloseHandle(hOpenFile);
}

void self_replication() {
	HANDLE hOpenFile = (HANDLE)CreateFile(L"test_program.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
	CloseHandle(hOpenFile);
}

void open_another_folder() {
	HANDLE hOpenFile = (HANDLE)CreateFile(L"wxk.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE) {
		printf("create error!\n");
		return;
	}
	printf("just for for convenience,we put string 'wsxk' into file\n");
	char write_string[5] = "wsxk";
	int flag;
	flag = WriteFile(hOpenFile, write_string, sizeof(write_string), NULL, NULL);
	FlushFileBuffers(hOpenFile);
	CloseHandle(hOpenFile);
}

void modify_startup_registry() {
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("open successfully!\n");
	}
	else {
		printf("open failed\n");
	}
	TCHAR value[255] = L"C:\\Users\\wsxk\\Desktop\\software_course_design\\qt_gui\\x64\\Debug\\test_program.exe";
	size_t size = wcslen(value);
	lRet = RegSetValueEx(hKey, L"wxk", 0, REG_SZ, (CONST BYTE*)value, sizeof(TCHAR) * size);
	if (lRet == ERROR_SUCCESS)
	{
		printf("set value successfully!\n");
		return;
	}
	else {
		printf("failed to set value!\n");
	}
	RegCloseKey(hKey);
}

void socket_recv_data() {
	//���ֱر�
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//�����׽���
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//���������������
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(6666);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//Sleep(500);
	//���շ��������ص�����
	char szBuffer[MAXBYTE] = { 0 };
	recv(sock, szBuffer, MAXBYTE, NULL);
	//������յ�������
	printf("Message form server: %s\n", szBuffer);
	//�ر��׽���
	closesocket(sock);
	//��ֹʹ�� DLL
	WSACleanup();
}

void socket_send_data() {
	//ʹ��socket֮ǰ�������WSAStartup
	WSADATA wsaData;//2.2�汾
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("start wsa error!\n");
		return;
	}
	//�����׽��� �����
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
	sockAddr.sin_port = htons(6666);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//�������״̬
	listen(servSock, 20);
	//���տͻ������� ��������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	//��ͻ��˷�������
	char str[32] = "Hello my son!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);
	printf("send successfully!\n");
	//�ر��׽���
	closesocket(clntSock);
	closesocket(servSock);
	//��ֹ DLL ��ʹ��
	WSACleanup();
}