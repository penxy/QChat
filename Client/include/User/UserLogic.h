#ifndef __USERLOGIC_H
#define __USERLOGIC_H

#include "UserInfo.h"

class UserLogic : public UserInfo{
public:
	UserLogic();
	virtual ~UserLogic() = default;
public:
	void User_Create();
    void User_Login();
public:
	bool login_ok;//登录成功
protected:
    int myid;
	char MyName[MAX_USERNAME_SIZE];//保存自己的名字	
};

#endif

