#ifndef __USERLOGIC_H
#define __USERLOGIC_H

#include "UserInfo.h"


/* 执行逻辑 */
class UserLogic : public UserInfo{
public:
    UserLogic() = default;
    virtual ~UserLogic() = default;
public:
    void User_Create(int IndexOfUser);
    bool User_Login();
    void User_Logout();
};



#endif