#include "User.h"
#include <iostream>

extern const std::string __space;

void User::Clear_RBuf(){
    memset(ReadBuf, '\0', strlen(ReadBuf));
}
void User::Clear_Sbuf(){
    memset(SendBuf, '\0', strlen(SendBuf));
}
User::User(int sem_id) : Log(log_path), OK(false), sem_id(sem_id){
    ReadBuf = new char[MAX_PIPE_SIZE];
    SendBuf = new char[MAX_PIPE_SIZE];

    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;
}
User::~User(){
    delete[] ReadBuf;
    delete[] SendBuf;
}
void User::__Sem_Post(){
    semop(sem_id, &op, 1);
}

void User::SendSig(char sig){//OK 3.28
    CreateSendSigPack(sig);
    __Sem_Post();
    int fd = open(my_pipe, O_WRONLY);
    int ret = write(fd, SendBuf, strlen(SendBuf));
    WriteLog("ret = " + std::to_string(ret));
    close(fd);
    Clear_Sbuf();
}
void User::ReadSig(char sig){//OK 3.28
    SendSig(sig);
    int fd = open(my_pipe, O_RDONLY);
    read(fd, ReadBuf, MAX_PIPE_SIZE);
    close(fd);
}

Json::Value User::ApplyMessage(char sig){//OK 3.28
    ReadSig(sig);
    std::string packs = std::string(ReadBuf);

    Clear_RBuf();

    Json::Value data;
    Json::Reader reader;

    assert(reader.parse(packs, data));

    return data;
}

QStringListModel* User::ApplyData(char sig){//need data
    ReadSig(sig);
    std::string packs = std::string(ReadBuf);
    WriteLog(ReadBuf);
    Clear_RBuf();

    Json::Value data;
    Json::Reader reader;
    assert(reader.parse(packs, data));

    char Sig = data["sig"].asString()[0];
    QStringList S;
    switch(Sig){
    case CQ_FRIENDLSIT:{
        for(auto temp : data["arr"]){
            S << (getstr(temp["id"].asInt(), 5) + __space + temp["name"].asString()).c_str();
        }break;
    }
    case CQ_MYADD:{
        std::cout << "this\n";
        for(auto temp : data["arr"]){
            S << (getstr(temp["id"].asInt(), 5) + __space + temp["name"].asString()).c_str();
        }break;
    }
    case CQ_BEADD:{
        for(auto temp : data["arr"]){
            S << (getstr(temp["id"].asInt(), 5) + __space + temp["name"].asString()).c_str();
        }break;
    }
    }
    QStringListModel* ans = new QStringListModel(S);
    return ans;
}

/* the result */
void User::ApplyRes(char sig){//only need yes or no
    WriteLog("Allpy Client from res");
    ReadSig(sig);
    WriteLog("User.cpp: ApplyRes" + std::string("recvice the pack") + std::string(ReadBuf));
    std::string packs = std::string(ReadBuf);
    Clear_RBuf();

    Json::Value data;
    Json::Reader reader;
    assert(reader.parse(packs, data));

    char Sig = data["sig"].asString()[0];//can not asCString()

}
void User::CreateSendSigPack(char sig){
    Json::Value pack;

    std::string temp = "";
    temp.push_back(sig);
    pack["sig"] = temp;

    auto MyID = [&](){pack["myid"] = myid;};
    auto YouID = [&](){pack["youid"] = youid;};
    auto Name = [&](){pack["name"] = Sname;};
    auto Pass = [&](){pack["pass"] = password;};
    auto Mess = [&](){pack["mess"] = message;};

    switch(sig){
    case QC_FALLOW:
    case QC_FREJECT:{
        YouID();Name();
        break;
    }
    case QC_FADD:
    case QC_FDEL:
    case QC_USEARCHUSER:{
        YouID();break;
    }

    case QC_FRIENDLIST:{
        break;
    }
    case QC_FRIENDMESS:{
        YouID();break;
    }

    case QC_MYADD:
    case QC_BEADD:{
        break;
    }

    case QC_FMESSAGECLEAR:{
        YouID();break;
    }

    case QC_FSENDMESSAGE:{//send message to Friend
        YouID();Mess();break;
    }
    case QC_USERLOGIN:{
        MyID();Pass();break;
    }

    default:{
        break;
    }
    }
    Json::StreamWriterBuilder build;
    strcpy(SendBuf, Json::writeString(build, pack).c_str());
}
std::string User::getstr(int x, int len){
    std::string ans = "";
    while(x){
        ans.push_back(x % 10 + '0');
        x /= 10;
    }
    std::string temp = "";
    for(int i=0;i<len-(int)ans.size();i++)temp.push_back('0');
    for(int i=(int)ans.size()-1;i>=0;i--)temp.push_back(ans[i]);
    return temp;
}
