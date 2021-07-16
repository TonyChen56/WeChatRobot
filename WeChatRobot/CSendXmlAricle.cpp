// CSendXmlAricle.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CSendXmlAricle.h"
#include "afxdialogex.h"


// CSendXmlAricle 对话框

IMPLEMENT_DYNAMIC(CSendXmlAricle, CDialogEx)

CSendXmlAricle::CSendXmlAricle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SendXmlArticle, pParent)
	, m_selfwxid(_T(""))
	, m_recverwxid(_T(""))
	, m_title(_T(""))
	, m_subtitle(_T(""))
	, m_linkurl(_T(""))
	, m_picpath(_T(""))
{

}

CSendXmlAricle::~CSendXmlAricle()
{
}

void CSendXmlAricle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_selfwxid);
	DDX_Text(pDX, IDC_EDIT2, m_recverwxid);
	DDX_Text(pDX, IDC_EDIT6, m_title);
	DDX_Text(pDX, IDC_EDIT7, m_subtitle);
	DDX_Text(pDX, IDC_EDIT8, m_linkurl);
	DDX_Text(pDX, IDC_EDIT9, m_picpath);
}


BEGIN_MESSAGE_MAP(CSendXmlAricle, CDialogEx)
	ON_BN_CLICKED(IDC_SendXmlArticle, &CSendXmlAricle::OnBnClickedSendxmlarticle)
END_MESSAGE_MAP()


// CSendXmlAricle 消息处理程序



//************************************************************
// 函数名称: OnBnClickedSendxmlarticle
// 函数说明: 发送xml文章按钮
// 作    者: GuiShou
// 时    间: 2019/9/30
// 参    数: void
// 返 回 值: void
//***********************************************************
void CSendXmlAricle::OnBnClickedSendxmlarticle()
{
}
