// CFriendList.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CFriendList.h"
#include "afxdialogex.h"
#include "CSendMsg.h"
#include "CRoomAnnouncement.h"
#include "CAddChatRoomMember.h"
#include "CSendXmlCard.h"
#include "CChatRoomMember.h"
#include "CSetRoomName.h"
#include "CInviteGroupMember.h"
#include "CFriendInfo.h"
#include "CSetRemark.h"
#include <time.h>
#include <vector>
#include <fstream>
#include <atlconv.h>
#include <map>



DWORD dwIndex = 0;
wchar_t wxid[50];	//鼠标左键点击时拿到的微信ID
vector<CString> g_wxidvector;					//保存微信ID的容器

//是否关注聊天机器人
BOOL isAttentTuLing = FALSE;

IMPLEMENT_DYNAMIC(CFriendList, CDialogEx)

CFriendList::CFriendList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FRIEND_LIST, pParent)
	, m_GroupSendText(_T(""))
{

}

CFriendList::~CFriendList()
{
}

void CFriendList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FRIENDLIST, m_FriendList);
	DDX_Text(pDX, IDC_EDIT1, m_GroupSendText);
}


BEGIN_MESSAGE_MAP(CFriendList, CDialogEx)
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_ShowFriendList, &CFriendList::OnShowfriendlist)
	ON_NOTIFY(NM_RCLICK, IDC_FRIENDLIST, &CFriendList::OnRclickFriendlist)
	ON_NOTIFY(NM_CLICK, IDC_FRIENDLIST, &CFriendList::OnClickFriendlist)
	ON_COMMAND(ID_32780, &CFriendList::OnSendMsg)
	ON_COMMAND(ID_32784, &CFriendList::OnSetRoomAnnouncement)
	ON_COMMAND(ID_32782, &CFriendList::OnCopyWxid)
	ON_COMMAND(ID_32785, &CFriendList::OnCopyWxid)
	ON_COMMAND(ID_32781, &CFriendList::OnDeleteUser)
	ON_COMMAND(ID_32786, &CFriendList::OnQuitChatRoom)
	ON_COMMAND(ID_32787, &CFriendList::OnAddGroupMember)
	ON_COMMAND(ID_32783, &CFriendList::OnSendMsg)
	ON_COMMAND(ID_32788, &CFriendList::OnSendXmlCard)
	ON_COMMAND(ID_32789, &CFriendList::OnShowChatRoomMember)
	ON_COMMAND(ID_32790, &CFriendList::OnSetRoomName)
	ON_COMMAND(ID_32799, &CFriendList::OnInviteGroupMember)
	ON_COMMAND(ID_32804, &CFriendList::OnGetFriendInfo)
	ON_BN_CLICKED(IDC_CheckAll, &CFriendList::OnBnClickedCheckall)
	ON_BN_CLICKED(IDC_ReverseChoose, &CFriendList::OnBnClickedReversechoose)
	ON_BN_CLICKED(IDC_CancelAll, &CFriendList::OnBnClickedCancelall)
	ON_BN_CLICKED(IDC_GroupSend, &CFriendList::OnBnClickedGroupsend)
	ON_COMMAND(ID_32805, &CFriendList::OnSetRemark)
	ON_COMMAND(ID_32808, &CFriendList::OnTopMsg)
	ON_COMMAND(ID_32810, &CFriendList::OnTopMsg)
	ON_COMMAND(ID_32809, &CFriendList::OnCancleTopMsg)
	ON_COMMAND(ID_32811, &CFriendList::OnCancleTopMsg)
	ON_COMMAND(ID_32812, &CFriendList::OnOpenNewMsgNotify)
	ON_COMMAND(ID_32814, &CFriendList::OnOpenNewMsgNotify)
	ON_COMMAND(ID_32813, &CFriendList::OnMsgNoDisturb)
	ON_COMMAND(ID_32815, &CFriendList::OnMsgNoDisturb)
	ON_MESSAGE(SaveFriendList, &CFriendList::OnSavefriendlist)
END_MESSAGE_MAP()


// CFriendList 消息处理程序


BOOL CFriendList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_FriendList.InsertColumn(0, L"序号", 0, 50);
	m_FriendList.InsertColumn(1, L"微信ID", 0, 200);
	m_FriendList.InsertColumn(2, L"微信号", 0, 200);
	m_FriendList.InsertColumn(3, L"昵称", 0, 250);
	m_FriendList.InsertColumn(4, L"备注", 0, 253);

	m_FriendList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_CHECKBOXES);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
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
	//检测联系人列表中是否有聊天机器人
	if (StrCmpW(userinfo->UserId,ChatRobotWxID)==0)
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
	unique_ptr<CSendMsg> pSendmsg(new CSendMsg(wxid));
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
	unique_ptr<CRoomAnnouncement> pRoom(new CRoomAnnouncement(wxid));
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
// 函数名称: OnDeleteUser
// 函数说明: 响应删除好友菜单
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnDeleteUser()
{
	if (MessageBoxA(NULL, "是否删除好友", "Tip", MB_YESNO)==IDYES)
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
// 函数说明: 响应邀请群成员(50人以下)
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnAddGroupMember()
{
	unique_ptr<CAddChatRoomMember> addmember(new CAddChatRoomMember(wxid));
	addmember->DoModal();
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
	unique_ptr<CSendXmlCard> sendcard(new CSendXmlCard(wxid));
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
	unique_ptr<CChatRoomMember> chatroommember(new CChatRoomMember(wxid));
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
	unique_ptr<CSetRoomName> pSetroomname(new CSetRoomName(wxid));
	pSetroomname->DoModal();
}



//************************************************************
// 函数名称: OnInviteGroupMember
// 函数说明: 响应邀请群成员(50人以上)
// 作    者: GuiShou
// 时    间: 2019/9/19
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnInviteGroupMember()
{
	unique_ptr<CInviteGroupMember> Invitemember(new CInviteGroupMember(wxid));
	Invitemember->DoModal();
}


//************************************************************
// 函数名称: OnGetFriendInfo
// 函数说明: 响应查看好友信息菜单
// 作    者: GuiShou
// 时    间: 2019/10/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnGetFriendInfo()
{
	
}


//************************************************************
// 函数名称: OnBnClickedCheckall
// 函数说明: 全选
// 作    者: GuiShou
// 时    间: 2019/10/18
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnBnClickedCheckall()
{
	for (int i = 0; i < m_FriendList.GetItemCount(); i++)
	{
		m_FriendList.SetCheck(i, TRUE);
	}
}


//************************************************************
// 函数名称: OnBnClickedReversechoose
// 函数说明: 反选
// 作    者: GuiShou
// 时    间: 2019/10/18
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnBnClickedReversechoose()
{
	for (int i = 0; i < m_FriendList.GetItemCount(); i++)
	{
		if (m_FriendList.GetCheck(i) == FALSE)  //未被选中的
		{
			m_FriendList.SetCheck(i, TRUE);
		}
		else  //选中的
		{
			m_FriendList.SetCheck(i, FALSE);
		}
	}
}

//************************************************************
// 函数名称: OnBnClickedCancelall
// 函数说明: 取消
// 作    者: GuiShou
// 时    间: 2019/10/18
// 参    数: void
// 返 回 值: void
//***********************************************************

void CFriendList::OnBnClickedCancelall()
{
	for (int i = 0; i < m_FriendList.GetItemCount(); i++)
	{
		m_FriendList.SetCheck(i, FALSE);
	}
}




//************************************************************
// 函数名称: OnBnClickedGroupsend
// 函数说明: 群发
// 作    者: GuiShou
// 时    间: 2019/10/18
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnBnClickedGroupsend()
{
	
}



//************************************************************
// 函数名称: OnSetRemark
// 函数说明: 响应修改备注菜单
// 作    者: GuiShou
// 时    间: 2019/10/21
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnSetRemark()
{
}



//************************************************************
// 函数名称: OnTopMsg
// 函数说明: 响应置顶菜单
// 作    者: GuiShou
// 时    间: 2019/11/14
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnTopMsg()
{

}


//************************************************************
// 函数名称: OnCancleTopMsg
// 函数说明: 响应取消置顶菜单
// 作    者: GuiShou
// 时    间: 2019/11/14
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnCancleTopMsg()
{

}



//************************************************************
// 函数名称: OnOpenNewMsgNotify
// 函数说明: 响应开启新消息提醒菜单
// 作    者: GuiShou
// 时    间: 2019/11/14
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnOpenNewMsgNotify()
{
	
}



//************************************************************
// 函数名称: OnMsgNoDisturb
// 函数说明: 响应消息免打扰菜单
// 作    者: GuiShou
// 时    间: 2019/11/14
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFriendList::OnMsgNoDisturb()
{

}

//************************************************************
// 函数名称: OnSavefriendlist
// 函数说明: 响应保存好友列表消息
// 作    者: GuiShou
// 时    间: 2020/02/19
// 参    数: void
// 返 回 值: void
//***********************************************************
afx_msg LRESULT CFriendList::OnSavefriendlist(WPARAM wParam, LPARAM lParam)
{
	wstring wxUserFileName = L"UserLists.txt";

	//作为输出文件打开
	ofstream ofile;
	ofile.open(wxUserFileName, ios_base::trunc | ios_base::binary | ios_base::in);

	//获取所有行的数量
	int nRow = m_FriendList.GetItemCount();

	//获取所有列的数量
	int nCol = m_FriendList.GetHeaderCtrl()->GetItemCount();

	//开始循环行和列
	for (int i = 0; i < nRow; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			USES_CONVERSION;
			CString csTemp = m_FriendList.GetItemText(i, j);
			string sTemp(CW2A(csTemp.GetString()));
			char const* pos = (char const*)sTemp.c_str();
			//写入文件
			ofile.write(pos, sTemp.length());

			char const* cTab = "\t\t";
			ofile.write(cTab, strlen(cTab));
		}

		char const* cLine = "\r\n";
		ofile.write(cLine, strlen(cLine));
	}

	ofile.flush();
	ofile.close();
	return 0;
}
