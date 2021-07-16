#pragma once


//微信通用结构体
struct GeneralStruct
{
	wchar_t* pstr;
	int iLen;
	int iMaxLen;
	int full1;
	int full2;
	GeneralStruct(wchar_t* pString)
	{
		pstr = pString;
		iLen = wcslen(pString);
		iMaxLen = iLen * 2;
		full1 = 0;
		full2 = 0;
	}
};

//存储WM_COPYDATA消息的通用联合体
union MessageUnion
{
	//通用消息结构体
	struct MessageStruct
	{
		wchar_t msgdata1[MAX_PATH];
		wchar_t msgdata2[MAX_PATH];
	}genericmsg;

	//发送名片消息结构体
	struct XmlCardMessage
	{
		wchar_t RecverWxid[50];		//接收者的微信ID
		wchar_t SendWxid[50];		//需要发送的微信ID
		wchar_t NickName[50];		//昵称
	}xmlcardmsg;
	//发送艾特消息
	struct AtMsg
	{
		wchar_t chatroomid[50] = { 0 };
		wchar_t membermsgdata1[50] = { 0 };
		wchar_t membernickname[50] = { 0 };
		wchar_t msgmsgdata2[100] = { 0 };
	}atmsg;
	//XML文章消息
	struct SendXmlArticleStruct
	{
		wchar_t title[50];
		wchar_t subtitle[50];
		wchar_t urllink[200];
		wchar_t picpath[260];
		wchar_t selfwxid[50];
		wchar_t recverwxid[50];
	}xmlartmsg;
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


//修改备注结构体 0x22B的位置必须是1
struct SetRemarkStruct
{
	int full1 = 0x800;			//4
	int full2 = 0;				//8
	wchar_t* UnicodeWxid;		//0xC
	int UnicodeWxidLen;			//0x10
	int UnicodeWxidMaxLen;		//0x14
	int full5 = 0;				//0x18
	int full6 = 0;				//0x1C
	char full3[0x34] = { 0 };	//0x20
	wchar_t* Remark;			//0x54
	int RemarkLen;				//0x58
	int RemarkMaxLen;			//0x5C
	int full7 = 0;				//0x60
	int full8 = 0;				//0x64
	char full9[0x1C3] = { 0 };	//0x68
	int full10 = 1;				//0x228
	char full11[0x259] = { 0 };	//0x68
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

//V1
struct v1Info
{
	int fill = 0;
	wchar_t* v1 = 0;
	int v1Len;
	int maxV1Len;
	char fill2[0x41C] = { 0 };
	DWORD v2 = { 0 };
};

//V2
struct v2Info
{
	char fill[0x24C] = { 0 };
	DWORD fill3 = 0x25;
	char fill4[0x40] = { 0 };
	wchar_t* v2;
	int v2Len;
	int maxV2Len;
	char fill2[0x8] = { 0 };
};


//收款结构体
struct CllectMoneyStruct
{
	wchar_t* ptransferid;
	int transferidLen;
	int transferidMaxLen;
	char full[0x8] = { 0 };
	wchar_t* pwxid;
	int wxidLen;
	int wxidMaxLen;
	char full2[0x8] = { 0 };
};


//下载图片结构体
struct DwonImgStruct
{
	//92C
	char fill[0x14] = { 0 };
	DWORD params = 0;
	DWORD params1 = 0;
	char fill2[0x10] = { 0 };
	DWORD params2 = 0;
	char fill3[0x38] = { 0 };
	wchar_t * imgXml;
	int xmlLen = 0;
	int xmlMaxLen = 0;
	char fill4[0xC8] = { 0 };
	wchar_t * thumbImgPath;
	int thumbLen = 0;
	int thumbMaxLen = 0;
	char fill5[0x8] = { 0 };
	wchar_t * hImgPath;
	int hImgLen = 0;
	int hImgMaxLen = 0;
	char fill6[0x700] = { 0 };
};

//通过微信ID获取用户信息结构体
struct UserInfo
{
	wchar_t UserId[0x100];
	wchar_t UserNumber[0x100];
	wchar_t UserNickName[0x100];
};


//好友列表信息结构体
struct UserListInfo
{
	wchar_t UserId[80];
	wchar_t UserNumber[80];
	wchar_t UserRemark[80];
	wchar_t UserNickName[80];
};

//好友详细信息
struct UserInfoDetail
{
	wchar_t UserId[50];			//微信ID
	wchar_t UserNumber[50];		//微信账号
	wchar_t V1[200];				//V1
	wchar_t Remark[50];			//备注
	wchar_t UserNickName[50];	//微信昵称
	wchar_t smallHeader[1024] = { 0 };	//小头像
	wchar_t bigHeader[1024] = { 0 };	//大头像
};

//邀请进群的群ID结构体
struct RoomIdStruct
{
	char fill2[0x8] = { 0 };
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char fill[0x8] = { 0 };
};



