// CMyTableCtrl.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CMyTableCtrl.h"


// CMyTableCtrl

IMPLEMENT_DYNAMIC(CMyTableCtrl, CTabCtrl)

CMyTableCtrl::CMyTableCtrl()
{

}

CMyTableCtrl::~CMyTableCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTableCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTableCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTableCtrl 消息处理程序




void CMyTableCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nNum = GetCurSel();
	for (int i = 0; i < 3; i++)
	{
		if (i == nNum)
		{
			m_Dia[i]->ShowWindow(SW_SHOW);
		}
		else
		{
			m_Dia[i]->ShowWindow(SW_HIDE);
		}
	}
	*pResult = 0;
}
