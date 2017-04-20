#pragma once

extern int recvCmd(char *str);
extern int sendCmd(char *str);
extern struct coordinate;

void recvIniPol(char *str);
void recvIniThi(char *str);
void strtokCmd(char *str, vector<char*>& vec, const char *sep);
void printvec(vector<char*>& vec);
void transCmd(vector<char*>& vecin, vector<coordinate>& vecout);
void initial();
void clear();