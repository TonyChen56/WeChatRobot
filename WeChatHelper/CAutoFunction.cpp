#include "stdafx.h"
#include "CAutoFunction.h"
#include "Function.h"
#include <atlconv.h>
#include <direct.h> //_mkdir函数的头文件
#include <io.h>     //_access函数的头文件
#include <iostream>
#include <cstdio>
#include <ctime>
#include "ChatRecord.h"
#include <Shlobj.h>
#include <Shlwapi.h>
#include <atlconv.h>
#include <wininet.h>
#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib,"Wininet.lib")


//-----------------------------------------------保存表情-------------------------------------------------
BYTE bjmpcode[5] = { 0 };
DWORD dwReternAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetExpressionsAddr + 5;	//返回地址
DWORD dwCallAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetExpressionsCallAddr;


//************************************************************
// 函数名称: AgreeUserRequest
// 函数说明: 同意好友请求
// 作    者: GuiShou
// 时    间: 2019/7/17
// 参    数: v1 v2
// 返 回 值: void
//************************************************************
void AgreeUserRequest(wchar_t* v1, wchar_t* v2)
{
	DWORD base = GetWeChatWinBase();
	DWORD callAdd1 = base + WxAgreeUserRequestCall1;
	DWORD callAdd2 = base + WxAgreeUserRequestCall2;
	DWORD callAdd3 = base + WxAgreeUserRequestCall3;
	DWORD callAdd4 = base + WxAgreeUserRequestCall4;
	DWORD params = base + WxAgreeUserRequestParam;

	DWORD* asmP = (DWORD*)params;

	v1Info userInfoV1 = { 0 };
	v2Info userInfoV2 = { 0 };
	userInfoV1.v2 = (DWORD)&userInfoV2.fill;
	userInfoV1.v1 = v1;
	userInfoV1.v1Len = wcslen(v1);
	userInfoV1.maxV1Len = wcslen(v1) * 2;
	userInfoV2.v2 = v2;
	userInfoV2.v2Len = wcslen(v2);
	userInfoV2.maxV2Len = wcslen(v2) * 2;

	char* asmUser = (char*)&userInfoV1.fill;
	char buff[0x14] = { 0 };
	char buff2[0x48] = { 0 };
	char* asmBuff = buff2;

	__asm
	{
		mov ecx, asmUser;
		push 0x11;
		sub esp, 0x14;
		push esp;
		call callAdd1;
		mov ecx, asmUser;
		lea eax, buff;
		push eax;
		call callAdd2;
		mov esi, eax;
		sub esp, 0x8;
		mov ecx, asmP;
		call callAdd3;
		mov ecx, asmBuff;
		mov edx, ecx;
		push edx;
		push eax;
		push esi;
		call callAdd4;
	}
}


//************************************************************
// 函数名称: AutoAgreeUserRequest
// 函数说明: 自动同意好友请求
// 作    者: GuiShou
// 时    间: 2019/7/17
// 参    数: msg 消息内容
// 返 回 值: void
//************************************************************
void AutoAgreeUserRequest(wstring msg)
{
	int v1strat = msg.find(L"v3_");
	int v1end = msg.find(L"@stranger");
	wstring v1;
	v1 = msg.substr(v1strat, v1end - v1strat + 9);
	//找到v2
	int v2strat = msg.find(L"v4_");
	int v2end = msg.rfind(L"@stranger");
	wstring v2;
	v2 = msg.substr(v2strat, v2end - v2strat + 9);

	//调用同意好友请求的call
	AgreeUserRequest((wchar_t*)v1.c_str(), (wchar_t*)v2.c_str());
}


//************************************************************
// 函数名称: CllectMoney
// 函数说明: 收款
// 作    者: GuiShou
// 时    间: 2019/7/15
// 参    数: transferid 转账ID wxid 微信ID
// 返 回 值: void 
//************************************************************
void CllectMoney(wchar_t* transferid, wchar_t* wxid)
{
	CllectMoneyStruct cllect;
	cllect.ptransferid = transferid;
	cllect.transferidLen = wcslen(transferid) + 1;
	cllect.transferidMaxLen = (wcslen(transferid) + 1) * 2;
	cllect.pwxid = wxid;
	cllect.wxidLen = wcslen(wxid) + 1;
	cllect.wxidMaxLen = (wcslen(wxid) + 1) * 2;

	char* asmBuff = (char*)&cllect.ptransferid;

	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCall1 = dwWeChatWinAddr + WxCllectMoneyCall1;
	DWORD dwCall2 = dwWeChatWinAddr + WxCllectMoneyCall2;

	__asm
	{
		sub esp, 0x30;
		mov ecx, esp;
		mov eax, asmBuff;
		push eax;
		call dwCall1;
		call dwCall2;
		add esp, 0x30;
	}
}


//************************************************************
// 函数名称: AutoCllectMoney
// 函数说明: 自动收款
// 作    者: GuiShou
// 时    间: 2019/7/17
// 参    数: msg 消息内容
// 返 回 值: void
//************************************************************
void AutoCllectMoney(wstring msg,wchar_t* wxid)
{
	// 找到<transferid>字符串的位置
	int pos1 = msg.find(L"<transferid>");
	//找到]]></transferid>字符串的位置
	int pos2 = msg.find(L"]]></transferid>");
	//取出多余的字符串长度
	wstring noneed = L"<transferid><![CDATA[";
	int noneedLen = noneed.length();
	//取出转账ID
	wstring transferid;
	transferid = msg.substr(pos1 + noneedLen, (pos2 - pos1) - noneedLen);

	//调用收款call 实现自动收款
	CllectMoney((wchar_t*)transferid.c_str(), wxid);
}


//************************************************************
// 函数名称: AddCardUser
// 函数说明: 添加名片好友
// 作    者: GuiShou
// 时    间: 2019/7/18
// 参    数: v1 msg 消息内容
// 返 回 值: void
//************************************************************
void AddCardUser(wchar_t* v1, wchar_t* msg)
{
	DWORD dwWeChatWinAddr = GetWeChatWinBase();
	DWORD dwParam1 = dwWeChatWinAddr + WxAddWxUserParam1;
	DWORD dwCall1 = dwWeChatWinAddr + WxAddWxUserCall1;
	DWORD dwCall2 = dwWeChatWinAddr + WxAddWxUserCall2;
	DWORD dwCall3 = dwWeChatWinAddr + WxAddWxUserCall3;
	DWORD dwCall4 = dwWeChatWinAddr + WxAddWxUserCall4;
	DWORD dwCall5 = dwWeChatWinAddr + WxAddWxUserCall5;

	GeneralStruct pV1(v1);
	char* asmV1 = (char*)&pV1.pstr;
	char buff3[0x100] = { 0 };
	char* buff = buff3;
	__asm
	{
		sub esp, 0x18;
		mov ecx, esp;
		push  dwParam1;
		call dwCall1;
		sub esp, 0x18;
		mov eax, buff;
		mov ecx, esp;
		push eax;
		call dwCall2;
		push 0x11;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		mov edi, msg;
		push edi;
		call dwCall3;
		push 0x2;
		sub esp, 0x14;
		mov ecx, esp;
		mov ebx, asmV1;
		push ebx;
		call dwCall4;
		mov ecx, eax;
		call dwCall5;
	}
}



//************************************************************
// 函数名称: AutoAddCardUser
// 函数说明: 自动添加名片好友
// 作    者: GuiShou
// 时    间: 2019/7/18
// 参    数: msg 消息内容
// 返 回 值: void
//************************************************************
void AutoAddCardUser(wstring msg)
{
	//拿到V1
	int v1strat = msg.find(L"v1_");
	int v1end = msg.find(L"@stranger");
	wstring v1;
	v1 = msg.substr(v1strat, v1end - v1strat + 9);

	//调用添加名片好友函数
	AddCardUser((wchar_t*)v1.c_str(), (wchar_t*)L"快通过~快通过~ 吼吼！");
}


//************************************************************
// 函数名称: HookExtractExpression
// 函数说明: HOOK提取表情Call
// 作    者: GuiShou
// 时    间: 2019/7/21
// 参    数: void
// 返 回 值: void
//************************************************************
void HookExtractExpression()
{
	HookAnyAddress(GetWeChatWinBase() + WxGetExpressionsAddr, ExtractExpression);
}



//************************************************************
// 函数名称: ExtractExpression
// 函数说明: 提取表情
// 作    者: GuiShou
// 时    间: 2019/7/21
// 参    数: void
// 返 回 值: void
//************************************************************
void  __declspec(naked) ExtractExpression()
{
	__asm
	{
		pushad;
		push eax;
		call OutputExpression;
		popad;
		//恢复被覆盖的代码
		call dwCallAddr;
		//跳回返回地址
		jmp dwReternAddress;
	}
}


//************************************************************
// 函数名称: OutputExpression
// 函数说明: 输出表情
// 作    者: GuiShou
// 时    间: 2019/7/21
// 参    数: dwExpressionAddr 地址
// 返 回 值: void
//************************************************************
void __stdcall OutputExpression(DWORD dwExpressionAddr)
{
	//取出图片长度
	DWORD dwImageLen = *((DWORD*)(dwExpressionAddr + 4));
	//取出图片内容
	DWORD dwImage = *((DWORD*)(dwExpressionAddr));
	unsigned char magic_head[4] = { 0 };
	char postfix[5] = { 0 };
	memcpy(magic_head, (void*)dwImage, 3);
	//根据MAGIC头判断后缀
	if (magic_head[0] == 137 && magic_head[1] == 80 && magic_head[2] == 78)
	{
		strcpy_s(postfix, 5, ".png");
	}
	else if (magic_head[0] == 71 && magic_head[1] == 73 && magic_head[2] == 70)
	{
		strcpy_s(postfix, 5, ".gif");
	}
	else if (magic_head[0] == 255 && magic_head[1] == 216 && magic_head[2] == 255)
	{
		strcpy_s(postfix, 5, ".jpg");
	}

	//获取临时文件夹目录
	char temppath[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, temppath);
	char imagedir[25] = { "WeChatRecordExpressions" };

	//拼接存放微信表情的目录
	char WeChatExpressionsPath[MAX_PATH] = { 0 };
	sprintf_s(WeChatExpressionsPath, "%s%s\\", temppath, imagedir);
	//创建目录存放图片
	CreateDir(WeChatExpressionsPath);

	//保存表情图片
	CreateFileWithCurrentTime(WeChatExpressionsPath, postfix, dwImage, dwImageLen);
}






//************************************************************
// 函数名称: CreateFileWithCurrentTime
// 函数说明: 根据当前时间创建文件
// 作    者: GuiShou
// 时    间: 2019/9/24
// 参    数: filedir 文件目录 filepostfix文件后缀 filedata 文件开始地址 filedatalen文件 长度
// 返 回 值: void 
//************************************************************
void CreateFileWithCurrentTime(char* filedir, char* filepostfix, DWORD filedata, DWORD filedatalen)
{
	//获取当前时间作为文件名
	time_t rawtime;
	struct tm *ptminfo = new struct tm;
	time(&rawtime);
	localtime_s(ptminfo, &rawtime);
	char currenttime[30] = { 0 };
	sprintf_s(currenttime, "%02d%02d%02d%02d%02d%02d", ptminfo->tm_year + 1900,
		ptminfo->tm_mon + 1, ptminfo->tm_mday, ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

	//拼接完整的路径
	char filepath[MAX_PATH] = { 0 };
	sprintf_s(filepath, "%s%s%s", filedir, currenttime, filepostfix);
	//创建文件
	HANDLE hFile = CreateFileA(filepath, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "创建文件失败", "错误", 0);
		return;
	}
	//写入文件
	DWORD dwWrite = 0;
	WriteFile(hFile, (LPCVOID)filedata, filedatalen, &dwWrite, 0);
	//关闭句柄
	CloseHandle(hFile);
}


//************************************************************
// 函数名称: CreateDir
// 函数说明: 创建目录
// 作    者: GuiShou
// 时    间: 2019/7/21
// 参    数: dir 目录
// 返 回 值: void
//************************************************************
void CreateDir(const char *dir)
{
	int m = 0, n;
	string str1, str2;

	str1 = dir;
	str2 = str1.substr(0, 2);
	str1 = str1.substr(3, str1.size());

	while (m >= 0)
	{
		m = str1.find('\\');
		str2 += '\\' + str1.substr(0, m);
		n = _access(str2.c_str(), 0); //判断该目录是否存在
		if (n == -1)
		{
			_mkdir(str2.c_str());     //创建目录
		}
		str1 = str1.substr(m + 1, str1.size());
	}
}



//************************************************************
// 函数名称: GetXmlContent
// 函数说明: 获取需要的XML内容
// 作    者: GuiShou
// 时    间: 2019/11/15
// 参    数: fullxmlcontent 完整的XML内容  str1 需要获取的XML内容左边的字符串 str2 需要获取的XML内容右边的字符串
// 返 回 值: wstring 需要获取的XML内容
//************************************************************
wstring GetXmlContent(wstring fullxmlcontent, wstring str1, wstring str2)
{
	wstring targetstring;
	// 找到<title>字符串的位置
	int pos1 = fullxmlcontent.find(str1);
	//找到</title>字符串的位置
	int pos2 = fullxmlcontent.find(str2);

	if (pos1==wstring::npos|| pos2== wstring::npos)
	{
		return L"NULL";
	}

	//取出多余的字符串长度
	wstring noneedString1 = str1;
	int noneedLen1 = noneedString1.length();
	targetstring = fullxmlcontent.substr(pos1 + noneedLen1, pos2 - pos1 - noneedLen1);

	return targetstring;
}
