<<<<<<< HEAD
#include "stdafx.h"
#include "CAutoFunction.h"
#include <atlconv.h>
#include <string>
#include <direct.h> //_mkdir������ͷ�ļ�
#include <io.h>     //_access������ͷ�ļ�
#include <iostream>
#include <cstdio>
#include <ctime>
#include <stdio.h>

using namespace std;

//���ݵ�ԭ����
BYTE bbackcode[5] = { 0 };
BYTE bjmpcode[5] = { 0 };

DWORD pEax = 0;		//eax�Ĵ���
DWORD dwReternAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetExpressionsAddr + 5;	//���ص�ַ
DWORD dwCallAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetExpressionsCallAddr;



//************************************************************
// ��������: AgreeUserRequest
// ����˵��: ͬ���������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/17
// ��    ��: v1 v2
// �� �� ֵ: void
//************************************************************
void AgreeUserRequest(wchar_t* v1, wchar_t* v2)
{
	struct v1Info
	{
		int fill = 0;
		wchar_t* v1 = 0;
		int v1Len;
		int maxV1Len;
		char fill2[0x41C] = { 0 };
		DWORD v2 = { 0 };
	};

	struct v2Info
	{
		char fill[0x24C] = { 0 };
		DWORD fill3 = 0x25;
		char fill4[0x40] = { 0 };
		wchar_t* v2;
		int v2Len;
		int maxV2Len;
		char fill2[0x8] = { 0 };
	};

	DWORD base = (DWORD)LoadLibrary(L"WeChatWin.dll");
	DWORD callAdd1 = base + WxAgreeUserRequestCall1;
	DWORD callAdd2 = base + WxAgreeUserRequestCall2;
	DWORD callAdd3 = base + WxAgreeUserRequestCall3;
	DWORD callAdd4 = base + WxAgreeUserRequestCall4;
	DWORD params = base + 0x126E050;

	DWORD* asmP = (DWORD*)params;

	v1Info userInfoV1 = { 0 };
	v2Info userInfoV2 = { 0 };
	userInfoV1.v2 = (DWORD)&userInfoV2.fill;
	userInfoV1.v1 = v1;
	userInfoV1.v1Len = wcslen(v1);
	userInfoV1.maxV1Len = wcslen(v1) * 2;
	userInfoV2.v2 = v2;
	userInfoV2.v2Len = wcslen(v2);
	userInfoV2.maxV2Len = wcslen(v2) * 2;

	char* asmUser = (char*)&userInfoV1.fill;
	char buff[0x14] = { 0 };
	char buff2[0x48] = { 0 };
	char* asmBuff = buff2;

	__asm
	{
		mov ecx, asmUser;
		push 0x6;
		sub esp, 0x14;
		push esp;
		call callAdd1;
		mov ecx, asmUser;
		lea eax, buff;
		push eax;
		call callAdd2;
		mov esi, eax;
		sub esp, 0x8;
		mov ecx, asmP;
		call callAdd3;
		mov ecx, asmBuff;
		mov edx, ecx;
		push edx;
		push eax;
		push esi;
		call callAdd4;
	}

}


//************************************************************
// ��������: AutoAgreeUserRequest
// ����˵��: �Զ�ͬ���������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/17
// ��    ��: msg ��Ϣ����
// �� �� ֵ: void
//************************************************************
void AutoAgreeUserRequest(wstring msg)
{
	int v1strat = msg.find(L"v1_");
	int v1end = msg.find(L"@stranger");
	wstring v1;
	v1 = msg.substr(v1strat, v1end - v1strat + 9);
	//�ҵ�v2
	int v2strat = msg.find(L"v2_");
	int v2end = msg.rfind(L"@stranger");
	wstring v2;
	v2 = msg.substr(v2strat, v2end - v2strat + 9);
	//����ͬ����������call
	AgreeUserRequest((wchar_t*)v1.c_str(), (wchar_t*)v2.c_str());
}


//************************************************************
// ��������: CllectMoney
// ����˵��: �տ�
// ��    ��: GuiShou
// ʱ    ��: 2019/7/15
// ��    ��: transferid ת��ID wxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void CllectMoney(wchar_t* transferid, wchar_t* wxid)
{
	struct CllectMoneyStruct
	{
		wchar_t* ptransferid;
		int transferidLen;
		int transferidMaxLen;
		char full[0x8] = { 0 };
		wchar_t* pwxid;
		int wxidLen;
		int wxidMaxLen;
		char full2[0x8] = { 0 };
	};

	CllectMoneyStruct cllect;
	cllect.ptransferid = transferid;
	cllect.transferidLen = wcslen(transferid) + 1;
	cllect.transferidMaxLen = (wcslen(transferid) + 1) * 2;
	cllect.pwxid = wxid;
	cllect.wxidLen = wcslen(wxid) + 1;
	cllect.wxidMaxLen = (wcslen(wxid) + 1) * 2;

	char* asmBuff = (char*)&cllect.ptransferid;

	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCall1 = dwWeChatWinAddr + WxCllectMoneyCall1;
	DWORD dwCall2 = dwWeChatWinAddr + WxCllectMoneyCall2;


	__asm
	{
		sub esp, 0x30;
		mov ecx, esp;
		mov eax, asmBuff;
		push eax;
		call dwCall1;
		call dwCall2;
		add esp, 0x30;
	}
}


//************************************************************
// ��������: AutoCllectMoney
// ����˵��: �Զ��տ�
// ��    ��: GuiShou
// ʱ    ��: 2019/7/17
// ��    ��: msg ��Ϣ����
// �� �� ֵ: void
//************************************************************
void AutoCllectMoney(wstring msg,wchar_t* wxid)
{
	// �ҵ�<transferid>�ַ�����λ��
	int pos1 = msg.find(L"<transferid>");
	//�ҵ�]]></transferid>�ַ�����λ��
	int pos2 = msg.find(L"]]></transferid>");
	//ȡ��������ַ�������
	wstring noneed = L"<transferid><![CDATA[";
	int noneedLen = noneed.length();
	//ȡ��ת��ID
	wstring transferid;
	transferid = msg.substr(pos1 + noneedLen, (pos2 - pos1) - noneedLen);

	//�����տ�call ʵ���Զ��տ�
	CllectMoney((wchar_t*)transferid.c_str(), wxid);
}


//************************************************************
// ��������: AddCardUser
// ����˵��: �����Ƭ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/18
// ��    ��: v1 msg ��Ϣ����
// �� �� ֵ: void
//************************************************************
void AddCardUser(wchar_t* v1, wchar_t* msg)
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

	TextStruct pV1 = { 0 };
	pV1.pStr = v1;
	pV1.strLen = wcslen(v1) + 1;
	pV1.strMaxLen = (wcslen(v1) + 1) * 2;


	char* asmV1 = (char*)&pV1.pStr;
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
		push 0x11;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE8], esp;
		push - 0x1;
		mov edi, msg;
		push edi;
		call dwCall3;
		push 0x2;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE0], esp;
		mov ebx, asmV1;
		push ebx;
		call dwCall4;
		mov ecx, eax;
		call dwCall5;
	}
}



//************************************************************
// ��������: AutoAddCardUser
// ����˵��: �Զ������Ƭ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/18
// ��    ��: msg ��Ϣ����
// �� �� ֵ: void
//************************************************************
void AutoAddCardUser(wstring msg)
{
	//�õ�V1
	int v1strat = msg.find(L"v1_");
	int v1end = msg.find(L"@stranger");
	wstring v1;
	v1 = msg.substr(v1strat, v1end - v1strat + 9);

	//���������Ƭ���Ѻ���
	AddCardUser((wchar_t*)v1.c_str(), (wchar_t*)L"��ͨ��~��ͨ��~ ���");
}


//************************************************************
// ��������: HookExtractExpression
// ����˵��: HOOK��ȡ����Call
// ��    ��: GuiShou
// ʱ    ��: 2019/7/21
// ��    ��: dwHookOffset ƫ��
// �� �� ֵ: void
//************************************************************
void HookExtractExpression(DWORD dwHookOffset)
{
	//�õ�ģ���ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	//������ҪHOOK�ĵ�ַ
	DWORD dwHookAddr = dwWeChatWinAddr + dwHookOffset;

	//�������
	bjmpcode[0] = 0xE9;
	//����ƫ��
	*(DWORD*)(&bjmpcode[1]) = (DWORD)ExtractExpression - dwHookAddr - 5;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	//����ԭ�е�ָ��
	memcpy(bbackcode, (void*)dwHookAddr, 5);

	//д���Լ��Ĵ���
	memcpy((void*)dwHookAddr, bjmpcode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
}



//************************************************************
// ��������: ExtractExpression
// ����˵��: ��ȡ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/21
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void  __declspec(naked) ExtractExpression()
{
	//���ݼĴ���
	__asm pushad;
	__asm pushfd;
	//ȡ��ecx������
	__asm mov pEax, eax;
	OutputExpression(pEax);
	//�ָ��Ĵ���
	__asm popfd;
	__asm popad;

	__asm call dwCallAddr;	//����ԭ����call  ������ܳ���
	//��ת�����ص�ַ
	__asm jmp dwReternAddress;
}


//************************************************************
// ��������: OutputExpression
// ����˵��: �������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/21
// ��    ��: dwExpressionAddr ��ַ
// �� �� ֵ: void
//************************************************************
void OutputExpression(DWORD dwExpressionAddr)
{
	//ȡ��ͼƬ����
	DWORD dwImageLen = *((DWORD*)(dwExpressionAddr + 4));
	//ȡ��ͼƬ����
	DWORD dwImage = *((DWORD*)(dwExpressionAddr));
	unsigned char magic_head[4] = { 0 };
	char postfix[5] = { 0 };
	memcpy(magic_head, (void*)dwImage, 3);
	//����MAGICͷ�жϺ�׺
	if (magic_head[0] == 137 && magic_head[1] == 80 && magic_head[2] == 78)
	{
		strcpy_s(postfix, 5, ".png");
	}
	else if (magic_head[0] == 71 && magic_head[1] == 73 && magic_head[2] == 70)
	{
		strcpy_s(postfix, 5, ".gif");
	}
	else if (magic_head[0] == 255 && magic_head[1] == 216 && magic_head[2] == 255)
	{
		strcpy_s(postfix, 5, ".jpg");
	}

	//��ȡ��ʱ�ļ���Ŀ¼
	char temppath[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, temppath);
	char imagedir[20] = { "WeChatExpressions" };

	//ƴ�Ӵ��΢�ű����Ŀ¼
	char WeChatExpressionsPath[MAX_PATH] = { 0 };
	sprintf_s(WeChatExpressionsPath, "%s%s\\", temppath, imagedir);
	//����Ŀ¼���ͼƬ
	CreateDir(WeChatExpressionsPath);


	//��ȡ��ǰʱ����Ϊ�ļ���
	time_t rawtime;
	struct tm *ptminfo = new struct tm;
	time(&rawtime);
	localtime_s(ptminfo, &rawtime);
	char currenttime[30] = { 0 };
	sprintf_s(currenttime, "%02d%02d%02d%02d%02d%02d", ptminfo->tm_year + 1900,
		ptminfo->tm_mon + 1, ptminfo->tm_mday, ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);


	//ƴ��������ͼƬ·��
	char imagepath[MAX_PATH] = { 0 };
	sprintf_s(imagepath, "%s%s%s", WeChatExpressionsPath, currenttime, postfix);

	//�����ļ�
	HANDLE hFile = CreateFileA(imagepath, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "�����ļ�ʧ��", "����", 0);
		return;
	}
	//д���ļ�
	DWORD dwWrite = 0;
	WriteFile(hFile, (LPCVOID)dwImage, dwImageLen, &dwWrite, 0);
	//�رվ��
	CloseHandle(hFile);
}


//************************************************************
// ��������: CreateDir
// ����˵��: ����Ŀ¼
// ��    ��: GuiShou
// ʱ    ��: 2019/7/21
// ��    ��: dir Ŀ¼
// �� �� ֵ: void
//************************************************************
void CreateDir(const char *dir)
{
	int m = 0, n;
	string str1, str2;

	str1 = dir;
	str2 = str1.substr(0, 2);
	str1 = str1.substr(3, str1.size());

	while (m >= 0)
	{
		m = str1.find('\\');

		str2 += '\\' + str1.substr(0, m);
		n = _access(str2.c_str(), 0); //�жϸ�Ŀ¼�Ƿ����
		if (n == -1)
		{
			_mkdir(str2.c_str());     //����Ŀ¼
		}

		str1 = str1.substr(m + 1, str1.size());
	}
}
=======
#include "stdafx.h"
#include "CAutoFunction.h"
#include <atlconv.h>
#include <string>
#include <direct.h> //_mkdir������ͷ�ļ�
#include <io.h>     //_access������ͷ�ļ�
#include <iostream>
#include <cstdio>
#include <ctime>
#include <stdio.h>

using namespace std;

//���ݵ�ԭ����
BYTE bbackcode[5] = { 0 };
BYTE bjmpcode[5] = { 0 };

DWORD pEax = 0;		//eax�Ĵ���
DWORD dwReternAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetExpressionsAddr + 5;	//���ص�ַ
DWORD dwCallAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetExpressionsCallAddr;



//************************************************************
// ��������: AgreeUserRequest
// ����˵��: ͬ���������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/17
// ��    ��: v1 v2
// �� �� ֵ: void
//************************************************************
void AgreeUserRequest(wchar_t* v1, wchar_t* v2)
{
	struct v1Info
	{
		int fill = 0;
		wchar_t* v1 = 0;
		int v1Len;
		int maxV1Len;
		char fill2[0x41C] = { 0 };
		DWORD v2 = { 0 };
	};

	struct v2Info
	{
		char fill[0x24C] = { 0 };
		DWORD fill3 = 0x25;
		char fill4[0x40] = { 0 };
		wchar_t* v2;
		int v2Len;
		int maxV2Len;
		char fill2[0x8] = { 0 };
	};

	DWORD base = (DWORD)LoadLibrary(L"WeChatWin.dll");
	DWORD callAdd1 = base + WxAgreeUserRequestCall1;
	DWORD callAdd2 = base + WxAgreeUserRequestCall2;
	DWORD callAdd3 = base + WxAgreeUserRequestCall3;
	DWORD callAdd4 = base + WxAgreeUserRequestCall4;
	DWORD params = base + 0x126E050;

	DWORD* asmP = (DWORD*)params;

	v1Info userInfoV1 = { 0 };
	v2Info userInfoV2 = { 0 };
	userInfoV1.v2 = (DWORD)&userInfoV2.fill;
	userInfoV1.v1 = v1;
	userInfoV1.v1Len = wcslen(v1);
	userInfoV1.maxV1Len = wcslen(v1) * 2;
	userInfoV2.v2 = v2;
	userInfoV2.v2Len = wcslen(v2);
	userInfoV2.maxV2Len = wcslen(v2) * 2;

	char* asmUser = (char*)&userInfoV1.fill;
	char buff[0x14] = { 0 };
	char buff2[0x48] = { 0 };
	char* asmBuff = buff2;

	__asm
	{
		mov ecx, asmUser;
		push 0x6;
		sub esp, 0x14;
		push esp;
		call callAdd1;
		mov ecx, asmUser;
		lea eax, buff;
		push eax;
		call callAdd2;
		mov esi, eax;
		sub esp, 0x8;
		mov ecx, asmP;
		call callAdd3;
		mov ecx, asmBuff;
		mov edx, ecx;
		push edx;
		push eax;
		push esi;
		call callAdd4;
	}

}


//************************************************************
// ��������: AutoAgreeUserRequest
// ����˵��: �Զ�ͬ���������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/17
// ��    ��: msg ��Ϣ����
// �� �� ֵ: void
//************************************************************
void AutoAgreeUserRequest(wstring msg)
{
	int v1strat = msg.find(L"v1_");
	int v1end = msg.find(L"@stranger");
	wstring v1;
	v1 = msg.substr(v1strat, v1end - v1strat + 9);
	//�ҵ�v2
	int v2strat = msg.find(L"v2_");
	int v2end = msg.rfind(L"@stranger");
	wstring v2;
	v2 = msg.substr(v2strat, v2end - v2strat + 9);
	//����ͬ����������call
	AgreeUserRequest((wchar_t*)v1.c_str(), (wchar_t*)v2.c_str());
}


//************************************************************
// ��������: CllectMoney
// ����˵��: �տ�
// ��    ��: GuiShou
// ʱ    ��: 2019/7/15
// ��    ��: transferid ת��ID wxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void CllectMoney(wchar_t* transferid, wchar_t* wxid)
{
	struct CllectMoneyStruct
	{
		wchar_t* ptransferid;
		int transferidLen;
		int transferidMaxLen;
		char full[0x8] = { 0 };
		wchar_t* pwxid;
		int wxidLen;
		int wxidMaxLen;
		char full2[0x8] = { 0 };
	};

	CllectMoneyStruct cllect;
	cllect.ptransferid = transferid;
	cllect.transferidLen = wcslen(transferid) + 1;
	cllect.transferidMaxLen = (wcslen(transferid) + 1) * 2;
	cllect.pwxid = wxid;
	cllect.wxidLen = wcslen(wxid) + 1;
	cllect.wxidMaxLen = (wcslen(wxid) + 1) * 2;

	char* asmBuff = (char*)&cllect.ptransferid;

	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCall1 = dwWeChatWinAddr + WxCllectMoneyCall1;
	DWORD dwCall2 = dwWeChatWinAddr + WxCllectMoneyCall2;


	__asm
	{
		sub esp, 0x30;
		mov ecx, esp;
		mov eax, asmBuff;
		push eax;
		call dwCall1;
		call dwCall2;
		add esp, 0x30;
	}
}


//************************************************************
// ��������: AutoCllectMoney
// ����˵��: �Զ��տ�
// ��    ��: GuiShou
// ʱ    ��: 2019/7/17
// ��    ��: msg ��Ϣ����
// �� �� ֵ: void
//************************************************************
void AutoCllectMoney(wstring msg,wchar_t* wxid)
{
	// �ҵ�<transferid>�ַ�����λ��
	int pos1 = msg.find(L"<transferid>");
	//�ҵ�]]></transferid>�ַ�����λ��
	int pos2 = msg.find(L"]]></transferid>");
	//ȡ��������ַ�������
	wstring noneed = L"<transferid><![CDATA[";
	int noneedLen = noneed.length();
	//ȡ��ת��ID
	wstring transferid;
	transferid = msg.substr(pos1 + noneedLen, (pos2 - pos1) - noneedLen);

	//�����տ�call ʵ���Զ��տ�
	CllectMoney((wchar_t*)transferid.c_str(), wxid);
}


//************************************************************
// ��������: AddCardUser
// ����˵��: �����Ƭ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/18
// ��    ��: v1 msg ��Ϣ����
// �� �� ֵ: void
//************************************************************
void AddCardUser(wchar_t* v1, wchar_t* msg)
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

	TextStruct pV1 = { 0 };
	pV1.pStr = v1;
	pV1.strLen = wcslen(v1) + 1;
	pV1.strMaxLen = (wcslen(v1) + 1) * 2;


	char* asmV1 = (char*)&pV1.pStr;
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
		push 0x11;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE8], esp;
		push - 0x1;
		mov edi, msg;
		push edi;
		call dwCall3;
		push 0x2;
		sub esp, 0x14;
		mov ecx, esp;
		mov dword ptr ss : [ebp - 0xE0], esp;
		mov ebx, asmV1;
		push ebx;
		call dwCall4;
		mov ecx, eax;
		call dwCall5;
	}
}



//************************************************************
// ��������: AutoAddCardUser
// ����˵��: �Զ������Ƭ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/18
// ��    ��: msg ��Ϣ����
// �� �� ֵ: void
//************************************************************
void AutoAddCardUser(wstring msg)
{
	//�õ�V1
	int v1strat = msg.find(L"v1_");
	int v1end = msg.find(L"@stranger");
	wstring v1;
	v1 = msg.substr(v1strat, v1end - v1strat + 9);

	//���������Ƭ���Ѻ���
	AddCardUser((wchar_t*)v1.c_str(), (wchar_t*)L"��ͨ��~��ͨ��~ ���");
}


//************************************************************
// ��������: HookExtractExpression
// ����˵��: HOOK��ȡ����Call
// ��    ��: GuiShou
// ʱ    ��: 2019/7/21
// ��    ��: dwHookOffset ƫ��
// �� �� ֵ: void
//************************************************************
void HookExtractExpression(DWORD dwHookOffset)
{
	//�õ�ģ���ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	//������ҪHOOK�ĵ�ַ
	DWORD dwHookAddr = dwWeChatWinAddr + dwHookOffset;

	//�������
	bjmpcode[0] = 0xE9;
	//����ƫ��
	*(DWORD*)(&bjmpcode[1]) = (DWORD)ExtractExpression - dwHookAddr - 5;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	//����ԭ�е�ָ��
	memcpy(bbackcode, (void*)dwHookAddr, 5);

	//д���Լ��Ĵ���
	memcpy((void*)dwHookAddr, bjmpcode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
}



//************************************************************
// ��������: ExtractExpression
// ����˵��: ��ȡ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/21
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void  __declspec(naked) ExtractExpression()
{
	//���ݼĴ���
	__asm pushad;
	__asm pushfd;
	//ȡ��ecx������
	__asm mov pEax, eax;
	OutputExpression(pEax);
	//�ָ��Ĵ���
	__asm popfd;
	__asm popad;

	__asm call dwCallAddr;	//����ԭ����call  ������ܳ���
	//��ת�����ص�ַ
	__asm jmp dwReternAddress;
}


//************************************************************
// ��������: OutputExpression
// ����˵��: �������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/21
// ��    ��: dwExpressionAddr ��ַ
// �� �� ֵ: void
//************************************************************
void OutputExpression(DWORD dwExpressionAddr)
{
	//ȡ��ͼƬ����
	DWORD dwImageLen = *((DWORD*)(dwExpressionAddr + 4));
	//ȡ��ͼƬ����
	DWORD dwImage = *((DWORD*)(dwExpressionAddr));
	unsigned char magic_head[4] = { 0 };
	char postfix[5] = { 0 };
	memcpy(magic_head, (void*)dwImage, 3);
	//����MAGICͷ�жϺ�׺
	if (magic_head[0] == 137 && magic_head[1] == 80 && magic_head[2] == 78)
	{
		strcpy_s(postfix, 5, ".png");
	}
	else if (magic_head[0] == 71 && magic_head[1] == 73 && magic_head[2] == 70)
	{
		strcpy_s(postfix, 5, ".gif");
	}
	else if (magic_head[0] == 255 && magic_head[1] == 216 && magic_head[2] == 255)
	{
		strcpy_s(postfix, 5, ".jpg");
	}

	//��ȡ��ʱ�ļ���Ŀ¼
	char temppath[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, temppath);
	char imagedir[20] = { "WeChatExpressions" };

	//ƴ�Ӵ��΢�ű����Ŀ¼
	char WeChatExpressionsPath[MAX_PATH] = { 0 };
	sprintf_s(WeChatExpressionsPath, "%s%s\\", temppath, imagedir);
	//����Ŀ¼���ͼƬ
	CreateDir(WeChatExpressionsPath);


	//��ȡ��ǰʱ����Ϊ�ļ���
	time_t rawtime;
	struct tm *ptminfo = new struct tm;
	time(&rawtime);
	localtime_s(ptminfo, &rawtime);
	char currenttime[30] = { 0 };
	sprintf_s(currenttime, "%02d%02d%02d%02d%02d%02d", ptminfo->tm_year + 1900,
		ptminfo->tm_mon + 1, ptminfo->tm_mday, ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);


	//ƴ��������ͼƬ·��
	char imagepath[MAX_PATH] = { 0 };
	sprintf_s(imagepath, "%s%s%s", WeChatExpressionsPath, currenttime, postfix);

	//�����ļ�
	HANDLE hFile = CreateFileA(imagepath, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "�����ļ�ʧ��", "����", 0);
		return;
	}
	//д���ļ�
	DWORD dwWrite = 0;
	WriteFile(hFile, (LPCVOID)dwImage, dwImageLen, &dwWrite, 0);
	//�رվ��
	CloseHandle(hFile);
}


//************************************************************
// ��������: CreateDir
// ����˵��: ����Ŀ¼
// ��    ��: GuiShou
// ʱ    ��: 2019/7/21
// ��    ��: dir Ŀ¼
// �� �� ֵ: void
//************************************************************
void CreateDir(const char *dir)
{
	int m = 0, n;
	string str1, str2;

	str1 = dir;
	str2 = str1.substr(0, 2);
	str1 = str1.substr(3, str1.size());

	while (m >= 0)
	{
		m = str1.find('\\');

		str2 += '\\' + str1.substr(0, m);
		n = _access(str2.c_str(), 0); //�жϸ�Ŀ¼�Ƿ����
		if (n == -1)
		{
			_mkdir(str2.c_str());     //����Ŀ¼
		}

		str1 = str1.substr(m + 1, str1.size());
	}
}
>>>>>>> 06c014d... Add files via upload
