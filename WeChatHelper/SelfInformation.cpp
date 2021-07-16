#include "stdafx.h"
#include "SelfInformation.h"
#include "Function.h"
#include "CPublic.h"


//************************************************************
// 函数名称: GetSelfInformation
// 函数说明: 获取个人信息
// 作    者: GuiShou
// 时    间: 2019/12/4
// 参    数: void
// 返 回 值: void 
//************************************************************
//void GetInformation()
//{
//	Information *info = new Information;
//	char tempcontent[0x300];
//	//获取WeChatWin的基址
//	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
//
//	//微信ID 这里需要兼容新老微信号  新微信号是指针 老微信号是字符串
//	memset(tempcontent, 0, 0x300);
//	DWORD pWxid = dwWeChatWinAddr + 0x161C814;
//	//如果长度小于6或者大于20 说明这个地方是个指针
//	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWinAddr + 0x161C814));
//	if (strlen(tempcontent) < 0x6 || strlen(tempcontent) > 0x14)
//	{
//		//说明是新的微信号 微信ID用地址保存
//		sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWinAddr + 0x161C814)));
//	}
//	else
//	{
//		sprintf_s(tempcontent, "%s", (char*)(dwWeChatWinAddr + 0x161C814));
//	}
//	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode(tempcontent)) + 1, UTF8ToUnicode(tempcontent));
//
//	//微信ID
//	//char wxid[0x1000] = { 0 };
//	//DWORD pWxid = dwWeChatWinAddr + 0x161C814;
//	//sprintf_s(wxid, "%s", (char*)(*(DWORD*)pWxid));
//	//if (strlen(wxid) < 40)
//	//{
//	//	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode(wxid)) + 1, UTF8ToUnicode(wxid));
//	//}
//	//else
//	//{
//	//	wcscpy_s(info->wxid, wcslen(L"微信ID暂时无法显示") + 1, L"微信ID暂时无法显示");
//	//}
//
//	//微信性别
//	char sex[4] = { 0 };
//	memcpy(sex, (void*)(pWxid + 0x160), 1);
//
//	if (sex[0] == 1)
//	{
//		wcscpy_s(info->wxsex, wcslen(L"男") + 1, L"男");
//	}
//	if (sex[0] == 2)
//	{
//		wcscpy_s(info->wxsex, wcslen(L"女") + 1, L"女");
//	}
//
//	//微信昵称
//	char nickname[40] = { 0 };
//	if (*(DWORD*)(pWxid + 0x78 + 0x14) == 0xF)
//	{
//		sprintf_s(nickname, "%s", (char*)(pWxid + 0x78));
//		wcscpy_s(info->nickname, wcslen(UTF8ToUnicode(nickname)) + 1, UTF8ToUnicode(nickname));
//	}
//	else
//	{
//		DWORD pNickName = pWxid + 0x78;
//		sprintf_s(nickname, "%s", (char*)(*(DWORD*)pNickName));
//		wcscpy_s(info->nickname, wcslen(UTF8ToUnicode(nickname)) + 1, UTF8ToUnicode(nickname));
//	}
//
//	//微信账号
//	char wxcount[40] = { 0 };
//	sprintf_s(wxcount, "%s", (char*)(pWxid + 0x1DC));
//	wcscpy_s(info->wxcount, wcslen(UTF8ToUnicode(wxcount)) + 1, UTF8ToUnicode(wxcount));
//
//	//手机号
//	char phone[40] = { 0 };
//	sprintf_s(phone, "%s", (char*)(pWxid + 0xAC));
//	wcscpy_s(info->phonenumber, wcslen(UTF8ToUnicode(phone)) + 1, UTF8ToUnicode(phone));
//
//	//登陆设备
//	char device[15] = { 0 };
//	sprintf_s(device, "%s", (char*)(pWxid + 0x4B4));
//	wcscpy_s(info->device, wcslen(UTF8ToUnicode(device)) + 1, UTF8ToUnicode(device));
//
//	//国籍
//	char nation[10] = { 0 };
//	sprintf_s(nation, "%s", (char*)(pWxid + 0x254));
//	wcscpy_s(info->nation, wcslen(UTF8ToUnicode(nation)) + 1, UTF8ToUnicode(nation));
//
//	//省份
//	char province[20] = { 0 };
//	sprintf_s(province, "%s", (char*)(pWxid + 0x164));
//	wcscpy_s(info->province, wcslen(UTF8ToUnicode(province)) + 1, UTF8ToUnicode(province));
//
//	//城市
//	char city[20] = { 0 };
//	sprintf_s(city, "%s", (char*)(pWxid + 0x17C));
//	wcscpy_s(info->city, wcslen(UTF8ToUnicode(city)) + 1, UTF8ToUnicode(city));
//
//
//	//小头像
//	char header[0x100] = { 0 };
//	DWORD pHeader = pWxid + 0x358;
//	sprintf_s(header, "%s", (char*)(*(DWORD*)pHeader));
//	wcscpy_s(info->smallheader, wcslen(UTF8ToUnicode(header)) + 1, UTF8ToUnicode(header));
//
//
//	//大头像
//	char bigheader[0x100] = { 0 };
//	DWORD pbigheader = pWxid + 0x340;
//	sprintf_s(bigheader, "%s", (char*)(*(DWORD*)pbigheader));
//	wcscpy_s(info->bigheader, wcslen(UTF8ToUnicode(bigheader)) + 1, UTF8ToUnicode(bigheader));
//
//	//发送到客户端
//	HWND hInformation = FindWindow(NULL, L"Information");
//	if (hInformation == NULL)
//	{
//		OutputDebugStringA("未查找到Information窗口");
//		return;
//	}
//	COPYDATASTRUCT information_msg;
//	information_msg.dwData = WM_GetInformation;
//	information_msg.lpData = info;
//	information_msg.cbData = sizeof(Information);
//	//发送消息给控制端
//	SendMessage(hInformation, WM_COPYDATA, (WPARAM)hInformation, (LPARAM)&information_msg);
//
//	delete info;
//}



void GetInformation()
{
	unique_ptr<PersonalInformation> info(new PersonalInformation);

	DWORD dwWeChatWin = GetWeChatWinBase();

	char tempcontent[0x300];
	//微信号
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxCount));

	//判断是否为0 是0说明微信号为空
	if (tempcontent[0] == 0)
	{
		wcscpy_s(info->wxcount, wcslen(L"NULL") + 1, L"NULL");
	}
	else
	{
		wcscpy_s(info->wxcount, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());
	}


	//微信ID 这里需要兼容新老微信号  新微信号是指针 老微信号是字符串
	memset(tempcontent, 0, 0x300);
	DWORD pWxid = dwWeChatWin + WxID;
	//如果长度小于6或者大于20 说明这个地方是个指针
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxID));
	if (strlen(tempcontent) < 0x6 || strlen(tempcontent) > 0x14)
	{
		//说明是新的微信号 微信ID用地址保存
		sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxID)));
	}
	else
	{
		sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxID));
	}
	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//小头像
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxSmallHeader)));
	wcscpy_s(info->smallheader, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());



	//大头像
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxBigHeader)));
	wcscpy_s(info->bigheader, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//国家
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxNation));
	wcscpy_s(info->nation, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());

	//省份
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxProvince));
	wcscpy_s(info->province, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//城市
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxCity));
	wcscpy_s(info->city, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//手机号
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxPhoneNumber));
	wcscpy_s(info->phonenumber, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());

	//昵称
	memset(tempcontent, 0, 0x300);
	if (*(DWORD*)(dwWeChatWin + WxNickName + 0x14) == 0xF)
	{
		sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxNickName));
	}
	else
	{
		sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxNickName)));
	}
	
	wcscpy_s(info->nickname, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//缓存目录
	swprintf_s(info->cachedir, L"%s", (wchar_t*)(*(DWORD*)(dwWeChatWin + WxCacheDir)));


	//登陆设备
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxDevice));
	wcscpy_s(info->device, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//性别
	DWORD nSex = *(DWORD*)(dwWeChatWin + WxSex);
	if (nSex == 1)
	{
		wcscpy_s(info->wxsex, wcslen(L"男") + 1, L"男");
	}
	else if (nSex == 2)
	{
		wcscpy_s(info->wxsex, wcslen(L"女") + 1, L"女");
	}
	else
	{
		wcscpy_s(info->wxsex, wcslen(L"未设置") + 1, L"未设置");
	}


	HWND hInformation = FindWindow(NULL, L"Information");
	if (hInformation == NULL)
	{
		OutputDebugStringA("未查找到Information窗口");
		return;
	}
	COPYDATASTRUCT information_msg;
	information_msg.dwData = WM_GetInformation;
	information_msg.lpData = info.get();
	information_msg.cbData = sizeof(PersonalInformation);
	//发送消息给控制端
	SendMessage(hInformation, WM_COPYDATA, (WPARAM)hInformation, (LPARAM)&information_msg);
}
