<<<<<<< HEAD
#include "stdafx.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h >


//������Ϣ�Ľṹ��
struct Information
{
	wchar_t wxid[40];		//΢��ID
	wchar_t wxcount[40];	//΢���˺�
	wchar_t nickname[40];	//΢���ǳ�
	wchar_t wxsex[4];		//�Ա�
	wchar_t phone[30];		//�ֻ���
	wchar_t device[15];		//��½�豸
	wchar_t nation[10];		//����
	wchar_t province[20];	//ʡ��
	wchar_t city[20];		//����
	wchar_t header[0x100];	//ͷ��
};


//************************************************************
// ��������: GetInformation
// ����˵��: ��ȡ������Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/7
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void GetInformation()
{
	
	//�ǳƣ�WeChatWin.dll + 126D91C
	//΢���˺ţ�WeChatWin.dll + 126DA80
	//�ֻ��ţ�WeChatWin.dll + 126d950
	//��½�豸��WeChatWin.dll + 126DD48
	//������WeChatWin.dll + 126DAF8
	//ʡ�ݣ�WeChatWin.dll + 126DA08
	//���У�WeChatWin.dll + 126DA20
	//ͷ��ָ�룺WeChatWin.dll + 126DBE4
	//΢��IDָ�룺WeChatWin.dll + 126D8A4
	//�Ա�WeChatWin.dll+126DA04
	Information *info=new Information;

	//��ȡWeChatWin�Ļ�ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	//΢���Ա�
	char sex[4] = { 0 };
	memcpy(sex, (void*)(dwWeChatWinAddr + 0x126DA04), 1);

	if (sex[0] == 1)
	{
		wcscpy_s(info->wxsex, wcslen(L"��") + 1, L"��");
	}
	if (sex[0] == 2)
	{
		wcscpy_s(info->wxsex, wcslen(L"Ů") + 1, L"Ů");
	}

	//΢���ǳ�
	char nickname[40] = { 0 };
	sprintf_s(nickname, "%s", (char*)(dwWeChatWinAddr + 0x126D91C));
	wcscpy_s(info->nickname, wcslen(UTF8ToUnicode(nickname))+1, UTF8ToUnicode(nickname));
	

	//΢���˺�
	char wxcount[40] = { 0 };
	sprintf_s(wxcount, "%s", (char*)(dwWeChatWinAddr + 0x126DA80));
	wcscpy_s(info->wxcount, wcslen(UTF8ToUnicode(wxcount)) + 1, UTF8ToUnicode(wxcount));

	//�ֻ���
	char phone[40] = { 0 };
	sprintf_s(phone, "%s", (char*)(dwWeChatWinAddr + 0x126d950));
	wcscpy_s(info->phone, wcslen(UTF8ToUnicode(phone)) + 1, UTF8ToUnicode(phone));

	//��½�豸
	char device[15] = { 0 };
	sprintf_s(device, "%s", (char*)(dwWeChatWinAddr + 0x126DD48));
	wcscpy_s(info->device, wcslen(UTF8ToUnicode(device)) + 1, UTF8ToUnicode(device));

	//����
	char nation[10] = { 0 };
	sprintf_s(nation, "%s", (char*)(dwWeChatWinAddr + 0x126DAF8));
	wcscpy_s(info->nation, wcslen(UTF8ToUnicode(nation)) + 1, UTF8ToUnicode(nation));

	//ʡ��
	char province[20] = { 0 };
	sprintf_s(province, "%s", (char*)(dwWeChatWinAddr + 0x126DA08));
	wcscpy_s(info->province, wcslen(UTF8ToUnicode(province)) + 1, UTF8ToUnicode(province));

	//����
	char city[20] = { 0 };
	sprintf_s(city, "%s", (char*)(dwWeChatWinAddr + 0x126DA20));
	wcscpy_s(info->city, wcslen(UTF8ToUnicode(city)) + 1, UTF8ToUnicode(city));

	//΢��ID
	char wxid[40] = { 0 };
	DWORD pWxid = dwWeChatWinAddr + 0x126D8A4;
	sprintf_s(wxid, "%s", (char*)(*(DWORD*)pWxid));
	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode(wxid)) + 1, UTF8ToUnicode(wxid));

	//ͷ��
	char header[0x100] = { 0 };
	DWORD pHeader = dwWeChatWinAddr + 0x126DBE4;
	sprintf_s(header, "%s", (char*)(*(DWORD*)pHeader));
	wcscpy_s(info->header, wcslen(UTF8ToUnicode(header)) + 1, UTF8ToUnicode(header));

	//���͵��ͻ���
	HWND hInformation = FindWindow(NULL, L"Information");
	if (hInformation == NULL)
	{
		MessageBoxA(NULL, "δ���ҵ�Information����", "����", MB_OK);
		return;
	}
	COPYDATASTRUCT information_msg;
	information_msg.dwData = WM_GetInformation;
	information_msg.lpData = info;
	information_msg.cbData = sizeof(Information);
	//������Ϣ�����ƶ�
	SendMessage(hInformation, WM_COPYDATA, (WPARAM)hInformation, (LPARAM)&information_msg);
}



//************************************************************
// ��������: UTF8ToUnicode
// ����˵��: ��UTF8����תΪUnicode(΢��Ĭ�ϱ���ΪUTF8)
// ��    ��: GuiShou
// ʱ    ��: 2019/7/7
// ��    ��: str ��Ҫת�����ַ���
// �� �� ֵ: wchar_t ���ص��ַ��� 
//************************************************************
wchar_t * UTF8ToUnicode(const char* str)
{
	int    textlen = 0;
	wchar_t * result;
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t *)malloc((textlen + 1) * sizeof(wchar_t));
	memset(result, 0, (textlen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);
	return    result;
}



//************************************************************
// ��������: AddWxUser
// ����˵��: ��Ӻ���
// ��    ��: GuiShou
// ʱ    ��: 2019/7/13
// ��    ��: wxid ΢��ID msg��Ӻ���ʱҪ���͵���Ϣ
// �� �� ֵ: void 
//************************************************************
void AddWxUser(wchar_t* wxid, wchar_t* msg)
{
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwParam1 = dwWeChatWinAddr + WxAddWxUserParam1;
	DWORD dwCall1 = dwWeChatWinAddr + WxAddWxUserCall1;
	DWORD dwCall2 = dwWeChatWinAddr + WxAddWxUserCall2;
	DWORD dwCall3 = dwWeChatWinAddr + WxAddWxUserCall3;
	DWORD dwCall4 = dwWeChatWinAddr + WxAddWxUserCall4;
	DWORD dwCall5 = dwWeChatWinAddr + WxAddWxUserCall5;

	struct TextStruct
	{
		wchar_t* pStr;
		int strLen;
		int strMaxLen;

	};

	TextStruct pWxid = { 0 };
	pWxid.pStr = wxid;
	pWxid.strLen = wcslen(wxid) + 1;
	pWxid.strMaxLen = (wcslen(wxid) + 1) * 2;


	TextStruct pMsg = { 0 };
	pMsg.pStr = msg;
	pMsg.strLen = wcslen(msg) + 1;
	pMsg.strMaxLen = (wcslen(msg) + 1) * 2;

	char* asmWxid = (char*)&pWxid.pStr;
	char* asmMsg = (char*)&pMsg.pStr;
	DWORD asmMsgText = (DWORD)pMsg.pStr;
	char buff3[0x100] = { 0 };
	char* buff = buff3;
	__asm
	{
		sub esp, 0x18;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xDC], esp;
		push  dwParam1;
		call dwCall1;
		sub esp, 0x18;
		mov eax, buff;
		mov dword ptr ss : [ebp - 0xE4], esp;
		mov ecx, esp;
		push eax;
		call dwCall2;
		push 0x6;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE8], esp;
		push - 0x1;
		mov edi, asmMsgText;
		push edi;
		call dwCall3;
		mov eax, asmMsg;
		push 0x2;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE0], esp;
		mov ebx, asmWxid;
		push ebx;
		call dwCall4;
		mov ecx, eax;
		call dwCall5;
	}
}


//************************************************************
// ��������: AntiRevoke
// ����˵��: ������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/15
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void AntiRevoke()
{
	unsigned char fix[1] = { 0xEB };
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxAntiRevoke;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 1, PAGE_EXECUTE_READWRITE, &dwOldAttr);

	//Patch
	memcpy((LPVOID)dwPathcAddr, fix, 1);

	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
=======
#include "stdafx.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h >


//������Ϣ�Ľṹ��
struct Information
{
	wchar_t wxid[40];		//΢��ID
	wchar_t wxcount[40];	//΢���˺�
	wchar_t nickname[40];	//΢���ǳ�
	wchar_t wxsex[4];		//�Ա�
	wchar_t phone[30];		//�ֻ���
	wchar_t device[15];		//��½�豸
	wchar_t nation[10];		//����
	wchar_t province[20];	//ʡ��
	wchar_t city[20];		//����
	wchar_t header[0x100];	//ͷ��
};


//************************************************************
// ��������: GetInformation
// ����˵��: ��ȡ������Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/7
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void GetInformation()
{
	
	//�ǳƣ�WeChatWin.dll + 126D91C
	//΢���˺ţ�WeChatWin.dll + 126DA80
	//�ֻ��ţ�WeChatWin.dll + 126d950
	//��½�豸��WeChatWin.dll + 126DD48
	//������WeChatWin.dll + 126DAF8
	//ʡ�ݣ�WeChatWin.dll + 126DA08
	//���У�WeChatWin.dll + 126DA20
	//ͷ��ָ�룺WeChatWin.dll + 126DBE4
	//΢��IDָ�룺WeChatWin.dll + 126D8A4
	//�Ա�WeChatWin.dll+126DA04
	Information *info=new Information;

	//��ȡWeChatWin�Ļ�ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	//΢���Ա�
	char sex[4] = { 0 };
	memcpy(sex, (void*)(dwWeChatWinAddr + 0x126DA04), 1);

	if (sex[0] == 1)
	{
		wcscpy_s(info->wxsex, wcslen(L"��") + 1, L"��");
	}
	if (sex[0] == 2)
	{
		wcscpy_s(info->wxsex, wcslen(L"Ů") + 1, L"Ů");
	}

	//΢���ǳ�
	char nickname[40] = { 0 };
	sprintf_s(nickname, "%s", (char*)(dwWeChatWinAddr + 0x126D91C));
	wcscpy_s(info->nickname, wcslen(UTF8ToUnicode(nickname))+1, UTF8ToUnicode(nickname));
	

	//΢���˺�
	char wxcount[40] = { 0 };
	sprintf_s(wxcount, "%s", (char*)(dwWeChatWinAddr + 0x126DA80));
	wcscpy_s(info->wxcount, wcslen(UTF8ToUnicode(wxcount)) + 1, UTF8ToUnicode(wxcount));

	//�ֻ���
	char phone[40] = { 0 };
	sprintf_s(phone, "%s", (char*)(dwWeChatWinAddr + 0x126d950));
	wcscpy_s(info->phone, wcslen(UTF8ToUnicode(phone)) + 1, UTF8ToUnicode(phone));

	//��½�豸
	char device[15] = { 0 };
	sprintf_s(device, "%s", (char*)(dwWeChatWinAddr + 0x126DD48));
	wcscpy_s(info->device, wcslen(UTF8ToUnicode(device)) + 1, UTF8ToUnicode(device));

	//����
	char nation[10] = { 0 };
	sprintf_s(nation, "%s", (char*)(dwWeChatWinAddr + 0x126DAF8));
	wcscpy_s(info->nation, wcslen(UTF8ToUnicode(nation)) + 1, UTF8ToUnicode(nation));

	//ʡ��
	char province[20] = { 0 };
	sprintf_s(province, "%s", (char*)(dwWeChatWinAddr + 0x126DA08));
	wcscpy_s(info->province, wcslen(UTF8ToUnicode(province)) + 1, UTF8ToUnicode(province));

	//����
	char city[20] = { 0 };
	sprintf_s(city, "%s", (char*)(dwWeChatWinAddr + 0x126DA20));
	wcscpy_s(info->city, wcslen(UTF8ToUnicode(city)) + 1, UTF8ToUnicode(city));

	//΢��ID
	char wxid[40] = { 0 };
	DWORD pWxid = dwWeChatWinAddr + 0x126D8A4;
	sprintf_s(wxid, "%s", (char*)(*(DWORD*)pWxid));
	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode(wxid)) + 1, UTF8ToUnicode(wxid));

	//ͷ��
	char header[0x100] = { 0 };
	DWORD pHeader = dwWeChatWinAddr + 0x126DBE4;
	sprintf_s(header, "%s", (char*)(*(DWORD*)pHeader));
	wcscpy_s(info->header, wcslen(UTF8ToUnicode(header)) + 1, UTF8ToUnicode(header));

	//���͵��ͻ���
	HWND hInformation = FindWindow(NULL, L"Information");
	if (hInformation == NULL)
	{
		MessageBoxA(NULL, "δ���ҵ�Information����", "����", MB_OK);
		return;
	}
	COPYDATASTRUCT information_msg;
	information_msg.dwData = WM_GetInformation;
	information_msg.lpData = info;
	information_msg.cbData = sizeof(Information);
	//������Ϣ�����ƶ�
	SendMessage(hInformation, WM_COPYDATA, (WPARAM)hInformation, (LPARAM)&information_msg);
}



//************************************************************
// ��������: UTF8ToUnicode
// ����˵��: ��UTF8����תΪUnicode(΢��Ĭ�ϱ���ΪUTF8)
// ��    ��: GuiShou
// ʱ    ��: 2019/7/7
// ��    ��: str ��Ҫת�����ַ���
// �� �� ֵ: wchar_t ���ص��ַ��� 
//************************************************************
wchar_t * UTF8ToUnicode(const char* str)
{
	int    textlen = 0;
	wchar_t * result;
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t *)malloc((textlen + 1) * sizeof(wchar_t));
	memset(result, 0, (textlen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);
	return    result;
}


//************************************************************
// ��������: SendDatabaseKey
// ����˵��: �������ݿ���Կ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/13
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void SendDatabaseKey()
{
	char databasekey[0x20] = { 0 };
	//��ȡWeChatWin�Ļ�ַ
	DWORD dwKeyAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll")+ WxDatabaseKey;

	LPVOID* pAddr =(LPVOID*)(*(DWORD*)dwKeyAddr);

	DWORD dwOldAttr = 0;
	VirtualProtect(pAddr, 0x20, PAGE_EXECUTE_READWRITE, &dwOldAttr);

	memcpy(databasekey, pAddr, 0x20);

	VirtualProtect(pAddr, 0x20, dwOldAttr, &dwOldAttr);

	//���͵��ͻ���
	HWND hDatabase = FindWindow(NULL, L"Decrypt_Database");
	if (hDatabase == NULL)
	{
		MessageBoxA(NULL, "δ���ҵ�Decrypt_Database����", "����", MB_OK);
		return;
	}
	COPYDATASTRUCT datakey;
	datakey.dwData = WM_DecryptDatabase;
	datakey.lpData = databasekey;
	datakey.cbData = 0x20;
	//������Ϣ�����ƶ�
	SendMessage(hDatabase, WM_COPYDATA, (WPARAM)hDatabase, (LPARAM)&datakey);
}


//************************************************************
// ��������: AddWxUser
// ����˵��: ��Ӻ���
// ��    ��: GuiShou
// ʱ    ��: 2019/7/13
// ��    ��: wxid ΢��ID msg��Ӻ���ʱҪ���͵���Ϣ
// �� �� ֵ: void 
//************************************************************
void AddWxUser(wchar_t* wxid, wchar_t* msg)
{
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwParam1 = dwWeChatWinAddr + WxAddWxUserParam1;
	DWORD dwCall1 = dwWeChatWinAddr + WxAddWxUserCall1;
	DWORD dwCall2 = dwWeChatWinAddr + WxAddWxUserCall2;
	DWORD dwCall3 = dwWeChatWinAddr + WxAddWxUserCall3;
	DWORD dwCall4 = dwWeChatWinAddr + WxAddWxUserCall4;
	DWORD dwCall5 = dwWeChatWinAddr + WxAddWxUserCall5;

	struct TextStruct
	{
		wchar_t* pStr;
		int strLen;
		int strMaxLen;

	};

	TextStruct pWxid = { 0 };
	pWxid.pStr = wxid;
	pWxid.strLen = wcslen(wxid) + 1;
	pWxid.strMaxLen = (wcslen(wxid) + 1) * 2;


	TextStruct pMsg = { 0 };
	pMsg.pStr = msg;
	pMsg.strLen = wcslen(msg) + 1;
	pMsg.strMaxLen = (wcslen(msg) + 1) * 2;

	char* asmWxid = (char*)&pWxid.pStr;
	char* asmMsg = (char*)&pMsg.pStr;
	DWORD asmMsgText = (DWORD)pMsg.pStr;
	char buff3[0x100] = { 0 };
	char* buff = buff3;
	__asm
	{
		sub esp, 0x18;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xDC], esp;
		push  dwParam1;
		call dwCall1;
		sub esp, 0x18;
		mov eax, buff;
		mov dword ptr ss : [ebp - 0xE4], esp;
		mov ecx, esp;
		push eax;
		call dwCall2;
		push 0x6;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE8], esp;
		push - 0x1;
		mov edi, asmMsgText;
		push edi;
		call dwCall3;
		mov eax, asmMsg;
		push 0x2;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE0], esp;
		mov ebx, asmWxid;
		push ebx;
		call dwCall4;
		mov ecx, eax;
		call dwCall5;
	}
}


//************************************************************
// ��������: AntiRevoke
// ����˵��: ������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/15
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void AntiRevoke()
{
	unsigned char fix[1] = { 0xEB };
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxAntiRevoke;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 1, PAGE_EXECUTE_READWRITE, &dwOldAttr);

	//Patch
	memcpy((LPVOID)dwPathcAddr, fix, 1);

	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
>>>>>>> 06c014d... Add files via upload
}