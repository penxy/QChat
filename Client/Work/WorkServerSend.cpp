#include "WorkServerSend.h"
#include "SemServer.h"
#include "tool.h"

#include <string.h>


extern SemServer sem_server;
WorkServerSend::WorkServerSend() : sock(-1){
}
void WorkServerSend::SetSend(){
    SendBuf = sem_server.Get_SendSharedMemory();    
}

void* WorkServerSend::Run(void* arg){
    while(non_stop){
        sem_server.Wait();//_1
        if(non_stop)Send();
    }
    pthread_exit(NULL);
}
void WorkServerSend::Stop(){
    ToStop::Stop();
    /* wake up _1 */
    sem_server.Send2Pipe();
}
void WorkServerSend::SetSock(int sock){
    this->sock = sock;
}
void WorkServerSend::Send(){
    if(sock == -1){
        WriteLog("sock Send error");
        exit(EXIT_FAILURE);
    }
    send(sock, SendBuf, strlen(SendBuf), 0);
    WriteLog("Send to Server: " + std::string(SendBuf));
    ClearBuf(SendBuf);
}

