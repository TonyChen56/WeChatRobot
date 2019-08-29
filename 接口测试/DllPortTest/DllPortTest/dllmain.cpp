// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <stdio.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		HINSTANCE hDll = LoadLibrary(L"WeChatHelper.dll");

		typedef BOOL (WINAPI *FnIsWxVersionValid)();
		FnIsWxVersionValid IsWxVersionValid = (FnIsWxVersionValid)GetProcAddress(hDll, "IsWxVersionValid");
		BOOL isValid;
		isValid=IsWxVersionValid();
		
		char buff[MAX_PATH];
		sprintf_s(buff, "%d", isValid);
		MessageBoxA(NULL, buff, "Tip", 0);

	}
	break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

