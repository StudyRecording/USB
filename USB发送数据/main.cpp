#include <iostream>
#include <windows.h>
#include <tchar.h>

using namespace std;

int main()
{
	//�򿪴���
	HANDLE hcom;
	hcom = CreateFile(_T("COM1"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hcom == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "�򿪴���ʧ�ܣ�\n");
		exit(0);
	}
	//����Ĭ���շ���������С
	SetupComm(hcom, 1024, 1024);
	//�õ���������
	DCB dcb;
	GetCommState(hcom, &dcb);
	//���ô�������
	dcb.BaudRate = 9600;
	dcb.ByteSize = 8;
	dcb.Parity = 0;
	dcb.StopBits = 1;
	SetCommState(hcom, &dcb);
	//��������
	char data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
	DWORD dwWrittenLen = 0;
	int k = 0;
	for (;;) {
		if (!WriteFile(hcom, data, 8, &dwWrittenLen, NULL))
		{
			fprintf(stderr, "��������ʧ�ܣ�\n");
		}

		k++;

		printf("�����ڷ������ݳɹ�����%d��\n", k);
		Sleep(10 * 1000);  //10s����һ��
	}

	return 0;
}