#ifndef __CLIENTRECV_H
#define __CLIENTRECV_H

#include "ClientSend.h"

class ClientRecv : ClientSend{
public:
	ClientRecv() = default;
	virtual ~ClientRecv() = default;
public:
    static void Recv(void* info);
private:    
    static void RecvSig();
private:
    static char* buf;
};


#endif
