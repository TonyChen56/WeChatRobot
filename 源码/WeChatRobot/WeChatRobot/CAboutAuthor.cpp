// CAboutAuthor.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CAboutAuthor.h"
#include "afxdialogex.h"


// CAboutAuthor 对话框

IMPLEMENT_DYNAMIC(CAboutAuthor, CDialogEx)

CAboutAuthor::CAboutAuthor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUT_AUTHOR, pParent)
	, m_kanxue(_T(""))
	, m_wuaipojie(_T(""))
	, m_csdn(_T(""))
	, m_email(_T(""))
	, m_github(_T(""))
{

}

CAboutAuthor::~CAboutAuthor()
{
}

void CAboutAuthor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_kanxue);
	DDX_Text(pDX, IDC_EDIT2, m_wuaipojie);
	DDX_Text(pDX, IDC_EDIT3, m_csdn);
	DDX_Text(pDX, IDC_EDIT4, m_email);
	DDX_Text(pDX, IDC_EDIT5, m_github);
}


BEGIN_MESSAGE_MAP(CAboutAuthor, CDialogEx)
END_MESSAGE_MAP()


// CAboutAuthor 消息处理程序


BOOL CAboutAuthor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_kanxue = L"鬼手56";
	m_wuaipojie = L"鬼手56";
	m_github = L"https://github.com/TonyChen56";
	m_csdn = L"https://blog.csdn.net/qq_38474570";
	m_email = L"tonychen56@qq.com";
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
