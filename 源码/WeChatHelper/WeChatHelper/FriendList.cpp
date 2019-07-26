#include "stdafx.h"
#include "FriendList.h"
#include <stdio.h>
#include "shellapi.h"
#include <string>
#include <sstream>
#include <string>
#include <iomanip>
#include <strstream>
#include <list>
#include <iostream>
#include <tuple>
#include<fstream>
#include "ChatRecord.h"
#pragma comment(lib, "Version.lib")
using namespace std;

typedef tuple <
	//wxid1
	wstring,
	//wxName
	wstring,
	//v1
	wstring,
	//nickName
	wstring
> USER_INFO;

//定义7000个用户列表
list<USER_INFO> userInfoList(1);


//用户信息结构体
struct UserInfo
{
	wchar_t UserId[80];
	wchar_t UserNumber[80];
	wchar_t UserRemark[80];
	wchar_t UserNickName[80];
};


//用于调用微信发送消息call的结构体
struct wxMsg
{
	wchar_t* pMsg;		//微信ID
	int msgLen;			//ID长度
	int buffLen;		//缓冲区长度
	int fill1 = 0;
	int fill2 = 0;
};


//微信ID的结构体
struct Wxid
{
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char file[0x8] = { 0 };
};

//文件路径的结构体
struct filePath
{
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char file[0x18] = { 0 };
};

//发送图片的结构体
struct SendImageStruct
{
	wchar_t* pWxid = nullptr;
	DWORD length = 0;
	DWORD maxLength = 0;
	DWORD fill1 = 0;
	DWORD fill2 = 0;
	wchar_t wxid[1024] = { 0 };
};


//HOOK需要用到的的全局变量
DWORD overWritedCallAdd;
DWORD hookAddress;
DWORD jumBackAddress;
BYTE bBackCode[5] = { 0 };
DWORD r_esi = 0;


//************************************************************
// 函数名称: HookGetFriendList
// 函数说明: HOOK获取好友列表的call 
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: void
// 返 回 值: void 
//************************************************************
void HookGetFriendList()
{

	DWORD wxBaseAddress = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
	//需要hook的地址
	hookAddress = wxBaseAddress + FriendList;
	//被覆盖的CALL目标
	overWritedCallAdd = wxBaseAddress + FriendListCall;

	//跳回的地址
	jumBackAddress = hookAddress + 5;

	//组装跳转数据
	BYTE jmpCode[5] = { 0 };
	jmpCode[0] = 0xE9;


	//计算偏移
	*(DWORD*)& jmpCode[1] = (DWORD)GetUserListInfo - hookAddress - 5;

	// 保存以前的属性用于还原
	DWORD OldProtext = 0;

	// 因为要往代码段写入数据，又因为代码段是不可写的，所以需要修改属性
	VirtualProtect((LPVOID)hookAddress, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	//保存原有的指令
	memcpy(bBackCode, (void*)hookAddress, 5);

	//写入自己的代码
	memcpy((void*)hookAddress, jmpCode, 5);

	// 执行完了操作之后需要进行还原
	VirtualProtect((LPVOID)hookAddress, 5, OldProtext, &OldProtext);
}


//************************************************************
// 函数名称: UnHookGetFriendList
// 函数说明: 卸载HOOK获取好友列表的call 
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: void
// 返 回 值: void 
//************************************************************
void UnHookGetFriendList()
{
	//拿到模块基址
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	DWORD dwHookAddr = dwWeChatWinAddr + FriendList;

	// 保存以前的属性用于还原
	DWORD OldProtext = 0;

	// 因为要往代码段写入数据，又因为代码段是不可写的，所以需要修改属性
	VirtualProtect((LPVOID*)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	// Hook 就是向其中写入自己的代码
	memcpy((LPVOID*)dwHookAddr, bBackCode, 5);

	// 执行完了操作之后需要进行还原
	VirtualProtect((LPVOID*)dwHookAddr, 5, OldProtext, &OldProtext);
}


//************************************************************
// 函数名称: GetUserListInfo
// 函数说明: 获取用户信息
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: void
// 返 回 值: void 
//************************************************************
__declspec(naked) void GetUserListInfo()
{
	//保存现场
	__asm
	{
		//提取eax寄存器内容，放在一个变量中
		mov r_esi, esi

		//保存寄存器
		pushad
		pushf
	}

	//调用接收消息的函数
	SendUserListInfo();

	//恢复现场
	__asm
	{
		popf
		popad

		//补充被覆盖的代码
		call overWritedCallAdd

		//跳回被HOOK指令的下一条指令
		jmp jumBackAddress
	}
}


//************************************************************
// 函数名称: ReSendUser
// 函数说明: 再次发送好友信息
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: user
// 返 回 值: void 
//************************************************************
void ReSendUser(UserInfo* user)
{
	HWND hWnd = NULL;
	while (true)
	{
		//发送到控制端
		hWnd = FindWindow(NULL, TEXT("微信助手"));
		if (hWnd == NULL)
		{
			continue;
		}
		break;
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//保存一个数值, 可以用来作标志等
	userinfo.cbData = sizeof(UserInfo);// strlen(szSendBuf);//待发送的数据的长
	userinfo.lpData = user;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
}



//************************************************************
// 函数名称: SendUserListInfo
// 函数说明: 发送好友列表
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: void
// 返 回 值: void 
//************************************************************
void SendUserListInfo()
{
	//个人微信号、群号
	wstring wxid1 = GetMsgByAddress(r_esi + 0x10);
	wstring wxName = GetMsgByAddress(r_esi + 0x8C);
	wstring v1 = GetMsgByAddress(r_esi + 0x58);
	//个人微信昵称、群昵称
	wstring nickName = GetMsgByAddress(r_esi + 0x8C);
	USER_INFO userInfo(wxid1, wxName, v1, nickName);

	for (auto& userInfoOld : userInfoList)
	{
		wstring wxid = get<0>(userInfoOld);
		if (wxid == wxid1)
		{
			return;
		}
	}
	userInfoList.push_front(userInfo);


	UserInfo *user=new UserInfo;
	LPVOID pUserWxid = *((LPVOID *)(r_esi + 0x10));
	LPVOID pUserNumber = *((LPVOID *)(r_esi + 0x44));
	LPVOID pUserNick = *((LPVOID *)(r_esi + 0x8C));
	LPVOID pUserReMark = *((LPVOID *)(r_esi + 0x78));


	swprintf_s(user->UserId, L"%s", (wchar_t*)pUserWxid);
	swprintf_s(user->UserNumber, L"%s", (wchar_t*)pUserNumber);
	swprintf_s(user->UserNickName, L"%s", (wchar_t*)pUserNick);
	swprintf_s(user->UserRemark, L"%s", (wchar_t*)pUserReMark);


	//发送到控制端
	HWND hWnd = FindWindow(NULL, TEXT("微信助手"));
	if (hWnd == NULL)
	{
		//创建线程 发送消息 防止漏掉联系人
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReSendUser, user, 0, NULL);
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//保存一个数值, 可以用来作标志等
	userinfo.cbData = sizeof(UserInfo);// strlen(szSendBuf);//待发送的数据的长
	userinfo.lpData = user;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
}



//************************************************************
// 函数名称: SendTextMessage
// 函数说明: 发送文本消息
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: wxid 微信ID msg消息内容
// 返 回 值: void 
//************************************************************
void SendTextMessage(wchar_t* wxid, wchar_t* msg)
{
	//拿到发送消息的call的地址
	DWORD dwSendCallAddr = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll")) + WxSendMessage;

	//组装微信ID/群ID的结构体
	wxMsg id = { 0 };
	id.pMsg = wxid;
	id.msgLen = wcslen(wxid);
	id.buffLen = wcslen(wxid) * 2;

	//消息内容
	wxMsg text = { 0 };
	text.pMsg = msg;
	text.msgLen = wcslen(msg);
	text.buffLen = wcslen(msg) * 2;

	//取出微信ID和消息的地址
	char* pWxid = (char*)&id.pMsg;
	char* pWxmsg = (char*)&text.pMsg;

	char buff[0x81C] = { 0 };

	//调用微信发送消息call
	__asm {
		mov edx, pWxid;
		push 0x1;
		push 0;
		mov ebx, pWxmsg;
		push ebx;
		lea ecx, buff;
		call dwSendCallAddr;
		add esp, 0xC;
	}
}


//************************************************************
// 函数名称: SendFileMessage
// 函数说明: 发送文件消息
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: wxid 微信ID filepath 文件路径
// 返 回 值: void 
//************************************************************
void SendFileMessage(wchar_t* wxid, wchar_t* filepath)
{
	//构造需要的地址
	DWORD dwBase = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
	DWORD dwCall1 = dwBase + WxFileMessage1;
	DWORD dwCall2 = dwBase + WxFileMessage2;
	DWORD dwCall3 = dwBase + WxFileMessage3;	//组合数据
	DWORD dwCall4 = dwBase + WxFileMessage4;	//发送消息
	DWORD dwParams = dwBase + WxFileMessageParam;

	char buff[0x45C] = { 0 };

	//构造需要的数据
	Wxid wxidStruct = { 0 };
	wxidStruct.str = wxid;
	wxidStruct.strLen = wcslen(wxid);
	wxidStruct.maxLen = wcslen(wxid) * 2;

	filePath filePathStruct = { 0 };
	filePathStruct.str = filepath;
	filePathStruct.strLen = wcslen(filepath);
	filePathStruct.maxLen = wcslen(filepath) * 2;

	//取出需要的数据的地址
	char* pFilePath = (char*)&filePathStruct.str;
	char* pWxid = (char*)&wxidStruct.str;

	__asm {
		pushad;
		push 0x1;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		push dwParams;
		call dwCall1;
		sub esp, 0x14;
		mov ecx, esp;
		mov ebx, pFilePath;
		push ebx;
		call dwCall2;
		sub esp, 0x14;
		mov ecx, esp;
		push pWxid;
		call dwCall2;
		lea eax, buff;
		push eax;
		call dwCall3;
		mov ecx, eax;
		call dwCall4;
		popad;
	}
}



//************************************************************
// 函数名称: SendImageMessage
// 函数说明: 发送图片消息
// 作    者: GuiShou
// 时    间: 2019/7/7
// 参    数: wxid 微信ID filepath 图片路径
// 返 回 值: void 
//************************************************************
void SendImageMessage(wchar_t* wxid, wchar_t* filepath)
{
	//组装微信ID的数据结构
	SendImageStruct imagewxid;
	memcpy(imagewxid.wxid, wxid, wcslen(wxid) + 1);
	imagewxid.length = wcslen(wxid) + 1;
	imagewxid.maxLength = wcslen(wxid)*2;
	imagewxid.pWxid = wxid;

	//组装文件路径的数据结构
	SendImageStruct imagefilepath;
	memcpy(imagefilepath.wxid, filepath, wcslen(filepath) + 1);
	imagefilepath.length = wcslen(filepath) + 1;
	imagefilepath.maxLength = MAX_PATH;
	imagefilepath.pWxid = filepath;

	char buff[0x45C] = { 0 };

	DWORD dwCall1 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxSendImageCall1;
	DWORD dwCall2 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxSendImageCall2;
	DWORD myEsp = 0;


	//微信发送图片调用了GidCreateBimapFileCM 之后图片一直被占用 无法删除 patch掉下面的代码
	unsigned char oldcode[5] = {0};
	unsigned char fix[5] = { 0x31,0xC0,0x90,0x90,0x90 };
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxPatchAddr;
	//修改代码段属性
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 5, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//先保存原有指令
	memcpy(oldcode, (LPVOID)dwPathcAddr, 5);
	//再Patch掉
	memcpy((LPVOID)dwPathcAddr, fix, 5);
	__asm
	{
		//保存esp
		mov myEsp, esp;

		lea ebx, imagefilepath;
		push ebx;
		lea eax, imagewxid;
		push eax;
		lea eax, buff;
		push eax;
		push 0;
		call dwCall1;
		add esp, 0x4;
		mov ecx, eax;
		call dwCall2;
		//恢复堆栈
		mov eax, myEsp;
		mov esp, eax;
	}
	//调用完之后恢复
	memcpy((LPVOID)dwPathcAddr, oldcode, 5);
	//恢复属性
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}


//************************************************************
// 函数名称: WxDeleteUser
// 函数说明: 删除好友
// 作    者: GuiShou
// 时    间: 2019/7/8
// 参    数: wxid 微信ID
// 返 回 值: void 
//************************************************************
void DeleteUser(wchar_t* wxid)
{
	//结构体
	struct StructWxid
	{
		//发送的文本消息指针
		wchar_t* pWxid;
		//字符串长度
		DWORD length;
		//字符串最大长度
		DWORD maxLength;

		//补充两个占位数据
		DWORD fill1;
		DWORD fill2;
	};

	DWORD dwBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	//构造数据
	StructWxid structWxid = { 0 };
	structWxid.pWxid = wxid;
	structWxid.length = wcslen(wxid);
	structWxid.maxLength = wcslen(wxid) * 2;

	DWORD* asmMsg = (DWORD*)&structWxid.pWxid;
	DWORD dwCallAddr = dwBaseAddress + WxDeleteUser;

	__asm {
		mov ecx, 0;
		push ecx;
		mov edi, asmMsg;
		push edi;
		call  dwCallAddr;
	}
}


//************************************************************
// 函数名称: SendXmlCard
// 函数说明: 发送XML名片
// 作    者: GuiShou
// 时    间: 2019/7/10
// 参    数: RecverWxid 发送者微信ID SendWxid要发送的微信ID NickName微信昵称
// 返 回 值: void 
//************************************************************
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName)
{
	struct wxString
	{
		wchar_t * pStr;
		int strLen;
		int strMaxLen;
		char fillbuff[0x8];
	};

	wxString pWxid = { 0 };
	wxString pXml = { 0 };
	wchar_t xml[0x2000] = { 0 };
	pWxid.pStr = RecverWxid;
	pWxid.strLen = wcslen(RecverWxid);
	pWxid.strMaxLen = wcslen(RecverWxid) * 2;

	swprintf_s(xml, L"<?xml version=\"1.0\"?><msg bigheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/0\" smallheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/132\" username=\"%s\" nickname=\"%s\" fullpy=\"?\" shortpy=\"\" alias=\"%s\" imagestatus=\"3\" scene=\"17\" province=\"北京\" city=\"中国\" sign=\"\" sex=\"2\" certflag=\"0\" certinfo=\"\" brandIconUrl=\"\" brandHomeUrl=\"\" brandSubscriptConfigUrl= \"\" brandFlags=\"0\" regionCode=\"CN_BeiJing_BeiJing\" />", SendWxid, NickName, SendWxid);
	pXml.pStr = xml;
	pXml.strLen = wcslen(xml);
	pXml.strMaxLen = wcslen(xml) * 2;

	char* asmWxid = (char *)&pWxid.pStr;
	char* asmXml = (char *)&pXml.pStr;
	char buff[0x20C] = { 0 };
	DWORD callAdd = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxSendXmlCard;


	__asm {
		mov eax, asmXml
		push 0x2A
		mov edx, asmWxid
		push 0x0
		push eax
		lea ecx, buff
		call callAdd
		add esp, 0xC
	}
}