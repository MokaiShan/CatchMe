#include "stdafx.h"
#include "zfc.h"
#include "recvCmd.h"

string test = "test";
//全局变量
int map_x, map_y;//地图宽高
int Qp, Qt;//警察和小偷数量
int m, n;//视距
int nround;//轮数
int D=0, N=0, X=0, B=0;
vector<char*> vec_string;//INI或INF指令第一次分割
vector<char*> vec_map;//地图大小
vector<char*> vec_eye;//视距
vector<char*> vec_num;//警察和小偷数量
vector<char*> vec_coordinate;//坐标
vector<char*> vec_hinderone;//障碍物
vector<char*> vec_hinders;
vector<char*> vec_temp;
vector<coordinate> vec_police;//警察
vector<coordinate> vec_thief;//小偷
vector<bar> vec_hinder;//障碍物
typedef struct coordinate
{
	string id;
	int x;
	int y;
	char* move;
}police, thief;
police p = { "0",0,0,"T" };//用于初始化
thief t = { "0",0,0,"T" };//用于初始化
struct bar
{
	int x;
	int y;
};
bar b = { 0,0 };

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
		//cout << vec_thief.at(0).y;
	}
	else         //do nothing
	{
		
	}
    return 0;
}

int recvInf(char *str)
{
	//接收INF指令
	recv_messegeInf(str);
	//cout << vec_thief.at(0).y;
	if (myRole == "POL")
	{
		normal_direction(vec_police);
	}

	else if (myRole == "THI")
	{
		normal_direction(vec_thief);
	}

	string buf = "MOV[";
	int i = 0;
	if (myRole == "POL")
	{
		buf += to_string(nround) + "](";
		for (i = 0; i < Qp; i++) {
			buf += vec_police.at(i).id + ","
				+ vec_police.at(i).move + ";";
		}
		buf += ")";
	}
	else if (myRole == "THI")
	{
		buf += to_string(nround) + "](";
		for (i = 0; i < Qt; i++) {
			buf += vec_thief.at(i).id + ","
				+ vec_thief.at(i).move + ";";
		}
		buf += ")";
	}
	char *p1 = new char[buf.size() + 1];
	strcpy(p1, buf.c_str());
	sendCmd(p1);
	delete[] p1;
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
	strtokCmd(str, vec_string, "[]<>()");
	strtokCmd(vec_string.at(1), vec_map, ",");
	strtokCmd(vec_string.at(2), vec_eye, ",");
	strtokCmd(vec_string.at(3), vec_num, ",");
	strtokCmd(vec_string.at(4), vec_coordinate, ",;");
	initial();
	transCmd(vec_coordinate, vec_police);
	clear();
}

void recvIniThi(char *str)
{
	strtokCmd(str, vec_string, "[]<>()");
	strtokCmd(vec_string.at(1), vec_map, ",");
	strtokCmd(vec_string.at(2), vec_eye, ",");
	strtokCmd(vec_string.at(3), vec_num, ",");
	strtokCmd(vec_string.at(4), vec_coordinate, ",;");
	initial();
	transCmd(vec_coordinate, vec_thief);
	clear();
}

void strtokCmd(char *str, vector<char*>& vec, const char *sep)
{
	char *p2;
	p2 = strtok(str, sep);
	while (p2)
	{
		vec.push_back(p2);
		p2 = strtok(NULL, sep);
	}
	delete [] p2;
}

void transCmd(vector<char*>& vecin, vector<coordinate>& vecout)
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
	map_x = atoi(vec_map.at(0));
	map_y = atoi(vec_map.at(1));
	m = atoi(vec_eye.at(0));
	n = atoi(vec_eye.at(1));
	Qp = atoi(vec_num.at(0));
	Qt = atoi(vec_num.at(1));
	for (int i = 0; i<Qp; i++)
	{
		vec_police.push_back(p);
	}
	for (int i = 0; i<Qt; i++)
	{
		vec_thief.push_back(t);
	}
}

void clear()
{
	vec_string.clear();
	vec_coordinate.clear();
	vec_eye.clear();
	vec_map.clear();
	vec_num.clear();
	vec_hinderone.clear();
	vec_hinders.clear();
	vec_temp.clear();
}

void normal_direction(vector<coordinate>& vec_role) {
	for (int i = 0; i < vec_role.size(); i++)
	{
		int randNum = rand() % 8;
		D = 0, N = 0, X = 0, B = 0;
		for (int k = 0; k < vec_hinder.size(); k++)
		{
			if ((vec_hinder.at(k).x - vec_role.at(i).x) == 1)
			{
				D = 1;
			}
			else if ((vec_hinder.at(k).y - vec_role.at(i).y) == 1)
			{
				B = 1;
			}
			else if ((vec_hinder.at(k).y - vec_role.at(i).y) == -1)
			{
				N = 1;
			}
			else if ((vec_hinder.at(k).x - vec_role.at(i).x) == -1)
			{
				X = 1;
			}
		}
	}
}

void recv_messegeInf(char*s)
{
	char *p3, *p4, *p5, *p6, *p7, *p8;
	if (myRole == "POL")//警察
	{
		clear();
		int count = 0;
		string tem, tem1;
		tem = s;
		tem1 = s;
		p3 = new char[tem1.size() + 1];
		strcpy(p3,tem1.c_str());
		strtokCmd(p3, vec_temp, "<>");

		strtokCmd(s, vec_string, "[]()<>");
		count = vec_string.size();
		nround = stoi(vec_string[1]);//轮数信息
		strtokCmd(vec_string[2], vec_coordinate, ",;");
		transCmd(vec_coordinate, vec_police);
		vec_coordinate.clear();

		if (count == 3)//没有障碍物，也没有小偷
		{
			;
		}
		if (count == 4)//小偷和障碍物只有一个
		{
			p4 = new char[tem.size() + 1];
			strcpy(p4, tem.c_str());
			p5 = strstr(p4, "<>");
			if (p5 == NULL) //有小偷无障碍物
			{
				strtokCmd(vec_string[3], vec_coordinate, ",;");
				transCmd(vec_coordinate, vec_thief);
				vec_coordinate.clear();
			}
			else     //无小偷有障碍物
			{
				strtokCmd(vec_string[3], vec_hinderone, ";");
				initial_hinder(vec_hinderone.size());
				strtokCmd(vec_temp[1], vec_coordinate, "(,;)");
				transHINDER(vec_coordinate, vec_hinder);
				vec_coordinate.clear();
			}
		}
		if (count == 5)
		{
			strtokCmd(vec_string[3], vec_coordinate, ",;");
			transCmd(vec_coordinate, vec_thief);
			vec_coordinate.clear();
			strtokCmd(vec_string[4], vec_hinderone, ";");
			initial_hinder(vec_hinderone.size());
			strtokCmd(vec_temp[2], vec_coordinate, "(,;)");
			transHINDER(vec_coordinate, vec_hinder);
			vec_coordinate.clear();
		}
		delete[] p3, p4, p5;
	}
	if (myRole=="THI")//小偷
	{
		clear();
		int count = 0;
		string tem = s;
		cout << tem;
		strtokCmd(s, vec_string, "[]()<>");
		nround = stoi(vec_string[1]);//轮数信息
		p6=new char[tem.size()+1];
		strcpy(p6, tem.c_str());
		strtokCmd(p6, vec_temp, "<>");
		count = vec_temp.size();
		vec_coordinate.clear();
		strtokCmd(vec_temp[1], vec_coordinate, ",;");
		transCmd(vec_coordinate, vec_thief);
		vec_coordinate.clear();
		
		//无障碍
		//cout << vec_temp.at(0);
		//cout << vec_temp.at(2);
		p7 = strstr(vec_temp[0], "()");
		p8 = strstr(vec_temp[2], "()");
		if (p7 == NULL&&p8 == NULL) //有警察
		{
			strtokCmd(vec_string[2], vec_coordinate, ",;");
			transCmd(vec_coordinate, vec_police);
			vec_coordinate.clear();
			strtokCmd(vec_string[4], vec_hinderone, ";");
			initial_hinder(vec_hinderone.size());
			strtokCmd(vec_temp[2], vec_coordinate, "(,;)");
			transHINDER(vec_coordinate, vec_hinder);
			vec_coordinate.clear();
		}
		if (p7 == NULL&&p8 != NULL)
		{
			strtokCmd(vec_string[2], vec_coordinate, ",;");
			transCmd(vec_coordinate, vec_police);
			vec_coordinate.clear();
		}
		if (p7 != NULL&&p8 == NULL)
		{

			strtokCmd(vec_string[3], vec_hinderone, ";");
			initial_hinder(vec_hinderone.size());
			strtokCmd(vec_temp[2], vec_coordinate, "(,;)");
			transHINDER(vec_coordinate, vec_hinder);
			vec_coordinate.clear();
		}
		else if (p7 != NULL&&p8 != NULL)
		{
			;
		}
		delete[] p6, p7, p8;
	}
	
}

void initial_hinder(int a)
{
	for (int i = 0; i<a; i++)
	{
		vec_hinder.push_back(b);
	}
}

void transHINDER(vector<char*>& vecin, vector<bar>& vecout)
{
	for (int i = 0, j = 0; i<vecin.size(); i = i + 2, j++)
	{
		vecout.at(j).x = atoi(vecin.at(i));
		vecout.at(j).y = atoi(vecin.at(i + 1));
	}
}
