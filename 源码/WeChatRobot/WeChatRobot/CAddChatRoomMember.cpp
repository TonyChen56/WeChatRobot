// CAddChatRoomMember.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CAddChatRoomMember.h"
#include "afxdialogex.h"


// CAddChatRoomMember 对话框

IMPLEMENT_DYNAMIC(CAddChatRoomMember, CDialogEx)

CAddChatRoomMember::CAddChatRoomMember(LPCTSTR TempWxid, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_MEMBER, pParent), m_ChatRoomWxid(TempWxid)
	, m_wxid(_T(""))
{

}

CAddChatRoomMember::~CAddChatRoomMember()
{
}

void CAddChatRoomMember::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ChatRoomWXID, m_wxid);
}


BEGIN_MESSAGE_MAP(CAddChatRoomMember, CDialogEx)
	ON_BN_CLICKED(IDC_MAKE_SURE, &CAddChatRoomMember::OnBnClickedMakeSure)
END_MESSAGE_MAP()


// CAddChatRoomMember 消息处理程序


//************************************************************
// 函数名称: OnBnClickedMakeSure
// 函数说明: 响应确定按钮
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CAddChatRoomMember::OnBnClickedMakeSure()
{
	UpdateData(TRUE);

	struct AddGroupMem
	{
		wchar_t chatroomid[50];
		wchar_t wxid[50];
	};

	AddGroupMem *addgroupmember=new AddGroupMem;
	wcscpy_s(addgroupmember->wxid, wcslen(m_wxid) + 1, m_wxid);
	wcscpy_s(addgroupmember->chatroomid, wcslen(m_ChatRoomWxid) + 1, m_ChatRoomWxid);


	//查找窗口
	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT addgroupdata;
	addgroupdata.dwData = WM_AddGroupMember;
	addgroupdata.cbData = sizeof(AddGroupMem);
	addgroupdata.lpData = addgroupmember;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&addgroupdata);

	m_wxid = "";
	UpdateData(FALSE);
}
