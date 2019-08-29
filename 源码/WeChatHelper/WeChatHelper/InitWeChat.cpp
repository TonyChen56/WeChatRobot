<<<<<<< HEAD
#include "stdafx.h"
#include <string>
#include <strstream>
#include <iostream>
#pragma comment(lib,"Version.lib")
#include "message.h"
using namespace std;



//************************************************************
// ��������: IsWxVersionValid
// ����˵��: ���΢�Ű汾�Ƿ�ƥ��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: void
// �� �� ֵ: BOOL
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
				//���汾2.6.7.57
				//2
				int s_major_ver = (pVsInfo->dwFileVersionMS >> 16) & 0x0000FFFF;
				//6
				int s_minor_ver = pVsInfo->dwFileVersionMS & 0x0000FFFF;
				//7
				int s_build_num = (pVsInfo->dwFileVersionLS >> 16) & 0x0000FFFF;
				//57
				int s_revision_num = pVsInfo->dwFileVersionLS & 0x0000FFFF;

				//�Ѱ汾����ַ���
				strstream wxVer;
				wxVer << s_major_ver << "." << s_minor_ver << "." << s_build_num << "." << s_revision_num;
				wxVer >> asVer;
			}
		}
		delete[] pBuf;
	}

	//�汾ƥ��
	if (asVer == wxVersoin)
	{
		return TRUE;
	}

	//�汾��ƥ��
	return FALSE;
}


//************************************************************
// ��������: CheckIsLogin
// ����˵��: ���΢���Ƿ��½
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void CheckIsLogin()
{
	//��ȡWeChatWin�Ļ�ַ
	DWORD  dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	while (true)
	{
		DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset + 0x194;
		if (*(DWORD*)dwIsLogin != 0)
		{
			//���ҵ�½���ھ��
			HWND hLogin = FindWindow(NULL, L"Login");
			if (hLogin == NULL)
			{
				MessageBoxA(NULL, "δ���ҵ�Login����", "����", MB_OK);
				return;
			}
			COPYDATASTRUCT login_msg;
			login_msg.dwData = WM_Login;
			login_msg.lpData = NULL;
			login_msg.cbData = 0;
			//������Ϣ�����ƶ�
			SendMessage(hLogin, WM_COPYDATA, (WPARAM)hLogin, (LPARAM)&login_msg);
			break;
		}
	}
}



=======
#include "stdafx.h"
#include <string>
#include <strstream>
#include <iostream>
#pragma comment(lib,"Version.lib")
#include "message.h"
using namespace std;



//************************************************************
// ��������: IsWxVersionValid
// ����˵��: ���΢�Ű汾�Ƿ�ƥ��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: void
// �� �� ֵ: BOOL
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
				//���汾2.6.7.57
				//2
				int s_major_ver = (pVsInfo->dwFileVersionMS >> 16) & 0x0000FFFF;
				//6
				int s_minor_ver = pVsInfo->dwFileVersionMS & 0x0000FFFF;
				//7
				int s_build_num = (pVsInfo->dwFileVersionLS >> 16) & 0x0000FFFF;
				//57
				int s_revision_num = pVsInfo->dwFileVersionLS & 0x0000FFFF;

				//�Ѱ汾����ַ���
				strstream wxVer;
				wxVer << s_major_ver << "." << s_minor_ver << "." << s_build_num << "." << s_revision_num;
				wxVer >> asVer;
			}
		}
		delete[] pBuf;
	}

	//�汾ƥ��
	if (asVer == wxVersoin)
	{
		return TRUE;
	}

	//�汾��ƥ��
	return FALSE;
}


//************************************************************
// ��������: CheckIsLogin
// ����˵��: ���΢���Ƿ��½
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void CheckIsLogin()
{
	//��ȡWeChatWin�Ļ�ַ
	DWORD  dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	while (true)
	{
		DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset + 0x194;
		if (*(DWORD*)dwIsLogin != 0)
		{
			//���ҵ�½���ھ��
			HWND hLogin = FindWindow(NULL, L"Login");
			if (hLogin == NULL)
			{
				MessageBoxA(NULL, "δ���ҵ�Login����", "����", MB_OK);
				return;
			}
			COPYDATASTRUCT login_msg;
			login_msg.dwData = WM_Login;
			login_msg.lpData = NULL;
			login_msg.cbData = 0;
			//������Ϣ�����ƶ�
			SendMessage(hLogin, WM_COPYDATA, (WPARAM)hLogin, (LPARAM)&login_msg);
			break;
		}
	}
}



>>>>>>> 06c014d... Add files via upload
