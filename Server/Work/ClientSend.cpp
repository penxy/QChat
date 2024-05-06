#include "ClientSend.h"
#include "tool.h"


/* when client LoginYes, Send it, and then client will send sig of "CS_S_OK", continue send it  */

char* ClientSend::buf = new char[MAX_BUF_SIZE];

void ClientSend::Send2CR(char* buf = ClientSend::buf){
	if(Online[user[idx].youid])send(IDGetSock[user[idx].youid], buf, strlen(buf), 0);
    else user[user[idx].youid].WriteInBuffer(buf);

    WriteLog(std::string("Send to ClientR: ") + std::string(buf));
	ClearBuf(buf);
	
}
void ClientSend::Send2CS(){
	WriteLog("UserSock.cpp: Send to ClientS: " + std::string(buf));
    send(sock, buf, strlen(buf), 0);
    ClearBuf(buf);
	
}

void ClientSend::SendText(char* buf){
	//const char* Text_UserInfoMess = "sxxUuuuYYMDHMS";
    user[idx].youid = Get_Text_ID(buf);

    //turn uuu from youid to myid.
    std::string MyID = __10_64_string(idx, 3);

    for(int i=Idx_Text_ID;i<Idx_Text_ID+Len_ID;i++){
        buf[i] = MyID[i-Idx_Text_ID];
    }
    
    Send2CR(buf);
}


void ClientSend::SendSig(char sig){
	ClearBuf(buf);
    int myid = user[idx].myid;
    strcpy(buf, Sig);
    Set_Sig(buf, sig);

    switch(sig){
    case SC_F_BEALLOW:{
        Sig_Append_ID(buf, myid);Sig_Append_Name(buf, user[idx].myname);Send2CR();break;
    }
    case SC_F_BEREJECT:{
        Sig_Append_ID(buf, myid);Send2CR();break;
    }
    case SC_F_BEADD:{
        Sig_Append_ID(buf, myid);Sig_Append_Name(buf, user[idx].myname);Send2CR();break;
    }
    case SC_F_BEDEL:{
        Sig_Append_ID(buf, myid);
        Sig_Append_Name(buf, user[idx].myname);Send2CR();break;
    }
    case SC_FIND_ID_NO:{
        Send2CS();break;
    }
    case SC_FIND_ID_YES:{
        Sig_Append_Name(buf, user[user[idx].youid].myname);Send2CS();break;
    }
    case SC_U_LOGIN_NO:{
        Send2CS();break;
    }
    case SC_U_LOGIN_YES:{
        Sig_Append_Name(buf, user[user[idx].youid].myname);Send2CS();break;
    }
    case SC_S_EMPTY:{
        Send2CS();break;
    }
    case SC_U_CREATE_YES:{
        int id = ID_Queue.front();ID_Queue.pop();Sig_Append_ID(buf, id);Send2CS();break;
    }
    case SC_U_CREATE_NO:{
        Send2CS();break;
    }
    default:{
        WriteLog("UserSock.cpp, Unknow SendSig");
        break;
    }
    }
}
