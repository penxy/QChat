#ifndef USERINFO_H
#define USERINFO_H
#include "CS_Sig_config.h"
#include "config.h"
#include "tool.h"
#include "Log.h"


//save some recv


class UserInfo : public Log{
public:
    UserInfo();
    virtual ~UserInfo();
protected:
	void Sort_FriendID();
public:
    int youid;
    std::string Sname;
    std::string password;
    std::string Rname;
    std::string message;
protected:
    bool OK;//一些交互信号的反馈    
};



#endif // USERINFO_H
