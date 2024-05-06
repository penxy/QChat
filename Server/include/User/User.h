#ifndef __USER_H
#define __USER_H

#include "FriendLogic.h"


class User final : public FriendLogic{
public:
    User() = default;
    virtual ~User() = default;
};

#endif