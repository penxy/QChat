#ifndef __WORKSERVER_H
#define __WORKSERVER_H

#include "UserSQL.h"
#include <semaphore.h>

class WorkServer : public UserSQL{
public:
    WorkServer();
    virtual ~WorkServer();
public:
    /* main to recv from qt, and then send something server */
    void Recv();
private:
	void RecvSig();
    void RecvText();
	
    /* wake up QtSig, and then QtSig send sig to qt */
    void WakeUpQt();
protected:
    void Send_F_Text();
    void SendSig(char sig);
private:
    int nowIdx;
    int seq;
   
    char* RecvBuf;
    char* SendBuf;    
protected:
	/* recv the mess of server, and then can send something to qt */
    sem_t sem_recv_server;
};



#endif
