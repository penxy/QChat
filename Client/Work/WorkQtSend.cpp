#include "WorkQtSend.h"
#include "SemQt.h"
#include <string.h>

extern SemQt sem_qt;
void WorkQtSend::SetSend(){
    SendBuf = sem_qt.Get_SendSharedMemory();
}


void* WorkQtSend::Run(void* arg){
    while(non_stop){
        sem_qt.Sem_Wait();
        Send();
    }
    pthread_exit(NULL);
}



void WorkQtSend::Send(){
    int fd = open(pipe_path, O_WRONLY);
    int ret = write(fd, SendBuf, strlen(SendBuf));
    WriteLog("Send to Qt: " + std::string(SendBuf));
    memset(SendBuf, '\0', strlen(SendBuf));
    close(fd);
}

