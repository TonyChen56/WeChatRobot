#pragma once

//客户端和服务端通讯消息
#define WM_Login 0
#define WM_ShowQrPicture 1
#define WM_Logout 2
#define WM_GetFriendList 3
#define WM_ShowChatRecord 4
#define WM_SendTextMessage 5
#define WM_SendFileMessage 6
#define WM_GetInformation 7
#define WM_SendImageMessage 8
#define WM_SetRoomAnnouncement 9
#define WM_DeleteUser 10
#define WM_QuitChatRoom 11
#define WM_AddGroupMember 12
#define WM_SendXmlCard 13
#define WM_ShowChatRoomMembers 14
#define WM_ShowChatRoomMembersDone 15
#define WM_DecryptDatabase 16
#define WM_AddUser 17
#define WM_SetRoomName 18
#define WM_AutoChat 19
#define WM_CancleAutoChat 20
#define WM_AlreadyLogin 21
#define WM_SendAtMsg 22
#define WM_DelRoomMember 23
#define WM_OpenUrl 24
#define WM_InviteGroupMember 26
#define WM_SendXmlArticle 27
#define WM_GetFriendInfomations 28
#define WM_TimerToSend 29
#define WM_CancelTimerToSend 30
#define WM_SetRemark 31
#define WM_CreateChatRoom 32
#define WM_ModifyVersion 33
#define WM_DecodeImage 34
#define WM_SendVideoMessage 35
#define WM_SendGifMessage 36
#define WM_TopMsg 37
#define WM_CancleTopMsg 38
#define WM_OpenNewMsgNotify 39
#define WM_MsgNoDisturb 40
#define WM_FollowPublicAccount 41
#define WM_KeywordsReplyOpen 43
#define WM_KeywordsReplyClose 44


//窗口通讯的自定义消息
#define WM_ShowFriendList WM_USER+100
#define WM_ShowMessage WM_USER+101
#define SaveFriendList WM_USER+102

//聊天机器微信ID
#define ChatRobotWxID L"gh_f0e9306d8d03"