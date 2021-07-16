#pragma once

DWORD ProcessNameFindPID(const char* ProcessName);	//通过进程名获取进程ID
BOOL InjectDll(HANDLE& wxPid); //注入dll
BOOL CheckIsInject(DWORD dwProcessid);	//检测DLL是否已经注入
