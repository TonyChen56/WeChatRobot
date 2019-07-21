// CMain.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CMain.h"
#include "afxdialogex.h"
#include "CChatRecords.h"
#include "CFriendList.h"
#include "CFunctions.h"
#include "CPay.h"
#include "CAboutAuthor.h"


//好友信息
struct UserInfo
{
	wchar_t UserId[80];
	wchar_t UserNumber[80];
	wchar_t UserRemark[80];
	wchar_t UserNickName[80];
};


//消息结构体
struct Message
{
	wchar_t type[10];		//消息类型
	wchar_t source[20];		//消息来源
	wchar_t wxid[40];		//微信ID/群ID
	wchar_t msgSender[40];	//消息发送者
	wchar_t content[200];	//消息内容
};



IMPLEMENT_DYNAMIC(CMain, CDialogEx)

CMain::CMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN, pParent)
{

}

CMain::~CMain()
{
}

void CMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_MyTable);
}


BEGIN_MESSAGE_MAP(CMain, CDialogEx)
	ON_COMMAND(ID_32776, &CMain::OnWxLogout)
	ON_WM_COPYDATA()
	ON_COMMAND(ID_32779, &CMain::OnPayAuthor)
	ON_COMMAND(ID_32778, &CMain::OnAboutAuthor)
END_MESSAGE_MAP()


// CMain 消息处理程序


BOOL CMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	TCHAR Name[3][5] = { L"好友列表", L"聊天记录", L"功能大全" };
	for (int i = 0; i < 3; i++)
	{
		m_MyTable.InsertItem(i, Name[i]);
	}

	//给子窗口指针赋值

	m_MyTable.m_Dia[0] = new CFriendList();
	m_MyTable.m_Dia[1] = new CChatRecords();
	m_MyTable.m_Dia[2] = new CFunctions();

	//创建子窗口
	UINT DiaIds[3] = { IDD_FRIEND_LIST, IDD_CHAT_RECORDS, IDD_FUNCTIONS};
	for (int i = 0; i < 3; i++)
	{
		m_MyTable.m_Dia[i]->Create(DiaIds[i], &m_MyTable);
	}


	//控制两个窗口的大小
	CRect rc;
	m_MyTable.GetClientRect(rc);
	rc.DeflateRect(2, 23, 2, 2);
	for (int i = 0; i < 3; i++)
	{
		m_MyTable.m_Dia[i]->MoveWindow(rc);
	}


	//显示第一个子窗口
	m_MyTable.m_Dia[0]->ShowWindow(SW_SHOW);
	for (int i = 1; i < 3; i++)
	{
		m_MyTable.m_Dia[i]->ShowWindow(SW_HIDE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



//************************************************************
// 函数名称: OnWxLogout
// 函数说明: 响应退出微信菜单
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: void
// 返 回 值: void
//***********************************************************
void CMain::OnWxLogout()
{
	//查找窗口
	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT logout;
	logout.dwData = WM_Logout;
	logout.cbData = 0;
	logout.lpData = NULL;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&logout);
}


//************************************************************
// 函数名称: OnCopyData
// 函数说明: 响应CopyData消息
// 作    者: GuiShou
// 时    间: 2019/7/5
// 参    数: CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct
// 返 回 值: BOOL
//***********************************************************
BOOL CMain::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//显示好友列表
	if (pCopyDataStruct->dwData== WM_GetFriendList)
	{
		UserInfo *user = new UserInfo;
		user = (UserInfo*)pCopyDataStruct->lpData;

		//将消息发送给子窗口
		m_MyTable.m_Dia[0]->SendMessage(WM_ShowFriendList, (WPARAM)user, NULL);
	}
	//显示聊天记录
	else if(pCopyDataStruct->dwData == WM_ShowChatRecord)
	{
		Message *msg = new Message;
		msg = (Message*)pCopyDataStruct->lpData;

		//将消息发送给子窗口
		m_MyTable.m_Dia[1]->SendMessage(WM_ShowMessage, (WPARAM)msg, NULL);
	}
	

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


//************************************************************
// 函数名称: OnPayAuthor
// 函数说明: 响应打赏作者菜单
// 作    者: GuiShou
// 时    间: 2019/7/14
// 参    数: void
// 返 回 值: void
//***********************************************************
void CMain::OnPayAuthor()
{
	CPay pay;
	pay.DoModal();
}


//************************************************************
// 函数名称: OnAboutAuthor
// 函数说明: 响应关于作者菜单
// 作    者: GuiShou
// 时    间: 2019/7/14
// 参    数: void
// 返 回 值: void
//***********************************************************
void CMain::OnAboutAuthor()
{
	CAboutAuthor about;
	about.DoModal();
}
