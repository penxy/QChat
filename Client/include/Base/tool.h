#ifndef __TOOL_H
#define __TOOL_H


#include <string>
#include <cstring>
#include <string.h>
#include <iostream>



int __64_10(const std::string& s);//64转10
std::string __10_64_string(int temp, int len);//10转64 字符串


std::string get_time_64();//获取64进制的时间
std::string get_time_10();//获取10进制的时间
std::string get_time(int year, int month, int day, int hour, int minu, int seconds);


std::string getstr(char* buf, int nowIdx, int l, int r);
int GetID(char* buf, int nowIdx);
int GetGID(char* buf, int nowIdx);


void ClearBuf(char* buf);




#endif