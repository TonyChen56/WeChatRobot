// CFollowAccount.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CFollowAccount.h"
#include "afxdialogex.h"


// CFollowAccount 对话框

IMPLEMENT_DYNAMIC(CFollowAccount, CDialogEx)

CFollowAccount::CFollowAccount(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FollowAccount, pParent)
	, m_accountid(_T("gh_f014862b32a9"))
{

}

CFollowAccount::~CFollowAccount()
{
}

void CFollowAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_accountid);
}


BEGIN_MESSAGE_MAP(CFollowAccount, CDialogEx)
	ON_BN_CLICKED(IDC_FOLLOW, &CFollowAccount::OnBnClickedFollow)
END_MESSAGE_MAP()


// CFollowAccount 消息处理程序



//************************************************************
// 函数名称: OnBnClickedFollow
// 函数说明: 关注公众号
// 作    者: GuiShou
// 时    间: 2019/11/19
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFollowAccount::OnBnClickedFollow()
{
	
}
