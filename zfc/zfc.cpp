// zfc.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"
#include "zfc.h"
#include "recvCmd.h"
#include "sendCmd.h"
#include <stdio.h>
#include <windows.h>

string teamName = "";
string serverIp = "";
ushort serverPort = 0;
string myRole = ""; //"POL" OR "THI"
ushort localPort = 0;

inline char* UnicodeToAnsi(const wchar_t* szStr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}

int checkPara(int argc, _TCHAR* argv[])
{
	if (argc != 6)
	{
		log("���󣺲�����������(%d)��", argc);
		log("�����ʽ�� zfc ���� ������IP �������˿� ��ɫ��ע��POL��THI�� ���ؽ��ն˿ڣ�ע�����ֽ�ɫʹ�ò�ͬ�˿ڣ�");
		goto checkParaErr;
	}

	/*teamName = argv[1];
	serverIp = argv[2];
	serverPort = atoi(argv[3]);
	myRole = argv[4];
	localPort = atoi(argv[5]);*/

	teamName = UnicodeToAnsi(argv[1]);
	serverIp = UnicodeToAnsi(argv[2]);
	serverPort = atoi(UnicodeToAnsi(argv[3]));
	myRole = UnicodeToAnsi(argv[4]);
	localPort = atoi(UnicodeToAnsi(argv[5]));

	log("getPara: teamName[%s] serverIp[%s] serverPort[%u] myRole[%s] localPort[%u]",
		teamName.c_str(), serverIp.c_str(), serverPort, myRole.c_str(), localPort);
	if (myRole != "POL" && myRole != "THI")
	{
		log("���󣺽�ɫ��������%s������ʹ��POL��THI��", myRole.c_str());
		goto checkParaErr;
	}
	return OK;

checkParaErr:
	return ERRORR;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//������
	int rt = checkPara(argc, argv);
	if (rt<0) goto end;

	//��ʼ��UDP���ҽӽ��մ�����recvCmd�������ָ��
	if (ERRORR == InitClient((char*)serverIp.c_str(), serverPort, localPort, recvCmd))
	{
		log("InitClient ʧ��");
		return ERRORR;
	}

	//�����Լ���ɫ����Ϣ����������POL �� THIָ��
	sendMyInfoToServer();

	waitThreadEnd();//ѭ���ȴ��߳��˳��������ڽ��յ�ENDָ���ֱ����exit(0);�˳�����
end:
	getchar();
	return 0;
}
