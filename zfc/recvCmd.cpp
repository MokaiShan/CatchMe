#include "stdafx.h"
#include "zfc.h"
#include "recvCmd.h"

//ȫ�ֱ���
int map_x, map_y;//��ͼ���
int Qp, Qt;//�����С͵����
int m, n;//�Ӿ�
int nround;//����
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

