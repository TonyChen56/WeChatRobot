#include "stdafx.h"
#include "ChatRoomOperate.h"
#include <atlconv.h>

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
	DWORD callAdrress = GetWeChatWinBase()+ WxSetRoomAnnouncement;
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
		mov r_esp, esp;
		lea eax, bufferA;
		push eax;
		call callAdrress;

		//恢复堆栈寄存器
		mov eax, r_esp;
		mov esp, eax;
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
	DWORD dwBaseAddress = GetWeChatWinBase();
	DWORD dwCallAddr = dwBaseAddress + WxQuitChatRoom;

	//构造数据
	GeneralStruct structWxid(chatroomwxid);
	DWORD* asmMsg = (DWORD*)&structWxid.pstr;

	__asm 
	{
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
	DWORD dwBase = GetWeChatWinBase();
	DWORD dwCallAddr1 = dwBase + WxAddGroupMemberCall1;
	DWORD dwCallAddr2 = dwBase + WxAddGroupMemberCall2;
	DWORD dwCallAddr3 = dwBase + WxAddGroupMemberCall3;
	DWORD dwCallAddr4 = dwBase + WxAddGroupMemberCall4;

	DWORD dwParam = dwBase + WxAddGroupMemberParam1;
	DWORD dwParam2 = dwBase + WxAddGroupMemberParam2;

	//构造需要的数据
	GeneralStruct wxidStruct(wxid);
	RoomIdStruct chatroomStruct = { 0 };
	chatroomStruct.str = chatroomwxid;
	chatroomStruct.strLen = wcslen(chatroomwxid)*2;
	chatroomStruct.maxLen = wcslen(chatroomwxid) * 4;

	char wxidBuff[0xC] = { 0 };
	char tempWxid[0x14] = { 0 };
	char tempBuff[0x14] = { 0 };

	char* pWxid = (char*)&wxidStruct.pstr;
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
	//准备缓冲区
	DWORD dwWxidArr = 0;	//保存微信ID数据的地址
	char buff[0x164] = { 0 };
	char userListBuff[0x174] = { 0 };
	//构造数据
	GeneralStruct pWxid(chatroomwxid);
	char* asmWxid = (char *)&pWxid.pstr;

	//调用call
	DWORD dwCall1 = GetWeChatWinBase() + WxGetRoomUserWxidCall1;
	DWORD dwCall2 = GetWeChatWinBase()  + WxGetRoomUserWxidCall2;
	DWORD dwCall3 = GetWeChatWinBase()  + WxGetRoomUserWxidCall3;
	DWORD dwCall4 = GetWeChatWinBase()  + WxGetRoomUserWxidCall4;

	//获取群成员
	__asm
	{
		lea ecx, buff[16];
		call dwCall1;
		lea eax, buff[16];
		push eax;
		mov ebx, asmWxid;
		push ebx;
		call dwCall2;
		mov ecx, eax;
		call dwCall3;
		lea eax, buff;
		push eax;
		lea ecx, buff[16];
		call dwCall4;
		mov dwWxidArr, eax;
	}

	//拿到微信ID
	wchar_t test[0x100] = { 0 };
	wchar_t tempWxid[0x100] = { 0 };
	char tempWxidA[0x100] = { 0 };
	DWORD userList = *((DWORD *)dwWxidArr);		//userList这个里面的微信ID列表 3.1是ASCII格式的微信ID
	DWORD testTmp = dwWxidArr + 0xB4;
	int Len = *((int *)testTmp);				//取到微信ID的个数



	for (int i = 0; i < Len; i++)
	{
		DWORD temWxidAdd = userList + (i * 0x18);		//0x18是每个微信ID的间隔
		int flags = (int)(*((LPVOID*)(temWxidAdd + 0x14)));
		if (flags == 0xF)
		{
			sprintf_s(tempWxidA, "%s", (char*)temWxidAdd);
		}
		else
		{
			sprintf_s(tempWxidA, "%s", (char*)*((LPVOID *)temWxidAdd));
		}

		USES_CONVERSION;
		//2.再通过微信ID获取群成员信息
		GetUserInfoByWxid(A2W(tempWxidA));
	}


	//完成之后发送消息
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		OutputDebugStringA("未查找到ChatRoomMember窗口");
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
	DWORD WechatBase = (DWORD)GetModuleHandle(L"WeChatWin.dll");

	DWORD dwCall1 = WechatBase + WxGetUserInfoWithNoNetworkCall1;
	DWORD dwCall2 = WechatBase + WxGetUserInfoWithNoNetworkCall2;
	DWORD dwCall3 = WechatBase + WxGetUserInfoWithNoNetworkCall3;

	char buff[0x508] = { 0 };		
	char * asmHeadBuff = buff;
	char * asmBuff = &buff[0x18];

	GeneralStruct pWxid(userwxid);
	char* asmWxid = (char*)&pWxid.pstr;

	__asm
	{
		pushad;
		mov edi, asmWxid;		//微信ID结构体	
		mov eax, asmBuff;		//缓冲区
		push eax;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		mov dword ptr ds : [ecx], 0x0;
		mov dword ptr ds : [ecx + 0x4], 0x0;
		mov dword ptr ds : [ecx + 0x8], 0x0;
		mov dword ptr ds : [ecx + 0xC], 0x0;
		mov dword ptr ds : [ecx + 0x10], 0x0;
		push dword ptr ds : [edi];	//微信ID
		call dwCall1;				//call1
		call dwCall2;				//call2
		mov eax, asmHeadBuff;
		push eax;
		mov ecx, asmBuff;
		call dwCall3;
		popad
	}



	LPVOID lpWxid = *((LPVOID *)((DWORD)buff + 0x20));				//微信ID
	LPVOID lpWxcount = *((LPVOID *)((DWORD)buff + 0x34));			//微信账号
	LPVOID lpNickName = *((LPVOID *)((DWORD)buff + 0x7C));			//昵称




	//组装结构体
	UserInfo *userinfo = new UserInfo;
	swprintf_s(userinfo->UserId, L"%s", (wchar_t*)lpWxid);
	swprintf_s(userinfo->UserNickName, L"%s", (wchar_t*)lpNickName);
	swprintf_s(userinfo->UserNumber, L"%s", (wchar_t*)lpWxcount);



	//发送到客户端
	HWND hWnd = FindWindow(NULL, TEXT("ChatRoomMember"));
	if (hWnd == NULL)
	{
		OutputDebugStringA("未查找到ChatRoomMember窗口");
		return;
	}


	COPYDATASTRUCT userinfodata;
	userinfodata.dwData = WM_ShowChatRoomMembers;//保存一个数值, 可以用来作标志等
	userinfodata.cbData = sizeof(UserInfo);// strlen(szSendBuf);//待发送的数据的长
	userinfodata.lpData = userinfo;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfodata);

	delete userinfo;

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
	GeneralStruct pRoomwxid(roomwxid);
	GeneralStruct pRoomname(roomname);
	char* asmWxid = (char*)&pRoomwxid.pstr;
	char* asmRoomname = (char*)&pRoomname.pstr;

	DWORD dwWeChatWinAddr = GetWeChatWinBase();
	DWORD dwCall1 = dwWeChatWinAddr + WxSetRoomName;

	__asm
	{
		mov edx, asmRoomname;
		mov ecx, asmWxid;
		call dwCall1;
	}
}


//************************************************************
// 函数名称: SendRoomAtMsg
// 函数说明: 发送艾特消息
// 作    者: GuiShou
// 时    间: 2019/7/26
// 参    数: chatroomid 群ID memberwxid 群成员微信ID membernickname群成员昵称 msg 消息内容
// 返 回 值: void 
//************************************************************
void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* msg)
{
	//调用call组装数据格式
	DWORD dwDllBase = GetWeChatWinBase();
	DWORD dwPackageMsgDataCall = dwDllBase + WxPackageMsgData;
	DWORD dwSendTextCall = dwDllBase + WxSendMessage;

	//组装文本内容
	wchar_t tempmsg[500] = { 0 };
	swprintf_s(tempmsg, L"@%s %s", membernickname, msg);

	//组装微信ID数据结构体
	GeneralStruct wxid(memberwxid);
	//组装群ID数据结构体
	GeneralStruct roomid(chatroomid);
	//组装消息文本数据结构体
	GeneralStruct textcontent(tempmsg);
	//0x81C缓冲区
	BYTE buff[0x81C] = { 0 };

	//微信ID数据结构指针
	wchar_t* pWxid = (wchar_t*)&wxid.pstr;
	//群ID数据结构指针
	wchar_t* pRoomId = (wchar_t*)&roomid.pstr;
	//消息文本数据结构指针
	wchar_t* pTextContent = (wchar_t*)&textcontent.pstr;

	//装数据结构体缓冲区
	char databuff[16] = { 0 };
	//调用组装数据格式call
	__asm
	{
		mov eax, pWxid;			//微信ID结构体
		push eax;
		lea ecx, databuff;
		call dwPackageMsgDataCall;
	}


	//调用call发送艾特消息
	__asm
	{
		mov edx, pRoomId;		//群ID结构体
		lea eax, databuff;		//组装的数据结构
		push 0x1;
		push eax;
		mov ebx, pTextContent;	//消息文本的指针
		push ebx;
		lea ecx, buff;			//0x81C缓冲区
		call dwSendTextCall;	//发送消息call
		add esp, 0xC;
	}
}


//************************************************************
// 函数名称: DelRoomMember
// 函数说明: 删除群成员
// 作    者: GuiShou
// 时    间: 2019/7/26
// 参    数: roomid 群ID memberwxid 群成员微信ID 
// 返 回 值: void 
//************************************************************
void DelRoomMember(wchar_t* roomid, wchar_t* memberwxid)
{
	//拿到call的数据地址
	DWORD dwCall1 = GetWeChatWinBase() + WxDelRoomMemberCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxDelRoomMemberCall2;
	DWORD dwCall3 = GetWeChatWinBase() + WxDelRoomMemberCall3;

	//组装群ID结构体
	GeneralStruct roomiddata(roomid);

	//组装微信ID结构体
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


	__asm
	{
		pushad;
		sub esp, 0x14;
		mov ecx, esp;
		lea ebx, roomiddata.pstr;
		push ebx;
		call dwCall1;
		lea edi, datatbuffer;
		push edi;
		call dwCall2;
		mov ecx, eax;
		call dwCall3;
		popad;
	}
}

