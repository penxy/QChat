#ifndef __CLIENT_H
#define __CLIENT_H

#include "Log.h"
#include "WorkQtRecv.h"
#include "WorkQtSend.h"
#include "WorkServerRecv.h"
#include "WorkServerSend.h"
#include <semaphore.h>

/* if recv SIGINT, Stop */

class Client final : public Log{
public:
    Client();
    virtual ~Client();
public:
    void Run();
private:
    static void StopSig(int sig);
    void Connect();
private:
    int sock;
    static sem_t sem_stop_client;

    static WorkQtRecv obj_WorkQtRecv;
    static WorkQtSend obj_WorkQtSend;
    static WorkServerRecv obj_WorkServerRecv;
    static WorkServerSend obj_WorkServerSend;
};


#endif