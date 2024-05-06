#include "SemServer.h"

#include <iostream>
SemServer::SemServer() : Shmid_RecvBuf(-1), Shmid_SendBuf(-1){
    CreateSharedMemory();
    Sem_Init();
}
SemServer::~SemServer(){
    sem_destroy(&Sem_Send2Server);
    shmctl(Shmid_RecvBuf, IPC_RMID, NULL);
    shmctl(Shmid_SendBuf, IPC_RMID, NULL);
}
void SemServer::Sem_Init(){
    sem_init(&Sem_Send2Server, 0, 0);
}

void SemServer::Send2Pipe(){
    sem_post(&Sem_Send2Server);
}
void SemServer::Wait(){
    sem_wait(&Sem_Send2Server);
}
void SemServer::Leave_SharedMemory(char* buf){
    shmdt(buf);
}
char* SemServer::Get_RecvSharedMemory(){
    return (char*)shmat(Shmid_RecvBuf, NULL, 0);
}
char* SemServer::Get_SendSharedMemory(){
    return (char*)shmat(Shmid_SendBuf, NULL, 0);
}
void SemServer::CreateSharedMemory(){
    if(Shmid_RecvBuf == -1){
        key_t key = ftok("sem/sem_cs_recv", 'S');
        Shmid_RecvBuf = shmget(key, MAX_RECV_SIZE, 0666 | IPC_CREAT);
    }
    if(Shmid_SendBuf == -1){
        key_t key = ftok("sem/sem_cs_send", 'S');
        Shmid_SendBuf = shmget(key, MAX_SEND_SIZE, 0666 | IPC_CREAT);
    }
}