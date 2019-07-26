#include "stdafx.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h >


//个人信息的结构体
struct Information
{
	wchar_t wxid[40];		//微信ID
	wchar_t wxcount[40];	//微信账号
	wchar_t nickname[40];	//微信昵称
	wchar_t wxsex[4];		//性别
	wchar_t phone[30];		//手机号
	wchar_t device[15];		//登陆设备
	wchar_t nation[10];		//国籍
	wchar_t province[20];	//省份
	wchar_t city[20];		//城市
	wchar_t header[0x100];	//头像
};


//************************************************************
// 函数名称: GetInformation
// 函数说明: 获取个人信息
// 作    者: GuiShou
// 时    间: 2019/7/7
// 参    数: void
// 返 回 值: void 
//************************************************************
void GetInformation()
{
	
	//昵称：WeChatWin.dll + 126D91C
	//微信账号：WeChatWin.dll + 126DA80
	//手机号：WeChatWin.dll + 126d950
	//登陆设备：WeChatWin.dll + 126DD48
	//国籍：WeChatWin.dll + 126DAF8
	//省份：WeChatWin.dll + 126DA08
	//城市：WeChatWin.dll + 126DA20
	//头像指针：WeChatWin.dll + 126DBE4
	//微信ID指针：WeChatWin.dll + 126D8A4
	//性别：WeChatWin.dll+126DA04
	Information *info=new Information;

	//获取WeChatWin的基址
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	//微信性别
	char sex[4] = { 0 };
	memcpy(sex, (void*)(dwWeChatWinAddr + 0x126DA04), 1);

	if (sex[0] == 1)
	{
		wcscpy_s(info->wxsex, wcslen(L"男") + 1, L"男");
	}
	if (sex[0] == 2)
	{
		wcscpy_s(info->wxsex, wcslen(L"女") + 1, L"女");
	}

	//微信昵称
	char nickname[40] = { 0 };
	sprintf_s(nickname, "%s", (char*)(dwWeChatWinAddr + 0x126D91C));
	wcscpy_s(info->nickname, wcslen(UTF8ToUnicode(nickname))+1, UTF8ToUnicode(nickname));
	

	//微信账号
	char wxcount[40] = { 0 };
	sprintf_s(wxcount, "%s", (char*)(dwWeChatWinAddr + 0x126DA80));
	wcscpy_s(info->wxcount, wcslen(UTF8ToUnicode(wxcount)) + 1, UTF8ToUnicode(wxcount));

	//手机号
	char phone[40] = { 0 };
	sprintf_s(phone, "%s", (char*)(dwWeChatWinAddr + 0x126d950));
	wcscpy_s(info->phone, wcslen(UTF8ToUnicode(phone)) + 1, UTF8ToUnicode(phone));

	//登陆设备
	char device[15] = { 0 };
	sprintf_s(device, "%s", (char*)(dwWeChatWinAddr + 0x126DD48));
	wcscpy_s(info->device, wcslen(UTF8ToUnicode(device)) + 1, UTF8ToUnicode(device));

	//国籍
	char nation[10] = { 0 };
	sprintf_s(nation, "%s", (char*)(dwWeChatWinAddr + 0x126DAF8));
	wcscpy_s(info->nation, wcslen(UTF8ToUnicode(nation)) + 1, UTF8ToUnicode(nation));

	//省份
	char province[20] = { 0 };
	sprintf_s(province, "%s", (char*)(dwWeChatWinAddr + 0x126DA08));
	wcscpy_s(info->province, wcslen(UTF8ToUnicode(province)) + 1, UTF8ToUnicode(province));

	//城市
	char city[20] = { 0 };
	sprintf_s(city, "%s", (char*)(dwWeChatWinAddr + 0x126DA20));
	wcscpy_s(info->city, wcslen(UTF8ToUnicode(city)) + 1, UTF8ToUnicode(city));

	//微信ID
	char wxid[40] = { 0 };
	DWORD pWxid = dwWeChatWinAddr + 0x126D8A4;
	sprintf_s(wxid, "%s", (char*)(*(DWORD*)pWxid));
	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode(wxid)) + 1, UTF8ToUnicode(wxid));

	//头像
	char header[0x100] = { 0 };
	DWORD pHeader = dwWeChatWinAddr + 0x126DBE4;
	sprintf_s(header, "%s", (char*)(*(DWORD*)pHeader));
	wcscpy_s(info->header, wcslen(UTF8ToUnicode(header)) + 1, UTF8ToUnicode(header));

	//发送到客户端
	HWND hInformation = FindWindow(NULL, L"Information");
	if (hInformation == NULL)
	{
		MessageBoxA(NULL, "未查找到Information窗口", "错误", MB_OK);
		return;
	}
	COPYDATASTRUCT information_msg;
	information_msg.dwData = WM_GetInformation;
	information_msg.lpData = info;
	information_msg.cbData = sizeof(Information);
	//发送消息给控制端
	SendMessage(hInformation, WM_COPYDATA, (WPARAM)hInformation, (LPARAM)&information_msg);
}



//************************************************************
// 函数名称: UTF8ToUnicode
// 函数说明: 将UTF8编码转为Unicode(微信默认编码为UTF8)
// 作    者: GuiShou
// 时    间: 2019/7/7
// 参    数: str 需要转换的字符串
// 返 回 值: wchar_t 返回的字符串 
//************************************************************
wchar_t * UTF8ToUnicode(const char* str)
{
	int    textlen = 0;
	wchar_t * result;
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t *)malloc((textlen + 1) * sizeof(wchar_t));
	memset(result, 0, (textlen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);
	return    result;
}



//************************************************************
// 函数名称: AddWxUser
// 函数说明: 添加好友
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: wxid 微信ID msg添加好友时要发送的消息
// 返 回 值: void 
//************************************************************
void AddWxUser(wchar_t* wxid, wchar_t* msg)
{
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwParam1 = dwWeChatWinAddr + WxAddWxUserParam1;
	DWORD dwCall1 = dwWeChatWinAddr + WxAddWxUserCall1;
	DWORD dwCall2 = dwWeChatWinAddr + WxAddWxUserCall2;
	DWORD dwCall3 = dwWeChatWinAddr + WxAddWxUserCall3;
	DWORD dwCall4 = dwWeChatWinAddr + WxAddWxUserCall4;
	DWORD dwCall5 = dwWeChatWinAddr + WxAddWxUserCall5;

	struct TextStruct
	{
		wchar_t* pStr;
		int strLen;
		int strMaxLen;

	};

	TextStruct pWxid = { 0 };
	pWxid.pStr = wxid;
	pWxid.strLen = wcslen(wxid) + 1;
	pWxid.strMaxLen = (wcslen(wxid) + 1) * 2;


	TextStruct pMsg = { 0 };
	pMsg.pStr = msg;
	pMsg.strLen = wcslen(msg) + 1;
	pMsg.strMaxLen = (wcslen(msg) + 1) * 2;

	char* asmWxid = (char*)&pWxid.pStr;
	char* asmMsg = (char*)&pMsg.pStr;
	DWORD asmMsgText = (DWORD)pMsg.pStr;
	char buff3[0x100] = { 0 };
	char* buff = buff3;
	__asm
	{
		sub esp, 0x18;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xDC], esp;
		push  dwParam1;
		call dwCall1;
		sub esp, 0x18;
		mov eax, buff;
		mov dword ptr ss : [ebp - 0xE4], esp;
		mov ecx, esp;
		push eax;
		call dwCall2;
		push 0x6;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE8], esp;
		push - 0x1;
		mov edi, asmMsgText;
		push edi;
		call dwCall3;
		mov eax, asmMsg;
		push 0x2;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE0], esp;
		mov ebx, asmWxid;
		push ebx;
		call dwCall4;
		mov ecx, eax;
		call dwCall5;
	}
}


//************************************************************
// 函数名称: AntiRevoke
// 函数说明: 防撤回
// 作    者: GuiShou
// 时    间: 2019/7/15
// 参    数: void
// 返 回 值: void 
//************************************************************
void AntiRevoke()
{
	unsigned char fix[1] = { 0xEB };
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxAntiRevoke;
	//修改代码段属性
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 1, PAGE_EXECUTE_READWRITE, &dwOldAttr);

	//Patch
	memcpy((LPVOID)dwPathcAddr, fix, 1);

	//恢复属性
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}