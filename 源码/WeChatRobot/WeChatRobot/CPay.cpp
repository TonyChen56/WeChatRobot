// CPay.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CPay.h"
#include "afxdialogex.h"


// CPay 对话框

IMPLEMENT_DYNAMIC(CPay, CDialogEx)

CPay::CPay(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAY, pParent)
{

}

CPay::~CPay()
{
}

void CPay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPay, CDialogEx)
END_MESSAGE_MAP()


// CPay 消息处理程序
