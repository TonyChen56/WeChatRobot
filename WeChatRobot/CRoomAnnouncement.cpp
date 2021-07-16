// CRoomAnnouncement.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CRoomAnnouncement.h"
#include "afxdialogex.h"


// CRoomAnnouncement 对话框

IMPLEMENT_DYNAMIC(CRoomAnnouncement, CDialogEx)

CRoomAnnouncement::CRoomAnnouncement(LPCTSTR TempWxid, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROOMANNOUNCE, pParent), m_ChatRoomWxid(TempWxid)
	, m_Announcement(_T(""))
{

}

CRoomAnnouncement::~CRoomAnnouncement()
{
}

void CRoomAnnouncement::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Announcement);
}


BEGIN_MESSAGE_MAP(CRoomAnnouncement, CDialogEx)
	ON_BN_CLICKED(IDC_SendRoomAnnouncement, &CRoomAnnouncement::OnBnClickedSendroomannouncement)
END_MESSAGE_MAP()


// CRoomAnnouncement 消息处理程序


//************************************************************
// 函数名称: OnBnClickedSendroomannouncement
// 函数说明: 响应发送群公告按钮
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void
//***********************************************************
void CRoomAnnouncement::OnBnClickedSendroomannouncement()
{
	//将控件的值更新到变量
	UpdateData(TRUE);

	//构造发送的数据
	MessageStruct* pMessage = new MessageStruct(m_ChatRoomWxid, m_Announcement);

	//发送到服务端
	//查找窗口
	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT chatroommsg;
	chatroommsg.dwData = WM_SetRoomAnnouncement;
	chatroommsg.cbData = sizeof(MessageStruct);
	chatroommsg.lpData = pMessage;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&chatroommsg);

	delete pMessage;
	m_Announcement = "";
	UpdateData(FALSE);
}
