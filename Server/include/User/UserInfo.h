#ifndef __USERINFO_H
#define __USERINFO_H
#include "config.h"
#include "buffer.h"
#include <unordered_map>


class UserInfo{
public:
    UserInfo() = default;
    virtual ~UserInfo() = default;
public:
    void WriteInBuffer(char* buf);
    char* GetReadIdx(); 
    int GetReadLen();

    bool empty_buffer();


    void Read();
    void AfterRead();//更新下标[ReadPos]
public:
    int myid;           //if == -1, no this account;
    std::string myname;
    std::string mypassword;    

    int youid;
    std::string Rname;
    std::string pass;
private:
    Buffer buffer;
};



#endif