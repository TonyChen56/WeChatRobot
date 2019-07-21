// CChatRoomMember.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CChatRoomMember.h"
#include "afxdialogex.h"


struct UserInfo
{
	wchar_t UserId[50];
	wchar_t UserNumber[50];
	wchar_t UserNickName[50];
};


// CChatRoomMember 对话框

IMPLEMENT_DYNAMIC(CChatRoomMember, CDialogEx)

CChatRoomMember::CChatRoomMember(LPCTSTR TempWxid, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATROOM_MEMBER, pParent), m_ChatRoomWxid(TempWxid)
{

}

CChatRoomMember::~CChatRoomMember()
{
}

void CChatRoomMember::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ChatRoomMembers);
}


BEGIN_MESSAGE_MAP(CChatRoomMember, CDialogEx)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CChatRoomMember 消息处理程序


BOOL CChatRoomMember::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ChatRoomMembers.InsertColumn(0, L"序号", 0, 100);
	m_ChatRoomMembers.InsertColumn(1, L"微信ID", 0, 200);
	m_ChatRoomMembers.InsertColumn(2, L"微信号", 0, 200);
	m_ChatRoomMembers.InsertColumn(3, L"昵称", 0, 200);	
	m_ChatRoomMembers.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//拷贝群成员微信ID
	wchar_t memberwxid[50] = { 0 };
	wcscpy_s(memberwxid, wcslen(m_ChatRoomWxid) + 1, m_ChatRoomWxid);

	//查找窗口
	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT show_members;
	show_members.dwData = WM_ShowChatRoomMembers;
	show_members.cbData = (wcslen(memberwxid) + 1) * 2;
	show_members.lpData = memberwxid;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&show_members);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



BOOL CChatRoomMember::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	static DWORD dwIndex = 0;
	if (pCopyDataStruct->dwData == WM_ShowChatRoomMembers)
	{
		UserInfo *user = new UserInfo;
		user = (UserInfo*)pCopyDataStruct->lpData;
	
		CString index;
		index.Format(L"%d", dwIndex+1);
		//显示序号
		m_ChatRoomMembers.InsertItem(dwIndex, index);
		//显示微信ID
		m_ChatRoomMembers.SetItemText(dwIndex, 1, user->UserId);
		//显示微信号
		m_ChatRoomMembers.SetItemText(dwIndex, 2, user->UserNumber);
		//显示微信昵称
		m_ChatRoomMembers.SetItemText(dwIndex, 3, user->UserNickName);
		dwIndex++;
	}
	else if (pCopyDataStruct->dwData == WM_ShowChatRoomMembersDone)
	{
		//把序号清零
		dwIndex = 0;
	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
