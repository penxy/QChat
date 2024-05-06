#include "ClientRecv.h"
#include "tool.h"


char* ClientRecv::buf = new char[MAX_BUF_SIZE]; 

void ClientRecv::Recv(void *info){
    sock = ((Info*)info)->c_sock;
    int epollfd = ((Info*)info)->epollfd;
    ClearBuf(buf);

    while(1){
        int ret = recv(sock, buf, MAX_BUF_SIZE - 1, 0);
        if(ret < 0){
            if(errno == EAGAIN)reset_oneshot(sock, epollfd);
            return;  
        }else if(ret == 0){
            delfd(sock, epollfd);
            Logout();
            WriteLog("client disconnect");
            return;
        }else{
            WriteLog("Recv from Client: " + std::string(buf));
        }

        if(ret < Min_Len){
            WriteLog("unknow len");
        }
        if(buf[Idx_SigFlag] == '>'){
            RecvSig();
        }else{
            SendText(buf);
            ClearBuf(buf);
        }
    }
    delete info;
}

/* recv Sig from Client */
void ClientRecv::RecvSig(){
    char sig = buf[Idx_Sig];
    /* if online, idx = SockGetID[sock];else is first Login. */
    if(sig != CS_U_CREATE){
        if(Online[SockGetID[sock]])idx = SockGetID[sock];
        else idx = GetID(&buf[Idx_ID]);
    }

    auto R_Set_YouID = [&](){user[idx].youid = GetID(&buf[Idx_ID]);};
    auto R_Set_Name = [&](int Idx, int p = idx){user[p].Rname = GetName(&buf[Idx]);};//if is CS_U_CREATE, need p
    auto R_Set_Pass = [&](int Idx, int p = idx){user[p].pass = GetPass(&buf[Idx]);};


    switch(sig){
    case CS_F_ALLOW:{
        R_Set_YouID();
        /* allow */
        user[idx].Friend_Allow();

        /* beallow */
        user[user[idx].youid].youid = idx;
        user[user[idx].youid].Friend_Allow();

        SendSig(SC_F_BEALLOW);

        break;
    }
    case CS_F_REJECT:{
        SendSig(SC_F_BEREJECT);break;
    }
    case CS_F_ADD:{
        SendSig(SC_F_BEADD);
        break;
    }
    case CS_F_DEL:{
        R_Set_YouID();
        /* del */
        user[idx].Friend_Del();
        /* bedel */
        user[user[idx].youid].youid = idx;
        user[user[idx].youid].Friend_Del();

        SendSig(SC_F_BEDEL);
        break;
    }
    case CS_FIND_ID:{
        R_Set_YouID();
        
        //防止自己加自己
        if(user[idx].myid == user[idx].youid){
            SendSig(SC_FIND_ID_NO);
            break;
        }

        if(user[user[idx].youid].myid == -1){
            SendSig(SC_FIND_ID_NO);
        }else{
            SendSig(SC_FIND_ID_YES);
        }break;
    }
    case CS_U_LOGIN:{
        R_Set_YouID();
        R_Set_Pass(Idx_P_U);

        if(!user[idx].User_Login()){
            SendSig(SC_U_LOGIN_NO);
        }else{
            Login();
            SendSig(SC_U_LOGIN_YES);
            //SendInBuffer();   don't need, because client will send CS_S_OK, and then send.  4.29
        }break;
    }
    case CS_S_OK:{
        if(user[idx].myid == -1)break;//error id

        if(user[idx].empty_buffer())SendSig(SC_S_EMPTY);
        else SendInBuffer();
        break;
    }
    case CS_U_CREATE:{
        if(ID_Queue.empty())SendSig(SC_U_CREATE_NO);
        else{            
            int idx = ID_Queue.front();
            R_Set_Name(Idx_N, idx);
            R_Set_Pass(Idx_P_N, idx);

            user[idx].User_Create(idx); 
            SendSig(SC_U_CREATE_YES);            
        }
        break;
    }

    default:{
        WriteLog("RecvSig error");break;
    }
    }
}