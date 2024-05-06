#ifndef __CLIENTSEND_H
#define __CLIENTSEND_H

#include "SQL.h"
#include "CS_Sig_config.h"

#include <iostream>



class ClientSend : public SQL{
public:
	ClientSend() = default;
	virtual ~ClientSend() = default;
protected:
	static void Send2CR(char* buf);/* Send to Client_Recv */
	static void Send2CS();/* Send to Client_Send */
    static void SendText(char* buf);
    static void SendSig(char sig);
private:
	static char* buf;	
};



#endif