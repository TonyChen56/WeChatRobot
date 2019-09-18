// COpenUrl.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "COpenUrl.h"
#include "afxdialogex.h"


// COpenUrl 对话框

IMPLEMENT_DYNAMIC(COpenUrl, CDialogEx)

COpenUrl::COpenUrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OpenUrl, pParent)
	, m_urls(_T("www.baidu.com"))
{

}

COpenUrl::~COpenUrl()
{
}

void COpenUrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_urls);
}


BEGIN_MESSAGE_MAP(COpenUrl, CDialogEx)
	ON_BN_CLICKED(IDC_OPEN, &COpenUrl::OnBnClickedOpen)
END_MESSAGE_MAP()


// COpenUrl 消息处理程序


//************************************************************
// 函数名称: OnBnClickedOpen
// 函数说明: 打开浏览器按钮
// 作    者: GuiShou
// 时    间: 2019/9/10
// 参    数: void
// 返 回 值: void
//***********************************************************
void COpenUrl::OnBnClickedOpen()
{
	UpdateData(TRUE);
	if (m_urls=="")
	{
		MessageBoxA(NULL,"url不能为空", "Tip", MB_OK);
		return;
	}

	wchar_t urls[50] = { 0 };
	wcscpy_s(urls, wcslen(m_urls) + 1, m_urls);
	//点击按钮 拿到url 发送给控制端
	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT openurl;
	openurl.dwData = WM_OpenUrl;
	openurl.cbData = (wcslen(urls) + 1) * 2;
	openurl.lpData = urls;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&openurl);
}
