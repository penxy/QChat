#ifndef __QC_SIG_CONFIG_H
#define __QC_SIG_CONFIG_H

/* QC之间 id 都是数字 */
#define QC_F_ALLOW						'0'						//  同意申请					youid name
#define QC_F_REJECT						'1'						//  拒绝申请					youid name
#define QC_F_ADD						'2'						//  申请添加好友			    youid
#define QC_F_DEL						'3'						//	删除好友					youid
#define QC_FIND_ID						'4'                     //  搜索ID						youid
#define QC_U_CREATE						'5'                     //  注册						name password
#define QC_U_LOGIN						'6'                     //  登录						myid password



#define QC_F_CLEAR_MESS                 'A'                     //  清空好友消息                 youid
#define QC_F_SEND_MESS                  'B'                     //  发给好友消息                 youid mess

#define QC_FRIEND_LIST					'C'						// id name
#define QC_FRIEND_MESS					'D'						// id - Message

#define QC_MYADD						'E'						//  newFriendid - name
#define QC_MYBEADD						'F'						//	BenewFriendid - name


/* Client给Qt的消息 */

#define CQ_U_CREATE_YES					'0'						//注册成功					myid
#define CQ_U_CREATE_NO					'1'						//注册失败
#define CQ_U_LOGIN_YES					'2'						//登录成功
#define CQ_U_LOGIN_NO					'3'						//登录失败
#define CQ_FIND_ID_YES					'4'						//ID查找成功				name
#define CQ_FIND_ID_NO					'5'						//ID查找失败


#define CQ_FRIEND_LIST					'A'						// id name
#define CQ_FRIEND_MESS					'B'						// id - Message
#define CQ_MYADD						'C'						//  newFriendid - name
#define CQ_MYBEADD						'D'						//	BenewFriendid - name



#endif
