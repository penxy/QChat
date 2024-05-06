#ifndef __SEMSERVER_H
#define __SEMSERVER_H

#include "config.h"
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/socket.h>
#include <semaphore.h>
#include "Log.h"

/*
    in order to make sem and shared memory between ServerSig and WorkServer
*/

class SemServer{
public:
    SemServer();
    ~SemServer();
public:
    void Sem_Init();
    void Send2Pipe();
    void Wait();
    void Leave_SharedMemory(char* buf);
    char* Get_RecvSharedMemory();
    char* Get_SendSharedMemory();
    void CreateSharedMemory();
private:
    sem_t Sem_Send2Server;
    int Shmid_RecvBuf;
    int Shmid_SendBuf;
};



#endif
