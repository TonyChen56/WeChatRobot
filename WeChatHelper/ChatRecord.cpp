
#include "stdafx.h"
#include <string>
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")
#include "ChatRecord.h"
#include "FriendList.h"
#include "CAutoFunction.h"
#include "Function.h"
#include <stdio.h>
#include <WINSOCK2.H>
#pragma comment(lib,"ws2_32.lib")
using namespace std;



#define SERVER_ADDRESS "127.0.0.1" //服务器端IP地址      
#define PORT           8080         //服务器的端口号      
#define MSGSIZE        1024         //收发缓冲区的大小  

BOOL g_AutoChat = FALSE;	//是否自动聊天
BOOL isSendTuLing = FALSE;	//是否已经发给了机器人
wchar_t tempwxid[50];	//存放微信ID


//返回地址
DWORD RetkReciveMsgAddr = GetWeChatWinBase() + WxReciveMessage + 5;

//被覆盖的call的地址
DWORD OverReciveMsgCallAddr = GetWeChatWinBase() + WxReciveMessageCall;


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
	HookAnyAddress(GetWeChatWinBase() + WxReciveMessage, RecieveWxMesage);
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
		pushad;
		push eax;
		call SendWxMessage;
		popad;
		//调用被覆盖的call
		call OverReciveMsgCallAddr;
		//跳转到返回地址
		jmp RetkReciveMsgAddr;
	}
}



//************************************************************
// 函数名称: ReceiveMsgProc
// 函数说明: 接收消息的线程回调函数
// 作    者: GuiShou
// 时    间: 2019/11/8
// 参    数: Context 上下文
// 返 回 值: void 
//************************************************************
void DealWithMsg(LPVOID Context)
{


	try
	{
		ChatMessageData* msg = (ChatMessageData*)Context;


		BOOL isFriendMsg = FALSE;		//是否是好友消息
		BOOL isImageMessage = FALSE;	//是否是图片消息
		BOOL isRadioMessage = FALSE;	//是否是视频消息
		BOOL isVoiceMessage = FALSE;	//是否是语音消息
		BOOL isBusinessCardMessage = FALSE;	//是否是名片消息
		BOOL isExpressionMessage = FALSE;	//是否是名片消息
		BOOL isLocationMessage = FALSE;	//是否是位置消息
		BOOL isSystemMessage = FALSE;	//是否是系统或红包消息
		BOOL isPos_File_Money_XmlLink = FALSE;			//是否位置 文件 转账和链接消息
		BOOL isFriendRequestMessage = FALSE;	//是否是好友请求消息
		BOOL isOther = FALSE;	//是否是其他消息


		switch (msg->dwtype)
		{
		case 0x01:
			wcscpy_s(msg->sztype, 0x20, L"文字");
			break;
		case 0x03:
			wcscpy_s(msg->sztype, 0x20, L"图片");
			isImageMessage = TRUE;
			break;
		case 0x22:
			wcscpy_s(msg->sztype, 0x20, L"语音");
			isVoiceMessage = TRUE;
			break;
		case 0x25:
			wcscpy_s(msg->sztype, 0x20, L"好友确认");
			isFriendRequestMessage = TRUE;
			break;
		case 0x28:
			wcscpy_s(msg->sztype, 0x20, L"POSSIBLEFRIEND_MSG");
			isOther = TRUE;
			break;
		case 0x2A:
			wcscpy_s(msg->sztype, 0x20, L"名片");
			isBusinessCardMessage = TRUE;
			break;
		case 0x2B:
			wcscpy_s(msg->sztype, 0x20, L"视频");
			isRadioMessage = TRUE;
			break;
		case 0x2F:
			//石头剪刀布
			wcscpy_s(msg->sztype, 0x20, L"表情");
			isExpressionMessage = TRUE;
			break;
		case 0x30:
			wcscpy_s(msg->sztype, 0x20, L"位置");
			isLocationMessage = TRUE;
			break;
		case 0x31:
			//共享实时位置
			//文件
			//转账
			//链接
			//收款
			wcscpy_s(msg->sztype, 0x20, L"共享实时位置、文件、转账、链接");
			isPos_File_Money_XmlLink = TRUE;
			break;
		case 0x32:
			wcscpy_s(msg->sztype, 0x20, L"VOIPMSG");
			isOther = TRUE;
			break;
		case 0x33:
			wcscpy_s(msg->sztype, 0x20, L"微信初始化");
			isOther = TRUE;
			break;
		case 0x34:
			wcscpy_s(msg->sztype, 0x20, L"VOIPNOTIFY");
			isOther = TRUE;
			break;
		case 0x35:
			wcscpy_s(msg->sztype, 0x20, L"VOIPINVITE");
			isOther = TRUE;
			break;
		case 0x3E:
			wcscpy_s(msg->sztype, 0x20, L"小视频");
			isRadioMessage = TRUE;
			break;
		case 0x270F:
			wcscpy_s(msg->sztype, 0x20, L"SYSNOTICE");
			isOther = TRUE;
			break;
		case 0x2710:
			//系统消息
			//红包
			wcscpy_s(msg->sztype, 0x20, L"系统消息");
			isSystemMessage = TRUE;
			break;
		case 0x2712:
			//提现消息
			wcscpy_s(msg->sztype, 0x20, L"提现消息");
			break;
		default:
			break;
		}



		wstring fullmessgaedata(msg->content);	//完整的消息内容
		wchar_t* tempcontent = msg->content;	//完整的消息内容

		//根据微信ID判断是否是好友消息
		wstring wxid_wstr = msg->wxid;
		if (wxid_wstr.find(L"@im.chatroom") != wxid_wstr.npos)
		{
			wcscpy_s(msg->source, 0x400, L"企业微信群消息");
		}
		else if (wxid_wstr.find(L"@chatroom") != wxid_wstr.npos)
		{
			wcscpy_s(msg->source, 0x400, L"群消息");
		}
		else
		{
			wcscpy_s(msg->source, 0x400, L"好友消息");
			isFriendMsg = TRUE;
			wcscpy_s(msg->sendername, 0x100, L"NULL");

		}




		//将微信ID转为微信昵称/群名称 
		wstring transformwxid(msg->wxid);
		swprintf_s(msg->wxname, L"%s", GetNickNameByWxid(transformwxid).c_str());

		//将群发送者微信ID转换为发送着昵称
		if (isFriendMsg == FALSE)
		{
			//根据微信ID获取详细信息这里有问题
			swprintf_s(msg->sendername, L"%s", GetNicknameByWxid(msg->sender));
		}


		//显示消息内容  过滤无法显示的消息 防止奔溃
		if (StrStrW(msg->wxid, L"gh"))
		{
			isFriendMsg = FALSE;

			//如果是聊天机器人发来的消息 并且消息已经发送给机器人
			if ((StrCmpW(msg->wxid, ChatRobotWxID) == 0) && isSendTuLing)
			{
				SendTextMessage(tempwxid, msg->content);
				isSendTuLing = FALSE;
			}
			//如果微信ID为gh_3dfda90e39d6 说明是收款消息
			else if ((StrCmpW(msg->wxid, L"gh_3dfda90e39d6") == 0))
			{
				swprintf_s(msg->content, L"%s", L"微信收款到账");
			}
			else
			{
				//如果微信ID中带有gh 说明是公众号
				swprintf_s(msg->content, L"%s", L"公众号发来推文,请在手机上查看");

			}
		}

		//处理图片消息 
		else if (isImageMessage == TRUE)
		{
			swprintf_s(msg->content, L"%s", L"收到图片消息");
		}
		else if (isRadioMessage == TRUE)
		{
			swprintf_s(msg->content, L"%s", L"收到视频消息,请在手机上查看");
		}
		else if (isVoiceMessage == TRUE)
		{
			swprintf_s(msg->content, L"%s", L"收到语音消息,请在手机上查看");
		}
		else if (isBusinessCardMessage == TRUE)
		{
			//自动添加名片好友
			//AutoAddCardUser(fullmessgaedata);
			swprintf_s(msg->content, L"%s", L"收到名片消息,已自动添加好友");

		}
		else if (isExpressionMessage == TRUE)
		{
			swprintf_s(msg->content, L"%s", L"收到表情消息,请在手机上查看");
		}
		else if (isFriendRequestMessage == TRUE)
		{
			//自动通过好友请求
			AutoAgreeUserRequest(fullmessgaedata);
			swprintf_s(msg->content, L"%s", L"收到好友请求,已自动通过");

		}
		//处理XML文章和自动接收转账消息
		else if (isPos_File_Money_XmlLink == TRUE)
		{
			//判断是否是转账消息
			//判断是否是转账消息
			if (StrStrW(tempcontent, L"<type>2000</type>"))
			{
				//自动收款
				wcscpy_s(msg->sztype, 0x20, L"转账消息");
				AutoCllectMoney(fullmessgaedata, msg->wxid);
				swprintf_s(msg->content, L"%s", L"收到转账消息,已自动收款");
			}
			//<type>5 </type> 包括XML文章和进群链接
			else if (StrStrW(tempcontent, L"<type>5</type>"))
			{
				//邀请入群的链接
				if (fullmessgaedata.find(L"<![CDATA[邀请你加入群聊]]></title>") != wstring::npos&&fullmessgaedata.find(L"<url><![CDATA[") != wstring::npos)
				{
					wcscpy_s(msg->sztype, 0x20, L"群邀请");
					swprintf_s(msg->content, L"%s", L"收到群邀请,请在手机上查看");
				}
				//留言入选通知
				else if (fullmessgaedata.find(L"留言入选通知") != wstring::npos)
				{
					wcscpy_s(msg->sztype, 0x20, L"留言入选");
					swprintf_s(msg->content, L"%s", L"公众号留言入选通知,请在手机上查看");
				}
				else
				{
					//否则 说明是XML文章链接
					wcscpy_s(msg->sztype, 0x20, L"XML文章消息");
					swprintf_s(msg->content, L"%s", L"收到XML文章消息,请在手机上查看");
				}
			}
			//文件消息
			else if (StrStrW(tempcontent, L"<type>6</type>"))
			{
				wcscpy_s(msg->sztype, 0x20, L"文件消息");
				swprintf_s(msg->content, L"%s", L"收到文件 请及时查看");
			}
			//共享实时位置消息
			else if (StrStrW(tempcontent, L"<type>17</type>"))
			{
				wcscpy_s(msg->sztype, 0x20, L"共享实时位置");
				swprintf_s(msg->content, L"%s", L"收到共享实时位置 请在手机上查看");
			}
			//合并转发的聊天记录
			else if (StrStrW(tempcontent, L"的聊天记录</title>"))
			{
				wcscpy_s(msg->sztype, 0x20, L"聊天记录消息");
				swprintf_s(msg->content, L"%s", L"收到合并转发的聊天记录 请在手机上查看");
			}
		}

		else if (isLocationMessage == TRUE)
		{
			swprintf_s(msg->content, L"%s", L"收到位置消息,请在手机上查看");
		}
		else if (isSystemMessage == TRUE)
		{
			//在这里处理加入群聊消息
			if ((StrStrW(tempcontent, L"移出了群聊") || StrStrW(tempcontent, L"加入了群聊")))
			{
				wcscpy_s(msg->content, wcslen(tempcontent) + 1, tempcontent);
			}
			else
			{
				swprintf_s(msg->content, L"%s", L"收到红包或系统消息,请在手机上查看");
			}
		}
		//过滤完所有消息之后
		else
		{
			//判断消息长度 如果长度超过就不显示
			if (wcslen(tempcontent) > 200)
			{
				swprintf_s(msg->content, L"%s", L"消息内容过长 已经过滤");
			}
		}


		//这里处理自动聊天
		if (isFriendMsg == TRUE && g_AutoChat == TRUE && isSendTuLing == FALSE)
		{

			//保存一下微信ID
			wcscpy_s(tempwxid, wcslen(msg->wxid) + 1, msg->wxid);
			//拿到消息内容 发给机器人
			SendTextMessage((wchar_t*)ChatRobotWxID, msg->content);
			isSendTuLing = TRUE;
		}


		//发送到控制端
		HWND hWnd = FindWindow(NULL, TEXT("微信助手"));
		if (hWnd == NULL)
		{
			OutputDebugStringA("未查找到微信助手窗口");
			return;
		}

		COPYDATASTRUCT chatmsg;
		chatmsg.dwData = WM_ShowChatRecord;//保存一个数值, 可以用来作标志等
		chatmsg.cbData = sizeof(ChatMessageData);// strlen(szSendBuf);//待发送的数据的长
		chatmsg.lpData = msg;// szSendBuf;//待发送的数据的起始地址(可以为NULL)
		SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&chatmsg);

		delete msg;
	}
	catch (...)
	{
		OutputDebugStringA("聊天记录出异常了");
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
void __stdcall SendWxMessage(DWORD r_eax)
{
	if (IsBadReadPtr((void*)r_eax, 4) || IsBadReadPtr((void*)(r_eax + MsgTypeOffset), 4) || IsBadReadPtr((void*)(r_eax + MsgContentOffset), 4) || IsBadReadPtr((void*)(r_eax + WxidOffset), 4) || IsBadReadPtr((void*)(r_eax + GroupMsgSenderOffset), 4))
	{
		return;
	}
	try
	{
		ChatMessageData* msg = new ChatMessageData;
		//取出消息类型
		msg->dwtype = *((DWORD*)(r_eax + MsgTypeOffset));
	
		//取出消息内容
		LPVOID pContent = *((LPVOID *)(r_eax + MsgContentOffset));
		swprintf_s(msg->content, L"%s", (wchar_t*)pContent);
	
	
		//取出微信ID/群ID
		LPVOID pWxid = *((LPVOID *)(r_eax + WxidOffset));
		swprintf_s(msg->wxid, L"%s", (wchar_t*)pWxid);
	
		if (StrStrW(msg->wxid, L"gh_"))
		{
			return;
		}
	
	
	
		//取出消息发送者
		LPVOID pSender = *((LPVOID *)(r_eax + GroupMsgSenderOffset));
		swprintf_s(msg->sender, L"%s", (wchar_t*)pSender);
		

		//取出消息发送者
		LPVOID pSource = *((LPVOID *)(r_eax + MsgSourceOffset));
		swprintf_s(msg->source, L"%s", (wchar_t*)pSource);
	
		//创建线程处理消息
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DealWithMsg, msg, 0, NULL);
		CloseHandle(hThread);
	}
	catch (...)
	{
		OutputDebugStringA("接收消息异常了....");
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
std::wstring GetMsgByAddress(DWORD memAddress)
{
	wstring tmp;
	DWORD msgLength = *(DWORD*)(memAddress + 4);
	if (msgLength > 0) {
		WCHAR* msg = new WCHAR[msgLength + 1]{ 0 };
		wmemcpy_s(msg, msgLength + 1, (WCHAR*)(*(DWORD*)memAddress), msgLength + 1);
		tmp = msg;
		delete[]msg;
	}
	return  tmp;
}


