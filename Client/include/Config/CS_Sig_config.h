#ifndef __CS_SIG_CONFIG_H
#define __CS_SIG_CONFIG_H

//have a init signal string ">s?UUUGG" and ">s?UUU" and ">s?"
#define CS_F_ALLOW						'0'						//  同意申请					>s0uuu				[youid]
#define CS_F_REJECT						'1'						//  拒绝申请					>s1uuu				[youid]
#define CS_F_ADD						'2'						//  申请添加好友				>s2uuu(8n)			[youid][Sname]
#define CS_F_DEL						'3'						//	删除好友					>s3uuu				[youid]
#define CS_FIND_ID						'4'                     //  搜索ID						>s4uuu				[youid]
#define CS_FIND_GID						'f'                     //  搜索GID						>sfUUUgg			[gid]
#define CS_U_CREATE						'j'                     //  注册						>sjUUUGG(8n)(16p)	[Sname][pass]
#define CS_U_LOGIN						'k'                     //  登录						>skuuuGG(16p)		[MyId][Sname]

#define CS_S_OK							'l'						//  可以继续发送				>sl

//S -> Client_Send
#define SC_FIND_ID_YES					'0'						// 								>s0uuu(8n)				[youid][Rname]
#define SC_FIND_ID_NO					'1'						//								>s1

#define SC_U_CREATE_YES					'6'						//								>s6uuu				[MyId]
#define SC_U_CREATE_NO					'7'						//								>s7

#define SC_U_LOGIN_YES					'8'						//								>s8
#define SC_U_LOGIN_NO					'9'						//								>s9

#define SC_F_ALLOW_YES					'c'						//	添加好友成功(对方群数量没达到MAX_FRIEND_SIZE)		>sc
#define SC_F_ALLOW_NO					'd'						//														>sd

#define SC_S_EMPTY                      'Z'                     //缓存区空                      >sZ                


//S -> Client_Recv
#define SC_F_BEALLOW					'A'						//被同意加好友					>sAuuu(8n)					[myid]
#define SC_F_BEREJECT					'B'						//被拒绝添加好友                >sBuuu					[myid]
#define SC_F_BEADD						'C'						//被加							>sCuuu(8n)				[myid][Sname]		//Sname : myname
#define SC_F_BEDEL						'D'						//被删							>sDuuu					[myid]


#endif
