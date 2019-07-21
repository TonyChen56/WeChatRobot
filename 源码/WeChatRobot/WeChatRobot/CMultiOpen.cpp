#include "stdafx.h"
#include <TlHelp32.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi")
#include "CMultiOpen.h"
#include <stdio.h>


typedef NTSTATUS(NTAPI *NTQUERYOBJECT)(
	_In_opt_   HANDLE Handle,
	_In_       OBJECT_INFORMATION_CLASS ObjectInformationClass,
	_Out_opt_  PVOID ObjectInformation,
	_In_       ULONG ObjectInformationLength,
	_Out_opt_  PULONG ReturnLength
	);


typedef NTSTATUS
(NTAPI *ZWQUERYSYSTEMINFORMATION)(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID SystemInformation,
	IN ULONG SystemInformationLength,
	OUT PULONG ReturnLength OPTIONAL
	);
ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandleA("ntdll.dll"), "ZwQuerySystemInformation");
NTQUERYOBJECT    NtQueryObject = (NTQUERYOBJECT)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryObject");


//************************************************************
// 函数名称: ElevatePrivileges
// 函数说明: 进程提权
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: void
// 返 回 值: BOOL
//***********************************************************
BOOL ElevatePrivileges()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken))
		return FALSE;
	LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&tkp.Privileges[0].Luid);
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if(!AdjustTokenPrivileges(hToken,FALSE,&tkp,sizeof(TOKEN_PRIVILEGES),NULL,NULL))
	{
		return FALSE;
	}

	return TRUE;
}


//************************************************************
// 函数名称: DuplicateHandleEx
// 函数说明: 复制句柄
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: void
// 返 回 值: BOOL
//***********************************************************
HANDLE DuplicateHandleEx(DWORD pid, HANDLE h, DWORD flags)
{
	HANDLE hHandle = NULL;

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if(hProc)
	{
		if(!DuplicateHandle(hProc,
			(HANDLE)h, GetCurrentProcess(),
			&hHandle, 0, FALSE, /*DUPLICATE_SAME_ACCESS*/flags))
		{
			hHandle = NULL;
		}
	}

	CloseHandle(hProc);
	return hHandle;
}


//************************************************************
// 函数名称: GetProcIds
// 函数说明: 获取PID
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: Name Pids
// 返 回 值: int
//***********************************************************
int GetProcIds(LPWSTR Name, DWORD* Pids)
{
	PROCESSENTRY32 pe32 = {sizeof(pe32)};
	int num = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnap)
	{
		if(Process32First(hSnap, &pe32))
		{
			do {
				if(!StrCmpW(Name, pe32.szExeFile))
				{
					if(Pids)
					{
						Pids[num++] = pe32.th32ProcessID;
					}
				}
			} while(Process32Next(hSnap, &pe32));
		}
		CloseHandle(hSnap);
	}

	return num;
}


//************************************************************
// 函数名称: IsTargetPid
// 函数说明: 是否是目标PID
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: Pid Pids num
// 返 回 值: BOOL
//***********************************************************
BOOL IsTargetPid(DWORD Pid, DWORD* Pids, int num)
{
	for(int i=0; i<num; i++)
	{
		if(Pid == Pids[i])
		{
			return TRUE;
		}
	}
	return FALSE;
}


//************************************************************
// 函数名称: PatchWeChat
// 函数说明: 修改微信
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: void
// 返 回 值: int
//***********************************************************
int PatchWeChat()
{
	DWORD dwSize = 0;
	POBJECT_NAME_INFORMATION pNameInfo;
	POBJECT_NAME_INFORMATION pNameType;
	PVOID pbuffer = NULL;
	NTSTATUS Status;
	DWORD nIndex = 0;
	DWORD dwFlags = 0;
	char szType[128] = {0};
	char szName[512] = {0};

	ElevatePrivileges();

	DWORD Pids[100] = {0};

	DWORD Num = GetProcIds(L"WeChat.exe", Pids);
	if(Num == 0)
	{
		return 0;
	}
		
	if(!ZwQuerySystemInformation)
	{
		goto Exit0;
	}

	pbuffer = VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);

	if(!pbuffer)
	{
		goto Exit0;
	}

	Status = ZwQuerySystemInformation(SystemHandleInformation, pbuffer, 0x1000, &dwSize);

	if(!NT_SUCCESS(Status))
	{
		if (STATUS_INFO_LENGTH_MISMATCH != Status)
		{
			goto Exit0;
		}
		else
		{
			// 这里大家可以保证程序的正确性使用循环分配稍好
			if (NULL != pbuffer)
			{
				VirtualFree(pbuffer, 0, MEM_RELEASE);
			}

			if (dwSize*2 > 0x4000000)  // MAXSIZE
			{
				goto Exit0;
			}

			pbuffer = VirtualAlloc(NULL, dwSize*2, MEM_COMMIT, PAGE_READWRITE);

			if(!pbuffer)
			{
				goto Exit0;
			}

			Status = ZwQuerySystemInformation(SystemHandleInformation, pbuffer, dwSize*2, NULL);

			if(!NT_SUCCESS(Status))
			{
				goto Exit0;    
			}
		}
	}

	PSYSTEM_HANDLE_INFORMATION1 pHandleInfo = (PSYSTEM_HANDLE_INFORMATION1)pbuffer;

	for(nIndex = 0; nIndex < pHandleInfo->NumberOfHandles; nIndex++)
	{
		if(IsTargetPid(pHandleInfo->Handles[nIndex].UniqueProcessId, Pids, Num))
		{
			//
			HANDLE hHandle = DuplicateHandleEx(pHandleInfo->Handles[nIndex].UniqueProcessId, 
										(HANDLE)pHandleInfo->Handles[nIndex].HandleValue,
										DUPLICATE_SAME_ACCESS
										);
			if(hHandle == NULL) continue;
	
			Status = NtQueryObject(hHandle, ObjectNameInformation, szName, 512, &dwFlags);

			if (!NT_SUCCESS(Status))
			{
				CloseHandle(hHandle);
				continue;
			}

			Status = NtQueryObject(hHandle, ObjectTypeInformation, szType, 128, &dwFlags);

			if (!NT_SUCCESS(Status))
			{
				CloseHandle(hHandle);
				continue;
			}

			pNameInfo = (POBJECT_NAME_INFORMATION)szName;
			pNameType = (POBJECT_NAME_INFORMATION)szType;

			WCHAR TypName[1024] = {0};
			WCHAR Name[1024] = {0};

			wcsncpy_s(TypName, (WCHAR*)pNameType->Name.Buffer, pNameType->Name.Length/2);
			wcsncpy_s(Name, (WCHAR*)pNameInfo->Name.Buffer, pNameInfo->Name.Length/2);

			// 匹配是否为需要关闭的句柄名称
			if (0 == wcscmp(TypName, L"Mutant"))
			{
				if (wcsstr(Name, L"_WeChat_App_Instance_Identity_Mutex_Name"))
				{
					CloseHandle(hHandle);

					hHandle = DuplicateHandleEx(pHandleInfo->Handles[nIndex].UniqueProcessId, 
						(HANDLE)pHandleInfo->Handles[nIndex].HandleValue,
						DUPLICATE_CLOSE_SOURCE
						);

					if(hHandle)
					{
						printf("+ Patch wechat success!\n");
						CloseHandle(hHandle);
					}
					else
					{
						printf("- Patch error: %d\n", GetLastError());
					}

					goto Exit0;
				}
			}

			CloseHandle(hHandle);
		}
		
	}

Exit0:
	if (NULL != pbuffer)
	{
		VirtualFree(pbuffer, 0, MEM_RELEASE);
	}

	return 0;
}


//************************************************************
// 函数名称: OpenWeChat
// 函数说明: 打开微信
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: void
// 返 回 值: void
//***********************************************************
void OpenWeChat()
{
	HKEY hKey = NULL;
	if(ERROR_SUCCESS != RegOpenKey(HKEY_CURRENT_USER, L"Software\\Tencent\\WeChat", &hKey))
	{
		return;
	}
	
	DWORD Type = REG_SZ;
	WCHAR Path[MAX_PATH] = {0};
	DWORD cbData = MAX_PATH*sizeof(WCHAR);
	if(ERROR_SUCCESS != RegQueryValueEx(hKey, L"InstallPath", 0, &Type, (LPBYTE)Path, &cbData))
	{
		goto __exit;
	}
	
	PathAppend(Path, L"WeChat.exe");

	ShellExecute(NULL, L"Open", Path, NULL, NULL, SW_SHOW);
	
__exit:
	if(hKey)
	{
		RegCloseKey(hKey);
	}
}

