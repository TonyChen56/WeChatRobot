<<<<<<< HEAD
#include "stdafx.h"
#include "FriendList.h"
#include <stdio.h>
=======
#include "stdafx.h"
#include "FriendList.h"
#include <stdio.h>
>>>>>>> 06c014d... Add files via upload
#include "shellapi.h"
#include <string>
#include <sstream>
#include <string>
#include <iomanip>
#include <strstream>
#include <list>
#include <iostream>
#include <tuple>
#include<fstream>
#include "ChatRecord.h"
<<<<<<< HEAD
#pragma comment(lib, "Version.lib")
using namespace std;

=======
#pragma comment(lib, "Version.lib")
using namespace std;

>>>>>>> 06c014d... Add files via upload
typedef tuple <
	//wxid1
	wstring,
	//wxName
	wstring,
	//v1
	wstring,
	//nickName
	wstring
<<<<<<< HEAD
> USER_INFO;

//����7000���û��б�
list<USER_INFO> userInfoList(1);


//�û���Ϣ�ṹ��
struct UserInfo
{
	wchar_t UserId[80];
	wchar_t UserNumber[80];
	wchar_t UserRemark[80];
	wchar_t UserNickName[80];
};


//���ڵ���΢�ŷ�����Ϣcall�Ľṹ��
struct wxMsg
{
	wchar_t* pMsg;		//΢��ID
	int msgLen;			//ID����
	int buffLen;		//����������
	int fill1 = 0;
	int fill2 = 0;
};


//΢��ID�Ľṹ��
struct Wxid
{
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char file[0x8] = { 0 };
};

//�ļ�·���Ľṹ��
struct filePath
{
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char file[0x18] = { 0 };
};

//����ͼƬ�Ľṹ��
struct SendImageStruct
{
=======
> USER_INFO;

//����7000���û��б�
list<USER_INFO> userInfoList(1);


//�û���Ϣ�ṹ��
struct UserInfo
{
	wchar_t UserId[80];
	wchar_t UserNumber[80];
	wchar_t UserRemark[80];
	wchar_t UserNickName[80];
};


//���ڵ���΢�ŷ�����Ϣcall�Ľṹ��
struct wxMsg
{
	wchar_t* pMsg;		//΢��ID
	int msgLen;			//ID����
	int buffLen;		//����������
	int fill1 = 0;
	int fill2 = 0;
};


//΢��ID�Ľṹ��
struct Wxid
{
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char file[0x8] = { 0 };
};

//�ļ�·���Ľṹ��
struct filePath
{
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char file[0x18] = { 0 };
};

//����ͼƬ�Ľṹ��
struct SendImageStruct
{
>>>>>>> 06c014d... Add files via upload
	wchar_t* pWxid = nullptr;
	DWORD length = 0;
	DWORD maxLength = 0;
	DWORD fill1 = 0;
	DWORD fill2 = 0;
<<<<<<< HEAD
	wchar_t wxid[1024] = { 0 };
};


//HOOK��Ҫ�õ��ĵ�ȫ�ֱ���
DWORD overWritedCallAdd;
DWORD hookAddress;
DWORD jumBackAddress;
BYTE bBackCode[5] = { 0 };
DWORD r_esi = 0;


//************************************************************
// ��������: HookGetFriendList
// ����˵��: HOOK��ȡ�����б��call 
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void HookGetFriendList()
{

	DWORD wxBaseAddress = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
	//��Ҫhook�ĵ�ַ
	hookAddress = wxBaseAddress + FriendList;
	//�����ǵ�CALLĿ��
	overWritedCallAdd = wxBaseAddress + FriendListCall;

	//���صĵ�ַ
	jumBackAddress = hookAddress + 5;

	//��װ��ת����
	BYTE jmpCode[5] = { 0 };
	jmpCode[0] = 0xE9;


	//����ƫ��
	*(DWORD*)& jmpCode[1] = (DWORD)GetUserListInfo - hookAddress - 5;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID)hookAddress, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	//����ԭ�е�ָ��
	memcpy(bBackCode, (void*)hookAddress, 5);

	//д���Լ��Ĵ���
	memcpy((void*)hookAddress, jmpCode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID)hookAddress, 5, OldProtext, &OldProtext);
}


//************************************************************
// ��������: UnHookGetFriendList
// ����˵��: ж��HOOK��ȡ�����б��call 
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void UnHookGetFriendList()
{
	//�õ�ģ���ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	DWORD dwHookAddr = dwWeChatWinAddr + FriendList;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID*)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	// Hook ����������д���Լ��Ĵ���
	memcpy((LPVOID*)dwHookAddr, bBackCode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID*)dwHookAddr, 5, OldProtext, &OldProtext);
}


//************************************************************
// ��������: GetUserListInfo
// ����˵��: ��ȡ�û���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
__declspec(naked) void GetUserListInfo()
{
	//�����ֳ�
	__asm
	{
		//��ȡeax�Ĵ������ݣ�����һ��������
		mov r_esi, esi

		//����Ĵ���
		pushad
		pushf
	}

	//���ý�����Ϣ�ĺ���
	SendUserListInfo();

	//�ָ��ֳ�
	__asm
	{
		popf
		popad

		//���䱻���ǵĴ���
		call overWritedCallAdd

		//���ر�HOOKָ�����һ��ָ��
		jmp jumBackAddress
	}
}


//************************************************************
// ��������: ReSendUser
// ����˵��: �ٴη��ͺ�����Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: user
// �� �� ֵ: void 
//************************************************************
void ReSendUser(UserInfo* user)
{
	HWND hWnd = NULL;
	while (true)
	{
		//���͵����ƶ�
		hWnd = FindWindow(NULL, TEXT("΢������"));
		if (hWnd == NULL)
		{
			continue;
		}
		break;
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//����һ����ֵ, ������������־��
	userinfo.cbData = sizeof(UserInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfo.lpData = user;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
}



//************************************************************
// ��������: SendUserListInfo
// ����˵��: ���ͺ����б�
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void SendUserListInfo()
{
=======
	wchar_t wxid[1024] = { 0 };
};


//HOOK��Ҫ�õ��ĵ�ȫ�ֱ���
DWORD overWritedCallAdd;
DWORD hookAddress;
DWORD jumBackAddress;
BYTE bBackCode[5] = { 0 };
DWORD r_esi = 0;


//************************************************************
// ��������: HookGetFriendList
// ����˵��: HOOK��ȡ�����б��call 
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void HookGetFriendList()
{

	DWORD wxBaseAddress = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
	//��Ҫhook�ĵ�ַ
	hookAddress = wxBaseAddress + FriendList;
	//�����ǵ�CALLĿ��
	overWritedCallAdd = wxBaseAddress + FriendListCall;

	//���صĵ�ַ
	jumBackAddress = hookAddress + 5;

	//��װ��ת����
	BYTE jmpCode[5] = { 0 };
	jmpCode[0] = 0xE9;


	//����ƫ��
	*(DWORD*)& jmpCode[1] = (DWORD)GetUserListInfo - hookAddress - 5;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID)hookAddress, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	//����ԭ�е�ָ��
	memcpy(bBackCode, (void*)hookAddress, 5);

	//д���Լ��Ĵ���
	memcpy((void*)hookAddress, jmpCode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID)hookAddress, 5, OldProtext, &OldProtext);
}


//************************************************************
// ��������: UnHookGetFriendList
// ����˵��: ж��HOOK��ȡ�����б��call 
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void UnHookGetFriendList()
{
	//�õ�ģ���ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	DWORD dwHookAddr = dwWeChatWinAddr + FriendList;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID*)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	// Hook ����������д���Լ��Ĵ���
	memcpy((LPVOID*)dwHookAddr, bBackCode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID*)dwHookAddr, 5, OldProtext, &OldProtext);
}


//************************************************************
// ��������: GetUserListInfo
// ����˵��: ��ȡ�û���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
__declspec(naked) void GetUserListInfo()
{
	//�����ֳ�
	__asm
	{
		//��ȡeax�Ĵ������ݣ�����һ��������
		mov r_esi, esi

		//����Ĵ���
		pushad
		pushf
	}

	//���ý�����Ϣ�ĺ���
	SendUserListInfo();

	//�ָ��ֳ�
	__asm
	{
		popf
		popad

		//���䱻���ǵĴ���
		call overWritedCallAdd

		//���ر�HOOKָ�����һ��ָ��
		jmp jumBackAddress
	}
}


//************************************************************
// ��������: ReSendUser
// ����˵��: �ٴη��ͺ�����Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: user
// �� �� ֵ: void 
//************************************************************
void ReSendUser(UserInfo* user)
{
	HWND hWnd = NULL;
	while (true)
	{
		//���͵����ƶ�
		hWnd = FindWindow(NULL, TEXT("΢������"));
		if (hWnd == NULL)
		{
			continue;
		}
		break;
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//����һ����ֵ, ������������־��
	userinfo.cbData = sizeof(UserInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfo.lpData = user;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
}



//************************************************************
// ��������: SendUserListInfo
// ����˵��: ���ͺ����б�
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void SendUserListInfo()
{
>>>>>>> 06c014d... Add files via upload
	//����΢�źš�Ⱥ��
	wstring wxid1 = GetMsgByAddress(r_esi + 0x10);
	wstring wxName = GetMsgByAddress(r_esi + 0x8C);
	wstring v1 = GetMsgByAddress(r_esi + 0x58);
	//����΢���ǳơ�Ⱥ�ǳ�
	wstring nickName = GetMsgByAddress(r_esi + 0x8C);
	USER_INFO userInfo(wxid1, wxName, v1, nickName);

	for (auto& userInfoOld : userInfoList)
	{
		wstring wxid = get<0>(userInfoOld);
		if (wxid == wxid1)
		{
			return;
		}
	}
<<<<<<< HEAD
	userInfoList.push_front(userInfo);


	UserInfo *user=new UserInfo;
	LPVOID pUserWxid = *((LPVOID *)(r_esi + 0x10));
	LPVOID pUserNumber = *((LPVOID *)(r_esi + 0x44));
	LPVOID pUserNick = *((LPVOID *)(r_esi + 0x8C));
	LPVOID pUserReMark = *((LPVOID *)(r_esi + 0x78));


	swprintf_s(user->UserId, L"%s", (wchar_t*)pUserWxid);
	swprintf_s(user->UserNumber, L"%s", (wchar_t*)pUserNumber);
	swprintf_s(user->UserNickName, L"%s", (wchar_t*)pUserNick);
	swprintf_s(user->UserRemark, L"%s", (wchar_t*)pUserReMark);


	//���͵����ƶ�
	HWND hWnd = FindWindow(NULL, TEXT("΢������"));
	if (hWnd == NULL)
	{
		//�����߳� ������Ϣ ��ֹ©����ϵ��
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReSendUser, user, 0, NULL);
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//����һ����ֵ, ������������־��
	userinfo.cbData = sizeof(UserInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfo.lpData = user;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
}



//************************************************************
// ��������: SendTextMessage
// ����˵��: �����ı���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: wxid ΢��ID msg��Ϣ����
// �� �� ֵ: void 
//************************************************************
void SendTextMessage(wchar_t* wxid, wchar_t* msg)
{
	//�õ�������Ϣ��call�ĵ�ַ
	DWORD dwSendCallAddr = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll")) + WxSendMessage;

	//��װ΢��ID/ȺID�Ľṹ��
	wxMsg id = { 0 };
	id.pMsg = wxid;
	id.msgLen = wcslen(wxid);
	id.buffLen = wcslen(wxid) * 2;

	//��Ϣ����
	wxMsg text = { 0 };
	text.pMsg = msg;
	text.msgLen = wcslen(msg);
	text.buffLen = wcslen(msg) * 2;

	//ȡ��΢��ID����Ϣ�ĵ�ַ
	char* pWxid = (char*)&id.pMsg;
	char* pWxmsg = (char*)&text.pMsg;

	char buff[0x81C] = { 0 };

	//����΢�ŷ�����Ϣcall
	__asm {
		mov edx, pWxid;
		push 0x1;
		push 0;
		mov ebx, pWxmsg;
		push ebx;
		lea ecx, buff;
		call dwSendCallAddr;
		add esp, 0xC;
	}
}


//************************************************************
// ��������: SendFileMessage
// ����˵��: �����ļ���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: wxid ΢��ID filepath �ļ�·��
// �� �� ֵ: void 
//************************************************************
void SendFileMessage(wchar_t* wxid, wchar_t* filepath)
{
	//������Ҫ�ĵ�ַ
	DWORD dwBase = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
	DWORD dwCall1 = dwBase + WxFileMessage1;
	DWORD dwCall2 = dwBase + WxFileMessage2;
	DWORD dwCall3 = dwBase + WxFileMessage3;	//�������
	DWORD dwCall4 = dwBase + WxFileMessage4;	//������Ϣ
	DWORD dwParams = dwBase + WxFileMessageParam;

	char buff[0x45C] = { 0 };

	//������Ҫ������
	Wxid wxidStruct = { 0 };
	wxidStruct.str = wxid;
	wxidStruct.strLen = wcslen(wxid);
	wxidStruct.maxLen = wcslen(wxid) * 2;

	filePath filePathStruct = { 0 };
	filePathStruct.str = filepath;
	filePathStruct.strLen = wcslen(filepath);
	filePathStruct.maxLen = wcslen(filepath) * 2;

	//ȡ����Ҫ�����ݵĵ�ַ
	char* pFilePath = (char*)&filePathStruct.str;
	char* pWxid = (char*)&wxidStruct.str;

	__asm {
		pushad;
		push 0x1;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		push dwParams;
		call dwCall1;
		sub esp, 0x14;
		mov ecx, esp;
		mov ebx, pFilePath;
		push ebx;
		call dwCall2;
		sub esp, 0x14;
		mov ecx, esp;
		push pWxid;
		call dwCall2;
		lea eax, buff;
		push eax;
		call dwCall3;
		mov ecx, eax;
		call dwCall4;
		popad;
	}
}



//************************************************************
// ��������: SendImageMessage
// ����˵��: ����ͼƬ��Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/7
// ��    ��: wxid ΢��ID filepath ͼƬ·��
// �� �� ֵ: void 
//************************************************************
void SendImageMessage(wchar_t* wxid, wchar_t* filepath)
{
	//��װ΢��ID�����ݽṹ
	SendImageStruct imagewxid;
	memcpy(imagewxid.wxid, wxid, wcslen(wxid) + 1);
	imagewxid.length = wcslen(wxid) + 1;
	imagewxid.maxLength = wcslen(wxid)*2;
	imagewxid.pWxid = wxid;

	//��װ�ļ�·�������ݽṹ
	SendImageStruct imagefilepath;
	memcpy(imagefilepath.wxid, filepath, wcslen(filepath) + 1);
	imagefilepath.length = wcslen(filepath) + 1;
	imagefilepath.maxLength = MAX_PATH;
	imagefilepath.pWxid = filepath;

	char buff[0x45C] = { 0 };

	DWORD dwCall1 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxSendImageCall1;
	DWORD dwCall2 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxSendImageCall2;
	DWORD myEsp = 0;


	//΢�ŷ���ͼƬ������GidCreateBimapFileCM ֮��ͼƬһֱ��ռ�� �޷�ɾ�� patch������Ĵ���
	unsigned char oldcode[5] = {0};
	unsigned char fix[5] = { 0x31,0xC0,0x90,0x90,0x90 };
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxPatchAddr;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 5, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//�ȱ���ԭ��ָ��
	memcpy(oldcode, (LPVOID)dwPathcAddr, 5);
	//��Patch��
	memcpy((LPVOID)dwPathcAddr, fix, 5);
	__asm
	{
		//����esp
		mov myEsp, esp;

		lea ebx, imagefilepath;
		push ebx;
		lea eax, imagewxid;
		push eax;
		lea eax, buff;
		push eax;
		push 0;
		call dwCall1;
		add esp, 0x4;
		mov ecx, eax;
		call dwCall2;
		//�ָ���ջ
		mov eax, myEsp;
		mov esp, eax;
	}
	//������֮��ָ�
	memcpy((LPVOID)dwPathcAddr, oldcode, 5);
	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}


//************************************************************
// ��������: WxDeleteUser
// ����˵��: ɾ������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/8
// ��    ��: wxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void DeleteUser(wchar_t* wxid)
{
=======
	userInfoList.push_front(userInfo);


	UserInfo *user=new UserInfo;
	LPVOID pUserWxid = *((LPVOID *)(r_esi + 0x10));
	LPVOID pUserNumber = *((LPVOID *)(r_esi + 0x44));
	LPVOID pUserNick = *((LPVOID *)(r_esi + 0x8C));
	LPVOID pUserReMark = *((LPVOID *)(r_esi + 0x78));


	swprintf_s(user->UserId, L"%s", (wchar_t*)pUserWxid);
	swprintf_s(user->UserNumber, L"%s", (wchar_t*)pUserNumber);
	swprintf_s(user->UserNickName, L"%s", (wchar_t*)pUserNick);
	swprintf_s(user->UserRemark, L"%s", (wchar_t*)pUserReMark);


	//���͵����ƶ�
	HWND hWnd = FindWindow(NULL, TEXT("΢������"));
	if (hWnd == NULL)
	{
		//�����߳� ������Ϣ ��ֹ©����ϵ��
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReSendUser, user, 0, NULL);
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//����һ����ֵ, ������������־��
	userinfo.cbData = sizeof(UserInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfo.lpData = user;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
}



//************************************************************
// ��������: SendTextMessage
// ����˵��: �����ı���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: wxid ΢��ID msg��Ϣ����
// �� �� ֵ: void 
//************************************************************
void SendTextMessage(wchar_t* wxid, wchar_t* msg)
{
	//�õ�������Ϣ��call�ĵ�ַ
	DWORD dwSendCallAddr = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll")) + WxSendMessage;

	//��װ΢��ID/ȺID�Ľṹ��
	wxMsg id = { 0 };
	id.pMsg = wxid;
	id.msgLen = wcslen(wxid);
	id.buffLen = wcslen(wxid) * 2;

	//��Ϣ����
	wxMsg text = { 0 };
	text.pMsg = msg;
	text.msgLen = wcslen(msg);
	text.buffLen = wcslen(msg) * 2;

	//ȡ��΢��ID����Ϣ�ĵ�ַ
	char* pWxid = (char*)&id.pMsg;
	char* pWxmsg = (char*)&text.pMsg;

	char buff[0x81C] = { 0 };

	//����΢�ŷ�����Ϣcall
	__asm {
		mov edx, pWxid;
		push 0x1;
		push 0;
		mov ebx, pWxmsg;
		push ebx;
		lea ecx, buff;
		call dwSendCallAddr;
		add esp, 0xC;
	}
}


//************************************************************
// ��������: SendFileMessage
// ����˵��: �����ļ���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: wxid ΢��ID filepath �ļ�·��
// �� �� ֵ: void 
//************************************************************
void SendFileMessage(wchar_t* wxid, wchar_t* filepath)
{
	//������Ҫ�ĵ�ַ
	DWORD dwBase = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
	DWORD dwCall1 = dwBase + WxFileMessage1;
	DWORD dwCall2 = dwBase + WxFileMessage2;
	DWORD dwCall3 = dwBase + WxFileMessage3;	//�������
	DWORD dwCall4 = dwBase + WxFileMessage4;	//������Ϣ
	DWORD dwParams = dwBase + WxFileMessageParam;

	char buff[0x45C] = { 0 };

	//������Ҫ������
	Wxid wxidStruct = { 0 };
	wxidStruct.str = wxid;
	wxidStruct.strLen = wcslen(wxid);
	wxidStruct.maxLen = wcslen(wxid) * 2;

	filePath filePathStruct = { 0 };
	filePathStruct.str = filepath;
	filePathStruct.strLen = wcslen(filepath);
	filePathStruct.maxLen = wcslen(filepath) * 2;

	//ȡ����Ҫ�����ݵĵ�ַ
	char* pFilePath = (char*)&filePathStruct.str;
	char* pWxid = (char*)&wxidStruct.str;

	__asm {
		pushad;
		push 0x1;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		push dwParams;
		call dwCall1;
		sub esp, 0x14;
		mov ecx, esp;
		mov ebx, pFilePath;
		push ebx;
		call dwCall2;
		sub esp, 0x14;
		mov ecx, esp;
		push pWxid;
		call dwCall2;
		lea eax, buff;
		push eax;
		call dwCall3;
		mov ecx, eax;
		call dwCall4;
		popad;
	}
}



//************************************************************
// ��������: SendImageMessage
// ����˵��: ����ͼƬ��Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/7
// ��    ��: wxid ΢��ID filepath ͼƬ·��
// �� �� ֵ: void 
//************************************************************
void SendImageMessage(wchar_t* wxid, wchar_t* filepath)
{
	//��װ΢��ID�����ݽṹ
	SendImageStruct imagewxid;
	memcpy(imagewxid.wxid, wxid, wcslen(wxid) + 1);
	imagewxid.length = wcslen(wxid) + 1;
	imagewxid.maxLength = wcslen(wxid)*2;
	imagewxid.pWxid = wxid;

	//��װ�ļ�·�������ݽṹ
	SendImageStruct imagefilepath;
	memcpy(imagefilepath.wxid, filepath, wcslen(filepath) + 1);
	imagefilepath.length = wcslen(filepath) + 1;
	imagefilepath.maxLength = MAX_PATH;
	imagefilepath.pWxid = filepath;

	char buff[0x45C] = { 0 };

	DWORD dwCall1 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxSendImageCall1;
	DWORD dwCall2 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxSendImageCall2;
	DWORD myEsp = 0;


	//΢�ŷ���ͼƬ������GidCreateBimapFileCM ֮��ͼƬһֱ��ռ�� �޷�ɾ�� patch������Ĵ���
	unsigned char oldcode[5] = {0};
	unsigned char fix[5] = { 0x31,0xC0,0x90,0x90,0x90 };
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxPatchAddr;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 5, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//�ȱ���ԭ��ָ��
	memcpy(oldcode, (LPVOID)dwPathcAddr, 5);
	//��Patch��
	memcpy((LPVOID)dwPathcAddr, fix, 5);
	__asm
	{
		//����esp
		mov myEsp, esp;

		lea ebx, imagefilepath;
		push ebx;
		lea eax, imagewxid;
		push eax;
		lea eax, buff;
		push eax;
		push 0;
		call dwCall1;
		add esp, 0x4;
		mov ecx, eax;
		call dwCall2;
		//�ָ���ջ
		mov eax, myEsp;
		mov esp, eax;
	}
	//������֮��ָ�
	memcpy((LPVOID)dwPathcAddr, oldcode, 5);
	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}


//************************************************************
// ��������: WxDeleteUser
// ����˵��: ɾ������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/8
// ��    ��: wxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void DeleteUser(wchar_t* wxid)
{
>>>>>>> 06c014d... Add files via upload
	//�ṹ��
	struct StructWxid
	{
		//���͵��ı���Ϣָ��
		wchar_t* pWxid;
		//�ַ�������
		DWORD length;
		//�ַ�����󳤶�
		DWORD maxLength;

		//��������ռλ����
		DWORD fill1;
		DWORD fill2;
<<<<<<< HEAD
	};

	DWORD dwBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	//��������
	StructWxid structWxid = { 0 };
	structWxid.pWxid = wxid;
	structWxid.length = wcslen(wxid);
	structWxid.maxLength = wcslen(wxid) * 2;

	DWORD* asmMsg = (DWORD*)&structWxid.pWxid;
	DWORD dwCallAddr = dwBaseAddress + WxDeleteUser;

	__asm {
		mov ecx, 0;
		push ecx;
		mov edi, asmMsg;
		push edi;
		call  dwCallAddr;
	}
}


//************************************************************
// ��������: SendXmlCard
// ����˵��: ����XML��Ƭ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/10
// ��    ��: RecverWxid ������΢��ID SendWxidҪ���͵�΢��ID NickName΢���ǳ�
// �� �� ֵ: void 
//************************************************************
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName)
{
	struct wxString
	{
		wchar_t * pStr;
		int strLen;
		int strMaxLen;
		char fillbuff[0x8];
	};

	wxString pWxid = { 0 };
	wxString pXml = { 0 };
	wchar_t xml[0x2000] = { 0 };
	pWxid.pStr = RecverWxid;
	pWxid.strLen = wcslen(RecverWxid);
	pWxid.strMaxLen = wcslen(RecverWxid) * 2;

	swprintf_s(xml, L"<?xml version=\"1.0\"?><msg bigheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/0\" smallheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/132\" username=\"%s\" nickname=\"%s\" fullpy=\"?\" shortpy=\"\" alias=\"%s\" imagestatus=\"3\" scene=\"17\" province=\"����\" city=\"�й�\" sign=\"\" sex=\"2\" certflag=\"0\" certinfo=\"\" brandIconUrl=\"\" brandHomeUrl=\"\" brandSubscriptConfigUrl= \"\" brandFlags=\"0\" regionCode=\"CN_BeiJing_BeiJing\" />", SendWxid, NickName, SendWxid);
	pXml.pStr = xml;
	pXml.strLen = wcslen(xml);
	pXml.strMaxLen = wcslen(xml) * 2;

	char* asmWxid = (char *)&pWxid.pStr;
	char* asmXml = (char *)&pXml.pStr;
	char buff[0x20C] = { 0 };
	DWORD callAdd = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxSendXmlCard;


	__asm {
		mov eax, asmXml
		push 0x2A
		mov edx, asmWxid
		push 0x0
		push eax
		lea ecx, buff
		call callAdd
		add esp, 0xC
	}
=======
	};

	DWORD dwBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	//��������
	StructWxid structWxid = { 0 };
	structWxid.pWxid = wxid;
	structWxid.length = wcslen(wxid);
	structWxid.maxLength = wcslen(wxid) * 2;

	DWORD* asmMsg = (DWORD*)&structWxid.pWxid;
	DWORD dwCallAddr = dwBaseAddress + WxDeleteUser;

	__asm {
		mov ecx, 0;
		push ecx;
		mov edi, asmMsg;
		push edi;
		call  dwCallAddr;
	}
}


//************************************************************
// ��������: SendXmlCard
// ����˵��: ����XML��Ƭ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/10
// ��    ��: RecverWxid ������΢��ID SendWxidҪ���͵�΢��ID NickName΢���ǳ�
// �� �� ֵ: void 
//************************************************************
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName)
{
	struct wxString
	{
		wchar_t * pStr;
		int strLen;
		int strMaxLen;
		char fillbuff[0x8];
	};

	wxString pWxid = { 0 };
	wxString pXml = { 0 };
	wchar_t xml[0x2000] = { 0 };
	pWxid.pStr = RecverWxid;
	pWxid.strLen = wcslen(RecverWxid);
	pWxid.strMaxLen = wcslen(RecverWxid) * 2;

	swprintf_s(xml, L"<?xml version=\"1.0\"?><msg bigheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/0\" smallheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/132\" username=\"%s\" nickname=\"%s\" fullpy=\"?\" shortpy=\"\" alias=\"%s\" imagestatus=\"3\" scene=\"17\" province=\"����\" city=\"�й�\" sign=\"\" sex=\"2\" certflag=\"0\" certinfo=\"\" brandIconUrl=\"\" brandHomeUrl=\"\" brandSubscriptConfigUrl= \"\" brandFlags=\"0\" regionCode=\"CN_BeiJing_BeiJing\" />", SendWxid, NickName, SendWxid);
	pXml.pStr = xml;
	pXml.strLen = wcslen(xml);
	pXml.strMaxLen = wcslen(xml) * 2;

	char* asmWxid = (char *)&pWxid.pStr;
	char* asmXml = (char *)&pXml.pStr;
	char buff[0x20C] = { 0 };
	DWORD callAdd = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxSendXmlCard;


	__asm {
		mov eax, asmXml
		push 0x2A
		mov edx, asmWxid
		push 0x0
		push eax
		lea ecx, buff
		call callAdd
		add esp, 0xC
	}
>>>>>>> 06c014d... Add files via upload
}