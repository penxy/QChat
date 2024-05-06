#include "Server.h"
#include <functional>
#include <signal.h>

#include "tool.h"
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>


#include <pthread.h>

#define NOT_TIMEWAIT 1
#define debug(x) std::cout << #x << " = " << x << "\n"

bool Server::not_stop = true;

Server::Server(){
	Server_Init();
}
Server::~Server(){}

void Server::setnonblock(int fd){
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}
void Server::addfd(int fd, bool is_oneshot){
    struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	if(is_oneshot)event.events |= EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblock(fd);
}
void Server::delfd(int fd){
	struct epoll_event event;
	memset(&event, 0, sizeof(event));
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
	close(fd);
}
void Server::reset_oneshot(int fd){
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}
void Server::Stop(int sig){
	not_stop = false;
}

void Server::Run(){
	int cnt;
	while(not_stop){
		cnt = epoll_wait(epollfd, events, MAX_EPOLL, -1);
		for(int i=0;i<cnt;i++){
			int sockfd = events[i].data.fd;
			if(sockfd == sock){//MySig::Conn
				struct sockaddr_in s_adr;
				socklen_t s_adr_len = sizeof(s_adr);
				int c_sock = accept(sockfd, (struct sockaddr*)&s_adr, &s_adr_len);
				addfd(c_sock, true);
				std::cout << "Client Connect:  " + std::to_string(c_sock) << "\n";
			}else if(events[i].events & EPOLLIN){
				struct Info* temp = new Info(sockfd, epollfd); 
				pool->Add_Task((void*)temp);//and then use a thread to run UserSock.cpp work();
			}
		}
	}
	Server_Destroy();
	WriteLog("Server Stop");
}
void Server::Server_Init(){
	signal(SIGINT, Stop);
	pool = ThreadPool::Init_pool();

	sock = socket(AF_INET, SOCK_STREAM, 0);
#ifdef NOT_TIMEWAIT
	int optval = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
#endif
	struct sockaddr_in adr;
	memset(&adr, 0, sizeof(adr));
	adr.sin_family = AF_INET;
	adr.sin_addr.s_addr = inet_addr(SERVERIP);
	adr.sin_port = htons(SERVER_PORT);
	int ret;
	ret = bind(sock, (struct sockaddr*)&adr, sizeof(adr));
	ret = listen(sock, MAX_LISTEN);

	events = new epoll_event[MAX_EPOLL];
    epollfd = epoll_create(5);

	addfd(sock, false);
	WriteLog("Server Run");
}
void Server::Server_Destroy(){
	pool->Destroy_pool();
	delete[] events;
	close(epollfd);
	close(sock);
}