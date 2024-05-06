#ifndef __WORKSERVERRECV_H
#define __WORKSERVERRECV_H

#include "Log.h"
#include <semaphore.h>

class WorkServerRecv : public Log{
public:
    WorkServerRecv();
    virtual ~WorkServerRecv();
public:
    void SetSock(int sock);
    void SetRecv();
    void* Run(void* arg);
    void Stop();
private:
    static void Recv();
    static void signal_handler(int sig);
public:
    static int sock;
private:
    static sem_t sem_stop;
    static char* RecvBuf;
};

#endif