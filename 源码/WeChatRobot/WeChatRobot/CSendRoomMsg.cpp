// CSendRoomMsg.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CSendRoomMsg.h"
#include "afxdialogex.h"


// CSendRoomMsg 对话框

IMPLEMENT_DYNAMIC(CSendRoomMsg, CDialogEx)

CSendRoomMsg::CSendRoomMsg(LPCTSTR TempWxid,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEND_ROOM_MSG, pParent), m_ChatRoomWxid(TempWxid)
	, m_chatroommmsg(_T(""))
{

}

CSendRoomMsg::~CSendRoomMsg()
{
}

void CSendRoomMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_chatroommmsg);
}


BEGIN_MESSAGE_MAP(CSendRoomMsg, CDialogEx)
	ON_BN_CLICKED(IDC_SendChatRoomMsg, &CSendRoomMsg::OnBnClickedSendchatroommsg)
END_MESSAGE_MAP()





//************************************************************
// 函数名称: OnBnClickedSendchatroommsg
// 函数说明: 响应发送按钮
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CSendRoomMsg::OnBnClickedSendchatroommsg()
{
	//同步控件数据到变量
	UpdateData(TRUE);

	if (m_chatroommmsg=="")
	{
		MessageBoxW(L"消息不能为空", L"Tip", 0);
		return;
	}

	//消息结构体
	struct MessageStruct
	{
		wchar_t wxid[40];
		wchar_t content[MAX_PATH];
	};


	//填充数据到结构体
	MessageStruct *message = new MessageStruct;

	wcscpy_s(message->wxid, wcslen(m_ChatRoomWxid) + 1, m_ChatRoomWxid);
	wcscpy_s(message->content, wcslen(m_chatroommmsg) + 1 , m_chatroommmsg);

	//查找窗口
	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT MessageData;


	MessageData.dwData = WM_SendTextMessage;
	MessageData.cbData = sizeof(MessageStruct);
	MessageData.lpData = message;

	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&MessageData);

	//清空文本
	m_chatroommmsg = "";

	UpdateData(FALSE);
}
