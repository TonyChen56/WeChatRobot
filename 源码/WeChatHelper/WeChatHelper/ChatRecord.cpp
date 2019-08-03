#include "stdafx.h"
#include <string>
#include <Shlwapi.h>
#include "ChatRecord.h"
#include "FriendList.h"
#include "CAutoFunction.h"
#pragma comment(lib,"Shlwapi.lib")
using namespace std;


BOOL g_AutoChat = FALSE;	//是否自动聊天
BOOL isSendTuLing = FALSE;	//是否已经发给了图灵机器人
BOOL isText = TRUE;			//是否是文字消息
wchar_t tempwxid[50] = { 0 };	//存放微信ID

DWORD r_esp = 0;
DWORD r_eax = 0;

CHAR originalCode[5] = { 0 };
//参数的偏移
DWORD dwParam = (DWORD)GetModuleHandle(L"WeChatWin.dll") + ReciveMessageParam;

//计算需要HOOK的地址
DWORD dwHookAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + ReciveMessage - 5;

//返回地址
DWORD RetAddr = dwHookAddr + 5;

//消息结构体
struct Message
{
	wchar_t type[10];		//消息类型
	wchar_t source[20];		//消息来源
	wchar_t wxid[40];		//微信ID/群ID
	wchar_t msgSender[40];	//消息发送者
	wchar_t content[200];	//消息内容
};


//************************************************************
// 函数名称: HookChatRecord
// 函数说明: HOOK聊天记录
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void 
//************************************************************
void HookChatRecord()
{
	//组装数据
	BYTE bJmpCode[5] = { 0xE9 };
	*(DWORD*)&bJmpCode[1] = (DWORD)RecieveWxMesage - dwHookAddr - 5;

	//保存当前位置的指令,在unhook的时候使用。
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwHookAddr, originalCode, 5, 0);

	//覆盖指令 B9 E8CF895C //mov ecx,0x5C89CFE8
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwHookAddr, bJmpCode, 5, 0);
}



//************************************************************
// 函数名称: RecieveMesage
// 函数说明: 接收消息
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void 
//************************************************************
__declspec(naked) void RecieveWxMesage()
{
	//保存现场
	__asm
	{
		//补充被覆盖的代码
		//5B950573  |.  B9 E8CF895C           mov ecx,WeChatWi.5C89CFE8
		//mov ecx,0x5C89CFE8
		mov ecx, dwParam

		//提取esp寄存器内容，放在一个变量中
		mov r_esp, esp
		mov r_eax, eax

		pushad
		pushfd
	}
	SendWxMessage();

	//恢复现场
	__asm
	{
		popfd
		popad
		//跳回被HOOK指令的下一条指令
		jmp RetAddr
	}
}


//************************************************************
// 函数名称: SendMessage
// 函数说明: 将接收到的消息发送给客户端
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void 
//************************************************************
void SendWxMessage()
{
	Message *msg=new Message;
	//信息块的位置
	DWORD** msgAddress = (DWORD * *)r_esp;
	//消息类型
	DWORD msgType = *((DWORD*)(**msgAddress + 0x30));
	
	BOOL isFriendMsg = FALSE;		//是否是好友消息
	BOOL isImageMessage = FALSE;	//是否是图片消息
	BOOL isRadioMessage = FALSE;	//是否是视频消息
	BOOL isVoiceMessage = FALSE;	//是否是语音消息
	BOOL isBusinessCardMessage = FALSE;	//是否是名片消息
	BOOL isExpressionMessage = FALSE;	//是否是名片消息
	BOOL isLocationMessage = FALSE;	//是否是位置消息
	BOOL isSystemMessage = FALSE;	//是否是系统或红包消息
	BOOL isFriendRequestMessage = FALSE;	//是否是好友请求消息
	BOOL isOther = FALSE;	//是否是其他消息


	switch (msgType)
	{
	case 0x01:
		memcpy(msg->type, L"文字",sizeof(L"文字"));
		break;
	case 0x03:
		memcpy(msg->type, L"图片", sizeof(L"图片"));
		isImageMessage = TRUE;
		break;
	case 0x22:
		memcpy(msg->type, L"语音", sizeof(L"语音"));
		isVoiceMessage = TRUE;
		break;
	case 0x25:
		memcpy(msg->type, L"好友确认", sizeof(L"好友确认"));
		isFriendRequestMessage = TRUE;
		break;
	case 0x28:
		memcpy(msg->type, L"POSSIBLEFRIEND_MSG", sizeof(L"POSSIBLEFRIEND_MSG"));
		isOther = TRUE;
		break;
	case 0x2A:
		memcpy(msg->type, L"名片", sizeof(L"名片"));
		isBusinessCardMessage = TRUE;
		break;
	case 0x2B:
		memcpy(msg->type, L"视频", sizeof(L"视频"));
		isRadioMessage = TRUE;
		break;
	case 0x2F:
		//石头剪刀布
		memcpy(msg->type, L"表情", sizeof(L"表情"));
		isExpressionMessage = TRUE;
		break;
	case 0x30:
		memcpy(msg->type, L"位置", sizeof(L"位置"));
		isLocationMessage = TRUE;
		break;
	case 0x31:
		//共享实时位置
		//文件
		//转账
		//链接
		memcpy(msg->type, L"共享实时位置、文件、转账、链接", sizeof(L"共享实时位置、文件、转账、链接"));
		isOther = TRUE;
		break;
	case 0x32:
		memcpy(msg->type, L"VOIPMSG", sizeof(L"VOIPMSG"));
		isOther = TRUE;
		break;
	case 0x33:
		memcpy(msg->type, L"微信初始化", sizeof(L"微信初始化"));
		isOther = TRUE;
		break;
	case 0x34:
		memcpy(msg->type, L"VOIPNOTIFY", sizeof(L"VOIPNOTIFY"));
		isOther = TRUE;
		break;
	case 0x35:
		memcpy(msg->type, L"VOIPINVITE", sizeof(L"VOIPINVITE"));
		isOther = TRUE;
		break;
	case 0x3E:
		memcpy(msg->type, L"小视频", sizeof(L"小视频"));
		isRadioMessage = TRUE;
		break;
	case 0x270F:
		memcpy(msg->type, L"SYSNOTICE", sizeof(L"SYSNOTICE"));
		isOther = TRUE;
		break;
	case 0x2710:
		//系统消息
		//红包
		memcpy(msg->type, L"红包、系统消息", sizeof(L"红包、系统消息"));
		isSystemMessage = TRUE;
		break;
	default:
		isOther = TRUE;
		break;
	}
	//消息内容
	wstring fullmessgaedata = GetMsgByAddress(**msgAddress + 0x68);	//完整的消息内容
	//判断消息来源是群消息还是好友消息
	wstring msgSource2 = L"<msgsource />\n";
	wstring msgSource = L"";
	msgSource.append(GetMsgByAddress(**msgAddress + 0x168));
	//好友消息
	if (msgSource.length() <= msgSource2.length())
	{
		memcpy(msg->source, L"好友消息", sizeof(L"好友消息"));
		isFriendMsg = TRUE;
	}
	else
	{
		//群消息
		memcpy(msg->source, L"群消息", sizeof(L"群消息"));
	}

	//显示微信ID/群ID
	LPVOID pWxid = *((LPVOID *)(**msgAddress + 0x40));
	swprintf_s(msg->wxid, L"%s", (wchar_t*)pWxid);

	
	//如果是群消息
	if (isFriendMsg == FALSE)
	{
		//显示消息发送者
		LPVOID pSender = *((LPVOID *)(**msgAddress + 0x114));
		swprintf_s(msg->msgSender, L"%s", (wchar_t*)pSender);
	}
	else
	{
		memcpy(msg->msgSender, L"NULL", sizeof(L"NULL"));
	}


	//显示消息内容  过滤无法显示的消息 防止奔溃
	if (StrStrW(msg->wxid, L"gh"))
	{
		//如果是图灵机器人发来的消息 并且消息已经发送给图灵机器人
		if ((StrCmpW(msg->wxid,L"gh_ab370b2e4b62")==0)&&isSendTuLing==TRUE)
		{
			wchar_t tempcontent[0x200] = { 0 };
			//首先判断机器人回复的消息类型 如果不是文字 直接回复
			if (msgType!=0x01)
			{
				SendTextMessage(tempwxid, (wchar_t*)L"啦啦啦");
				isSendTuLing = FALSE;
			}
			//再次判断发送给机器人的消息类型
			else if (isText == FALSE)
			{
				SendTextMessage(tempwxid, (wchar_t*)L"亲 不支持此类消息哦 请发文字 么么哒");
				isSendTuLing = FALSE;
				isText = TRUE;
			}
			else   //如果是文字 再次判断长度
			{
				//接着拿到消息内容 发送给好友
				LPVOID pContent = *((LPVOID *)(**msgAddress + 0x68));
				swprintf_s(tempcontent, L"%s", (wchar_t*)pContent);
				//判断返回的消息是否过长
				if (wcslen(tempcontent) > 0x100)
				{
					wcscpy_s(tempcontent, wcslen(L"啦啦啦"), L"啦啦啦");
				}

				SendTextMessage(tempwxid, tempcontent);
				isSendTuLing = FALSE;
			}
		}
		else
		{
			//如果微信ID中带有gh 说明是公众号
			swprintf_s(msg->content, L"%s", L"公众号发来推文,请在手机上查看");
		}
	}
	//过滤图片消息 
	else if (isImageMessage == TRUE)
	{
		swprintf_s(msg->content, L"%s", L"收到图片消息,请在手机上查看");
	}
	else if (isRadioMessage ==TRUE)
	{
		swprintf_s(msg->content, L"%s", L"收到视频消息,请在手机上查看");
	}
	else if (isVoiceMessage==TRUE)
	{
		swprintf_s(msg->content, L"%s", L"收到语音消息,请在手机上查看");
	}
	else if (isBusinessCardMessage == TRUE)
	{
		swprintf_s(msg->content, L"%s", L"收到名片消息,已自动添加好友");
		//自动添加好友
		AutoAddCardUser(fullmessgaedata);
	}
	else if (isExpressionMessage == TRUE)
	{
		swprintf_s(msg->content, L"%s", L"收到表情消息,请在手机上查看");
	}
	//自动通过好友请求
	else if(isFriendRequestMessage==TRUE)
	{
		swprintf_s(msg->content, L"%s", L"收到好友请求,已自动通过");
		//自动通过好友请求
		AutoAgreeUserRequest(fullmessgaedata);
	}
	else if (isOther == TRUE)
	{
		//取出消息内容
		wchar_t tempcontent[0x1000] = { 0 };
		LPVOID pContent = *((LPVOID *)(**msgAddress + 0x68));
		swprintf_s(tempcontent, L"%s", (wchar_t*)pContent);
		//判断是否是转账消息
		if (StrStrW(tempcontent,L"微信转账"))
		{
			swprintf_s(msg->content, L"%s", L"收到转账消息,已自动收款");

			//自动收款
			AutoCllectMoney(fullmessgaedata, msg->wxid);	
		}
		else
		{
			//判断是否是转账消息
			swprintf_s(msg->content, L"%s", L"收到共享实时位置、文件、链接等其他消息,请在手机上查看");
		}
	}
	else if (isLocationMessage == TRUE)
	{
		swprintf_s(msg->content, L"%s", L"收到位置消息,请在手机上查看");
	}
	else if (isSystemMessage == TRUE)
	{
		swprintf_s(msg->content, L"%s", L"收到红包或系统消息,请在手机上查看");
	}
	//过滤完所有消息之后
	else
	{
		wchar_t tempbuff[0x1000];
		LPVOID pContent = *((LPVOID *)(**msgAddress + 0x68));
		swprintf_s(tempbuff, L"%s", (wchar_t*)pContent);
		//判断消息长度 如果长度超过就不显示
		if (wcslen(tempbuff)>200)
		{
			swprintf_s(msg->content, L"%s", L"消息内容过长 已经过滤");
		}
		else
		{
			swprintf_s(msg->content, L"%s", (wchar_t*)pContent);
		}

	}


	//发送到控制端
	HWND hWnd = FindWindow(NULL, TEXT("微信助手"));
	if (hWnd == NULL)
	{
		MessageBoxA(NULL, "未找到微信助手窗口", "发送端", MB_OK);
	}

	COPYDATASTRUCT chatmsg;
	chatmsg.dwData = WM_ShowChatRecord;//保存一个数值, 可以用来作标志等
	chatmsg.cbData = sizeof(Message);// strlen(szSendBuf);//待发送的数据的长
	chatmsg.lpData = msg;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&chatmsg);

	//这里处理自动聊天
	if (isFriendMsg == TRUE && g_AutoChat == TRUE)
	{
		//判断消息类型
		if (msgType != 0x01)
		{
			isText = FALSE;
		}
		//保存一下微信ID
		wcscpy_s(tempwxid, wcslen(msg->wxid) + 1, msg->wxid);

		//判断消息内容是否是你好
		if (wcscmp(msg->content, L"你好") == 0)
		{
			swprintf_s(msg->content, L"%s", L"哈喽");
		}

		

		//拿到消息内容 发给图灵机器人
		SendTextMessage((wchar_t*)L"gh_ab370b2e4b62", msg->content);
		isSendTuLing = TRUE;
	}
}


//************************************************************
// 函数名称: GetMsgByAddress
// 函数说明: 从地址中获取消息内容
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: DWORD memAddress  目标地址
// 返 回 值: LPCWSTR	消息内容
//************************************************************
LPCWSTR GetMsgByAddress(DWORD memAddress)
{
	//获取字符串长度
	DWORD msgLength = *(DWORD*)(memAddress + 4);
	if (msgLength == 0)
	{
		WCHAR* msg = new WCHAR[1];
		msg[0] = 0;
		return msg;
	}

	WCHAR* msg = new WCHAR[msgLength + 1];
	ZeroMemory(msg, msgLength + 1);

	//复制内容
	wmemcpy_s(msg, msgLength + 1, (WCHAR*)(*(DWORD*)memAddress), msgLength + 1);
	return msg;
}


