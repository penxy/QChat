#ifndef __CLIENTLOGIC_H
#define __CLIENTLOGIC_H
#include "ClientInfo.h"

class ClientLogic : public ClientInfo{
public:
	ClientLogic() = default;
	virtual ~ClientLogic() = default;
protected:
	static void SendInBuffer();
protected:
	static void Login();
    static void Logout();	
};





#endif