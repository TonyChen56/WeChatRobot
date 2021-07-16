// CSetRemark.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CSetRemark.h"
#include "afxdialogex.h"

// CSetRemark 对话框

IMPLEMENT_DYNAMIC(CSetRemark, CDialogEx)

CSetRemark::CSetRemark(LPCTSTR TempWxid, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SetRemark, pParent), m_wxid(TempWxid)
	, m_remark(_T(""))
{

}

CSetRemark::~CSetRemark()
{
}

void CSetRemark::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_remark);
}


BEGIN_MESSAGE_MAP(CSetRemark, CDialogEx)
	ON_BN_CLICKED(IDC_SetRemark, &CSetRemark::OnBnClickedSetremark)
END_MESSAGE_MAP()


// CSetRemark 消息处理程序


void CSetRemark::OnBnClickedSetremark()
{
	
}
