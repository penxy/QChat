#include "log.h"

#include <iostream>
#include <ctime>  
#include <iomanip>  
#include <sstream>  
#include <syslog.h>  
#include <thread>
#include <string.h>  
#include <chrono>
Log::Log(const char* path){
    InitLog(path);
}
Log::~Log(){
    CloseLog();
}

void Log::InitLog(const char* path){
    openlog(path, LOG_PID | LOG_ODELAY | LOG_PERROR, LOG_USER);
    int fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0664);
    dup2(fd, STDERR_FILENO);
}
void Log::CloseLog(){
    closelog();
}
void Log::WriteLog(const char* mess){
    std::thread::id tid = std::this_thread::get_id();
    std::stringstream s;

    // 获取当前时间，包括微秒
    auto now = std::chrono::system_clock::now();
    auto now_us = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto epoch = now_us.time_since_epoch();
    std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(epoch);
    std::time_t now_c = std::chrono::system_clock::to_time_t(std::chrono::time_point<std::chrono::system_clock>(sec));

    int microseconds = epoch.count() % 1000000;
    s << "[" << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "." << std::setfill('0') << std::setw(6) << microseconds << "] [" << tid << "] " << mess;

    std::string temp = s.str();
    syslog(LOG_INFO, "%s", temp.c_str());
}
void Log::WriteLog(const std::string& mess){
    WriteLog(mess.c_str());
}