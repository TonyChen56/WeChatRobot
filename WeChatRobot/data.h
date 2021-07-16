#pragma once

//通用消息结构体
struct MessageStruct
{
	wchar_t msgdata1[MAX_PATH];
	wchar_t msgdata2[MAX_PATH];

	MessageStruct(wchar_t* pString1, wchar_t* pString2)
	{
		wcscpy_s(msgdata1, wcslen(pString1) + 1, pString1);
		wcscpy_s(msgdata2, wcslen(pString2) + 1, pString2);
	}

	MessageStruct(CString pString1, CString pString2)
	{
		wcscpy_s(msgdata1, wcslen(pString1) + 1, pString1);
		wcscpy_s(msgdata2, wcslen(pString2) + 1, pString2);
	}
};


//聊天记录的消息结构体
struct ChatMessageData
{
	DWORD dwtype;				//消息类型
	wchar_t sztype[0x20];			//消息类型
	wchar_t source[0x400];			//消息来源
	wchar_t wxid[0x40];			//微信ID/群ID
	wchar_t wxname[0x200];			//微信名称/群名称
	wchar_t sender[0x100];			//消息发送者
	wchar_t sendername[0x100];		//消息发送者昵称
	wchar_t content[0x5000];	//消息内容
};

//发送名片消息结构体
struct XmlCardMessage
{
	wchar_t RecverWxid[50];		//接收者的微信ID
	wchar_t SendWxid[50];		//需要发送的微信ID
	wchar_t NickName[50];		//昵称
};
//发送艾特消息
struct AtMsg
{
	wchar_t chatroomid[50] = { 0 };
	wchar_t memberwxid[50] = { 0 };
	wchar_t membernickname[50] = { 0 };
	wchar_t msgcontent[100] = { 0 };
};
//XML文章消息
struct SendXmlArticleStruct
{
	wchar_t title[50];
	wchar_t subtitle[50];
	wchar_t urllink[200];
	wchar_t picpath[260];
	wchar_t selfwxid[50];
	wchar_t recverwxid[50];
};


//个人信息的结构体
struct PersonalInformation
{
	wchar_t wxid[40];			//微信ID
	wchar_t wxcount[40];		//微信账号
	wchar_t v1[150];			//V1
	wchar_t nickname[50];		//微信昵称
	wchar_t remark[50];			//备注
	wchar_t wxsex[10];			//性别
	wchar_t phonenumber[30];	//手机号
	wchar_t device[20];			//登陆设备
	wchar_t nation[20];			//国籍
	wchar_t province[20];		//省份
	wchar_t city[20];			//城市
	wchar_t area[20];			//地区
	wchar_t language[10];		//语言
	wchar_t bigheader[0x100];	//大头像
	wchar_t smallheader[0x100];	//小头像
	wchar_t signature[50];		//个性签名
	wchar_t background[0x100];	//朋友圈背景
	wchar_t cachedir[MAX_PATH];	//缓存目录
	wchar_t startdir[MAX_PATH];	//启动目录
};


//好友列表的用户信息
struct UserInfo
{
	wchar_t UserId[80];
	wchar_t UserNumber[80];
	wchar_t UserRemark[80];
	wchar_t UserNickName[80];
};

//群成员的信息结构体
struct ChatRoomMemberInfo
{
	wchar_t UserId[0x100];
	wchar_t UserNumber[0x100];
	wchar_t UserNickName[0x100];
};

//好友详细信息结构体
struct UserInfoDetail
{
	wchar_t UserId[50];			//微信ID
	wchar_t UserNumber[50];		//微信账号
	wchar_t V1[200];				//V1
	wchar_t Remark[50];			//备注
	wchar_t UserNickName[50];	//微信昵称
	wchar_t smallHeader[1024];	//小头像
	wchar_t bigHeader[1024];	//大头像
};