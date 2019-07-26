// CFunctions.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CFunctions.h"
#include "afxdialogex.h"
#include "CInformation.h"
#include "CDecryptImage.h"
#include "CMultiOpen.h"
#include "CAddUser.h"
#include "CFriendList.h"

extern BOOL isAttentTuLing;
BOOL bAutoChat = FALSE;

// CFunctions 对话框

IMPLEMENT_DYNAMIC(CFunctions, CDialogEx)

CFunctions::CFunctions(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FUNCTIONS, pParent)
{

}

CFunctions::~CFunctions()
{
}

void CFunctions::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFunctions, CDialogEx)
	ON_BN_CLICKED(IDC_INFORMATION, &CFunctions::OnBnClickedInformation)
	ON_BN_CLICKED(IDC_DECRYPT_PIC, &CFunctions::OnBnClickedDecryptPic)
	ON_BN_CLICKED(IDC_MULTI_OPEN, &CFunctions::OnBnClickedMultiOpen)
	ON_BN_CLICKED(IDC_ADD_USER, &CFunctions::OnBnClickedAddUser)
	ON_BN_CLICKED(IDC_AUTO_CHAT, &CFunctions::OnBnClickedAutoChat)
	ON_BN_CLICKED(IDC_GET_EXPRESSION, &CFunctions::OnBnClickedGetExpression)
END_MESSAGE_MAP()



//************************************************************
// 函数名称: OnBnClickedInformation
// 函数说明: 响应个人信息按钮
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedInformation()
{
	CInformation info;
	info.DoModal();
}


//************************************************************
// 函数名称: OnBnClickedDecryptPic
// 函数说明: 响应解密图片按钮
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedDecryptPic()
{
	CDecryptImage decryptimage;
	decryptimage.DoModal();
}


//************************************************************
// 函数名称: OnBnClickedDecryptPic
// 函数说明: 响应解密图片按钮
// 作    者: GuiShou
// 时    间: 2019/7/6
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedMultiOpen()
{
	PatchWeChat();

	OpenWeChat();
}




//************************************************************
// 函数名称: OnBnClickedAddUser
// 函数说明: 响应添加好友按钮
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedAddUser()
{
	CAddUser adduser;
	adduser.DoModal();
}

//************************************************************
// 函数名称: OnBnClickedAutoChat
// 函数说明: 响应自动聊天按钮
// 作    者: GuiShou
// 时    间: 2019/7/16
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedAutoChat()
{
	//检测是否关注图灵机器人
	if (isAttentTuLing)
	{
		if (bAutoChat == FALSE)
		{
			MessageBoxW(L"自动聊天已开启");
			CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
			COPYDATASTRUCT autochat;
			autochat.dwData = WM_AutoChat;
			autochat.cbData = 0;
			autochat.lpData = NULL;
			//发送消息
			pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&autochat);
			bAutoChat = TRUE;
		}
		else
		{
			MessageBoxW(L"自动聊天已关闭");
			CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
			COPYDATASTRUCT autochat;
			autochat.dwData = WM_CancleAutoChat;
			autochat.cbData = 0;
			autochat.lpData = NULL;
			//发送消息
			pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&autochat);
			bAutoChat = FALSE;
		}
	}
	else
	{
		MessageBoxW(L"请先关注图灵机器人公众号", L"错误", 0);
	}

	
	
}


//************************************************************
// 函数名称: OnBnClickedGetExpression
// 函数说明: 提取微信表情按钮
// 作    者: GuiShou
// 时    间: 2019/7/21
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedGetExpression()
{
	char temppath[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, temppath);
	char expresspath[MAX_PATH] = { 0 };
	sprintf_s(expresspath,"%s%s", temppath, "WeChatExpressions");
	MessageBoxA(NULL, expresspath, "微信表情目录", 0);
}
