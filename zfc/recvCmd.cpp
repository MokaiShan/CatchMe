#include "stdafx.h"
#include "zfc.h"
#include "recvCmd.h"

//ȫ�ֱ���
int map_x, map_y;//��ͼ���
int Qp, Qt;//�����С͵����
int m, n;//�Ӿ�
int nround;//����
vector<char*> vec_string;//INI��INFָ���һ�ηָ�
vector<char*> vec_map;//��ͼ��С
vector<char*> vec_eye;//�Ӿ�
vector<char*> vec_num;//�����С͵����
vector<char*> vec_coordinate;//����
vector<coordinate> vec_police;//����
vector<coordinate> vec_thief;//С͵
vector<bar> vec_hinder;//�ϰ���
typedef struct coordinate
{
	string id;
	int x;
	int y;
	char* move;
}police, thief;
police p = { "0",0,0,"T" };//���ڳ�ʼ��
thief t = { "0",0,0,"T" };//���ڳ�ʼ��
struct bar
{
	int x;
	int y;
};


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
		cout << vec_thief.at(0).x;
	}
	else         //do nothing
	{
		;
	}
    return 0;
}

int recvInf(char *str)
{
	//����INFָ��

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
		buf += to_string(Qp) + "](";
		for (i = 0; i < Qp; i++) {
			buf += vec_police.at(i).id + ","
				+ vec_police.at(i).move + ";";
		}
		buf += ")";
	}
	else if (myRole == "THI")
	{
		buf += to_string(Qt) + "](";
		for (i = 0; i < Qt; i++) {
			buf += vec_thief.at(i).id + ","
				+ vec_thief.at(i).move + ";";
		}
		buf += ")";
	}
	char* buff = buf.c_str;
	sendCmd(buff);
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
	char *p;
	p = strtok(str, sep);
	while (p)
	{
		vec.push_back(p);
		p = strtok(NULL, sep);
	}
	delete p;
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
}

void normal_direction(vector<coordinate>& vec_role) {
	int rand_direction = rand() % 4;
	for (int i = 0; i < vec_role.size; i++) {
		for (int k = 0; k < vec_hinder.size; k++) {
			while (true) {
				if (rand_direction == 0) {
					if ((vec_hinder.at(k).y - vec_role.at(i).y) == 0)
					{
						vec_role.at(i).move = "B";
						break;
					}
					else if ((vec_hinder.at(k).x - vec_role.at(i).x) == 0)
					{
						vec_role.at(i).move = "D";
						break;
					}
					else if ((vec_role.at(k).y - vec_hinder.at(i).y) == 0)
					{
						vec_role.at(i).move = "N";
						break;
					}
					else if ((vec_role.at(k).x - vec_hinder.at(i).x) == 0)
					{
						vec_role.at(i).move = "X";
						break;
					}
				}
				else if (rand_direction == 1) {
					if ((vec_hinder.at(k).x - vec_role.at(i).x) == 0)
					{
						vec_role.at(i).move = "D";
						break;
					}
					else if ((vec_role.at(k).y - vec_hinder.at(i).y) == 0)
					{
						vec_role.at(i).move = "N";
						break;
					}
					else if ((vec_role.at(k).x - vec_hinder.at(i).x) == 0)
					{
						vec_role.at(i).move = "X";
						break;
					}
					else if ((vec_hinder.at(k).y - vec_role.at(i).y) == 0)
					{
						vec_role.at(i).move = "B";
						break;
					}
				}
				else if (rand_direction == 2) {
					if ((vec_role.at(k).y - vec_hinder.at(i).y) == 0)
					{
						vec_role.at(i).move = "N";
						break;
					}
					else if ((vec_role.at(k).x - vec_hinder.at(i).x) == 0)
					{
						vec_role.at(i).move = "X";
						break;
					}
					else if ((vec_hinder.at(k).y - vec_role.at(i).y) == 0)
					{
						vec_role.at(i).move = "B";
						break;
					}
					else if ((vec_hinder.at(k).x - vec_role.at(i).x) == 0)
					{
						vec_role.at(i).move = "D";
						break;
					}
				}
				else if (rand_direction == 3) {
					if ((vec_role.at(k).x - vec_hinder.at(i).x) == 0)
					{
						vec_role.at(i).move = "X";
						break;
					}
					else if ((vec_hinder.at(k).y - vec_role.at(i).y) == 0)
					{
						vec_role.at(i).move = "B";
						break;
					}
					else if ((vec_hinder.at(k).x - vec_role.at(i).x) == 0)
					{
						vec_role.at(i).move = "D";
						break;
					}
					else if ((vec_role.at(k).y - vec_hinder.at(i).y) == 0)
					{
						vec_role.at(i).move = "N";
						break;
					}
				}
			}
		}
	}
}

