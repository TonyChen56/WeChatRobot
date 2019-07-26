#pragma once

void HookGetFriendList();		//HOOK获取好友列表的call
void GetUserListInfo();		   //获取好友列表
void UnHookGetFriendList();	   //卸载HOOK获取好友列表的call
void SendUserListInfo();		//发送好友列表
void SendTextMessage(wchar_t* wxid, wchar_t* msg);	//发送文本消息
void SendFileMessage(wchar_t* wxid, wchar_t* filepath);	//发送文件消息
void SendImageMessage(wchar_t* wxid, wchar_t* filepath);//发送图片消息
void DeleteUser(wchar_t* wxid);	//删除好友
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName); //发送XML名片

