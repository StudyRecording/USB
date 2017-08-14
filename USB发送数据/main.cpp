#include <iostream>
#include <windows.h>
#include <tchar.h>

using namespace std;

int main()
{
	//打开串口
	HANDLE hcom;
	hcom = CreateFile(_T("COM1"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hcom == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "打开串口失败！\n");
		exit(0);
	}
	//配置默认收发缓存区大小
	SetupComm(hcom, 1024, 1024);
	//得到串口配置
	DCB dcb;
	GetCommState(hcom, &dcb);
	//配置串口属性
	dcb.BaudRate = 9600;
	dcb.ByteSize = 8;
	dcb.Parity = 0;
	dcb.StopBits = 1;
	SetCommState(hcom, &dcb);
	//发送数据
	char data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
	DWORD dwWrittenLen = 0;
	int k = 0;
	for (;;) {
		if (!WriteFile(hcom, data, 8, &dwWrittenLen, NULL))
		{
			fprintf(stderr, "发送数据失败！\n");
		}

		k++;

		printf("往串口发送数据成功！第%d次\n", k);
		Sleep(10 * 1000);  //10s发送一次
	}

	return 0;
}