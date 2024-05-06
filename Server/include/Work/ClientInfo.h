#ifndef __CLIENTINFO_H
#define __CLIENTINFO_H

#include <unordered_map>
#include <queue>

#include "config.h"
#include "User.h"
#include "log.h"
/*   
    sock                sock of ClientSend
    idx                 目前操作的user[idx]
    user[idx].youid     对方
    user[idx].myid = idx;
*/

class ClientInfo : public Log{
public:
	ClientInfo();
	virtual ~ClientInfo();

protected:
    static int sock;
    static int idx;//目前所操作的id
    static User* user;
    static std::unordered_map<int, bool>Online;
    static std::unordered_map<int, int>IDGetSock;
    static std::unordered_map<int, int>SockGetID;

    static constexpr char* Sig = ">s?";
    static std::queue<int>ID_Queue;	
};



#endif