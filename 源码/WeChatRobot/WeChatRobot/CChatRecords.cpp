// CChatRecords.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CChatRecords.h"
#include "afxdialogex.h"

DWORD g_index=0;

//消息结构体
struct Message
{
	wchar_t type[10];		//消息类型
	wchar_t source[20];		//消息来源
	wchar_t wxid[40];		//微信ID/群ID
	wchar_t msgSender[40];	//消息发送者
	wchar_t content[200];	//消息内容
};


// CChatRecords 对话框

IMPLEMENT_DYNAMIC(CChatRecords, CDialogEx)

CChatRecords::CChatRecords(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_RECORDS, pParent)
{

}

CChatRecords::~CChatRecords()
{
}

void CChatRecords::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ChatRecord);
}


BEGIN_MESSAGE_MAP(CChatRecords, CDialogEx)
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_ShowMessage, &CChatRecords::OnShowmessage)
END_MESSAGE_MAP()


// CChatRecords 消息处理程序


BOOL CChatRecords::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ChatRecord.InsertColumn(0, L"消息类型", 0, 100);
	m_ChatRecord.InsertColumn(1, L"消息来源", 0, 100);
	m_ChatRecord.InsertColumn(2, L"微信ID/群ID", 0, 150);
	m_ChatRecord.InsertColumn(3, L"群发送者", 0, 150);
	m_ChatRecord.InsertColumn(4, L"消息内容", 0, 310);
	m_ChatRecord.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CChatRecords::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


//************************************************************
// 函数名称: OnShowmessage
// 函数说明: 响应Showmessage消息 处理父窗口发过来的消息
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: WPARAM wParam, LPARAM lParam
// 返 回 值: BOOL
//***********************************************************
afx_msg LRESULT CChatRecords::OnShowmessage(WPARAM wParam, LPARAM lParam)
{
	//取数据
	Message *msg = (Message*)wParam;

	//显示到控件
	m_ChatRecord.InsertItem(g_index, msg->type);
	m_ChatRecord.SetItemText(g_index, 1, msg->source);
	m_ChatRecord.SetItemText(g_index, 2, msg->wxid);
	m_ChatRecord.SetItemText(g_index, 3, msg->msgSender);
	m_ChatRecord.SetItemText(g_index, 4, msg->content);
	return 0;
}
