// CFriendInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CFriendInfo.h"
#include "afxdialogex.h"




// CFriendInfo 对话框

IMPLEMENT_DYNAMIC(CFriendInfo, CDialogEx)

CFriendInfo::CFriendInfo(LPCTSTR TempWxid, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FRIENDINFO, pParent), m_Wxid(TempWxid)
	, m_wxid(_T(""))
	, m_wxnumber(_T(""))
	, m_wxv1(_T(""))
	, m_wxremark(_T(""))
	, m_wxnickname(_T(""))
	, wxsmallheader(_T(""))
	, wxbigheader(_T(""))
{

}

CFriendInfo::~CFriendInfo()
{
}

void CFriendInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_wxid);
	DDX_Text(pDX, IDC_EDIT2, m_wxnumber);
	DDX_Text(pDX, IDC_EDIT6, m_wxv1);
	DDX_Text(pDX, IDC_EDIT7, m_wxremark);
	DDX_Text(pDX, IDC_EDIT8, m_wxnickname);
	DDX_Text(pDX, IDC_EDIT9, wxsmallheader);
	DDX_Text(pDX, IDC_EDIT10, wxbigheader);
}


BEGIN_MESSAGE_MAP(CFriendInfo, CDialogEx)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CFriendInfo 消息处理程序


BOOL CFriendInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	return TRUE;  
}



//************************************************************
// 函数名称: OnCopyData
// 函数说明: 响应CopyData消息
// 作    者: GuiShou
// 时    间: 2019/10/9
// 参    数: CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct
// 返 回 值: BOOL
//***********************************************************
BOOL CFriendInfo::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
