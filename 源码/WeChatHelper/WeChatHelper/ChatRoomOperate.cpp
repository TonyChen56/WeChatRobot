<<<<<<< HEAD
#include "stdafx.h"
#include "ChatRoomOperate.h"
#include <stdio.h>
#include <string>
using namespace std;


//************************************************************
// ��������: SetWxRoomAnnouncement
// ����˵��: ����Ⱥ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: chartoomwxid ȺID Announcement Ⱥ����
// �� �� ֵ: void 
//************************************************************
void SetWxRoomAnnouncement(wchar_t* chatroomwxid, wchar_t* Announcement)
{
	//��ȡWeChatWin�Ļ�ַ
	DWORD callAdrress = (DWORD)GetModuleHandle(L"WeChatWin.dll")+ WxSetRoomAnnouncement;
=======
#include "stdafx.h"
#include "ChatRoomOperate.h"
#include <stdio.h>


//************************************************************
// ��������: SetWxRoomAnnouncement
// ����˵��: ����Ⱥ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: chartoomwxid ȺID Announcement Ⱥ����
// �� �� ֵ: void 
//************************************************************
void SetWxRoomAnnouncement(wchar_t* chatroomwxid, wchar_t* Announcement)
{
	//��ȡWeChatWin�Ļ�ַ
	DWORD callAdrress = (DWORD)GetModuleHandle(L"WeChatWin.dll")+ WxSetRoomAnnouncement;
>>>>>>> 06c014d... Add files via upload
	//��װ����
	CHAR bufferA[0xD0] = { 0 };
	DWORD* bufA = (DWORD*)& bufferA;

	CHAR buffer[0xD0] = { 0 };
	DWORD* buf = (DWORD*)& buffer;

	buf[0] = (DWORD)chatroomwxid;
	buf[1] = wcslen(chatroomwxid);
	buf[2] = wcslen(chatroomwxid) * 2;
	buf[3] = 0;
	buf[4] = 0;

	buf[0 + 5] = (DWORD)Announcement;
	buf[1 + 5] = wcslen(Announcement);
	buf[2 + 5] = wcslen(Announcement) * 2;
	buf[3 + 5] = 0;
	buf[4 + 5] = 0;

	bufA[0] = (DWORD)& buffer;
	bufA[1] = bufA[0] + 0x60;
	bufA[2] = bufA[0] + 0x60;

	DWORD r_esp = 0;
	__asm
	{
		//�����ջ�Ĵ���
		mov r_esp, esp

		//654B85B1 | .  8D85 30FFFFFF lea eax, [local.52]
		//654B85B7 | .  50            push eax
		//654B85B8 | .E8 43FF2000   call WeChatWi.656C8500;  ����Ⱥ����
		lea eax, bufferA
		push eax
		call callAdrress

		//�ָ���ջ�Ĵ���
		mov eax, r_esp
		mov esp, eax
<<<<<<< HEAD
	}
}



//************************************************************
// ��������: QuitChatRoom
// ����˵��: �˳�Ⱥ��
// ��    ��: GuiShou
// ʱ    ��: 2019/7/9
// ��    ��: chartoomwxid ȺID 
// �� �� ֵ: void 
//************************************************************
void QuitChatRoom(wchar_t* chatroomwxid)
{
=======
	}
}



//************************************************************
// ��������: QuitChatRoom
// ����˵��: �˳�Ⱥ��
// ��    ��: GuiShou
// ʱ    ��: 2019/7/9
// ��    ��: chartoomwxid ȺID 
// �� �� ֵ: void 
//************************************************************
void QuitChatRoom(wchar_t* chatroomwxid)
{
>>>>>>> 06c014d... Add files via upload
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
	DWORD dwCallAddr = dwBaseAddress + WxQuitChatRoom;

	//��������
	StructWxid structWxid = { 0 };
	structWxid.pWxid = chatroomwxid;
	structWxid.length = wcslen(chatroomwxid);
	structWxid.maxLength = wcslen(chatroomwxid) * 2;

	DWORD* asmMsg = (DWORD*)&structWxid.pWxid;

	__asm {
		mov ebx, asmMsg;
		push ebx;
		call dwCallAddr;
	}
}


//************************************************************
// ��������: AddGroupMember
// ����˵��: ���Ⱥ��Ա
// ��    ��: GuiShou
// ʱ    ��: 2019/7/9
// ��    ��: chartoomwxid ȺID  wxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void AddGroupMember(wchar_t* chatroomwxid, wchar_t* wxid)
{
	DWORD dwBase = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCallAddr1 = dwBase + WxAddGroupMemberCall1;
	DWORD dwCallAddr2 = dwBase + WxAddGroupMemberCall2;
	DWORD dwCallAddr3 = dwBase + WxAddGroupMemberCall3;
	DWORD dwCallAddr4 = dwBase + WxAddGroupMemberCall4;

	DWORD dwParam = dwBase + WxAddGroupMemberParam1;
	DWORD dwParam2 = dwBase + WxAddGroupMemberParam2;

	//΢��ID�Ľṹ��
	struct Wxid
	{
		wchar_t* str;
		int strLen = 0;
		int maxLen = 0;
		char file[0x8] = { 0 };
	};

	//ȺID�ṹ��
	struct tempChatRoom
	{
		char fill2[0x8] = { 0 };
		wchar_t* str;
		int strLen = 0;
		int maxLen = 0;
		char fill[0x8] = { 0 };
	};


	//������Ҫ������
	Wxid wxidStruct = { 0 };
	wxidStruct.str = wxid;
	wxidStruct.strLen = wcslen(wxid)*2;
	wxidStruct.maxLen = wcslen(wxid) * 4;

	tempChatRoom chatroomStruct = { 0 };
	chatroomStruct.str = chatroomwxid;
	chatroomStruct.strLen = wcslen(chatroomwxid)*2;
	chatroomStruct.maxLen = wcslen(chatroomwxid) * 4;

	char wxidBuff[0xC] = { 0 };
	char tempWxid[0x14] = { 0 };
	char tempBuff[0x14] = { 0 };

	char* pWxid = (char*)&wxidStruct.str;
	char* pChatRoom = (char*)&chatroomStruct.fill2;

	__asm {
		pushad;
		lea esi, wxidBuff;
		mov ecx, esi;
		mov eax, pWxid;
		push eax;
		call dwCallAddr1;
		push 0;
		push dwParam;
		lea ecx, tempWxid;
		call dwCallAddr2;
		sub esp, 0x14;
		mov ecx, pChatRoom;
		mov eax, esp;
		push eax;
		call dwCallAddr3;
		push esi;
		mov ecx, dwParam2;
		call dwCallAddr4;
		popad;
	}
}


//************************************************************
// ��������: ShowChatRoomUser
// ����˵��: ��ʾȺ��Ա
// ��    ��: GuiShou
// ʱ    ��: 2019/7/13
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void ShowChatRoomUser(wchar_t* chatroomwxid)
{
	//1.�Ȼ�ȡȺ��Ա��΢��ID
	struct wxStr
	{
		wchar_t * pStr;
		int strLen;
		int strMaxLen;
		int fill = 0;
		int fill2 = 0;
	};
	//׼��������
	DWORD dwWxidArr = 0;	//����΢��ID���ݵĵ�ַ
	char buff[0x164] = { 0 };
	char userListBuff[0x174] = { 0 };
	//��������
	wxStr pWxid = { 0 };
	pWxid.pStr = chatroomwxid;
	pWxid.strLen = wcslen(chatroomwxid);
	pWxid.strMaxLen = wcslen(chatroomwxid) * 2;
	char * asmWxid = (char *)&pWxid.pStr;

	//����call
	DWORD dwCall1 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall1;
	DWORD dwCall2 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall2;
	DWORD dwCall3 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall3;
	DWORD dwCall4 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall4;

	//��ȡȺ��Ա
	__asm {
		lea ecx, buff[16]
		call dwCall1
		lea eax, buff[16]
		push eax
		mov ebx, asmWxid
		push ebx
		call dwCall2
		mov ecx, eax
		call dwCall3
		lea eax, buff
		push eax
		lea ecx, buff[16]
		call dwCall4
		mov dwWxidArr, eax
	}

	//�õ�΢��ID
	wchar_t test[0x100] = { 0 };
	wchar_t tempWxid[0x100] = { 0 };
	DWORD userList = *((DWORD *)dwWxidArr);
	DWORD testTmp = dwWxidArr + 0xB0;
	int Len = *((int *)testTmp);

	for (int i = 0; i < Len; i++)
	{
		DWORD temWxidAdd = userList + (i * 20);
		swprintf_s(tempWxid, L"%s", (wchar_t*)*((LPVOID *)temWxidAdd));
		//2.��ͨ��΢��ID��ȡȺ��Ա��Ϣ
		GetUserInfoByWxid(tempWxid);
	}

	//���֮������Ϣ
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		MessageBoxA(NULL, "δ�ҵ�ChatRoomMember����", "����", 0);
		return;
	}

	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembersDone;//����һ����ֵ, ������������־��
	userinfodata.cbData = 0;// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfodata.lpData = NULL;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);
}



//************************************************************
// ��������: GetUserInfoByWxid
// ����˵��: ͨ��΢��ID��ȡ�û���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/13
// ��    ��: userwxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void GetUserInfoByWxid(wchar_t* userwxid)
{
	struct wechatText
	{
		wchar_t* pStr;
		int strLen;
		int iStrLen;
	};

	struct UserInfo
	{
		wchar_t UserId[50];
		wchar_t UserNumber[50];
		wchar_t UserNickName[50];
	};


	DWORD dwCall1 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetUserInfoByWxidCall1;
	DWORD dwCall2 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetUserInfoByWxidCall2;
	DWORD dwCall3 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetUserInfoByWxidCall3;


	wechatText pWxid = { 0 };
	pWxid.pStr = userwxid;
	pWxid.strLen = wcslen(userwxid);
	pWxid.iStrLen = wcslen(userwxid) * 2;
	char* asmWxid = (char*)& pWxid.pStr;
	char buff[0x3D8] = { 0 };
	DWORD userData = 0;		//�û����ݵĵ�ַ
	__asm 
	{
		lea edi, buff
		push edi
		sub esp, 0x14
		mov eax, asmWxid
		mov ecx, esp
		mov dword ptr ss : [ebp - 0x2C], esp
		push eax
		call dwCall1
		call dwCall2
		call dwCall3
		mov userData, edi
	}


	DWORD wxidAdd = userData + 0x8;		//΢��ID
	DWORD wxNickAdd = userData + 0x64;	//�ǳ�
	DWORD wxuserIDAdd = userData + 0x1C;	//΢���˺�
	

	//��װ�ṹ��
	UserInfo* userinfo = new UserInfo;

	swprintf_s(userinfo->UserId, L"%s", (wchar_t*)(*((LPVOID*)wxidAdd)));
	swprintf_s(userinfo->UserNickName, L"%s", (wchar_t*)(*((LPVOID*)wxNickAdd)));
	swprintf_s(userinfo->UserNumber, L"%s", (wchar_t*)(*((LPVOID*)wxuserIDAdd)));


	//���͵��ͻ���
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		MessageBoxA(NULL, "δ�ҵ�ChatRoomMember����", "����", 0);
		return;
	}

	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembers;//����һ����ֵ, ������������־��
	userinfodata.cbData = sizeof(UserInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfodata.lpData = userinfo;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);
}



//************************************************************
// ��������: SetRoomName
// ����˵��: �޸�Ⱥ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/14
// ��    ��: roomwxid ȺID roomnameȺ����
// �� �� ֵ: void 
//************************************************************
void SetRoomName(wchar_t* roomwxid, wchar_t* roomname)
{
	struct SetRoomNameStruct
	{
		wchar_t* pStr;
		int strLen;
		int strMaxLen;
		char full[0x8] = { 0 };
	};
	SetRoomNameStruct pRoomwxid = { 0 };
	pRoomwxid.pStr = roomwxid;
	pRoomwxid.strLen = wcslen(roomwxid) + 1;
	pRoomwxid.strMaxLen = (wcslen(roomwxid) + 1) * 2;

	SetRoomNameStruct pRoomname = { 0 };
	pRoomname.pStr = roomname;
	pRoomname.strLen = wcslen(roomname) + 1;
	pRoomname.strMaxLen = (wcslen(roomname) + 1) * 2;

	char* asmWxid = (char*)&pRoomwxid.pStr;
	char* asmRoomname = (char*)&pRoomname.pStr;

	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCall1 = dwWeChatWinAddr + WxSetRoomName;


	__asm
	{
		mov edx, asmRoomname;
		mov ecx, asmWxid;
		call dwCall1;
	}
}


//���Ͱ�����Ϣ��Ҫ�����ݽṹ
class TEXT_WX
{
public:
	wchar_t* pWxid = nullptr;
	DWORD length = 0;
	DWORD maxLength = 0;
	DWORD fill1 = 0;
	DWORD fill2 = 0;
	wchar_t wxid[1024] = { 0 };

	TEXT_WX(wstring wsWxid)
	{
		const wchar_t* temp = wsWxid.c_str();
		wmemcpy(wxid, temp, wsWxid.length());
		length = wsWxid.length();
		maxLength = wsWxid.capacity();
		fill1 = 0;
		fill2 = 0;
		pWxid = wxid;
	}
};




class ROOM_AT
{
public:
	DWORD at_WxidList = 0;
	DWORD at_end1 = 0;
	DWORD at_end2 = 0;
};


class  TEXT_WXID
{
public:
	wchar_t* pWxid = nullptr;
	DWORD length = 0;
	DWORD maxLength = 0;
	DWORD fill1 = 0;
	DWORD fill2 = 0;
};



//************************************************************
// ��������: SendRoomAtMsg
// ����˵��: ���Ͱ�����Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/26
// ��    ��: chatroomid ȺID memberwxid Ⱥ��Ա΢��ID membernicknameȺ��Ա�ǳ� msg ��Ϣ����
// �� �� ֵ: void 
//************************************************************
void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* msg)
{
	HMODULE dllAdress = GetModuleHandleA("WeChatWin.dll");
	DWORD callAddress_SendText = (DWORD)dllAdress + WxSendMessage;


	TEXT_WX wxId(chatroomid);
	wchar_t tempmsg[100] = { 0 };
	swprintf_s(tempmsg, L"@%s %s", membernickname, msg);
	TEXT_WX wxMsg(tempmsg);

	TEXT_WXID wxAtId;
	wxAtId.pWxid = memberwxid;
	wxAtId.length = wcslen(memberwxid);
	wxAtId.maxLength = wcslen(memberwxid) * 2;
	wxAtId.fill1 = 0;
	wxAtId.fill2 = 0;
	//DWORD* asmWxid = (DWORD*)& wxAtId.pWxid;

	ROOM_AT roomAt;
	roomAt.at_WxidList = (DWORD)& wxAtId.pWxid;
	roomAt.at_end1 = roomAt.at_WxidList + 5 * 4;
	roomAt.at_end2 = roomAt.at_end1;

	//����һ��������
	BYTE buff[0x81C] = { 0 };

	//ִ�л�����
	__asm
	{
		lea edx, wxId

		//���ݲ���
		push 0x1

		lea eax, roomAt
		push eax

		//΢����Ϣ����
		lea ebx, wxMsg

		push ebx
		lea ecx, buff

		//���ú���
		call callAddress_SendText

		//ƽ���ջ
		add esp, 0xC
	}
}


//************************************************************
// ��������: DelRoomMember
// ����˵��: ɾ��Ⱥ��Ա
// ��    ��: GuiShou
// ʱ    ��: 2019/7/26
// ��    ��: roomid ȺID memberwxid Ⱥ��Ա΢��ID 
// �� �� ֵ: void 
//************************************************************
void DelRoomMember(wchar_t* roomid, wchar_t* memberwxid)
{
	//ȺID�ṹ��
	struct RoomIdStruct
	{
		wchar_t* roomid;
		int roomidLen;
		int roomidMaxLen;
		int full = 0;
		int full2 = 0;
	};

	//�õ�call�����ݵ�ַ
	DWORD dwCall1 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxDelRoomMemberCall1;
	DWORD dwCall2 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxDelRoomMemberCall2;
	DWORD dwCall3 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxDelRoomMemberCall3;

	//��װȺID�ṹ��
	RoomIdStruct roomiddata;
	roomiddata.roomid = roomid;
	roomiddata.roomidLen = wcslen(roomid) + 1;
	roomiddata.roomidMaxLen = (wcslen(roomid) + 1) * 2;

	//��װ΢��ID�ṹ��
	wchar_t wxidbuff[0xD0] = { 0 };
	DWORD* dwBuff = (DWORD*)&wxidbuff;
	dwBuff[0] = (DWORD)memberwxid;
	dwBuff[1] = wcslen(memberwxid);
	dwBuff[2] = wcslen(memberwxid) * 2;
	dwBuff[3] = 0;
	dwBuff[4] = 0;


	wchar_t datatbuffer[0xD0] = { 0 };
	DWORD* dwDatabuf = (DWORD*)&datatbuffer;
	dwDatabuf[0] = (DWORD)& wxidbuff;
	dwDatabuf[1] = dwDatabuf[0] + 0x14;
	dwDatabuf[2] = dwDatabuf[0] + 0x14;

	char tempbuff[50] = { 0 };
	sprintf_s(tempbuff, "%p", DelRoomMember);
	MessageBoxA(NULL, tempbuff, "��ַ", 0);


	//����ɾ��Ⱥ��Աcall
	__asm
	{
		pushad;
		sub esp, 0x14;
		lea eax, roomiddata.roomid;
		mov ecx, esp;
		push eax;
		call dwCall1;
		lea edi, datatbuffer;
		push edi;
		call dwCall2;
		mov ecx, eax;
		call dwCall3;
		popad;
	}






=======
	};

	DWORD dwBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCallAddr = dwBaseAddress + WxQuitChatRoom;

	//��������
	StructWxid structWxid = { 0 };
	structWxid.pWxid = chatroomwxid;
	structWxid.length = wcslen(chatroomwxid);
	structWxid.maxLength = wcslen(chatroomwxid) * 2;

	DWORD* asmMsg = (DWORD*)&structWxid.pWxid;

	__asm {
		mov ebx, asmMsg;
		push ebx;
		call dwCallAddr;
	}
}


//************************************************************
// ��������: AddGroupMember
// ����˵��: ���Ⱥ��Ա
// ��    ��: GuiShou
// ʱ    ��: 2019/7/9
// ��    ��: chartoomwxid ȺID  wxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void AddGroupMember(wchar_t* chatroomwxid, wchar_t* wxid)
{
	DWORD dwBase = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCallAddr1 = dwBase + WxAddGroupMemberCall1;
	DWORD dwCallAddr2 = dwBase + WxAddGroupMemberCall2;
	DWORD dwCallAddr3 = dwBase + WxAddGroupMemberCall3;
	DWORD dwCallAddr4 = dwBase + WxAddGroupMemberCall4;

	DWORD dwParam = dwBase + WxAddGroupMemberParam1;
	DWORD dwParam2 = dwBase + WxAddGroupMemberParam2;

	//΢��ID�Ľṹ��
	struct Wxid
	{
		wchar_t* str;
		int strLen = 0;
		int maxLen = 0;
		char file[0x8] = { 0 };
	};

	//ȺID�ṹ��
	struct tempChatRoom
	{
		char fill2[0x8] = { 0 };
		wchar_t* str;
		int strLen = 0;
		int maxLen = 0;
		char fill[0x8] = { 0 };
	};


	//������Ҫ������
	Wxid wxidStruct = { 0 };
	wxidStruct.str = wxid;
	wxidStruct.strLen = wcslen(wxid)*2;
	wxidStruct.maxLen = wcslen(wxid) * 4;

	tempChatRoom chatroomStruct = { 0 };
	chatroomStruct.str = chatroomwxid;
	chatroomStruct.strLen = wcslen(chatroomwxid)*2;
	chatroomStruct.maxLen = wcslen(chatroomwxid) * 4;

	char wxidBuff[0xC] = { 0 };
	char tempWxid[0x14] = { 0 };
	char tempBuff[0x14] = { 0 };

	char* pWxid = (char*)&wxidStruct.str;
	char* pChatRoom = (char*)&chatroomStruct.fill2;

	__asm {
		pushad;
		lea esi, wxidBuff;
		mov ecx, esi;
		mov eax, pWxid;
		push eax;
		call dwCallAddr1;
		push 0;
		push dwParam;
		lea ecx, tempWxid;
		call dwCallAddr2;
		sub esp, 0x14;
		mov ecx, pChatRoom;
		mov eax, esp;
		push eax;
		call dwCallAddr3;
		push esi;
		mov ecx, dwParam2;
		call dwCallAddr4;
		popad;
	}
}


//************************************************************
// ��������: ShowChatRoomUser
// ����˵��: ��ʾȺ��Ա
// ��    ��: GuiShou
// ʱ    ��: 2019/7/13
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void ShowChatRoomUser(wchar_t* chatroomwxid)
{
	//1.�Ȼ�ȡȺ��Ա��΢��ID
	struct wxStr
	{
		wchar_t * pStr;
		int strLen;
		int strMaxLen;
		int fill = 0;
		int fill2 = 0;
	};
	//׼��������
	DWORD dwWxidArr = 0;	//����΢��ID���ݵĵ�ַ
	char buff[0x164] = { 0 };
	char userListBuff[0x174] = { 0 };
	//��������
	wxStr pWxid = { 0 };
	pWxid.pStr = chatroomwxid;
	pWxid.strLen = wcslen(chatroomwxid);
	pWxid.strMaxLen = wcslen(chatroomwxid) * 2;
	char * asmWxid = (char *)&pWxid.pStr;

	//����call
	DWORD dwCall1 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall1;
	DWORD dwCall2 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall2;
	DWORD dwCall3 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall3;
	DWORD dwCall4 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall4;

	//��ȡȺ��Ա
	__asm {
		lea ecx, buff[16]
		call dwCall1
		lea eax, buff[16]
		push eax
		mov ebx, asmWxid
		push ebx
		call dwCall2
		mov ecx, eax
		call dwCall3
		lea eax, buff
		push eax
		lea ecx, buff[16]
		call dwCall4
		mov dwWxidArr, eax
	}

	//�õ�΢��ID
	wchar_t test[0x100] = { 0 };
	wchar_t tempWxid[0x100] = { 0 };
	DWORD userList = *((DWORD *)dwWxidArr);
	DWORD testTmp = dwWxidArr + 0xB0;
	int Len = *((int *)testTmp);

	for (int i = 0; i < Len; i++)
	{
		DWORD temWxidAdd = userList + (i * 20);
		swprintf_s(tempWxid, L"%s", (wchar_t*)*((LPVOID *)temWxidAdd));
		//2.��ͨ��΢��ID��ȡȺ��Ա��Ϣ
		GetUserInfoByWxid(tempWxid);
	}

	//���֮������Ϣ
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		MessageBoxA(NULL, "δ�ҵ�ChatRoomMember����", "����", 0);
		return;
	}

	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembersDone;//����һ����ֵ, ������������־��
	userinfodata.cbData = 0;// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfodata.lpData = NULL;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);
}



//************************************************************
// ��������: GetUserInfoByWxid
// ����˵��: ͨ��΢��ID��ȡ�û���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/13
// ��    ��: userwxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void GetUserInfoByWxid(wchar_t* userwxid)
{
	struct wechatText
	{
		wchar_t* pStr;
		int strLen;
		int iStrLen;
	};

	struct UserInfo
	{
		wchar_t UserId[50];
		wchar_t UserNumber[50];
		wchar_t UserNickName[50];
	};


	DWORD dwCall1 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetUserInfoByWxidCall1;
	DWORD dwCall2 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetUserInfoByWxidCall2;
	DWORD dwCall3 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetUserInfoByWxidCall3;


	wechatText pWxid = { 0 };
	pWxid.pStr = userwxid;
	pWxid.strLen = wcslen(userwxid);
	pWxid.iStrLen = wcslen(userwxid) * 2;
	char* asmWxid = (char*)& pWxid.pStr;
	char buff[0x3D8] = { 0 };
	DWORD userData = 0;		//�û����ݵĵ�ַ
	__asm 
	{
		lea edi, buff
		push edi
		sub esp, 0x14
		mov eax, asmWxid
		mov ecx, esp
		mov dword ptr ss : [ebp - 0x2C], esp
		push eax
		call dwCall1
		call dwCall2
		call dwCall3
		mov userData, edi
	}


	DWORD wxidAdd = userData + 0x8;		//΢��ID
	DWORD wxNickAdd = userData + 0x64;	//�ǳ�
	DWORD wxuserIDAdd = userData + 0x1C;	//΢���˺�
	

	//��װ�ṹ��
	UserInfo* userinfo = new UserInfo;

	swprintf_s(userinfo->UserId, L"%s", (wchar_t*)(*((LPVOID*)wxidAdd)));
	swprintf_s(userinfo->UserNickName, L"%s", (wchar_t*)(*((LPVOID*)wxNickAdd)));
	swprintf_s(userinfo->UserNumber, L"%s", (wchar_t*)(*((LPVOID*)wxuserIDAdd)));


	//���͵��ͻ���
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		MessageBoxA(NULL, "δ�ҵ�ChatRoomMember����", "����", 0);
		return;
	}

	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembers;//����һ����ֵ, ������������־��
	userinfodata.cbData = sizeof(UserInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfodata.lpData = userinfo;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);
}



//************************************************************
// ��������: SetRoomName
// ����˵��: �޸�Ⱥ����
// ��    ��: GuiShou
// ʱ    ��: 2019/7/14
// ��    ��: roomwxid ȺID roomnameȺ����
// �� �� ֵ: void 
//************************************************************
void SetRoomName(wchar_t* roomwxid, wchar_t* roomname)
{
	struct SetRoomNameStruct
	{
		wchar_t* pStr;
		int strLen;
		int strMaxLen;
		char full[0x8] = { 0 };
	};
	SetRoomNameStruct pRoomwxid = { 0 };
	pRoomwxid.pStr = roomwxid;
	pRoomwxid.strLen = wcslen(roomwxid) + 1;
	pRoomwxid.strMaxLen = (wcslen(roomwxid) + 1) * 2;

	SetRoomNameStruct pRoomname = { 0 };
	pRoomname.pStr = roomname;
	pRoomname.strLen = wcslen(roomname) + 1;
	pRoomname.strMaxLen = (wcslen(roomname) + 1) * 2;

	char* asmWxid = (char*)&pRoomwxid.pStr;
	char* asmRoomname = (char*)&pRoomname.pStr;

	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCall1 = dwWeChatWinAddr + WxSetRoomName;


	__asm
	{
		mov edx, asmRoomname;
		mov ecx, asmWxid;
		call dwCall1;
	}
>>>>>>> 06c014d... Add files via upload
}