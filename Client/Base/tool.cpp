#include "tool.h"
#include <algorithm>
#include <fcntl.h>
#include "Log.h"

extern Log log_server;


int __64_10(const char& c){
    if('9' >= c && c >= '0')return (int)(c - '0');
    if('z' >= c && c >= 'a')return (int)(c - 'a') + 10;
    if('Z' >= c && c >= 'A')return (int)(c - 'A') + 36;
    if(c == '?')return 62;
    if(c == '!')return 63;
    std::cerr << "__64_10 error 2\n";
}
char __10_64_char(int now){
    if(now <= 9 && 0 <= now)return (char)(now + '0');
    else if(now <= 35 && 10 <= now)return char(now - 10 + 'a');
    else if(now <= 61 && 36 <= now)return char(now - 36 + 'A');
    else if(now <= 62)return '?';
    return '!';
}


int __64_10(const std::string& s){
    int temp = 0;
    int ret = 0;
    for(const char& c : s){
        if('9' >= c && c >= '0')temp = (temp << 6) + (int)(c - '0');
        else if('z' >= c && c >= 'a')temp = (temp << 6) + (int)(c - 'a') + 10;
        else if('Z' >= c && c >= 'A')temp = (temp << 6) + (int)(c - 'A') + 36;
        else if(c == '?')temp = (temp << 6) + 62;
        else if(c == '!')temp = (temp << 6) + 63;
    }return temp;
}
std::string __10_64_string(int temp, int len){
    std::string s = "";
    while (temp) {
        s.push_back(__10_64_char(temp % 64));
        temp /= 64;
    }
    std::reverse(s.begin(), s.end());
    while (s.size() < len) {
        s = "0" + s;
    }
    return s;
}
std::string get_time_10(){
    time_t now = time(0);
    struct tm* temp = localtime(&now);
    std::string ans = "";
    ans += std::to_string(temp -> tm_year + 1900);ans.push_back('-');
    ans += std::to_string(temp -> tm_mon + 1);ans.push_back('-');
    ans += std::to_string(temp -> tm_mday);ans.push_back(' ');
    ans += std::to_string(temp -> tm_hour);ans.push_back(':');
    ans += std::to_string(temp -> tm_min);ans.push_back(':');
    ans += std::to_string(temp -> tm_sec);
    return ans;
}
std::string get_time_64(){
    time_t now = time(0);
    struct tm* temp = localtime(&now);
    std::string ans = "";
    ans = ans + __10_64_string(temp -> tm_year + 1900, 2);
    ans = ans + __10_64_char(temp -> tm_mon + 1);
    ans = ans + __10_64_char(temp -> tm_mday);
    ans = ans + __10_64_char(temp -> tm_hour);
    ans = ans + __10_64_char(temp -> tm_min);
    ans = ans + __10_64_char(temp -> tm_sec);
    return ans;
}
std::string get_time(int year, int month, int day, int hour, int minu, int seconds){
    std::string ans = std::to_string(year);
    ans.push_back('-');
    ans = ans + std::to_string(month);
    ans.push_back('-');
    ans = ans + std::to_string(day);
    ans.push_back(' ');
    ans = ans + std::to_string(hour);
    ans.push_back(':');
    ans = ans + std::to_string(minu);
    ans.push_back(':');
    ans = ans + std::to_string(seconds);
    return ans;
}


std::string getstr(char* buf, int nowIdx, int l, int r){
    std::string s = "";
    for(int i=l;i<=r;i++){
        s.push_back(buf[nowIdx + i]);
    }
    return s;
}
int GetID(char* buf, int nowIdx){
    return __64_10(getstr(buf, nowIdx, 3, 5));
}
int GetGID(char* buf, int nowIdx){
    return __64_10(getstr(buf, nowIdx, 6, 7));
}







void ClearBuf(char* buf){
	memset(buf, '\0', strlen(buf));	
}