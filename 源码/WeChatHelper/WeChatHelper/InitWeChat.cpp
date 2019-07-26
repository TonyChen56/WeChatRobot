#include "stdafx.h"
#include <string>
#include <strstream>
#include <iostream>
#pragma comment(lib,"Version.lib")
#include "message.h"
using namespace std;



//************************************************************
// 函数名称: IsWxVersionValid
// 函数说明: 检查微信版本是否匹配
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: void
// 返 回 值: BOOL
//************************************************************
BOOL IsWxVersionValid()
{
	DWORD wxBaseAddress = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
	const string wxVersoin = "2.6.8.52";

	WCHAR VersionFilePath[MAX_PATH];
	if (GetModuleFileName((HMODULE)wxBaseAddress, VersionFilePath, MAX_PATH) == 0)
	{
		return FALSE;
	}

	string asVer = "";
	VS_FIXEDFILEINFO* pVsInfo;
	unsigned int iFileInfoSize = sizeof(VS_FIXEDFILEINFO);
	int iVerInfoSize = GetFileVersionInfoSize(VersionFilePath, NULL);
	if (iVerInfoSize != 0) {
		char* pBuf = new char[iVerInfoSize];
		if (GetFileVersionInfo(VersionFilePath, 0, iVerInfoSize, pBuf)) {
			if (VerQueryValue(pBuf, TEXT("\\"), (void**)& pVsInfo, &iFileInfoSize)) {
				//主版本2.6.7.57
				//2
				int s_major_ver = (pVsInfo->dwFileVersionMS >> 16) & 0x0000FFFF;
				//6
				int s_minor_ver = pVsInfo->dwFileVersionMS & 0x0000FFFF;
				//7
				int s_build_num = (pVsInfo->dwFileVersionLS >> 16) & 0x0000FFFF;
				//57
				int s_revision_num = pVsInfo->dwFileVersionLS & 0x0000FFFF;

				//把版本变成字符串
				strstream wxVer;
				wxVer << s_major_ver << "." << s_minor_ver << "." << s_build_num << "." << s_revision_num;
				wxVer >> asVer;
			}
		}
		delete[] pBuf;
	}

	//版本匹配
	if (asVer == wxVersoin)
	{
		return TRUE;
	}

	//版本不匹配
	return FALSE;
}


//************************************************************
// 函数名称: CheckIsLogin
// 函数说明: 检查微信是否登陆
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: void
// 返 回 值: void
//************************************************************
void CheckIsLogin()
{
	//获取WeChatWin的基址
	DWORD  dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	while (true)
	{
		DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset + 0x194;
		if (*(DWORD*)dwIsLogin != 0)
		{
			//查找登陆窗口句柄
			HWND hLogin = FindWindow(NULL, L"Login");
			if (hLogin == NULL)
			{
				MessageBoxA(NULL, "未查找到Login窗口", "错误", MB_OK);
				return;
			}
			COPYDATASTRUCT login_msg;
			login_msg.dwData = WM_Login;
			login_msg.lpData = NULL;
			login_msg.cbData = 0;
			//发送消息给控制端
			SendMessage(hLogin, WM_COPYDATA, (WPARAM)hLogin, (LPARAM)&login_msg);
			break;
		}
	}
}



