<<<<<<< HEAD
#pragma once

void SetWxRoomAnnouncement(wchar_t* chatroomwxid,wchar_t* Announcement);	//����Ⱥ����
void QuitChatRoom(wchar_t* chatroomwxid);	//�˳�Ⱥ��
void AddGroupMember(wchar_t* chatroomwxid, wchar_t* wxid);	//���Ⱥ��Ա
void ShowChatRoomUser(wchar_t* chatroomwxid);	//��ʾȺ��Ա
void GetUserInfoByWxid(wchar_t* userwxid);		//ͨ��΢��ID��ȡ�û���Ϣ
void SetRoomName(wchar_t* roomwxid, wchar_t* roomname);	//�޸�Ⱥ����

void DelRoomMember(wchar_t* roomid, wchar_t* memberwxid);	//ɾ��Ⱥ��Ա
//���Ͱ�����Ϣ
void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* msg);
=======
#pragma once

void SetWxRoomAnnouncement(wchar_t* chatroomwxid,wchar_t* Announcement);	//����Ⱥ����
void QuitChatRoom(wchar_t* chatroomwxid);	//�˳�Ⱥ��
void AddGroupMember(wchar_t* chatroomwxid, wchar_t* wxid);	//���Ⱥ��Ա
void ShowChatRoomUser(wchar_t* chatroomwxid);	//��ʾȺ��Ա
void GetUserInfoByWxid(wchar_t* userwxid);		//ͨ��΢��ID��ȡ�û���Ϣ
void SetRoomName(wchar_t* roomwxid, wchar_t* roomname);	//�޸�Ⱥ����
>>>>>>> 06c014d... Add files via upload
