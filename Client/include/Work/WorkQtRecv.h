#ifndef __WORKQTRECV_H
#define __WORKQTRECV_H

#include "ToStop.h"
#include "Log.h"
#include <sys/sem.h>

class WorkQtRecv : public ToStop, public Log{
public:
    WorkQtRecv();
    virtual ~WorkQtRecv() = default;
public:
    void SetRecv();
    void* Run(void* arg);
private:
    void Recv();
private:
    char* RecvBuf;

    int sem_id;
    struct sembuf op;

    static constexpr char* pipe_path = "/tmp/my_pipe";
    const char* Qt_path = "Qt/Test";
};

#endif