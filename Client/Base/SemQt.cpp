#include "SemQt.h"
#include <iostream>
#include <string.h>
#include <errno.h>

SemQt::SemQt() : Shmid_RecvBuf(-1), Shmid_SendBuf(-1){
    CreateSharedMemory();
    Sem_Init();
}
SemQt::~SemQt(){
    sem_destroy(&Sem_Send2Qt);
    shmctl(Shmid_RecvBuf, IPC_RMID, NULL);
    shmctl(Shmid_SendBuf, IPC_RMID, NULL);
}
void SemQt::Sem_Init(){
    sem_init(&Sem_Send2Qt, 0, 0);
}
void SemQt::Sem_Wait(){
    sem_wait(&Sem_Send2Qt);
}
void SemQt::Send2Pipe(){
    sem_post(&Sem_Send2Qt);        
}
/* 取消指向共享内存的指针 */
void SemQt::Leave_SharedMemory(char* buf){
    shmdt(buf);
}
char* SemQt::Get_RecvSharedMemory(){
    return (char*)shmat(Shmid_RecvBuf, NULL, 0);
}
char* SemQt::Get_SendSharedMemory(){
    return (char*)shmat(Shmid_SendBuf, NULL, 0);
}
void SemQt::CreateSharedMemory(){
    if(Shmid_RecvBuf == -1){
        key_t key = ftok("sem/sem_cq_recv", 'S');
        Shmid_RecvBuf = shmget(key, MAX_PIPE_SIZE, 0666 | IPC_CREAT);
    }
    if(Shmid_SendBuf == -1){
        key_t key = ftok("sem/sem_cq_send", 'S');
        Shmid_SendBuf = shmget(key, MAX_PIPE_SIZE, 0666 | IPC_CREAT);
    }
 }