// CChatRecords.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CChatRecords.h"
#include "afxdialogex.h"
#include "stdafx.h"
#include "WeChatRobot.h"
#include "CChatRecords.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <string.h>
#include <locale.h>
#include "CSendRoomMsg.h"
#include <assert.h>
#include <afxwin.h>
#include <stdio.h>
#include <windows.h>
#include "Wininet.h"
#pragma comment(lib,"Wininet.lib")
#include <fstream>
#include <mmsystem.h>   //多媒体播放所需的头文件
#pragma comment(lib,"winmm.lib")  //多媒体播放所需的库文件

DWORD g_index=0;


//string转UTF8
std::string string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}


//wchar_t转string
std::string Wchar_tToString(wchar_t *wchar)
{
	std::string szDst;
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
	char *psText; // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
	return szDst;
}


//string转wchar_t
wchar_t * StringToWchar_t(const std::string & str)
{
	wchar_t * m_chatroommmsg = new wchar_t[str.size() * 2];  //
	memset(m_chatroommmsg, 0, str.size() * 2);
	setlocale(LC_ALL, "zh_CN.UTF-8");
	swprintf(m_chatroommmsg, str.size() * 2, L"%S", str.c_str());

	return m_chatroommmsg;
}


void Log(const std::string & type, const std::string & wxid, const std::string & source, const std::string & msgSender, const std::string & content) {
	setlocale(LC_ALL, "zh_CN.UTF-8");
	time_t t = time(0);
	char ch[64];
	strftime(ch, sizeof(ch), "%Y-%m-%d %H-%M-%S", localtime(&t)); //年-月-日 时-分-秒
	std::string times = ch;
	std::string log;
	if (strstr(msgSender.c_str(), "NULL") != NULL) 
	{
		log = string_To_UTF8(
			"************************ " + times + " ************************" +
			"\n" + "消息类型：" + type +
			"\n" + "消息来源：" + source +
			"\n" + "微信ID：" + wxid +
			"\n" + "消息内容：" + content +
			"\n" + "-------------------------------- 分割线 --------------------------------\n\n\n"
		);
	}
	else
	{
		log = string_To_UTF8(
			"************************ " + times + " ************************" +
			"\n" + "消息类型：" + type +
			"\n" + "消息来源：" + source +
			"\n" + "群ID：" + wxid +
			"\n" + "群发送者：" + msgSender +
			"\n" + "消息内容：" + content +
			"\n" + "-------------------------------- 分割线 --------------------------------\n\n\n"
		);
	}
	

	FILE * fp = fopen("log.txt", "ab+");
	fwrite(log.c_str(), log.length(), 1, fp);
	fclose(fp);
}


//消息结构体
struct Message
{
	wchar_t type[10];		//消息类型
	wchar_t source[20];		//消息来源
	wchar_t wxid[40];		//微信ID/群ID
	wchar_t msgSender[40];	//消息发送者
	wchar_t content[200];	//消息内容
	BOOL isMoney = FALSE;	//是否是收款消息
};


// CChatRecords 对话框

IMPLEMENT_DYNAMIC(CChatRecords, CDialogEx)

CChatRecords::CChatRecords(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_RECORDS, pParent)
{

}

CChatRecords::~CChatRecords()
{
}

void CChatRecords::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ChatRecord);
}


BEGIN_MESSAGE_MAP(CChatRecords, CDialogEx)
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_ShowMessage, &CChatRecords::OnShowmessage)
END_MESSAGE_MAP()


// CChatRecords 消息处理程序


BOOL CChatRecords::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ChatRecord.InsertColumn(0, L"消息类型", 0, 100);
	m_ChatRecord.InsertColumn(1, L"消息来源", 0, 100);
	m_ChatRecord.InsertColumn(2, L"微信ID/群ID", 0, 150);
	m_ChatRecord.InsertColumn(3, L"群发送者", 0, 150);
	m_ChatRecord.InsertColumn(4, L"消息内容", 0, 310);
	m_ChatRecord.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CChatRecords::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


//************************************************************
// 函数名称: OnShowmessage
// 函数说明: 响应Showmessage消息 处理父窗口发过来的消息
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: WPARAM wParam, LPARAM lParam
// 返 回 值: BOOL
//***********************************************************
afx_msg LRESULT CChatRecords::OnShowmessage(WPARAM wParam, LPARAM lParam)
{
	//取数据
	Message *msg = (Message*)wParam;

	//显示到控件
	m_ChatRecord.InsertItem(g_index, msg->type);
	m_ChatRecord.SetItemText(g_index, 1, msg->source);
	m_ChatRecord.SetItemText(g_index, 2, msg->wxid);
	m_ChatRecord.SetItemText(g_index, 3, msg->msgSender);
	m_ChatRecord.SetItemText(g_index, 4, msg->content);

	if (msg->isMoney==TRUE)
	{
		//如果是收款消息 播放音效
		if (GetFileAttributesA("微信收款音效.mp3")==INVALID_FILE_ATTRIBUTES)
		{
			MessageBoxA(NULL, "未找到微信收款音效文件 无法播放语音提示", "Tip", 0);
		}
		else
		{
			mciSendString(L"open 微信收款音效.mp3", 0, 0, 0);
			mciSendString(L"play 微信收款音效.mp3", 0, 0, 0);
		}
		
	}

	std::string type = Wchar_tToString(msg->type);
	std::string wxid = Wchar_tToString(msg->wxid);
	std::string source = Wchar_tToString(msg->source);
	std::string msgSender = Wchar_tToString(msg->msgSender);
	std::string content = Wchar_tToString(msg->content);
	Log(type.c_str(),wxid.c_str(), source.c_str(), msgSender.c_str(), content.c_str());

	return 0;
}
