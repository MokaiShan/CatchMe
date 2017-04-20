#include "stdafx.h"
#include "zfc.h"
#include "recvCmd.h"

//全局变量
int map_x, map_y;//地图宽高
int Qp, Qt;//警察和小偷数量
int m, n;//视距
int nround;//轮数
typedef struct coordinate
{
	string id;
	int x;
	int y;
	char* move;
}police, thief;
struct bar
{
	int x;
	int y;
};
vector<char*> vec_string;//INI或INF指令第一次分割
vector<char*> vec_map;//地图大小
vector<char*> vec_eye;//视距
vector<char*> vec_num;//警察和小偷数量
vector<char*> vec_coordinate;//坐标
vector<coordinate> vec_police;//警察
vector<coordinate> vec_thief;//小偷

police a = { "0",0,0,"T" };

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

void strtokCmd(char *str, vector<char*>& vec, const char *sep)
{
	char *p;
	p = strtok(str, sep);
	while (p)
	{
		vec.push_back(p);
		p = strtok(NULL, sep);
	}
}

void printvec(vector<char*>& vec)
{
	for (int i = 0; i<vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

void transPOL(vector<char*>& vecin, vector<coordinate>& vecout)
{
	for (int i = 0, j = 0; i<vecin.size(); i = i + 3, j++)
	{
		vecout.at(j).id = vecin.at(i);
		vecout.at(j).x = atoi(vecin.at(i + 1));
		vecout.at(j).y = atoi(vecin.at(i + 2));
	}
}

void initial()
{
	map_x = atoi(vec_map[0]);
	map_y = atoi(vec_map[1]);
	m = atoi(vec_eye[0]);
	n = atoi(vec_eye[1]);
	Qp = atoi(vec_num[0]);
	Qt = atoi(vec_num[1]);
	for (int i = 0; i<Qp; i++)
	{
		vec_police.push_back(a);
	}
}

