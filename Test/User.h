#ifndef USER_H
#define USER_H
#include "CQSigconfig.h"
#include "LimitConfig.h"

#include <jsoncpp/json/json.h>
#include <QStringListModel>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>
#include "Log.h"


class User : Log{
public:
    User(int sem_id);
    virtual ~User();
public:
    void SendSig(char sig);
    void ApplyRes(char sig);
    QStringListModel* ApplyData(char sig);
    Json::Value ApplyMessage(char sig);
public:
    bool OK;
    int myid;
    char MyName[MAX_USERNAME_SIZE];
    int gid;
    int youid;
    std::string message;
    std::string Sname;
    std::string Rname;
    std::string password;
private:
    void ReadSig(char sig);
    void CreateSendSigPack(char sig);
    void Clear_RBuf();
    void Clear_Sbuf();
private:
    std::string getstr(int x, int len);
    /* to wake up Client to recvice the json pack */
    void __Sem_Post();
private:
    const char* my_pipe = "/tmp/my_pipe";
    char* ReadBuf;
    char* SendBuf;
    int sem_id;
    struct sembuf op;

    static constexpr char* log_path = "/home/pxy/Work_2/Client/Log/QtLog.txt";
};















#endif
