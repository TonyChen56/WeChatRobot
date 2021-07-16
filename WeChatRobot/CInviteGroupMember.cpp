// CInviteGroupMember.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CInviteGroupMember.h"
#include "afxdialogex.h"


// CInviteGroupMember 对话框

IMPLEMENT_DYNAMIC(CInviteGroupMember, CDialogEx)

CInviteGroupMember::CInviteGroupMember(LPCTSTR TempGroupId, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_InviteMember, pParent), m_ChatRoomWxid(TempGroupId)
	, m_wxid(_T(""))
{

}

CInviteGroupMember::~CInviteGroupMember()
{
}

void CInviteGroupMember::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_wxid);
}


BEGIN_MESSAGE_MAP(CInviteGroupMember, CDialogEx)
	ON_BN_CLICKED(IDC_INVITE, &CInviteGroupMember::OnBnClickedInvite)
END_MESSAGE_MAP()



//************************************************************
// 函数名称: OnBnClickedInvite
// 函数说明: 响应确定按钮
// 作    者: GuiShou
// 时    间: 2019/9/19
// 参    数: void
// 返 回 值: void
//***********************************************************
void CInviteGroupMember::OnBnClickedInvite()
{

}
