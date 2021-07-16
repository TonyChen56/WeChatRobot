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




//************************************************************
// 函数名称: string_To_UTF8
// 函数说明: string转UTF8
// 作    者: GuiShou
// 时    间: 2019/11/7
// 参    数: str 需要转换的字符串
// 返 回 值: string 转换后的字符串
//***********************************************************
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


//************************************************************
// 函数名称: Wchar_tToString
// 函数说明: wchar转string
// 作    者: GuiShou
// 时    间: 2019/11/7
// 参    数: wchar 需要转换的字符串
// 返 回 值: string 转换后的字符串
//***********************************************************
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


//************************************************************
// 函数名称: StringToWchar_t
// 函数说明: string转wchar
// 作    者: GuiShou
// 时    间: 2019/11/7
// 参    数: str 需要转换的字符串
// 返 回 值: wchar_t* 转换后的字符串
//***********************************************************
wchar_t * StringToWchar_t(const std::string & str)
{
	wchar_t * m_chatroommmsg = new wchar_t[str.size() * 2];  //
	memset(m_chatroommmsg, 0, str.size() * 2);
	setlocale(LC_ALL, "zh_CN.UTF-8");
	swprintf(m_chatroommmsg, str.size() * 2, L"%S", str.c_str());

	return m_chatroommmsg;
}



//************************************************************
// 函数名称: Log
// 函数说明: 记录聊天记录到本地
// 作    者: GuiShou
// 时    间: 2019/11/7
// 参    数: type 消息类型 wxid微信ID source消息来源 msgSender消息发送者 content消息内容
// 返 回 值: void
//***********************************************************
void Log(const std::string & type, const std::string & wxid, const std::string & source, const std::string & msgSender, const std::string & content)
{
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
			"\n" + "微信昵称：" + wxid +
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
			"\n" + "群名称：" + wxid +
			"\n" + "群发送者：" + msgSender +
			"\n" + "消息内容：" + content +
			"\n" + "-------------------------------- 分割线 --------------------------------\n\n\n"
		);
	}
	

	FILE * fp = fopen("log.txt", "ab+");
	fwrite(log.c_str(), log.length(), 1, fp);
	fclose(fp);
}



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
	m_ChatRecord.InsertColumn(2, L"微信昵称/群名称", 0, 150);
	m_ChatRecord.InsertColumn(3, L"群发送者", 0, 150);
	m_ChatRecord.InsertColumn(4, L"消息内容", 0, 465);
	m_ChatRecord.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
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
	ChatMessageData *msg = (ChatMessageData*)wParam;

	//显示到控件
	m_ChatRecord.InsertItem(g_index, msg->sztype);
	m_ChatRecord.SetItemText(g_index, 1, msg->source);
	m_ChatRecord.SetItemText(g_index, 2, msg->wxname);
	m_ChatRecord.SetItemText(g_index, 3, msg->sendername);
	m_ChatRecord.SetItemText(g_index, 4, msg->content);


	//保存聊天记录到本地
	std::string type = Wchar_tToString(msg->sztype);
	std::string wxid = Wchar_tToString(msg->wxname);
	std::string source = Wchar_tToString(msg->source);
	std::string msgSender = Wchar_tToString(msg->sendername);
	std::string content = Wchar_tToString(msg->content);
	Log(type.c_str(), wxid.c_str(), source.c_str(), msgSender.c_str(), content.c_str());
	return 0;
}
