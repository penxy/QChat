#ifndef __WORKSERVERSEND_H
#define __WORKSERVERSEND_H

#include "SemServer.h"
#include "ToStop.h"
#include "Log.h"


class WorkServerSend : public ToStop, public Log{
public:
    WorkServerSend();
    ~WorkServerSend() = default;
public:
    void SetSend();
    void SetSock(int sock);
    void* Run(void* arg);
    static void Stop();
private:
    void Send();
public:    
	int sock;
private:
    char* SendBuf;
};




#endif