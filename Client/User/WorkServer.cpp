#include "CS_Sig_config.h"

#include "WorkServer.h"
#include "SemServer.h"
#include "SemQt.h"
#include "tool.h"

#define debug(x) std::cout << #x << " = " << x << "\n";
#define GetID() GetID(RecvBuf, nowIdx)
#define getstr(x, y) getstr(RecvBuf, nowIdx, x, y)

/* don't send CS_S_OK if recv the SC_S_EMPTY */
bool __buffer_empty = false;

const char* Text_UserInfoMess = "sxxUuuuYYMDHMS";
const char* SigUG = ">s?UUUGG";
const char* SigU = ">s?UUU";
const char* Sig = ">s?";

extern SemServer sem_server;

WorkServer::WorkServer() : nowIdx(0), seq(0){
    RecvBuf = sem_server.Get_RecvSharedMemory();
    SendBuf = sem_server.Get_SendSharedMemory();
	
	ClearBuf(RecvBuf);
	ClearBuf(SendBuf);
    sem_init(&sem_recv_server, 0, 0);
}
WorkServer::~WorkServer(){
    sem_destroy(&sem_recv_server);
}

//所有和OK有关的
void WorkServer::WakeUpQt(){    /* wake up QtSig, and then QtSig send sig to qt */
    sem_post(&sem_recv_server);
}



/*

Recv();
RecvText();
RecvSig();

*/

/*-----------------------------------Recv---------------------------------------*/
void WorkServer::Recv(){
    debug(nowIdx);
    if(RecvBuf[nowIdx] == '\0' || nowIdx >= strlen(RecvBuf)){
        nowIdx = 0;
		ClearBuf(RecvBuf);
        return;
    }
    if(RecvBuf[nowIdx] == '>')
        RecvSig();
    else
        RecvText();
	
	/* need Send CS_S_OK ? */
    if(!login_ok)return;
    if(!__buffer_empty){//buffer not empty()
        SendSig(CS_S_OK);
        __buffer_empty = false;
    }
}

/*  

sxxUuuuYYMDHMS| ... |     
sxxGuuuggYYMDHMS| ... |  

*/
void WorkServer::RecvText(){
    int len = __64_10(getstr(1, 2));//sxx...
    if(RecvBuf[nowIdx + 3] == 'U'){
		youid = GetID();
        RecvFMess(
			FMess(
                0, 
                std::string(&RecvBuf[nowIdx + 16], &RecvBuf[nowIdx + len - 2]), 
                get_time(
                    __64_10(getstr(7, 8)),
                    __64_10(getstr(9, 9)),
                    __64_10(getstr(10, 10)), 
                    __64_10(getstr(11, 11)), 
                    __64_10(getstr(12, 12)), 
                    __64_10(getstr(13, 13))
                )
	        )
        );
    }
    nowIdx += len;
    Recv();
}


/*
SC_F_BEALLOW
SC_F_BEREJECT
SC_F_BEADD
SC_F_BEDEL

SC_U_CREATE_YES
SC_U_CREATE_NO
SC_U_LOGIN_YES
SC_U_LOGIN_NO
SC_FIND_ID_YES
SC_FIND_ID_NO

SC_S_EMPTY

*/

void WorkServer::RecvSig(){
    char sig = RecvBuf[nowIdx + 2];
	int len = 0;
    switch(sig){
        case SC_F_BEALLOW: {
            //>sAuuu(8n)
            youid = GetID();
            Rname = getstr(6, 13);
            len = 14;
			
			Friend_BeAllow();
            break;
        }
        case SC_F_BEREJECT: {
            //>sBuuu                                                                                                                        //new
            youid = GetID();
			len = 6;
			
            Friend_BeReject();            
            break;
        }
        case SC_F_BEADD: {
            //>sCuuu(8n)
            youid = GetID();
            Rname = getstr(6, 13);
            len = 14;
			
			Friend_BeAdd();            
            break;
        }
        case SC_F_BEDEL: {
            //>sDuuu
            youid = GetID();
            len = 6;
			
            Friend_BeDel();
            break;
        }
        case SC_U_CREATE_YES:{
            //>spuuu
            myid = GetID();
			len = 6;

            User_Create();
            CreateSQL();	            //创建一个数据库

            WakeUpQt();
            break;
        }
        case SC_U_CREATE_NO:{
            //>sq
            OK = false;
            len = 3;
            
            WakeUpQt();
            break;
        }
        case SC_U_LOGIN_YES:{
            //>s8nnnnnnnn
            strcpy(MyName, &RecvBuf[3]);
			len = 11;
			
			User_Login();
			Load();//Load in SQL
            
            WakeUpQt();
            break;
        }
        case SC_U_LOGIN_NO:{
            //>sn
            OK = false;
            len = 3;
            
            WakeUpQt();
            break;
        }
        case SC_FIND_ID_YES:{
            //>sjnnnnnnnn
            Rname = getstr(3, 10);
            OK = true;
            len = 11;
            
            WakeUpQt();
            break;
        }
        case SC_FIND_ID_NO:{
            //>sk
            OK = false;
            len = 3;
            
            WakeUpQt();
            break;
        }
        case SC_S_EMPTY:{
            len = 3;
            __buffer_empty = true;
            break;
        }
        default:{
			//error
            exit(1);
        }
    }
    nowIdx += len;
    Recv();
}
/*-----------------------------------Recv---------------------------------------*/











/*

SendSig
Send_F_Text

*/
/*-----------------------------------Send---------------------------------------*/

/*

CS_F_ALLOW
CS_F_REJECT
CS_F_ADD
CS_F_DEL

CS_FIND_ID

CS_U_CREATE
CS_U_LOGIN

CS_S_OK

*/


void WorkServer::SendSig(char sig){
    int p = 3;
    auto InitSigUG = [&](){strcpy(SendBuf, SigUG);};
    auto InitSigU = [&](){strcpy(SendBuf, SigU);};
    auto InitSig = [&](){strcpy(SendBuf, Sig);};
    auto SetID = [&](int id){if(id == -1){p += 3;return;}strcpy(&SendBuf[p], __10_64_string(id, 3).c_str());p += 3;};
    auto SetGID = [&](int gid){if(gid == -1){p += 2;return;}strcpy(&SendBuf[p], __10_64_string(gid, 2).c_str());p += 2;};
    auto SetName = [&](const std::string& name){strcpy(&SendBuf[p], Sname.c_str());for(int i=p+Sname.size();i<p+8;i++){SendBuf[i] = ' ';}p += 8;};
    auto SetPass = [&](const std::string& password){strcpy(&SendBuf[p], password.c_str());for(int i=p+password.size();i<p+16;i++){SendBuf[i] = ' ';}p += 16;};
	
    switch(sig){
        case CS_F_ALLOW:{
            //>s0uuu
            InitSigU();
            SetID(youid);break;
        }
        case CS_F_REJECT:{
            //>s1uuu
            InitSigU();
            SetID(youid);break;
        }
        case CS_F_ADD:{
            //>s2uuuGG(8n)
            InitSigUG();
            SetID(youid);
			SetGID(-1);
			SetName(Sname);
            break;
        }
        case CS_F_DEL:{
            //>s3uuu
            InitSigU();
            SetID(youid);break;
        }
        case CS_FIND_ID:{
            //s4uuu
            InitSigU();
            SetID(youid);break;
        }
        case CS_U_CREATE:{
            //>sknnnnnnnnpppppppppppppppp
            InitSig();
            SetName(Sname);
            SetPass(password);
            break;
        }
        case CS_U_LOGIN:{
            //>sluuupppppppppppppppp
            InitSigU();
            SetID(myid);
            SetPass(password);break;
        }
		case CS_S_OK:{
            InitSig();
			break;
		}
        default:{
            exit(1);
        }
    }
    SendBuf[1] = (seq + '0');seq ^= 1;
    SendBuf[2] = sig;
    sem_server.Send2Pipe();
}

void WorkServer::Send_F_Text(){
    /* 更新本地消息列表 */
    SendFMess();

    int nowIdx = 0;
    int message_len = message.size();
    SendBuf[nowIdx++] = seq + '0';seq ^= 1;
    /* 总长度 */
    strcpy(&SendBuf[nowIdx], __10_64_string(message_len + 4 + strlen(Text_UserInfoMess), 2).c_str());nowIdx += 2;

    SendBuf[nowIdx++] = 'U';
    strcpy(&SendBuf[nowIdx], __10_64_string(youid, 3).c_str());nowIdx += 3;
    strcpy(&SendBuf[nowIdx], get_time_64().c_str());nowIdx += 7;
    SendBuf[nowIdx++] = '|';
    SendBuf[nowIdx++] = ' ';
    strcpy(&SendBuf[nowIdx], message.c_str());nowIdx += message_len;
    SendBuf[nowIdx++] = ' ';
    SendBuf[nowIdx++] = '|';

    WriteLog(std::string("Send_F_Text: ") + SendBuf);

    sem_server.Send2Pipe();
}
/*-----------------------------------Send---------------------------------------*/
