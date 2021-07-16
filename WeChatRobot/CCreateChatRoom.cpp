// CCreateChatRoom.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CCreateChatRoom.h"
#include "afxdialogex.h"



IMPLEMENT_DYNAMIC(CCreateChatRoom, CDialogEx)

CCreateChatRoom::CCreateChatRoom(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CreateChatRoom, pParent)
	, m_wxid1(_T(""))
	, m_wxid2(_T(""))
{

}

CCreateChatRoom::~CCreateChatRoom()
{
}

void CCreateChatRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_wxid1);
	DDX_Text(pDX, IDC_EDIT2, m_wxid2);
}


BEGIN_MESSAGE_MAP(CCreateChatRoom, CDialogEx)
	ON_BN_CLICKED(IDC_CreateChatRoom, &CCreateChatRoom::OnBnClickedCreatechatroom)
END_MESSAGE_MAP()


// CCreateChatRoom 消息处理程序

//************************************************************
// 函数名称: OnBnClickedCreatechatroom
// 函数说明: 创建群聊
// 作    者: GuiShou
// 时    间: 2019/10/22
// 参    数: void
// 返 回 值: void
//***********************************************************
void CCreateChatRoom::OnBnClickedCreatechatroom()
{

}
