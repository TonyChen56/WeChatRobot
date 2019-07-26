#include "stdafx.h"
#include "MainWindow.h"


void LogoutWeChat()
{
	DWORD dwBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCallAddress = dwBaseAddress + Logout;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dwCallAddress, 0, NULL, 0);
	if (hThread != 0)
	{
		CloseHandle(hThread);
	}
}

