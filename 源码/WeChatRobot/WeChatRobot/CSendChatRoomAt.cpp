// CSendChatRoomAt.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CSendChatRoomAt.h"
#include "afxdialogex.h"


// CSendChatRoomAt 对话框

IMPLEMENT_DYNAMIC(CSendChatRoomAt, CDialogEx)

CSendChatRoomAt::CSendChatRoomAt(LPCTSTR TempWxid, LPCTSTR TempNickName, LPCTSTR TempChatRoomid, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SENDAT, pParent), m_MemberWxid(TempWxid), m_MemberNickName(TempNickName), m_ChatRoomid(TempChatRoomid)
	, m_msg(_T(""))
{

}

CSendChatRoomAt::~CSendChatRoomAt()
{
}

void CSendChatRoomAt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_msg);
}


BEGIN_MESSAGE_MAP(CSendChatRoomAt, CDialogEx)
	ON_BN_CLICKED(IDC_SendAt, &CSendChatRoomAt::OnBnClickedSendat)
END_MESSAGE_MAP()


// CSendChatRoomAt 消息处理程序


//************************************************************
// 函数名称: OnBnClickedSendat
// 函数说明: 响应发送按钮
// 作    者: GuiShou
// 时    间: 2019/7/23
// 参    数: void
// 返 回 值: void
//***********************************************************
void CSendChatRoomAt::OnBnClickedSendat()
{
	struct AtMsg
	{
		wchar_t chatroomid[50] = { 0 };
		wchar_t memberwxid[50] = { 0 };
		wchar_t membernickname[50] = { 0 };
		wchar_t msgcontent[100] = { 0 };
	};
	UpdateData(TRUE);
	AtMsg* msg = new AtMsg;
	wcscpy_s(msg->chatroomid, wcslen(m_ChatRoomid) + 1, m_ChatRoomid);
	wcscpy_s(msg->memberwxid, wcslen(m_MemberWxid) + 1, m_MemberWxid);
	wcscpy_s(msg->membernickname, wcslen(m_MemberNickName) + 1, m_MemberNickName);
	wcscpy_s(msg->msgcontent, wcslen(m_msg) + 1, m_msg);


	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT atmsgdata;
	atmsgdata.dwData = WM_SendAtMsg;
	atmsgdata.cbData = sizeof(AtMsg);
	atmsgdata.lpData = msg;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&atmsgdata);

	m_msg = "";
	UpdateData(FALSE);
}

