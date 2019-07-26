#pragma once

void SetWxRoomAnnouncement(wchar_t* chatroomwxid,wchar_t* Announcement);	//设置群公告
void QuitChatRoom(wchar_t* chatroomwxid);	//退出群聊
void AddGroupMember(wchar_t* chatroomwxid, wchar_t* wxid);	//添加群成员
void ShowChatRoomUser(wchar_t* chatroomwxid);	//显示群成员
void GetUserInfoByWxid(wchar_t* userwxid);		//通过微信ID获取用户信息
void SetRoomName(wchar_t* roomwxid, wchar_t* roomname);	//修改群名称

void DelRoomMember(wchar_t* roomid, wchar_t* memberwxid);	//删除群成员
//发送艾特消息
void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* msg);