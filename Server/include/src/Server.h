#ifndef __SERVER_H
#define __SERVER_H

#include "config.h"
#include "User.h"
#include "pool.h"
#include "log.h"

#define MAX_EPOLL 32768 + 10
#define MAX_LISTEN 1024


#define SERVERIP "127.0.0.1"

class Server : public Log{
public:
    Server();
    ~Server();   
public:
    void Run();
private:
    static void Stop(int sig);

    void Server_Init();
    void Server_Destroy();
private:
    void setnonblock(int fd);
    void addfd(int fd, bool is_oneshot);
    void delfd(int fd);
    void reset_oneshot(int fd);    
private:
    int sock;
    static bool not_stop;
private:
    int epollfd;
    struct epoll_event* events;
	ThreadPool* pool;
    static constexpr char* log_path = "Log/Log_Server.txt";
};





#endif