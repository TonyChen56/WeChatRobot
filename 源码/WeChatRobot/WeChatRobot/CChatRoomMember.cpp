// CChatRoomMember.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CChatRoomMember.h"
#include "afxdialogex.h"
#include "CSendChatRoomAt.h"

//群成员的信息结构体
struct UserInfo
{
	wchar_t UserId[50];
	wchar_t UserNumber[50];
	wchar_t UserNickName[50];
};

wchar_t memberwxid[50] = { 0 };			//群成员的微信ID
wchar_t membernickname[50] = { 0 };		//群成员的微信昵称


int nSelected = 0;	//选中行的行号 

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
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CChatRoomMember::OnClickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CChatRoomMember::OnRclickList1)
	ON_COMMAND(ID_32795, &CChatRoomMember::OnSendChatRoomAt)
	ON_COMMAND(ID_32796, &CChatRoomMember::OnCopyWxid)
	ON_COMMAND(ID_32797, &CChatRoomMember::OnDelRoomMember)
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

//************************************************************
// 函数名称: OnRclickFriendlist
// 函数说明: 响应List控件的左键点击消息 
// 作    者: GuiShou
// 时    间: 2019/7/23
// 参    数: pNMHDR pResult
// 返 回 值: void
//***********************************************************
void CChatRoomMember::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	//拿到微信ID和微信昵称
	memcpy(memberwxid, m_ChatRoomMembers.GetItemText(pNMItemActivate->iItem, 1), 40);
	memcpy(membernickname, m_ChatRoomMembers.GetItemText(pNMItemActivate->iItem, 3), 40);


	POSITION p = m_ChatRoomMembers.GetFirstSelectedItemPosition(); //获取选中行位置
	nSelected = m_ChatRoomMembers.GetNextSelectedItem(p); //获取选中行的索引

	*pResult = 0;
}

//************************************************************
// 函数名称: OnRclickList1
// 函数说明: 响应List控件的右键点击消息 
// 作    者: GuiShou
// 时    间: 2019/7/23
// 参    数: pNMHDR pResult
// 返 回 值: void
//***********************************************************
void CChatRoomMember::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//弹出好友相关的菜单
	CMenu m_Menu, *tMenu;
	m_Menu.LoadMenu(IDR_MENU2);

	//拿到第0个下拉菜单(菜单可能有很多列 这个函数是拿到第几列)
	tMenu = m_Menu.GetSubMenu(2);

	//获取鼠标位置
	CPoint pt;
	GetCursorPos(&pt);

	//弹出菜单
	TrackPopupMenu(tMenu->m_hMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, m_hWnd, 0);
	*pResult = 0;
}



//************************************************************
// 函数名称: OnSendChatRoomAt
// 函数说明: 发送艾特消息
// 作    者: GuiShou
// 时    间: 2019/7/23
// 参    数: void
// 返 回 值: void
//***********************************************************
void CChatRoomMember::OnSendChatRoomAt()
{
	CSendChatRoomAt *sendat = new CSendChatRoomAt(memberwxid, membernickname, m_ChatRoomWxid);
	sendat->DoModal();
}


//************************************************************
// 函数名称: OnCopyWxid
// 函数说明: 复制微信ID
// 作    者: GuiShou
// 时    间: 2019/7/25
// 参    数: void
// 返 回 值: void
//***********************************************************
void CChatRoomMember::OnCopyWxid()
{
	CString strText = memberwxid;

	//复制剪切板
	if (!strText.IsEmpty())
	{
		if (OpenClipboard())
		{
			TCHAR* pszData;
			HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, (strText.GetLength() + 1) * sizeof(TCHAR));
			if (hClipboardData)
			{
				pszData = (TCHAR*)GlobalLock(hClipboardData);
				_tcscpy_s(pszData, wcslen(strText) + 1, strText);
				GlobalUnlock(hClipboardData);
				SetClipboardData(CF_UNICODETEXT, hClipboardData);//根据相应的数据选择第一个参数，（CF_TEXT）  
			}
			CloseClipboard();
		}
	}
}

//************************************************************
// 函数名称: OnDelRoomMember
// 函数说明: 删除群成员
// 作    者: GuiShou
// 时    间: 2019/7/26
// 参    数: void
// 返 回 值: void
//***********************************************************
void CChatRoomMember::OnDelRoomMember()
{
	if (MessageBoxA(NULL, "是否删除群成员", "Tip", MB_YESNO))
	{
		struct DelMemberStruct
		{
			wchar_t roomid[50];
			wchar_t memberwxid[50];
		};
		DelMemberStruct* pMember = new DelMemberStruct;
		wcscpy_s(pMember->roomid, wcslen(m_ChatRoomWxid) + 1, m_ChatRoomWxid);
		wcscpy_s(pMember->memberwxid, wcslen(memberwxid) + 1, memberwxid);


		CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
		COPYDATASTRUCT delmemberdata;
		delmemberdata.dwData = WM_DelRoomMember;
		delmemberdata.cbData = sizeof(DelMemberStruct);
		delmemberdata.lpData = pMember;
		//发送消息
		pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&delmemberdata);

		//删除选中行
		m_ChatRoomMembers.DeleteItem(nSelected); //根据索引删除
	}
	
}
