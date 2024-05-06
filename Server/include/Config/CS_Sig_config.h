#ifndef __CS_SIG_CONFIG_H
#define __CS_SIG_CONFIG_H


//have a init signal string ">s?UUUGG" and ">s?UUU" and ">s?"
#define CS_F_ALLOW						'0'						//  同意申请					>s0uuu				[youid]
#define CS_F_REJECT						'1'						//  拒绝申请					>s1uuu				[youid]
#define CS_F_ADD						'2'						//  申请添加好友				>s2uuu(8空格)			[youid][Sname]
#define CS_F_DEL						'3'						//	删除好友					>s3uuu				[youid]

#define CS_FIND_ID						'4'                     //  搜索ID						>s4uuu				[youid]

#define CS_U_LOGIN						'k'                     //  登录						>skuuuGG(16空格)		[MyId][Sname]
#define CS_S_OK							'l'						//  可以继续发送				>sl

#define CS_U_CREATE						'j'                     //  注册						>sjUUUGG(8n)(16p)	[Sname][pass]


//S -> Client_Send
#define SC_FIND_ID_YES					'0'						// 								>s0(8s)				[name]
#define SC_FIND_ID_NO					'1'						//								>s1

#define SC_U_LOGIN_YES					'8'						//								>s8
#define SC_U_LOGIN_NO					'9'						//								>s9



//RecvSig
//S -> Client_Recv

#define SC_F_BEALLOW					'A'						//被同意加好友					>sAuuu(8n)					[myid]
#define SC_F_BEREJECT					'B'						//被拒绝添加好友                >sBuuu					[myid]
#define SC_F_BEADD						'C'						//被加							>sCuuu(8n)				[myid][Sname]		//Sname : myname
#define SC_F_BEDEL						'D'						//被删							>sDuuu					[myid]

#define SC_S_EMPTY                      'Z'                     //缓存区空                      >sZ                

#define SC_U_CREATE_YES					'6'						//								>s6uuu				[MyId]
#define SC_U_CREATE_NO					'7'						//								>s7


#endif



/*
Server
int SockGetID[MAX_ID_SIZE];
struct UserInfo{
    bool is_vaild;//是否有效
    int* groups;
    int* friends;
    int group_size;
    int friend_size;
    std::unorder_map<int, int>FIdGetIdx;
    std::unorder_map<int, int>GIdGetIdx;

    void Add_Friend();
    void Add_Group();
    void Del_Friend();
    void Del_Group();
};
struct GroupInfo{
    bool is_vaild;//是否有效
    int leaderId;
    std::unordered_set<int>memberID;
    void Add_Member(int id);
    void Del_Member(int id);
};


CS_F_ALLOW
    SC_F_ALLOW_YES
        SC_F_BEALLOW
    SC_F_ALLOW_NO
CS_F_REJECT
    SC_F_BEREJECT
CS_F_ADD
    SC_F_BEADD
CS_F_DEL
    SC_F_BEDEL

CS_FIND_ID
    SC_FIND_ID_YES[is_vaild]
    SC_FIND_ID_NO[!is_vaild]

CS_G_RENAME
    SC_G_RENAME
CS_G_SETLEADER
    SC_G_LEADER
CS_G_ALLOW
    SC_G_ALLOW_YES
        SC_G_BEALLOW
    SC_G_ALLOW_NO
CS_G_REMOVE
    SC_G_BEREMOVE
CS_G_INVITE
    SC_G_INVITE_YES
        SC_G_BEINVITE
    SC_G_INVITE_NO
CS_G_REJECT
    SC_G_BEREJECT
CS_G_CREATE
    SC_G_CREATE_YES
    SC_G_CREATE_NO
CS_G_INSERT
    SC_G_BEINSERT	[send to leader]
CS_G_DELETE
CS_G_QUIT
    SC_G_MEMBERQUIT

CS_FIND_GID
    SC_FIND_ID_YES
    SC_FIND_ID_NO

CS_U_DELETE
    SC_F_DELETE
CS_U_RENAME
    SC_F_RENAME
CS_U_PASS
    SC_U_SETPASS_YES
    SC_U_SETPASS_NO
CS_U_CREATE
    SC_U_CREATE_YES
    SC_U_CREATE_NO
CS_U_LOGIN
    SC_U_LOGIN_YES
    SC_U_LOGIN_NO

CS_S_OK

*/
