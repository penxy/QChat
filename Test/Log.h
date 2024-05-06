#ifndef __LOG_H
#define __LOG_H

#include <string>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


class Log{
public:
    Log(const char* path = Initpath);
    virtual ~Log();
public:
    static void WriteLog(const char* mess);
    static void WriteLog(const std::string& mess);
private:
    static void InitLog(const char* path);
    static void CloseLog();
private:
    static constexpr char* Initpath = "/home/pxy/Work_2/Client/Log/log.txt";
};



#endif



