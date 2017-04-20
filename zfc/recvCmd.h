#pragma once

extern int recvCmd(char *str);
extern int sendCmd(char *str);
void recvIniPol(char *str);
void recvIniThi(char *str);
extern struct coordinate;

void strtokCmd(char *str, vector<char*>& vec, const char *sep);
void printvec(vector<char*>& vec);
void transPOL(vector<char*>& vecin, vector<coordinate>& vecout);
void initial();