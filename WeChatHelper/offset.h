#pragma once
#define WxFriendList 0x5244A8					//好友列表 1
#define WxFriendListCall 0x64550				//好友列表 1
#define WxReciveMessage 0x3DF42C			//接收消息 	 1
#define WxReciveMessageCall 0x87A70			//接收消息 	  1
#define WxGoToQrCode1 0x264830				//跳转到二维码 1
#define WxGoToQrCode2 0x3ADE40				//跳转到二维码 1
#define WxQrCodeOffset 0x266AAC				//获取二维码 1
#define WxQrCodeOffsetCall 0x58BD30			//获取二维码 1
#define WxSendMessage 0x3B63B0				//发送文本消息 1
#define WxLogout 0x4E7210						//退出 1
#define WxFileMessage1 0x58DA10				 //发送文件消息 1
#define WxFileMessage2 0x58DA50				 //发送文件消息 1
#define WxFileMessage3 0x68D00				 //发送文件消息 1
#define WxFileMessage4 0x2C1960				 //发送文件消息 1
#define WxFileMessageParam 0x17FFE10		 //发送文件消息 1
#define WxSendImageCall3 0x58DA50			//发送图片消息 1
#define WxSendImageCall1 0x639F0			//发送图片消息 1
#define WxSendImageCall2 0x3B5C70			//发送图片消息 1
#define WxPatchAddr 0x3B2AE6				//发送图片消息 1
#define WxSetRoomAnnouncement 0x3074E0			//发送群公告 1
#define WxDeleteUser 0x325C80					//删除好友 1
#define WxQuitChatRoom 0x3045B0					//退出群聊 1
#define WxAddGroupMemberCall1 0x827B0			//添加群成员 1
#define WxAddGroupMemberCall2 0x58DB60			//添加群成员 1
#define WxAddGroupMemberCall3 0x932D0			//添加群成员 1
#define WxAddGroupMemberCall4 0x2FF220			//添加群成员 1
#define WxAddGroupMemberParam1 0x1AD1B34		//添加群成员 1
#define WxAddGroupMemberParam2 0x1AD2358		//添加群成员 1
#define WxSendXmlCard 0x3B63B0				//发送名片 1
#define WxGetRoomUserWxidCall1 0x512DD0			//获取群成员ID 1
#define WxGetRoomUserWxidCall2 0x379A90			//获取群成员ID 1
#define WxGetRoomUserWxidCall3 0x5193F0			//获取群成员ID 1
#define WxGetRoomUserWxidCall4 0x5137F0			//获取群成员ID 1
#define WxGetUserInfoWithNoNetworkCall1 0x58DDD0		 //根据微信ID获取用户信息 1
#define WxGetUserInfoWithNoNetworkCall2 0x3245E0		 //根据微信ID获取用户信息 1
#define WxGetUserInfoWithNoNetworkCall3 0x4FD8F0		 //根据微信ID获取用户信息 1
#define WxGetUserInfoByWxidCall1 0x58DA50		//根据微信ID获取用户信息 1
#define WxGetUserInfoByWxidCall2 0x63930		//根据微信ID获取用户信息 1
#define WxGetUserInfoByWxidCall3 0x3245E0		//根据微信ID获取用户信息 1
#define WxAddWxUserParam1 0x1730C30				//添加好友 1
#define WxAddWxUserCall1 0x57860				//添加好友 1
#define WxAddWxUserCall2 0x83780				//添加好友 1
#define WxAddWxUserCall3 0x58DA10				//添加好友 1
#define WxAddWxUserCall4 0x58DA50				//添加好友 1
#define WxAddWxUserCall5 0x322B20				//添加好友 1
#define WxSetRoomName 0x303A50					//修改群名称 1
#define WxCllectMoneyCall1 0x9C5310				//收款 1
#define WxCllectMoneyCall2 0x9C5390				//收款 1
#define WxAgreeUserRequestCall1 0x1F0360		//同意好友请求 1
#define WxAgreeUserRequestCall2 0x5D860			//同意好友请求 1
#define WxAgreeUserRequestCall3 0x10FFA0		//同意好友请求 1
#define WxAgreeUserRequestCall4 0x1D7180		//同意好友请求 1
#define WxAgreeUserRequestParam 0x1AB2E98		//同意好友请求 1
#define WxGetExpressionsAddr 0x2D3C68			//提取微信表情  没啥用 去除
#define WxGetExpressionsCallAddr 0x2D7E60		//提取微信表情  没啥用 去除
#define WxDelRoomMemberCall1 0x58DA50			//删除群成员 1
#define WxDelRoomMemberCall2 0x7CD80			//删除群成员 1
#define WxDelRoomMemberCall3 0x2FF410			//删除群成员 1
#define WxOpenUrlCall1 0x58DA50					//打开浏览器 1
#define WxOpenUrlCall2 0x9C9CA0					//打开浏览器 1
#define WxPackageMsgData 0x827B0		//组装艾特消息数据结构 1
#define WxAntiRevoke 0x3DED99			//防撤回 1
//聊天记录偏移
#define MsgTypeOffset 0x30				//消息类型的偏移 
#define MsgContentOffset 0x68			//消息内容的偏移 
#define MsgSourceOffset 0x1B8			//消息来源的偏移 
#define WxidOffset 0x40					//微信ID/群ID偏移 	
#define GroupMsgSenderOffset 0x164		//群消息发送者偏移 
//个人信息 基址 
#define WxSelfInfoBase 0x1AD1AF0				// 1
// 登陆标志位 
#define LoginSign_Offset 0x1AD4858	// 1
//微信ID ASCII指针
#define WxID WxSelfInfoBase+0x44	//
//大头像 ASCII指针
#define WxBigHeader WxSelfInfoBase+0x384	//
//小头像 ASCII指针
#define WxSmallHeader WxSelfInfoBase+0x39C	//
//国家 ASCII字符
#define WxNation WxSelfInfoBase+0x298		//
//微信号 ASCII字符
#define WxCount WxSelfInfoBase+0x220		//
//城市 ASCII字符
#define WxProvince WxSelfInfoBase+0x1A8		//
//地区  ASCII字符
#define WxCity WxSelfInfoBase+0x1C0			//
//手机号 ASCII字符
#define WxPhoneNumber WxSelfInfoBase+0xF0   //
//昵称 ASCII字符
#define WxNickName WxSelfInfoBase+0xBC		//
//缓存目录  Unicode指针
#define WxCacheDir WxSelfInfoBase+0x10		//
//登陆设备 ASCII字符
#define WxDevice WxSelfInfoBase+0x510		//
//性别 
#define WxSex WxSelfInfoBase+0x1A4			//
