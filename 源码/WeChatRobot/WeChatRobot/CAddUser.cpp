// CAddUser.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CAddUser.h"
#include "afxdialogex.h"


// CAddUser 对话框

IMPLEMENT_DYNAMIC(CAddUser, CDialogEx)

CAddUser::CAddUser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_USER, pParent)
	, m_wxid(_T(""))
	, m_content(_T(""))
{

}

CAddUser::~CAddUser()
{
}

void CAddUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_wxid);
	DDX_Text(pDX, IDC_EDIT2, m_content);
}


BEGIN_MESSAGE_MAP(CAddUser, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_USER, &CAddUser::OnBnClickedAddUser)
END_MESSAGE_MAP()


// CAddUser 消息处理程序



//************************************************************
// 函数名称: OnBnClickedAddUser
// 函数说明: 响应添加好友按钮
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: void
// 返 回 值: void
//***********************************************************
void CAddUser::OnBnClickedAddUser()
{
	UpdateData(TRUE);
	struct AddUserStruct
	{
		wchar_t wxid[50];
		wchar_t content[50];
	};

	AddUserStruct* addUser = new AddUserStruct;

	wcscpy_s(addUser->wxid, wcslen(m_wxid) + 1, m_wxid);
	wcscpy_s(addUser->content, wcslen(m_content) + 1, m_content);

	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT adduserdata;
	adduserdata.dwData = WM_AddUser;
	adduserdata.cbData = sizeof(AddUserStruct);
	adduserdata.lpData = addUser;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&adduserdata);


	m_wxid = "";
	m_content = "";
	UpdateData(FALSE);
}
