#ifndef __CQSIGCONFIG_H
#define __CQSIGCONFIG_H

/* QC之间 id 都是数字 */
#define QC_FALLOW						'0'						//  同意申请					youid name
#define QC_FREJECT						'1'						//  拒绝申请					youid name
#define QC_FADD							'2'						//  申请添加好友			    youid
#define QC_FDEL							'3'						//	删除好友					youid

#define QC_USEARCHUSER					'4'                     //  搜索ID						youid

#define QC_USERLOGIN					'l'                     //  登录						myid password

#define QC_FMESSAGECLEAR                'E'                     //  清空好友消息                 youid
#define QC_FSENDMESSAGE                 'o'                     //  发给好友消息                 youid mess


#define QC_FRIENDLIST					'r'						// id name
#define QC_FRIENDMESS					's'						// id - Message

#define QC_MYADD						'w'						//  newFriendid - name
#define QC_BEADD						'x'						//	BenewFriendid - name




/* Client给Qt的消息 */

#define CQ_LOGINYES						'2'						//登录成功
#define CQ_LOGINNO						'3'						//登录失败

#define CQ_SEARCHIDYES					'8'						//ID查找成功				name
#define CQ_SEARCHIDNO					'9'						//ID查找失败



#define CQ_FRIENDLSIT					'c'						// id name
#define CQ_FRIENDMESS					'd'						// id - Message

#define CQ_GROUPLIST                    'e'						//  gid name
#define CQ_GROUPMEMBER                  'f'						//	id name
#define CQ_GROUPMESS                    'g'						//	gid - Message

#define CQ_MYADD						'h'						//  newFriendid - name
#define CQ_BEADD						'i'						//	BenewFriendid - name





#endif
