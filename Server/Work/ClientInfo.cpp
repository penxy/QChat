#include "ClientInfo.h"


User* ClientInfo::user = new User[MAX_ID];

std::unordered_map<int, bool>ClientInfo::Online;
std::unordered_map<int, int>ClientInfo::IDGetSock;
std::unordered_map<int, int>ClientInfo::SockGetID;

int ClientInfo::sock;
int ClientInfo::idx;

std::queue<int>ClientInfo::ID_Queue;

//#define DEBUG 1
ClientInfo::ClientInfo(){
	for(int i=0;i<MAX_ID;i++){
        user[i].myid = SockGetID[i] = IDGetSock[i] = -1;
        Online[i] = false;
        ID_Queue.push(i);
    }

#ifdef DEBUG
    for(int i=0;i<2;i++){
        user[i].myid = i;
        user[i].mypassword = "12345";
        ID_Queue.pop();
    }
    user[0].myname = "Tom";
    user[1].myname = "Jerry";
#endif
}
ClientInfo::~ClientInfo(){
	
	
}