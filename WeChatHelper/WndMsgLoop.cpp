#include "stdafx.h"
#include "WndMsgLoop.h"
#include "InitWeChat.h"
#include "Login.h"
#include "MainWindow.h"
#include "FriendList.h"
#include "ChatRecord.h"
#include "Function.h"
#include "ChatRoomOperate.h"
#include "CAutoFunction.h"
#include "SelfInformation.h"
#include <stdio.h>

extern BOOL g_AutoChat;					//自动聊天



//************************************************************
// 函数名称: RegisterWindow
// 函数说明: 初始化窗口 
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: HMODULE hModule 句柄
// 返 回 值: void 
//************************************************************
void InitWindow(HMODULE hModule)
{
	//检查当前微信版本
	if (IsWxVersionValid())
	{
		//获取WeChatWin的基址
		DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	
		//检测微信是否登陆
		DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset;
		if (*(DWORD*)dwIsLogin == 0)	//等于0说明微信未登录
		{
			//开线程持续检测微信登陆状态
			HANDLE hThread= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CheckIsLogin, 0, 0, NULL);
			CloseHandle(hThread);

			//HOOK获取好友列表的call
			HookGetFriendList();
			
			//HOOK接收消息
			HookChatRecord();
			
			//防撤回
			AntiRevoke();
			
			//HOOK提取表情 
			//HookExtractExpression();

			//注册窗口
			RegisterWindow(hModule);
		}
		else
		{
			//如果微信已经登陆 发送消息给客户端
			HWND hLogin = FindWindow(NULL, L"Login");
			if (hLogin == NULL)
			{
				OutputDebugStringA("未查找到Login窗口");
				return;
			}
			COPYDATASTRUCT login_msg;
			login_msg.dwData = WM_AlreadyLogin;
			login_msg.lpData = NULL;
			login_msg.cbData = 0;
			//发送消息给控制端
			SendMessage(hLogin, WM_COPYDATA, (WPARAM)hLogin, (LPARAM)&login_msg);
		}
	}
	else
	{
		MessageBoxA(NULL, "当前微信版本不匹配，请下载WeChat 3.2.1.154", "错误", MB_OK);
	}

}


//************************************************************
// 函数名称: RegisterWindow
// 函数说明: 注册窗口
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: HMODULE hModule 窗口句柄
// 返 回 值: void 
//************************************************************

void RegisterWindow(HMODULE hModule)
{
	//1  设计一个窗口类
	WNDCLASS wnd;
	wnd.style = CS_VREDRAW | CS_HREDRAW;//风格
	wnd.lpfnWndProc = WndProc;//窗口回调函数指针.
	wnd.cbClsExtra = NULL;
	wnd.cbWndExtra = NULL;
	wnd.hInstance = hModule;
	wnd.hIcon = NULL;
	wnd.hCursor = NULL;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = TEXT("WeChatHelper");
	//2  注册窗口类
	RegisterClass(&wnd);
	//3  创建窗口
	HWND hWnd = CreateWindow(
		TEXT("WeChatHelper"),  //窗口类名
		TEXT("WeChatHelper"),//窗口名
		WS_OVERLAPPEDWINDOW,//窗口风格
		10, 10, 500, 300, //窗口位置
		NULL,             //父窗口句柄
		NULL,             //菜单句柄
		hModule,        //实例句柄
		NULL              //传递WM_CREATE消息时的附加参数
	);
	//4  更新显示窗口
	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);
	//5  消息循环（消息泵）
	MSG  msg = {};
	//   5.1获取消息
	while (GetMessage(&msg, 0, 0, 0))
	{
		//   5.2翻译消息
		TranslateMessage(&msg);
		//   5.3转发到消息回调函数
		DispatchMessage(&msg);
	}
}


//************************************************************
// 函数名称: WndProc
// 函数说明: 回调函数 用于和控制端通信 
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam
// 返 回 值: LRESULT 
//************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_COPYDATA)
	{
		COPYDATASTRUCT *pCopyData = (COPYDATASTRUCT*)lParam;
		//接收通用消息结构体
		MessageUnion *msg = (MessageUnion*)pCopyData->lpData;
		switch (pCopyData->dwData)
		{
		//显示二维码
		case WM_ShowQrPicture:
		{
			GotoQrCode();
			HookQrCode();
		}
		break;
		//退出微信
		case WM_Logout:
		{
			LogoutWeChat();
		}
		break;
		//发送文本消息
		case WM_SendTextMessage:
		{
			SendTextMessage(msg->genericmsg.msgdata1, msg->genericmsg.msgdata2);
			
		}
		break;
		//发送文件消息
		case WM_SendFileMessage:
		{
			SendFileMessage(msg->genericmsg.msgdata1, msg->genericmsg.msgdata2);
		}
		break;
		//发送图片消息
		case WM_SendImageMessage:
		{
			SendImageMessage(msg->genericmsg.msgdata1, msg->genericmsg.msgdata2);
		}
		break;
		//获取个人信息
		case WM_GetInformation:
		{
			GetInformation();
		}
		break;
		//发送群公告
		case WM_SetRoomAnnouncement:
		{
			SetWxRoomAnnouncement(msg->genericmsg.msgdata1, msg->genericmsg.msgdata2);
		}
		break;
		//删除好友
		case WM_DeleteUser:
		{
			DeleteUser((wchar_t*)pCopyData->lpData);
		}
		break;
		//退出群聊
		case WM_QuitChatRoom:
		{
			QuitChatRoom((wchar_t*)pCopyData->lpData);
		}
		break;
		//添加群成员
		case WM_AddGroupMember:
		{
			AddGroupMember(msg->genericmsg.msgdata1, msg->genericmsg.msgdata2);
		}
		break;
		//发送名片
		case WM_SendXmlCard:
		{
			SendXmlCard(msg->xmlcardmsg.RecverWxid, msg->xmlcardmsg.SendWxid, msg->xmlcardmsg.NickName);
		}
		break;
		//显示群成员
		case WM_ShowChatRoomMembers:
		{
			ShowChatRoomUser((wchar_t*)pCopyData->lpData);
		}
		break;
		//添加好友
		case WM_AddUser:
		{
			AddWxUser(msg->genericmsg.msgdata1, msg->genericmsg.msgdata2);
		}
		break;
		//修改群名称
		case WM_SetRoomName:
		{
			SetRoomName(msg->genericmsg.msgdata1, msg->genericmsg.msgdata2);

		}
		break;
		//自动聊天
		case WM_AutoChat:
		{
			g_AutoChat = TRUE;
		}
		break;
		//取消自动聊天
		case WM_CancleAutoChat:
		{
			g_AutoChat = FALSE;
		}
		break;
		//发送艾特消息
		case WM_SendAtMsg:
		{
			SendRoomAtMsg(msg->atmsg.chatroomid, msg->atmsg.membermsgdata1, msg->atmsg.membernickname, msg->atmsg.msgmsgdata2);
		}
		break;
		//删除群成员
		case WM_DelRoomMember:
		{
			DelRoomMember(msg->genericmsg.msgdata1, msg->genericmsg.msgdata2);
		}
		break;
		//打开URL
		case WM_OpenUrl:
		{
			OpenUrl((wchar_t*)pCopyData->lpData);
		}
		break;
		default:
			break;
		}
	}

	return DefWindowProc(hWnd, Message, wParam, lParam);
}




