// CSetRoomName.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CSetRoomName.h"
#include "afxdialogex.h"


// CSetRoomName 对话框

IMPLEMENT_DYNAMIC(CSetRoomName, CDialogEx)

CSetRoomName::CSetRoomName(LPCTSTR TempWxid,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SET_ROOM_NAME, pParent), m_ChatRoomWxid(TempWxid)
	, m_roomname(_T(""))
{

}

CSetRoomName::~CSetRoomName()
{
}

void CSetRoomName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_roomname);
}


BEGIN_MESSAGE_MAP(CSetRoomName, CDialogEx)
	ON_BN_CLICKED(IDC_SetRoomName, &CSetRoomName::OnBnClickedSetroomname)
END_MESSAGE_MAP()


// CSetRoomName 消息处理程序



//************************************************************
// 函数名称: OnBnClickedSetroomname
// 函数说明: 响应修改群名称按钮
// 作    者: GuiShou
// 时    间: 2019/7/14
// 参    数: void
// 返 回 值: void
//***********************************************************
void CSetRoomName::OnBnClickedSetroomname()
{
	UpdateData(TRUE);
	struct SetRoomNameStruct
	{
		wchar_t roomwxid[50];
		wchar_t roomname[50];
	};
	SetRoomNameStruct *roomname=new SetRoomNameStruct;

	wcscpy_s(roomname->roomwxid, wcslen(m_ChatRoomWxid) + 1, m_ChatRoomWxid);
	wcscpy_s(roomname->roomname, wcslen(m_roomname) + 1, m_roomname);

	//查找窗口
	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT setroomnamedata;
	setroomnamedata.dwData = WM_SetRoomName;
	setroomnamedata.cbData = sizeof(SetRoomNameStruct);
	setroomnamedata.lpData = roomname;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&setroomnamedata);

	m_roomname = "";
	UpdateData(FALSE);
}
