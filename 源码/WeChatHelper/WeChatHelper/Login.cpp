#include "stdafx.h"
#include "Login.h"
#include <stdio.h>


//备份的原数据
BYTE backCode[5] = { 0 };
BYTE jmpCode[5] = { 0 };

DWORD pEcx = 0;		//ecx寄存器
DWORD dwRetAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + QrCodeOffset + 5;	//返回地址


//************************************************************
// 函数名称: HookQrCode
// 函数说明: HOOK微信二维码
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: DWORD dwHookOffset 要hook的偏移 
// 返 回 值: void
//************************************************************
void HookQrCode(DWORD dwHookOffset)
{
	//拿到模块基址
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	//计算需要HOOK的地址
	DWORD dwHookAddr = dwWeChatWinAddr + dwHookOffset;

	//填充数据
	jmpCode[0] = 0xE9;
	//计算偏移
	*(DWORD*)(&jmpCode[1]) = (DWORD)ShowPic - dwHookAddr - 5;

	// 保存以前的属性用于还原
	DWORD OldProtext = 0;

	// 因为要往代码段写入数据，又因为代码段是不可写的，所以需要修改属性
	VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	//保存原有的指令
	memcpy(backCode, (void*)dwHookAddr, 5);

	//写入自己的代码
	memcpy((void*)dwHookAddr, jmpCode, 5);

	// 执行完了操作之后需要进行还原
	VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
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
	//备份寄存器
	__asm pushad;
	__asm pushfd;
	//取出ecx的内容
	__asm mov pEcx, ecx;
	SaveImg(pEcx);
	//恢复寄存器
	__asm popfd;
	__asm popad;

	//跳转到返回地址
	__asm jmp dwRetAddr;
}


//************************************************************
// 函数名称: SaveImg
// 函数说明: 保存二维码图片
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: DWORD qrcode 二维码图片所在的地址
// 返 回 值: void
//************************************************************
void SaveImg(DWORD qrcode)
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
		MessageBoxA(NULL, "创建图片文件失败", "错误", 0);
		return;
	}

	DWORD dwRead = 0;
	if (WriteFile(hFile, PicData, cpyLen, &dwRead, NULL) == 0)
	{
		MessageBoxA(NULL, "写入图片文件失败", "错误", 0);
		return;
	}
	CloseHandle(hFile);
	
	//完成之后卸载HOOK
	UnHookQrCode(QrCodeOffset);

}



//************************************************************
// 函数名称: UnHook
// 函数说明: 卸载HOOK
// 作    者: GuiShou
// 时    间: 2019/6/16
// 参    数: void
// 返 回 值: void
//************************************************************
void UnHookQrCode(DWORD dwHookOffset)
{
	//拿到模块基址
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	DWORD dwHookAddr = dwWeChatWinAddr + dwHookOffset;

	// 保存以前的属性用于还原
	DWORD OldProtext = 0;

	// 因为要往代码段写入数据，又因为代码段是不可写的，所以需要修改属性
	VirtualProtect((LPVOID*)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	// Hook 就是向其中写入自己的代码
	memcpy((LPVOID*)dwHookAddr, backCode, 5);

	// 执行完了操作之后需要进行还原
	VirtualProtect((LPVOID*)dwHookAddr, 5, OldProtext, &OldProtext);
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
	DWORD dwCallAddr1 = dwBaseAddress + GoToQrCode1;
	DWORD dwCallAddr2 = dwBaseAddress + GoToQrCode2;

	__asm {
		call dwCallAddr1;
		mov ecx, eax;
		call dwCallAddr2;
	}
}

