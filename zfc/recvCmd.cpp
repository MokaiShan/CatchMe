#include "stdafx.h"
#include "zfc.h"
#include "recvCmd.h"

//ȫ�ֱ���
int map_x, map_y;//��ͼ���
int Qp, Qt;//�����С͵����
int m, n;//�Ӿ�
int nround;//����
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
vector<char*> vec_string;//INI��INFָ���һ�ηָ�
vector<char*> vec_map;//��ͼ��С
vector<char*> vec_eye;//�Ӿ�
vector<char*> vec_num;//�����С͵����
vector<char*> vec_coordinate;//����
vector<coordinate> vec_police;//����
vector<coordinate> vec_thief;//С͵

police a = { "0",0,0,"T" };

//����ʵ��
int recvIni(char *str)
{
    //���ճ�ʼ��ָ���
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
    //����INFָ��    
    return 0;
}

//���յ�ENDָ��˳�����
int recvEnd(char *str)
{
    log("recv END!");
    exit(0);//�˳�����
}

int recvCmd(char *str)
{
    log("[RECV]: %s",str);
    if(strstr(str,"INF"))
    {
        recvInf(str);
        //���յ�INF֮��Ĵ���
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

