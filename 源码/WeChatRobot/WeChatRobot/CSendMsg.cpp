// CSendMsg.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CSendMsg.h"
#include "afxdialogex.h"


#define 文本 0
#define 文件 1
#define 图片 2


//消息结构体
struct MessageStruct
{
	wchar_t wxid[40];
	wchar_t content[MAX_PATH];
};


// CSendMsg 对话框

IMPLEMENT_DYNAMIC(CSendMsg, CDialogEx)

CSendMsg::CSendMsg(LPCTSTR TempWxid,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SendMsg, pParent), m_wxid(TempWxid)
	, m_Radio(0)
	, m_Content(_T(""))
{

}

CSendMsg::~CSendMsg()
{
}

void CSendMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
	DDX_Text(pDX, IDC_EDIT1, m_Content);
}


BEGIN_MESSAGE_MAP(CSendMsg, CDialogEx)

	ON_BN_CLICKED(IDC_Send, &CSendMsg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_RADIO1, &CSendMsg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSendMsg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CSendMsg::OnBnClickedRadio1)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CSendMsg 消息处理程序


BOOL CSendMsg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//************************************************************
// 函数名称: OnBnClickedSend
// 函数说明: 响应发送按钮
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void
//***********************************************************
void CSendMsg::OnBnClickedSend()
{
	//同步控件数据到变量
	UpdateData(TRUE);

	if (m_Content == "")
	{
		MessageBoxW(L"消息不能为空", L"Tip", 0);
		return;
	}

	//填充数据到结构体
	MessageStruct *message = new MessageStruct;
	wcscpy_s(message->wxid, wcslen(m_wxid) + 1, m_wxid);
	wcscpy_s(message->content, wcslen(m_Content) + 1, m_Content);


	//查找窗口
	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT MessageData;

	//如果是文本就发送文本消息 如果是文件就发送文件消息
	if (m_Radio == 文本)
	{
		MessageData.dwData = WM_SendTextMessage;
	}
	else if (m_Radio == 文件)
	{
		//检查文件是否存在
		if (GetFileAttributes(m_Content) == INVALID_FILE_ATTRIBUTES)
		{
			MessageBox(L"文件不存在 请重试");
			return;
		}
		//发送文件消息
		MessageData.dwData = WM_SendFileMessage;
	}
	else if (m_Radio == 图片)
	{
		//检查图片是否存在
		if (GetFileAttributes(m_Content) == INVALID_FILE_ATTRIBUTES)
		{
			MessageBox(L"图片不存在 请重试");
			return;
		}
		//发送图片消息
		MessageData.dwData = WM_SendImageMessage;
	}

	MessageData.cbData = sizeof(MessageStruct);
	MessageData.lpData = message;

	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&MessageData);

	//清空文本
	m_Content = "";

	UpdateData(FALSE);
}



//************************************************************
// 函数名称: OnBnClickedRadio1
// 函数说明: 响应点击单选框
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void
//***********************************************************
void CSendMsg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
}


//************************************************************
// 函数名称: OnDropFiles 
// 函数说明: 响应拖拽文件
// 作	 者: GuiShou
// 时	 间: 2019/7/6
// 参	 数: HDROP hDropInfo 拖拽文件句柄
// 返 回 值: void
//************************************************************
void CSendMsg::OnDropFiles(HDROP hDropInfo)
{
	//获取文件路径
	TCHAR szPath[MAX_PATH] = { 0 };
	DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);

	//显示到控件
	m_Content = szPath;

	UpdateData(FALSE);

	CDialogEx::OnDropFiles(hDropInfo);
}
