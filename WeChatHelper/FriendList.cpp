#include "stdafx.h"
#include "FriendList.h"
#include "shellapi.h"
#include <sstream>
#include <iomanip>
#include <strstream>
#include <map>
#include <iostream>
#include <fstream>
#include "ChatRecord.h"
#pragma comment(lib, "Version.lib")


//保存所有好友列表的map容器
map<wstring, wstring> g_userinfolist;

DWORD overWritedCallAdd= GetWeChatWinBase() + WxFriendListCall;

DWORD jumBackAddress= GetWeChatWinBase() + WxFriendList+5;

//推荐号列表
wstring g_referencenumber[11] =
{
	L"fmessage",L"qqmail",L"medianote",L"qmessage",L"newsapp",L"filehelper"
	L"weixin", L"tmessage", L"mphelper",L"gh_7aac992b0363", L"qqsafe"
};

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
	HookAnyAddress(GetWeChatWinBase() + WxFriendList, GetUserListInfo);
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
	__asm
	{
		pushad;
		push esi;
		call SendUserListInfo;
		popad;

		//补充被覆盖的代码
		call overWritedCallAdd;

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
void ReSendUser(UserListInfo* user)
{
	HWND hWnd = NULL;
	while (true)
	{
		//发送到控制端
		hWnd = FindWindow(NULL, TEXT("微信助手"));
		if (hWnd == NULL)
		{
			Sleep(200);
			continue;
		}
		break;
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//保存一个数值, 可以用来作标志等
	userinfo.cbData = sizeof(UserListInfo);// strlen(szSendBuf);//待发送的数据的长
	userinfo.lpData = user;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
	delete user;
}




//************************************************************
// 函数名称: SendUserListInfo
// 函数说明: 发送好友列表
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: r_esi 好友列表所在的数据指针
// 返 回 值: void 
//************************************************************
void __stdcall SendUserListInfo(DWORD r_esi)
{
	//个人微信号、群号
	wstring wxid = GetMsgByAddress(r_esi + 0x8);
	wstring nickname = GetMsgByAddress(r_esi + 0x64);

	//好友列表去重
	map<wstring, wstring>::iterator it;
	it = g_userinfolist.find(wxid);
	//如果返回值不等于end() 说明找到了 直接返回防止重复
	if (it != g_userinfolist.end())
	{
		return;
	}
	//如果没有找到 则插入到容器
	g_userinfolist.insert(make_pair(wxid, nickname));

	//排除推荐号列表
	for (int i = 0; i < 11; i++)
	{
		if (g_referencenumber[i] == wxid)
		{
			return;
		}
	}


	unique_ptr<UserListInfo> user(new UserListInfo);

	LPVOID pUserWxid = *((LPVOID *)(r_esi + 0x8));		//微信ID
	LPVOID pUserNumber = *((LPVOID *)(r_esi + 0x1C));	//微信号
	LPVOID pUserNick = *((LPVOID *)(r_esi + 0x64));		//昵称
	LPVOID pUserReMark = *((LPVOID *)(r_esi + 0x50));	//备注

	swprintf_s(user->UserId, L"%s", (wchar_t*)pUserWxid);
	swprintf_s(user->UserNumber, L"%s", (wchar_t*)pUserNumber);
	swprintf_s(user->UserNickName, L"%s", (wchar_t*)pUserNick);
	swprintf_s(user->UserRemark, L"%s", (wchar_t*)pUserReMark);


	//发送到控制端
	HWND hWnd = FindWindow(NULL, TEXT("微信助手"));
	if (hWnd == NULL)
	{
		UserListInfo* outuser = new UserListInfo;
	
		swprintf_s(outuser->UserId, L"%s", (wchar_t*)pUserWxid);
		swprintf_s(outuser->UserNumber, L"%s", (wchar_t*)pUserNumber);
		swprintf_s(outuser->UserNickName, L"%s", (wchar_t*)pUserNick);
		swprintf_s(outuser->UserRemark, L"%s", (wchar_t*)pUserReMark);
	
	
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReSendUser, outuser, 0, NULL);
		CloseHandle(hThread);
	}
	
	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//保存一个数值, 可以用来作标志等
	userinfo.cbData = sizeof(UserListInfo);// strlen(szSendBuf);//待发送的数据的长
	userinfo.lpData = user.get();// szSendBuf;//待发送的数据的起始地址(可以为NULL)
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
	DWORD dwSendCallAddr = GetWeChatWinBase() + WxSendMessage;

	//组装微信ID/群ID的结构体
	GeneralStruct id(wxid);
	//消息内容
	GeneralStruct text(msg);

	//取出微信ID和消息的地址
	char* pWxid = (char*)&id.pstr;
	char* pWxmsg = (char*)&text.pstr;

	char buff[0x81C] = { 0 };
	char buff2[0x81C] = { 0 };

	//调用微信发送消息call
	__asm {
		push 0x1;
		lea edi, buff2;
		push edi;
		mov ebx, pWxmsg;
		push ebx;
		lea ecx, buff;
		mov edx, pWxid;
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
	DWORD dwBase = GetWeChatWinBase();
	DWORD dwCall1 = dwBase + WxFileMessage1;
	DWORD dwCall2 = dwBase + WxFileMessage2;
	DWORD dwCall3 = dwBase + WxFileMessage3;	//组合数据
	DWORD dwCall4 = dwBase + WxFileMessage4;	//发送消息
	DWORD dwParams = dwBase + WxFileMessageParam;

	char buff[0x528] = { 0 };

	//构造需要的数据
	GeneralStruct wxidStruct(wxid);
	GeneralStruct filePathStruct(filepath);

	//取出需要的数据的地址
	char* pFilePath = (char*)&filePathStruct.pstr;
	char* pWxid = (char*)&wxidStruct.pstr;



	__asm {
		pushad;
		sub esp, 0x14;
		lea eax, buff;
		mov ecx, esp;
		push eax;
		call dwCall2;

		push 0;
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
		mov eax, pWxid;
		mov ecx, esp;
		push eax;
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
	GeneralStruct imagewxid(wxid);
	//组装文件路径的数据结构
	GeneralStruct imagefilepath(filepath);
	char buff[0x528] = { 0 };
	char buff2[0x60] = { 0 };


	DWORD dwCall3 = GetWeChatWinBase() + WxSendImageCall3;
	DWORD dwCall1 = GetWeChatWinBase()+ WxSendImageCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxSendImageCall2;


	//微信发送图片调用了GidCreateBimapFileCM 之后图片一直被占用 无法删除 patch掉下面的代码
	unsigned char oldcode[5] = {0};
	unsigned char fix[5] = { 0x31,0xC0,0x90,0x90,0x90 };
	DWORD dwPathcAddr = GetWeChatWinBase() + WxPatchAddr;
	//修改代码段属性
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 5, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//先保存原有指令
	memcpy(oldcode, (LPVOID)dwPathcAddr, 5);
	//再Patch掉
	memcpy((LPVOID)dwPathcAddr, fix, 5);


	__asm
	{
		pushad;
		sub esp, 0x14;
		lea eax, buff2;
		mov ecx, esp;
		push eax;
		call dwCall3;
		lea ebx, imagefilepath;
		push ebx;
		lea eax, imagewxid;
		push eax;
		lea eax, buff;
		push eax;
		call dwCall1;
		mov ecx, eax;
		call dwCall2;
		popad;
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
	DWORD dwBaseAddress = GetWeChatWinBase();
	//构造数据
	GeneralStruct structWxid(wxid);
	DWORD* asmMsg = (DWORD*)&structWxid.pstr;
	DWORD dwCallAddr = dwBaseAddress + WxDeleteUser;

	__asm 
	{
		mov ecx, 0;
		push ecx;
		mov esi, asmMsg;
		push esi;
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
	wchar_t xml[0x2000] = { 0 };
	swprintf_s(xml, L"<?xml version=\"1.0\"?><msg bigheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/0\" smallheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/132\" username=\"%s\" nickname=\"%s\" fullpy=\"?\" shortpy=\"\" alias=\"%s\" imagestatus=\"3\" scene=\"17\" province=\"北京\" city=\"中国\" sign=\"\" sex=\"2\" certflag=\"0\" certinfo=\"\" brandIconUrl=\"\" brandHomeUrl=\"\" brandSubscriptConfigUrl= \"\" brandFlags=\"0\" regionCode=\"CN_BeiJing_BeiJing\" />", SendWxid, NickName, SendWxid);
	GeneralStruct pWxid(RecverWxid);
	GeneralStruct pXml(xml);


	char* asmWxid = (char *)&pWxid.pstr;
	char* asmXml = (char *)&pXml.pstr;
	char buff[0x20C] = { 0 };
	DWORD callAdd = GetWeChatWinBase() + WxSendXmlCard;


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



//************************************************************
// 函数名称: wstringToString
// 函数说明: 将wstring转成String
// 作    者: GuiShou
// 时    间: 2019/9/17
// 参    数: wstr
// 返 回 值: string 
//************************************************************
std::string wstringToString(const std::wstring& wstr)
{
	LPCWSTR pwszSrc = wstr.c_str();
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
		return std::string("");

	char* pszDst = new char[nLen];
	if (!pszDst)
		return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	std::string str(pszDst);
	delete[] pszDst;
	pszDst = NULL;
	return str;
}




//************************************************************
// 函数名称: GetNickNameByWxid
// 函数说明: 根据好友列表的微信ID/群ID来获取微信昵称/群昵称
// 作    者: GuiShou
// 时    间: 2020/2/10
// 参    数: nickname 昵称
// 返 回 值: void 
//************************************************************
wstring GetNickNameByWxid(wstring wxid)
{
	map<wstring, wstring>::iterator it;
	it = g_userinfolist.find(wxid);
	if (it != g_userinfolist.end())
	{
		return it->second;
	}
	else
	{
		return L"NULL";
	}
}


//************************************************************
// 函数名称: GetNicknameByWxid
// 函数说明: 根据微信ID获取昵称
// 作    者: GuiShou
// 时    间: 2020/2/10
// 参    数: wxid 微信ID
// 返 回 值: wchar_t* 昵称 
//************************************************************
wchar_t* GetNicknameByWxid(wchar_t* userwxid)
{
	DWORD dwCall1 = GetWeChatWinBase() + WxGetUserInfoByWxidCall1;
	DWORD dwCall2 =  GetWeChatWinBase() + WxGetUserInfoByWxidCall2;
	DWORD dwCall3 =  GetWeChatWinBase() + WxGetUserInfoByWxidCall3;

	GeneralStruct pWxid(userwxid);
	char* asmWxid = (char*)& pWxid.pstr;
	char buff[0x3D8] = { 0 };
	DWORD userData = 0;		//用户数据的地址
	__asm
	{
		pushad;
		lea edi, buff;
		push edi;
		sub esp, 0x14;
		mov eax, asmWxid;
		mov ecx, esp;
		push eax;
		call dwCall1;
		call dwCall2;
		call dwCall3;
		mov userData, edi;
		popad;
	}

	wchar_t tempnickname[100] = { 0 };
	DWORD wxNickAdd = userData + 0x64;	//昵称
	swprintf_s(tempnickname, L"%s", (wchar_t*)(*((LPVOID*)wxNickAdd)));

	wchar_t* nickname = new wchar_t[100]{ 0 };
	memcpy(nickname, tempnickname, wcslen(tempnickname) * 2);
	return nickname;
}
