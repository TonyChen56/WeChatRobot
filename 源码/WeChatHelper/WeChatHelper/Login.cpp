<<<<<<< HEAD
#include "stdafx.h"
#include "Login.h"
#include <stdio.h>


//���ݵ�ԭ����
BYTE backCode[5] = { 0 };
BYTE jmpCode[5] = { 0 };

DWORD pEcx = 0;		//ecx�Ĵ���
DWORD dwRetAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + QrCodeOffset + 5;	//���ص�ַ


//************************************************************
// ��������: HookQrCode
// ����˵��: HOOK΢�Ŷ�ά��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: DWORD dwHookOffset Ҫhook��ƫ�� 
// �� �� ֵ: void
//************************************************************
void HookQrCode(DWORD dwHookOffset)
{
	//�õ�ģ���ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	//������ҪHOOK�ĵ�ַ
	DWORD dwHookAddr = dwWeChatWinAddr + dwHookOffset;

	//�������
	jmpCode[0] = 0xE9;
	//����ƫ��
	*(DWORD*)(&jmpCode[1]) = (DWORD)ShowPic - dwHookAddr - 5;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	//����ԭ�е�ָ��
	memcpy(backCode, (void*)dwHookAddr, 5);

	//д���Լ��Ĵ���
	memcpy((void*)dwHookAddr, jmpCode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
}


//************************************************************
// ��������: ShowPic
// ����˵��: ��ʾ��ά��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/16
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void  __declspec(naked) ShowPic()
{
	//���ݼĴ���
	__asm pushad;
	__asm pushfd;
	//ȡ��ecx������
	__asm mov pEcx, ecx;
	SaveImg(pEcx);
	//�ָ��Ĵ���
	__asm popfd;
	__asm popad;

	//��ת�����ص�ַ
	__asm jmp dwRetAddr;
}


//************************************************************
// ��������: SaveImg
// ����˵��: �����ά��ͼƬ
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: DWORD qrcode ��ά��ͼƬ���ڵĵ�ַ
// �� �� ֵ: void
//************************************************************
void SaveImg(DWORD qrcode)
{
	//��ȡͼƬ����
	DWORD dwPicLen = qrcode + 0x4;
	size_t cpyLen = (size_t)*((LPVOID*)dwPicLen);
	//����ͼƬ������
	char PicData[0xFFF] = { 0 };
	memcpy(PicData, *((LPVOID*)qrcode), cpyLen);

	char szTempPath[MAX_PATH] = { 0 };
	char szPicturePath[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, szTempPath);

	sprintf_s(szPicturePath, "%s%s", szTempPath, "qrcode.png");
	//���ļ�д��TempĿ¼��
	HANDLE hFile = CreateFileA(szPicturePath, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL)
	{
		MessageBoxA(NULL, "����ͼƬ�ļ�ʧ��", "����", 0);
		return;
	}

	DWORD dwRead = 0;
	if (WriteFile(hFile, PicData, cpyLen, &dwRead, NULL) == 0)
	{
		MessageBoxA(NULL, "д��ͼƬ�ļ�ʧ��", "����", 0);
		return;
	}
	CloseHandle(hFile);
	
	//���֮��ж��HOOK
	UnHookQrCode(QrCodeOffset);

}



//************************************************************
// ��������: UnHook
// ����˵��: ж��HOOK
// ��    ��: GuiShou
// ʱ    ��: 2019/6/16
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void UnHookQrCode(DWORD dwHookOffset)
{
	//�õ�ģ���ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	DWORD dwHookAddr = dwWeChatWinAddr + dwHookOffset;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID*)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	// Hook ����������д���Լ��Ĵ���
	memcpy((LPVOID*)dwHookAddr, backCode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID*)dwHookAddr, 5, OldProtext, &OldProtext);
}


//************************************************************
// ��������: GotoQrCode
// ����˵��: ��ת����ά�봰��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/16
// ��    ��: void
// �� �� ֵ: void
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

=======
#include "stdafx.h"
#include "Login.h"
#include <stdio.h>


//���ݵ�ԭ����
BYTE backCode[5] = { 0 };
BYTE jmpCode[5] = { 0 };

DWORD pEcx = 0;		//ecx�Ĵ���
DWORD dwRetAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + QrCodeOffset + 5;	//���ص�ַ


//************************************************************
// ��������: HookQrCode
// ����˵��: HOOK΢�Ŷ�ά��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: DWORD dwHookOffset Ҫhook��ƫ�� 
// �� �� ֵ: void
//************************************************************
void HookQrCode(DWORD dwHookOffset)
{
	//�õ�ģ���ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	//������ҪHOOK�ĵ�ַ
	DWORD dwHookAddr = dwWeChatWinAddr + dwHookOffset;

	//�������
	jmpCode[0] = 0xE9;
	//����ƫ��
	*(DWORD*)(&jmpCode[1]) = (DWORD)ShowPic - dwHookAddr - 5;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	//����ԭ�е�ָ��
	memcpy(backCode, (void*)dwHookAddr, 5);

	//д���Լ��Ĵ���
	memcpy((void*)dwHookAddr, jmpCode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
}


//************************************************************
// ��������: ShowPic
// ����˵��: ��ʾ��ά��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/16
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void  __declspec(naked) ShowPic()
{
	//���ݼĴ���
	__asm pushad;
	__asm pushfd;
	//ȡ��ecx������
	__asm mov pEcx, ecx;
	SaveImg(pEcx);
	//�ָ��Ĵ���
	__asm popfd;
	__asm popad;

	//��ת�����ص�ַ
	__asm jmp dwRetAddr;
}


//************************************************************
// ��������: SaveImg
// ����˵��: �����ά��ͼƬ
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: DWORD qrcode ��ά��ͼƬ���ڵĵ�ַ
// �� �� ֵ: void
//************************************************************
void SaveImg(DWORD qrcode)
{
	//��ȡͼƬ����
	DWORD dwPicLen = qrcode + 0x4;
	size_t cpyLen = (size_t)*((LPVOID*)dwPicLen);
	//����ͼƬ������
	char PicData[0xFFF] = { 0 };
	memcpy(PicData, *((LPVOID*)qrcode), cpyLen);

	char szTempPath[MAX_PATH] = { 0 };
	char szPicturePath[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, szTempPath);

	sprintf_s(szPicturePath, "%s%s", szTempPath, "qrcode.png");
	//���ļ�д��TempĿ¼��
	HANDLE hFile = CreateFileA(szPicturePath, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL)
	{
		MessageBoxA(NULL, "����ͼƬ�ļ�ʧ��", "����", 0);
		return;
	}

	DWORD dwRead = 0;
	if (WriteFile(hFile, PicData, cpyLen, &dwRead, NULL) == 0)
	{
		MessageBoxA(NULL, "д��ͼƬ�ļ�ʧ��", "����", 0);
		return;
	}
	CloseHandle(hFile);
	
	//���֮��ж��HOOK
	UnHookQrCode(QrCodeOffset);

}



//************************************************************
// ��������: UnHook
// ����˵��: ж��HOOK
// ��    ��: GuiShou
// ʱ    ��: 2019/6/16
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void UnHookQrCode(DWORD dwHookOffset)
{
	//�õ�ģ���ַ
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	DWORD dwHookAddr = dwWeChatWinAddr + dwHookOffset;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID*)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	// Hook ����������д���Լ��Ĵ���
	memcpy((LPVOID*)dwHookAddr, backCode, 5);

	// ִ�����˲���֮����Ҫ���л�ԭ
	VirtualProtect((LPVOID*)dwHookAddr, 5, OldProtext, &OldProtext);
}


//************************************************************
// ��������: GotoQrCode
// ����˵��: ��ת����ά�봰��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/16
// ��    ��: void
// �� �� ֵ: void
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

>>>>>>> 06c014d... Add files via upload
