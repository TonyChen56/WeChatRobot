// CFunctions.cpp: 实现文件
//

#include "stdafx.h"
#include <direct.h>
#include <stdio.h>
#include "WeChatRobot.h"
#include "CFunctions.h"
#include "afxdialogex.h"
#include "CInformation.h"
#include "CDecryptImage.h"
#include "CMultiOpen.h"
#include "CAddUser.h"
#include "CFriendList.h"
#include "COpenUrl.h"
#include "CSendXmlAricle.h"
#include "CCreateChatRoom.h"
#include "CModifyVersion.h"
#include "CFollowAccount.h"


extern BOOL isAttentTuLing;		//是否关注聊天机器人
BOOL bAutoChat = FALSE;			//自动聊天

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
	ON_BN_CLICKED(IDC_OPEN_URL, &CFunctions::OnBnClickedOpenUrl)
	ON_BN_CLICKED(IDC_SendXmlArticle, &CFunctions::OnBnClickedSendxmlarticle)
	ON_BN_CLICKED(IDC_SendMsgByTimer, &CFunctions::OnBnClickedSendmsgbytimer)
	ON_BN_CLICKED(IDC_CreateRoom, &CFunctions::OnBnClickedCreateroom)
	ON_BN_CLICKED(IDC_ModifyVersion, &CFunctions::OnBnClickedModifyversion)
	ON_BN_CLICKED(IDC_FollowAccount, &CFunctions::OnBnClickedFollowaccount)
	ON_BN_CLICKED(IDC_KeyWordsReply, &CFunctions::OnBnClickedKeywordsreply)
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
	unique_ptr<CInformation> info(new CInformation);
	info->DoModal();
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
// 函数名称: OnBnClickedMultiOpen
// 函数说明: 响应无限多开按钮
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
	//检测是否关注聊天机器人
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
		MessageBoxW(L"请先关注小冰的宇宙公众号", L"提示", 0);
	}
}


//************************************************************
// 函数名称: OnBnClickedOpenUrl
// 函数说明: 打开微信浏览器
// 作    者: GuiShou
// 时    间: 2019/9/10
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedOpenUrl()
{
	COpenUrl openurl;
	openurl.DoModal();
}


//************************************************************
// 函数名称: OnBnClickedSendxmlarticle
// 函数说明: 发送xml文章
// 作    者: GuiShou
// 时    间: 2019/9/30
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedSendxmlarticle()
{
}


//************************************************************
// 函数名称: OnBnClickedSendmsgbytimer
// 函数说明: 定时发送
// 作    者: GuiShou
// 时    间: 2019/10/14
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedSendmsgbytimer()
{
		
}

//************************************************************
// 函数名称: OnBnClickedCreateroom
// 函数说明: 创建群聊
// 作    者: GuiShou
// 时    间: 2019/10/22
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedCreateroom()
{

}


//************************************************************
// 函数名称: OnBnClickedModifyversion
// 函数说明: 修改版本号
// 作    者: GuiShou
// 时    间: 2019/10/28
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedModifyversion()
{

}



//************************************************************
// 函数名称: OnBnClickedFollowaccount
// 函数说明: 关注公众号
// 作    者: GuiShou
// 时    间: 2019/11/19
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedFollowaccount()
{

}



//************************************************************
// 函数名称: OnBnClickedKeywordsreply
// 函数说明: 开启或关闭关键词回复
// 作    者: GuiShou
// 时    间: 2019/11/20
// 参    数: void
// 返 回 值: void
//***********************************************************
void CFunctions::OnBnClickedKeywordsreply()
{
	
}
