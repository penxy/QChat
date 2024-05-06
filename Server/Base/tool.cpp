#include "tool.h"
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>

int __64_10(const char& c){
    if('9' >= c && c >= '0')return (int)(c - '0');
    if('z' >= c && c >= 'a')return (int)(c - 'a') + 10;
    if('Z' >= c && c >= 'A')return (int)(c - 'A') + 36;
    if(c == '?')return 62;
    return 63;
}
int __64_10(const char* buf, int len){
    int ans = 0;
    for(int i=0;i<len;i++){
        ans = ans * 64 + __64_10(buf[i]);
    }
    return ans;
}

int GetID(const char* buf, int len){
    return __64_10(buf, len);
}
int GetGID(const char* buf, int len){
    return __64_10(buf, len);
}
int GetTotLen(const char* buf, int len){
    return __64_10(buf, len);
}

const std::string GetName(const char* buf, int len){
    std::string ans = "";
    for(int i=0;i<len && buf[i] != ' ';i++){
        ans.push_back(*(buf + i));
    }
    return ans;
}
const std::string GetPass(const char* buf, int len){
    return GetName(buf, len);   
}

char __10_64_char(int now){
    if(now <= 9 && 0 <= now)return (char)(now + '0');
    else if(now <= 35 && 10 <= now)return char(now  - 10 + 'a');
    else if(now <= 61 && 36 <= now)return char(now - 36 + 'A');
    else if(now <= 62)return '?';
    return '!';
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



void Set_Sig(char* buf, char sig){
    buf[Idx_Sig] = sig;
}
void Set_Sig_ID(char* buf, int myid, int idx){
    std::string temp = __10_64_string(myid, Len_ID);
    for(int i=0;i<Len_ID;i++){
        buf[i + idx] = temp[i];
    }
}

void Sig_Append_ID(char* buf, int id){
    strcpy(&buf[strlen(buf)], __10_64_string(id, Len_ID).c_str());
}
void Sig_Append_Name(char* buf, const std::string &name){
    int p = strlen(buf);
    strcpy(&buf[p], name.c_str());
    for(int i=p+name.size();i<p+8;i++){
        buf[i] = ' ';
    }
}

int Get_Text_ID(const char* buf, int len){
    return __64_10(&buf[Idx_Text_ID], len);
}
//const char* Text_UserInfoMess = "XXsxxUuuuYYMDHMS";
void Set_Text_ID(char* buf, int myid, int len){
    std::string MyID = __10_64_string(myid, 3);
    for(int i=Idx_Text_ID;i<Idx_Text_ID+len;i++){
        buf[i] = MyID[i];
    }
}





void reset_oneshot(int sock, int epollfd){
    struct epoll_event event;
	event.data.fd = sock;
	event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, sock, &event);
}

void delfd(int sock, int epollfd){
    close(sock);
    epoll_ctl(epollfd, EPOLL_CTL_DEL, sock, 0);
}
void ClearBuf(char* buf){
	memset(buf, '\0', strlen(buf));
}