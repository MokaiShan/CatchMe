#pragma once

extern int recvCmd(char *str);
extern int sendCmd(char *str);
extern struct coordinate;
extern struct bar;

void recvIniPol(char *str);
void recvIniThi(char *str);
void strtokCmd(char *str, vector<char*>& vec, const char *sep);
void transCmd(vector<char*>& vecin, vector<coordinate>& vecout);
void initial();
void clear();
void normal_direction(vector<coordinate>& vec_role);
void initial_hinder(int a);
void transHINDER(vector<char*>& vecin, vector<bar>& vecout);
void recv_messegeInf(char*s);