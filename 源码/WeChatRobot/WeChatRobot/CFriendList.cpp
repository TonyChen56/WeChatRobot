// CFriendList.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CFriendList.h"
#include "afxdialogex.h"
#include "CSendMsg.h"
#include "CRoomAnnouncement.h"
#include "CAddChatRoomMember.h"
#include "CSendRoomMsg.h"
#include "CSendXmlCard.h"
#include "CChatRoomMember.h"
#include "CSetRoomName.h"


struct UserInfo
{
	wchar_t UserId[80];
	wchar_t UserNumber[80];
	wchar_t UserRemark[80];
	wchar_t UserNickName[80];
};

DWORD dwIndex = 0;
wchar_t wxid[40] = { 0 };	//鼠标左键点击时拿到的微信ID



BOOL isAttentTuLing = FALSE;

IMPLEMENT_DYNAMIC(CFriendList, CDialogEx)

CFriendList::CFriendList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FRIEND_LIST, pParent)
{

}

CFriendList::~CFriendList()
{
}

void CFriendList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FRIENDLIST, m_FriendList);
}


BEGIN_MESSAGE_MAP(CFriendList, CDialogEx)
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_ShowFriendList, &CFriendList::OnShowfriendlist)
	ON_NOTIFY(NM_RCLICK, IDC_FRIENDLIST, &CFriendList::OnRclickFriendlist)
	ON_NOTIFY(NM_CLICK, IDC_FRIENDLIST, &CFriendList::OnClickFriendlist)
	ON_COMMAND(ID_32780, &CFriendList::OnSendMsg)
	ON_COMMAND(ID_32784, &CFriendList::OnSetRoomAnnouncement)
	ON_COMMAND(ID_32782, &CFriendList::OnCopyWxid)
	ON_COMMAND(ID_32785, &CFriendList::OnCopyChatRoomWxid)
	ON_COMMAND(ID_32781, &CFriendList::OnDeleteUser)
	ON_COMMAND(ID_32786, &CFriendList::OnQuitChatRoom)
	ON_COMMAND(ID_32787, &CFriendList::OnAddGroupMember)
	ON_COMMAND(ID_32783, &CFriendList::OnSendRoomMessage)
	ON_COMMAND(ID_32788, &CFriendList::OnSendXmlCard)
	ON_COMMAND(ID_32789, &CFriendList::OnShowChatRoomMember)
	ON_COMMAND(ID_32790, &CFriendList::OnSetRoomName)
END_MESSAGE_MAP()


// CFriendList 消息处理程序


BOOL CFriendList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_FriendList.InsertColumn(0, L"序号", 0, 50);
	m_FriendList.InsertColumn(1, L"微信ID", 0, 200);
	m_FriendList.InsertColumn(2, L"微信号", 0, 200);
	m_FriendList.InsertColumn(3, L"昵称", 0, 200);
	m_FriendList.InsertColumn(4, L"备注", 0, 200);

	m_FriendList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//************************************************************
// 函数名称: OnCopyData
// 函数说明: 响应CopyData消息
// 作    者: GuiShou
// 时    间: 2019/7/5
// 参    数: CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct
// 返 回 值: BOOL
//***********************************************************
BOOL CFriendList::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}



//************************************************************
// 函数名称: OnShowfriendlist
// 函数说明: 响应Showfriendlist消息 处理父窗口发过来的联系人
// 作    者: GuiShou
// 时    间: 2019/7/5
// 参    数: WPARAM wParam, LPARAM lParam
// 返 回 值: BOOL
//***********************************************************
afx_msg LRESULT CFriendList::OnShowfriendlist(WPARAM wParam, LPARAM lParam)
{
	//取数据
	UserInfo* userinfo = (UserInfo*)wParam;
	CString index;
	index.Format(L"%d",dwIndex+1);
	//显示到List控件
	//检测联系人列表中是否有图灵机器人
	if (StrCmpW(userinfo->UserId,L"gh_ab370b2e4b62")==0)
	{
		isAttentTuLing = TRUE;
	}

	m_FriendList.InsertItem(dwIndex, index);
	m_FriendList.SetItemText(dwIndex, 1, userinfo->UserId);
	m_FriendList.SetItemText(dwIndex, 2, userinfo->UserNumber);
	m_FriendList.SetItemText(dwIndex, 3, userinfo->UserNickName);
	m_FriendList.SetItemText(dwIndex, 4, userinfo->UserRemark);
	dwIndex++;
	return 0;
}


//************************************************************
// 函数名称: OnRclickFriendlist
// 函数说明: 响应List控件的右键点击消息 
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: WPARAM wParam, LPARAM lParam
// 返 回 值: void
//***********************************************************
void CFriendList::OnRclickFriendlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	//判断选中的是群ID还是个人微信ID
	if (StrStrW(wxid, L"chatroom") == NULL)
	{
		//弹出好友相关的菜单
		CMenu m_Menu, *tMenu;
		m_Menu.LoadMenu(IDR_MENU2);

		//拿到第0个下拉菜单(菜单可能有很多列 这个函数是拿到第几列)
		tMenu = m_Menu.GetSubMenu(0);

		//获取鼠标位置
		CPoint pt;
		GetCursorPos(&pt);

		//弹出菜单
		TrackPopupMenu(tMenu->m_hMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, m_hWnd, 0);

	}
	else
	{
		//弹出群相关的菜单
		CMenu m_Menu, *tMenu;
		m_Menu.LoadMenu(IDR_MENU2);

		//拿到第0个下拉菜单(菜单可能有很多列 这个函数是拿到第几列)
		tMenu = m_Menu.GetSubMenu(1);

		//获取鼠标位置
		CPoint pt;
		GetCursorPos(&pt);

		//弹出菜单
		TrackPopupMenu(tMenu->m_hMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, m_hWnd, 0);
	}
	

	*pResult = 0;
}


//************************************************************
// 函数名称: OnRclickFriendlist
// 函数说明: 响应List控件的左键点击消息 
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: pNMHDR pResult
// 返 回 值: void
//***********************************************************
void CFriendList::OnClickFriendlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//拿到微信ID
	memcpy(wxid, m_FriendList.GetItemText(pNMItemActivate->iItem, 1), 40);
	*pResult = 0;
}


//************************************************************
// 函数名称: OnSendMsg
// 函数说明: 响应发送消息菜单
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnSendMsg()
{
	//利用构造函数把选中的微信ID传过去
	CSendMsg *pSendmsg=new CSendMsg(wxid);
	pSendmsg->DoModal();
}


//************************************************************
// 函数名称: OnSendMsg
// 函数说明: 响应发送群公告菜单
// 作    者: GuiShou
// 时    间: 2019/7/7
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnSetRoomAnnouncement()
{
	//利用构造函数把选中的群ID传过去
	CRoomAnnouncement* pRoom = new CRoomAnnouncement(wxid);
	pRoom->DoModal();
}


//************************************************************
// 函数名称: OnCopyWxid
// 函数说明: 响应复制微信ID菜单
// 作    者: GuiShou
// 时    间: 2019/7/8
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnCopyWxid()
{
	CString strText= wxid;

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
// 函数名称: OnCopyChatRoomWxid
// 函数说明: 响应复制群ID菜单
// 作    者: GuiShou
// 时    间: 2019/7/8
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnCopyChatRoomWxid()
{
	CString strText = wxid;

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
// 函数名称: OnDeleteUser
// 函数说明: 响应删除好友菜单
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnDeleteUser()
{
	if (MessageBoxA(NULL, "是否删除好友", "Tip", MB_YESNO))
	{
		if (wcscmp(wxid,L"filehelper")==0)
		{
			MessageBoxA(NULL, "无法删除filehelper", "Tip", MB_OK);
			return;
		}
		//查找窗口
		CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
		COPYDATASTRUCT deleteuser;
		deleteuser.dwData = WM_DeleteUser;
		deleteuser.cbData = (wcslen(wxid)+1)*2;
		deleteuser.lpData = wxid;
		//发送消息
		pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&deleteuser);

		//删除选中行
		POSITION pos = m_FriendList.GetFirstSelectedItemPosition();
		int nItem = m_FriendList.GetNextSelectedItem(pos);
		m_FriendList.DeleteItem(nItem);
	}
	
}


//************************************************************
// 函数名称: OnQuiteChatRoom
// 函数说明: 响应退出群聊菜单
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnQuitChatRoom()
{
	if (MessageBoxA(NULL, "是否退出群聊", "Tip", MB_YESNO))
	{
		//查找窗口
		CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
		COPYDATASTRUCT quitchatroom;
		quitchatroom.dwData = WM_QuitChatRoom;
		quitchatroom.cbData = (wcslen(wxid) + 1) * 2;
		quitchatroom.lpData = wxid;
		//发送消息
		pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&quitchatroom);

		//删除选中行
		POSITION pos = m_FriendList.GetFirstSelectedItemPosition();
		int nItem = m_FriendList.GetNextSelectedItem(pos);
		m_FriendList.DeleteItem(nItem);
	}

}


//************************************************************
// 函数名称: OnAddGroupMember
// 函数说明: 响应添加群成员
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnAddGroupMember()
{
	CAddChatRoomMember *addmember = new CAddChatRoomMember(wxid);
	addmember->DoModal();
}


//************************************************************
// 函数名称: OnSendRoomMessage
// 函数说明: 响应发送群消息菜单
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnSendRoomMessage()
{
	CSendRoomMsg *sendroommsg = new CSendRoomMsg(wxid);
	sendroommsg->DoModal();
}



//************************************************************
// 函数名称: OnSendRoomMessage
// 函数说明: 响应发送xml名片菜单
// 作    者: GuiShou
// 时    间: 2019/7/10
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnSendXmlCard()
{
	CSendXmlCard *sendcard = new CSendXmlCard(wxid);
	sendcard->DoModal();
}


//************************************************************
// 函数名称: OnShowChatRoomMember
// 函数说明: 响应查看群成员菜单
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnShowChatRoomMember()
{
	CChatRoomMember *chatroommember=new CChatRoomMember(wxid);
	chatroommember->DoModal();
}

//************************************************************
// 函数名称: OnSetRoomName
// 函数说明: 响应修改群名称菜单
// 作    者: GuiShou
// 时    间: 2019/7/14
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnSetRoomName()
{
	CSetRoomName *pSetroomname = new CSetRoomName(wxid);
	pSetroomname->DoModal();
}
