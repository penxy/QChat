#ifndef __TOOL_H
#define __TOOL_H
#include <string>
#include <assert.h>
#include <string.h>

#define debug(x) std::cout << #x << " = " << x << "\n";

const int Idx_Len = 0;
const int Idx_ID = 3;
const int Idx_GID = 6;

//>s?
const int Idx_Sig = 2;//'?'
const int Idx_SigFlag = 0;//'>'

/* idx of name */
const int Idx_N_U = 6;
const int Idx_N_UG = 8;
const int Idx_N = 3;

/* idx of password, if have id/gid/name/pass */
const int Idx_P_N = 11;
const int Idx_P_U = 6;
const int Idx_P_UG = 8;
const int Idx_P_UGN = 16;
const int Idx_P_UGNP = 32;
const int Idx_P_UGP = 24;


const int Len_Len = 2;
const int Len_ID = 3;
const int Len_GID = 2;
const int Len_Name = 8;
const int Len_Pass = 16;


const int Idx_Text_ID = 4;

const int Min_Len = 3;//>s?

struct Info{
    int c_sock;
    int epollfd;
    Info(int c_sock, int epollfd){
        this->c_sock = c_sock;
        this->epollfd = epollfd;
    }
};


int __64_10(const char* buf, int len);
int __64_10(const char& c);
int GetID(const char* buf, int len = Len_ID);
int GetGID(const char* buf, int len = Len_GID);
int GetTotLen(const char* buf, int len = Len_Len);

const std::string GetName(const char* buf, int len = Len_Name);
const std::string GetPass(const char* buf, int len = Len_Pass);



char __10_64_char(int now);
std::string __10_64_string(int temp, int len);



void Set_Sig(char* buf, char sig);
void Set_Sig_ID(char* buf, int myid, int idx = Len_ID);

void Sig_Append_ID(char* buf, int id);
void Sig_Append_Name(char* buf, const std::string &name);


int Get_Text_ID(const char* buf, int len = Len_ID);
void Set_Text_ID(char* buf, int myid, int len = Len_ID);



void reset_oneshot(int sock, int epollfd);
void delfd(int sock, int epollfd);

void ClearBuf(char* buf);


#endif

