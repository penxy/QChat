#ifndef __FRIENDLOGIC_H
#define __FRIENDLOGIC_H


#include "config.h"
#include "UserLogic.h"

#include <unordered_map>
#include <string>


class FriendLogic : public UserLogic{
public:
    FriendLogic();
    virtual ~FriendLogic();
public:
    void Friend_Allow();
    void Friend_Del();
private:
    int* friends;
    int friend_size;
    std::unordered_map<int, int>FIdGetIdx;
};




#endif