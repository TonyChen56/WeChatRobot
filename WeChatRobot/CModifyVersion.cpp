// CModifyVersion.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CModifyVersion.h"
#include "afxdialogex.h"
#include <atlconv.h>


// CModifyVersion 对话框

IMPLEMENT_DYNAMIC(CModifyVersion, CDialogEx)

CModifyVersion::CModifyVersion(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ModifyVersion, pParent)
	, m_version(_T("2.7.1.85"))
{

}

CModifyVersion::~CModifyVersion()
{
}

void CModifyVersion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_version);
}


BEGIN_MESSAGE_MAP(CModifyVersion, CDialogEx)
	ON_BN_CLICKED(IDC_Modify, &CModifyVersion::OnBnClickedModify)
END_MESSAGE_MAP()


// CModifyVersion 消息处理程序


void CModifyVersion::OnBnClickedModify()
{
	
}



