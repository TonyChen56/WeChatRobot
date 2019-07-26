// CSendXmlCard.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CSendXmlCard.h"
#include "afxdialogex.h"


// CSendXmlCard 对话框

IMPLEMENT_DYNAMIC(CSendXmlCard, CDialogEx)

CSendXmlCard::CSendXmlCard(LPCTSTR TempWxid, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SendCard, pParent), m_Wxid(TempWxid)
	, m_SendWxid(_T(""))
	, m_SendNickName(_T(""))
{

}

CSendXmlCard::~CSendXmlCard()
{
}

void CSendXmlCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SendWxid);
	DDX_Text(pDX, IDC_EDIT2, m_SendNickName);
}


BEGIN_MESSAGE_MAP(CSendXmlCard, CDialogEx)
	ON_BN_CLICKED(IDC_SendCard, &CSendXmlCard::OnBnClickedSendcard)
END_MESSAGE_MAP()


// CSendXmlCard 消息处理程序




//************************************************************
// 函数名称: OnBnClickedSendcard
// 函数说明: 响应发送按钮
// 作    者: GuiShou
// 时    间: 2019/7/10
// 参    数: void
// 返 回 值: void
//***********************************************************
void CSendXmlCard::OnBnClickedSendcard()
{
	UpdateData(TRUE);

	struct XmlCardMessage
	{
		wchar_t RecverWxid[50];		//接收者的微信ID
		wchar_t SendWxid[50];		//需要发送的微信ID
		wchar_t NickName[50];		//昵称
	};

	XmlCardMessage* pCardMessage = new XmlCardMessage;

	wcscpy_s(pCardMessage->RecverWxid, wcslen(m_Wxid) + 1, m_Wxid);
	wcscpy_s(pCardMessage->SendWxid, wcslen(m_SendWxid) + 1, m_SendWxid);
	wcscpy_s(pCardMessage->NickName, wcslen(m_SendNickName) + 1, m_SendNickName);

	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT sendcard;
	sendcard.dwData = WM_SendXmlCard;
	sendcard.cbData = sizeof(XmlCardMessage);
	sendcard.lpData = pCardMessage;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&sendcard);

	m_SendWxid = "";
	m_SendNickName = "";
	UpdateData(FALSE);
}
