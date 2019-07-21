#include "stdafx.h"
#include "ChatRoomOperate.h"
#include <stdio.h>


//************************************************************
// 函数名称: SetWxRoomAnnouncement
// 函数说明: 发送群公告
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: chartoomwxid 群ID Announcement 群公告
// 返 回 值: void 
//************************************************************
void SetWxRoomAnnouncement(wchar_t* chatroomwxid, wchar_t* Announcement)
{
	//获取WeChatWin的基址
	DWORD callAdrress = (DWORD)GetModuleHandle(L"WeChatWin.dll")+ WxSetRoomAnnouncement;
	//组装数据
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
		//保存堆栈寄存器
		mov r_esp, esp

		//654B85B1 | .  8D85 30FFFFFF lea eax, [local.52]
		//654B85B7 | .  50            push eax
		//654B85B8 | .E8 43FF2000   call WeChatWi.656C8500;  发布群公告
		lea eax, bufferA
		push eax
		call callAdrress

		//恢复堆栈寄存器
		mov eax, r_esp
		mov esp, eax
	}
}



//************************************************************
// 函数名称: QuitChatRoom
// 函数说明: 退出群聊
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: chartoomwxid 群ID 
// 返 回 值: void 
//************************************************************
void QuitChatRoom(wchar_t* chatroomwxid)
{
	struct StructWxid
	{
		//发送的文本消息指针
		wchar_t* pWxid;
		//字符串长度
		DWORD length;
		//字符串最大长度
		DWORD maxLength;

		//补充两个占位数据
		DWORD fill1;
		DWORD fill2;
	};

	DWORD dwBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCallAddr = dwBaseAddress + WxQuitChatRoom;

	//构造数据
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
// 函数名称: AddGroupMember
// 函数说明: 添加群成员
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: chartoomwxid 群ID  wxid 微信ID
// 返 回 值: void 
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

	//微信ID的结构体
	struct Wxid
	{
		wchar_t* str;
		int strLen = 0;
		int maxLen = 0;
		char file[0x8] = { 0 };
	};

	//群ID结构体
	struct tempChatRoom
	{
		char fill2[0x8] = { 0 };
		wchar_t* str;
		int strLen = 0;
		int maxLen = 0;
		char fill[0x8] = { 0 };
	};


	//构造需要的数据
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
// 函数名称: ShowChatRoomUser
// 函数说明: 显示群成员
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: void
// 返 回 值: void 
//************************************************************
void ShowChatRoomUser(wchar_t* chatroomwxid)
{
	//1.先获取群成员的微信ID
	struct wxStr
	{
		wchar_t * pStr;
		int strLen;
		int strMaxLen;
		int fill = 0;
		int fill2 = 0;
	};
	//准备缓冲区
	DWORD dwWxidArr = 0;	//保存微信ID数据的地址
	char buff[0x164] = { 0 };
	char userListBuff[0x174] = { 0 };
	//构造数据
	wxStr pWxid = { 0 };
	pWxid.pStr = chatroomwxid;
	pWxid.strLen = wcslen(chatroomwxid);
	pWxid.strMaxLen = wcslen(chatroomwxid) * 2;
	char * asmWxid = (char *)&pWxid.pStr;

	//调用call
	DWORD dwCall1 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall1;
	DWORD dwCall2 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall2;
	DWORD dwCall3 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall3;
	DWORD dwCall4 = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxGetRoomUserWxidCall4;

	//获取群成员
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

	//拿到微信ID
	wchar_t test[0x100] = { 0 };
	wchar_t tempWxid[0x100] = { 0 };
	DWORD userList = *((DWORD *)dwWxidArr);
	DWORD testTmp = dwWxidArr + 0xB0;
	int Len = *((int *)testTmp);

	for (int i = 0; i < Len; i++)
	{
		DWORD temWxidAdd = userList + (i * 20);
		swprintf_s(tempWxid, L"%s", (wchar_t*)*((LPVOID *)temWxidAdd));
		//2.再通过微信ID获取群成员信息
		GetUserInfoByWxid(tempWxid);
	}

	//完成之后发送消息
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		MessageBoxA(NULL, "未找到ChatRoomMember窗口", "错误", 0);
		return;
	}

	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembersDone;//保存一个数值, 可以用来作标志等
	userinfodata.cbData = 0;// strlen(szSendBuf);//待发送的数据的长
	userinfodata.lpData = NULL;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);
}



//************************************************************
// 函数名称: GetUserInfoByWxid
// 函数说明: 通过微信ID获取用户信息
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: userwxid 微信ID
// 返 回 值: void 
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
	DWORD userData = 0;		//用户数据的地址
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


	DWORD wxidAdd = userData + 0x8;		//微信ID
	DWORD wxNickAdd = userData + 0x64;	//昵称
	DWORD wxuserIDAdd = userData + 0x1C;	//微信账号
	

	//组装结构体
	UserInfo* userinfo = new UserInfo;

	swprintf_s(userinfo->UserId, L"%s", (wchar_t*)(*((LPVOID*)wxidAdd)));
	swprintf_s(userinfo->UserNickName, L"%s", (wchar_t*)(*((LPVOID*)wxNickAdd)));
	swprintf_s(userinfo->UserNumber, L"%s", (wchar_t*)(*((LPVOID*)wxuserIDAdd)));


	//发送到客户端
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		MessageBoxA(NULL, "未找到ChatRoomMember窗口", "错误", 0);
		return;
	}

	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembers;//保存一个数值, 可以用来作标志等
	userinfodata.cbData = sizeof(UserInfo);// strlen(szSendBuf);//待发送的数据的长
	userinfodata.lpData = userinfo;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);
}



//************************************************************
// 函数名称: SetRoomName
// 函数说明: 修改群名称
// 作    者: GuiShou
// 时    间: 2019/7/14
// 参    数: roomwxid 群ID roomname群名称
// 返 回 值: void 
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