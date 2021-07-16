#pragma once
#include <string>
using namespace std;


void HookAnyAddress(DWORD dwHookAddr, LPVOID dwJmpAddress);		//HOOK任意地址

DWORD GetWeChatWinBase();		//获取WeChatWin基址

wchar_t * UTF8ToUnicode(const char* str);

wstring UTF8ToUnicode2(const char* str);


void DebugCode(LPVOID pAddress);