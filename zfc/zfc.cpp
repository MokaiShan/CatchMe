// zfc.cpp : 定义控制台应用程序的入口点。
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
		log("错误：参数个数错误(%d)！", argc);
		log("命令格式： zfc 队名 服务器IP 服务器端口 角色（注：POL或THI） 本地接收端口（注：两种角色使用不同端口）");
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
		log("错误：角色参数错误（%s）！请使用POL或THI。", myRole.c_str());
		goto checkParaErr;
	}
	return OK;

checkParaErr:
	return ERRORR;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//检查参数
	int rt = checkPara(argc, argv);
	if (rt<0) goto end;

	//初始化UDP，挂接接收处理函数recvCmd处理接收指令
	if (ERRORR == InitClient((char*)serverIp.c_str(), serverPort, localPort, recvCmd))
	{
		log("InitClient 失败");
		return ERRORR;
	}

	//发送自己角色的信息给服务器：POL 或 THI指令
	sendMyInfoToServer();

	waitThreadEnd();//循环等待线程退出，可以在接收到END指令后直接用exit(0);退出程序。
end:
	getchar();
	return 0;
}
