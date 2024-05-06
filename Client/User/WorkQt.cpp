/*
* author: pxy
* 2024-03-26 22:44:16 星期二
*/
#include "WorkQt.h"
#include "SemQt.h"

#include "QC_Sig_config.h"

#include <jsoncpp/json/json.h>
#include <assert.h>

#define debug(x) std::cout << #x << " = " << x << "\n"

extern SemQt sem_qt;
WorkQt::WorkQt(){
    SendBuf = sem_qt.Get_SendSharedMemory();
    RecvBuf = sem_qt.Get_RecvSharedMemory();
}
WorkQt::~WorkQt(){
    //...如果不是注销, 将数据写到数据库
}


void WorkQt::Wait_Server(){
    sem_wait(&sem_recv_server);
}

/*

CQ_U_CREATE_YES
CQ_FIND_ID_YES	

CQ_FRIEND_LIST
CQ_FRIEND_MESS
CQ_MYADD
CQ_MYBEADD

*/


void WorkQt::SendQTSig(char sig){
	Json::Value pack;
    std::string temp = "";
    temp.push_back(sig);

    pack["sig"] = temp;
    Json::Value arr(Json::arrayValue);
    Json::Value OneOfArr;

    switch(sig){
    case CQ_U_CREATE_YES:{
        pack["id"] = myid;break;
    }
    case CQ_FIND_ID_YES:{
        pack["name"] = Rname;break;
    }
	
    case CQ_FRIEND_LIST:{
        for(int i=0;i<(int)FriendInfo.size();i++){
            OneOfArr["id"] = FriendInfo[i].id;
            OneOfArr["name"] = FriendInfo[i].name;
            pack["arr"].append(OneOfArr);
        }break;
    }
    case CQ_FRIEND_MESS:{
        //time mess
        int idx = FIdGetIdx[youid];
        for(const auto& temp : FriendInfo[idx].Message){
			OneOfArr["type"] = temp.type;
            OneOfArr["time"] = temp.time;
            OneOfArr["mess"] = temp.mess;
            pack["arr"].append(OneOfArr);
        }break;
    }
    case CQ_MYADD:{
        for(const auto& temp : MyAddID){
            OneOfArr["id"] = temp.id;
            OneOfArr["name"] = temp.name;
            pack["arr"].append(OneOfArr);
        }break;
    }
    case CQ_MYBEADD:{
        for(const auto& temp : MyBeAddID){
            OneOfArr["id"] = temp.id;
            OneOfArr["name"] = temp.name;
            pack["arr"].append(OneOfArr);
        }break;
    }
    default:{
        break;
    }
    }
    Json::StreamWriterBuilder build;
    strcpy(SendBuf, Json::writeString(build, pack).c_str());

    sem_qt.Send2Pipe();    
}

/*

QC_F_ALLOW
QC_F_REJECT
QC_F_ADD
QC_F_DEL

QC_FIND_ID
QC_U_CREATE
QC_U_LOGIN

QC_F_CLEAR_MESS
QC_F_SEND_MESS

QC_FRIEND_LIST
QC_FRIEND_MESS

QC_MYADD
QC_MYBEADD

*/


void WorkQt::RecvQTSig(){
    Json::Value pack;
    Json::Reader reader;
    assert(reader.parse(std::string(RecvBuf), pack));
    ClearBuf(RecvBuf);
    
    auto YouID = [&](){youid = pack["youid"].asInt();};
    auto MyID = [&](){myid = pack["myid"].asInt();};
    //auto GID = [&](){gid = pack["gid"].asInt();};
    auto Mess = [&](){message = pack["mess"].asString();};
    auto Name = [&](){Sname = pack["name"].asString();if(Sname == "")Sname = MyName;};
    auto Pass = [&](){password = pack["pass"].asString();};

    char Sig = pack["sig"].asString()[0];
    Json::Value SendPack;
    switch(Sig){
    case QC_F_ALLOW:{
        YouID();Name();
		
        if(Friend_Allow())SendSig(CS_F_ALLOW);
		break;
    }
    case QC_F_REJECT: {
        YouID();Name();

        SendSig(CS_F_REJECT);

        Friend_Reject();
        break;
    }
    case QC_F_ADD:{
        YouID();
        Name();
        
        //friend now
        for(int i=0;i<FriendInfo.size();i++){
            if(youid == FriendInfo[i].id)return;
        }

        if(Friend_Add())SendSig(CS_F_ADD);

        break;
    }
    case QC_F_DEL:{
        YouID();

        SendSig(CS_F_DEL);

        Friend_Del();
        break;
    }
    case QC_FIND_ID:{//ID
        YouID();
        
        SendSig(CS_FIND_ID);
        Wait_Server();
        
        if(OK)SendQTSig(CQ_FIND_ID_YES);
        else SendQTSig(CQ_FIND_ID_NO);
        break;
    }

    case QC_U_CREATE:{//ID Create
        Name();Pass();
        //strcpy(MyName, Sname.c_str());

        SendSig(CS_U_CREATE);
        Wait_Server();


        if(OK){
            User_Create();
            SendQTSig(CQ_U_CREATE_YES);
        }
        else SendQTSig(CQ_U_CREATE_NO);
        break;
    }
    case QC_U_LOGIN:{
        MyID();
        Pass();

        SendSig(CS_U_LOGIN);
        Wait_Server();

        if(OK){
            User_Login();
            SendQTSig(CQ_U_LOGIN_YES);
        }
        else SendQTSig(CQ_U_LOGIN_NO);
        break;
    }


    case QC_F_CLEAR_MESS:{
        YouID();
        
        Clear_FriendMess();break;
    }
    case QC_F_SEND_MESS:{
        YouID();Mess();

        Send_F_Text();
        break;
    }
    case QC_FRIEND_LIST:{
        SendQTSig(CQ_FRIEND_LIST);break;
    }
    case QC_FRIEND_MESS:{
        YouID();
        SendQTSig(CQ_FRIEND_MESS);break;
    }
    case QC_MYADD:{
        SendQTSig(CQ_MYADD);break;
    }
    case QC_MYBEADD:{
        SendQTSig(CQ_MYBEADD);break;
    }
    default:{
        WriteLog("QtSig.cpp:497, SendQTSig error");
    }
    }
}



