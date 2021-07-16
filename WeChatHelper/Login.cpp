#include "stdafx.h"
#include "Login.h"


DWORD dwRetAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxQrCodeOffset + 5;	//返回地址
DWORD dwOverAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxQrCodeOffsetCall;	//覆盖的call


//************************************************************
// 函数名称: HookQrCode
// 函数说明: HOOK微信二维码
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: DWORD dwHookOffset 要hook的偏移 
// 返 回 值: void
//************************************************************
void HookQrCode()
{
	HookAnyAddress(GetWeChatWinBase()+ WxQrCodeOffset, ShowPic);
}


//************************************************************
// 函数名称: ShowPic
// 函数说明: 显示二维码
// 作    者: GuiShou
// 时    间: 2019/6/16
// 参    数: void
// 返 回 值: void
//************************************************************
void  __declspec(naked) ShowPic()
{
	__asm
	{
		pushad;
		pushfd;
		push ecx;
		call SaveImg;
		popfd;
		popad;
		call dwOverAddr;
		jmp dwRetAddr;
	}
}


//************************************************************
// 函数名称: SaveImg
// 函数说明: 保存二维码图片
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: DWORD qrcode 二维码图片所在的地址
// 返 回 值: void
//************************************************************
void __stdcall SaveImg(DWORD qrcode)
{
	//获取图片长度
	DWORD dwPicLen = qrcode + 0x4;
	size_t cpyLen = (size_t)*((LPVOID*)dwPicLen);
	//拷贝图片的数据
	char PicData[0xFFF] = { 0 };
	memcpy(PicData, *((LPVOID*)qrcode), cpyLen);

	char szTempPath[MAX_PATH] = { 0 };
	char szPicturePath[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, szTempPath);

	sprintf_s(szPicturePath, "%s%s", szTempPath, "qrcode.png");
	//将文件写到Temp目录下
	HANDLE hFile = CreateFileA(szPicturePath, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL)
	{
		OutputDebugStringA("创建图片文件失败");
		return;
	}

	DWORD dwRead = 0;
	if (WriteFile(hFile, PicData, cpyLen, &dwRead, NULL) == 0)
	{
		OutputDebugStringA("写入图片文件失败");
		return;
	}
	CloseHandle(hFile);
}



//************************************************************
// 函数名称: GotoQrCode
// 函数说明: 跳转到二维码窗口
// 作    者: GuiShou
// 时    间: 2019/6/16
// 参    数: void
// 返 回 值: void
//************************************************************
void GotoQrCode()
{
	DWORD dwBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCallAddr1 = dwBaseAddress + WxGoToQrCode1;
	DWORD dwCallAddr2 = dwBaseAddress + WxGoToQrCode2;

	__asm 
	{
		call dwCallAddr1;
		mov ecx, eax;
		call dwCallAddr2;
	}
}

