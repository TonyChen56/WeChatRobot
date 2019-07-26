#pragma once

#define LoginSign_Offset 0x126D860		//登陆标志位

#define QrCodeOffset 0x1F110B			//二维码
#define QrCodeContectOffset 0x127F618	//二维码内容
#define GoToQrCode1 0x1EEE30			//跳转到二维码
#define GoToQrCode2 0x2E3070			//跳转到二维码

#define Logout 0x3F2530;				//退出

#define FriendList 0x428965				//好友列表
#define FriendListCall 0x481F20			//好友列表

#define ReciveMessage 0x315E98			//接收消息
#define ReciveMessageParam 0x126D7F8		//接收消息的参数偏移

#define WxSendMessage 0x2EB4E0				//发送消息的call

#define WxFileMessage1 0x4818C0				//发送文件消息
#define WxFileMessage2 0x481900				//发送文件消息
#define WxFileMessage3 0x6BAC0				//发送文件消息
#define WxFileMessage4 0x237DF0				//发送文件消息
#define WxFileMessageParam 0x10A7C04		//发送文件消息

#define WxSendImageCall1 0x817F0			//发送图片消息
#define WxSendImageCall2 0x2EAED0			//发送图片消息
#define WxPatchAddr 0x2E7CB5				//发送图片消息

#define WxSetRoomAnnouncement 0x26CFF0			//发送群公告
#define WxDeleteUser 0x274660		//删除好友
#define WxQuitChatRoom 0x26A2F0		//退出群聊

#define WxAddGroupMemberCall1 0x55F10	//添加群成员
#define WxAddGroupMemberCall2 0x481A10	//添加群成员
#define WxAddGroupMemberCall3 0x67290	//添加群成员
#define WxAddGroupMemberCall4 0x2650D0	//添加群成员
#define WxAddGroupMemberParam1 0x126D8A4	//添加群成员
#define WxAddGroupMemberParam2 0x126DDC0	//添加群成员

#define WxSendXmlCard 0x2EB4E0	//发送名片

#define WxGetRoomUserWxidCall1 0x414680	//获取群成员微信ID
#define WxGetRoomUserWxidCall2 0x2BCF20	//获取群成员微信ID
#define WxGetRoomUserWxidCall3 0x41CAE0	//获取群成员微信ID
#define WxGetRoomUserWxidCall4 0x415170	//获取群成员微信ID

#define WxGetUserInfoByWxidCall1 0x481900	//根据微信ID获取用户信息
#define WxGetUserInfoByWxidCall2 0x4FFB0	//根据微信ID获取用户信息
#define WxGetUserInfoByWxidCall3 0x273280	//根据微信ID获取用户信息

#define WxDatabaseKey 0x126DCE0	//微信数据库密钥偏移

#define WxAddWxUserParam1 0x1006CA8	//添加好友
#define WxAddWxUserCall1 0x69C90		//添加好友
#define WxAddWxUserCall2 0x58D70		//添加好友
#define WxAddWxUserCall3 0x4818C0		//添加好友
#define WxAddWxUserCall4 0x481900		//添加好友
#define WxAddWxUserCall5 0x2715B0		//添加好友

#define WxSetRoomName 0x2698A0		//修改群名称


#define WxCllectMoneyCall1 0x676B10		//收款
#define WxCllectMoneyCall2 0x676B90		//收款
#define WxAntiRevoke 0x312565			//防撤回


#define WxAgreeUserRequestCall1 0x1865B0;	  //同意好友请求
#define WxAgreeUserRequestCall2 0x4F4F0;	  //同意好友请求
#define WxAgreeUserRequestCall3 0xCE4F0;	  //同意好友请求
#define WxAgreeUserRequestCall4 0x16BD40;	  //同意好友请求
#define WxAgreeUserRequestParam 0x126E050;	  //同意好友请求

#define WxGetExpressionsAddr 0x279C2E	//提取微信表情
#define WxGetExpressionsCallAddr 0x27DE10	//提取微信表情


#define WxDelRoomMemberCall1 0x481900	  //删除群成员
#define WxDelRoomMemberCall2 0x50010	  //删除群成员
#define WxDelRoomMemberCall3 0x2652F0	  //删除群成员