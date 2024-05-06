#ifndef __SEMQT_H
#define __SEMQT_H

#include "config.h"
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/socket.h>
#include <semaphore.h>
#include "Log.h"

/*
    in order to make pipe and shared memory between QtSig.cpp and WorkQt.cpp 
*/

class SemQt{
public:
    SemQt();
    ~SemQt();
public:
    void Sem_Init();
    void Sem_Wait();
    void Send2Pipe();
    /* 取消指向共享内存的指针 */
    void Leave_SharedMemory(char* buf);
    char* Get_RecvSharedMemory();
    char* Get_SendSharedMemory();

    void CreateSharedMemory();
private:
    sem_t Sem_Send2Qt;
    int Shmid_RecvBuf;
    int Shmid_SendBuf;
};


#endif
