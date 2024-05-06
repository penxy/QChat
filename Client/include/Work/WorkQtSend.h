#ifndef __WORKQTSEND_H
#define __WORKQTSEND_H
#include "ToStop.h"
#include "Log.h"

class WorkQtSend : public ToStop, public Log{
public:
    WorkQtSend() = default;
    virtual ~WorkQtSend() = default;
public:
    void SetSend();
    void* Run(void* arg);
private:
    void Send();
private:
    static constexpr char* pipe_path = "/tmp/my_pipe";
    char *SendBuf;
};


#endif