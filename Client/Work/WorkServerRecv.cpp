#include "WorkServerRecv.h"
#include "User.h"
#include "SemServer.h"


#include <signal.h>
#include <assert.h>


extern User *user;
sem_t WorkServerRecv::sem_stop;
int WorkServerRecv::sock = -1;
char* WorkServerRecv::RecvBuf;

extern SemServer sem_server;//when have mess need send to server
extern pid_t QtId;


void set_socket_nonblocking(int sockfd) {
    int ret = fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_ASYNC);
    assert(ret == 0);
}
/* set sock process*/
void set_socket_owner(int sockfd, pid_t pid) {
    int ret = fcntl(sockfd, F_SETOWN, pid);
    assert(ret == 0);
}

void WorkServerRecv::signal_handler(int sig) {
	if(sig == SIGIO){
        Recv();
    }else
        WriteLog("signal_handler error");
}

void* WorkServerRecv::Run(void* arg){
    set_socket_nonblocking(sock);
    set_socket_owner(sock, getpid());
    signal(SIGIO, signal_handler);

    sem_wait(&sem_stop);
    pthread_exit(NULL);
}

void WorkServerRecv::Recv(){
    memset(RecvBuf, '\0', strlen(RecvBuf));
    int ret = recv(sock, RecvBuf, MAX_RECV_SIZE - 1, 0);
    WriteLog(std::string("Recv From Server: ") + std::string(RecvBuf));
    if (ret == 0) {
        
        if(user->login_ok)user->Save();

        WriteLog("Server disconnected");
        kill(QtId, SIGINT);
        exit(EXIT_SUCCESS);
    } else if (ret < 0) {
    } else {
        user->Recv();
    }
}



void WorkServerRecv::Stop(){
    sem_post(&sem_stop);
}
WorkServerRecv::WorkServerRecv(){
    sem_init(&sem_stop, 0, 0);
}
WorkServerRecv::~WorkServerRecv(){
    sem_destroy(&sem_stop);
}
void WorkServerRecv::SetRecv(){
    RecvBuf = sem_server.Get_RecvSharedMemory();
}
void WorkServerRecv::SetSock(int sock){
    this->sock = sock;
}