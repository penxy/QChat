#include "ClientLogic.h"



void ClientLogic::Login(){
    Online[idx] = true;
    SockGetID[sock] = idx;
    IDGetSock[idx] = sock;
}
void ClientLogic::Logout(){
    Online[idx] = false;
    SockGetID[sock] = -1;
    IDGetSock[idx] = -1;
}

void ClientLogic::SendInBuffer(){//send something who in buffer
    //read
    user[idx].Read();
    int ret = send(sock, user[idx].GetReadIdx(), user[idx].GetReadLen(), 0);
	//update
    user[idx].AfterRead();
}