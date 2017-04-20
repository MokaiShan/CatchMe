#include "stdafx.h"
#include "zfc.h"
#include "recvCmd.h"

//全局变量
int map_x, map_y;//地图宽高
int Qp, Qt;//警察和小偷数量
int m, n;//视距
int nround;//轮数
struct coordinate
{
	string id;
	int x;
	int y;
	char move;
};
struct bar
{
	int x;
	int y;
};

//函数实现
int recvIni(char *str)
{
    //接收初始化指令处理
	if (myRole == "POL")
	{
		recvIniPol(str);
	}
	else if (myRole == "THI")
	{
		recvIniThi(str);
	}
	else
	{
		;
	}
    return 0;
}

int recvInf(char *str)
{
    //接收INF指令    
    return 0;
}

//接收到END指令，退出进程
int recvEnd(char *str)
{
    log("recv END!");
    exit(0);//退出进程
}

int recvCmd(char *str)
{
    log("[RECV]: %s",str);
    if(strstr(str,"INF"))
    {
        recvInf(str);
        //接收到INF之后的处理
    }
    else if(strstr(str,"INI"))
    {
        recvIni(str);
    }
    else if(strstr(str,"END"))
    {
        recvEnd(str);
    }
    else
    {
        log("\r\n ERROR RECV CMD[%s]!", str);
    }

    return 0;
}

void recvIniPol(char *str)
{
	
}

void recvIniThi(char *str)
{

}

