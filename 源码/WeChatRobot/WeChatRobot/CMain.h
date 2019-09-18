#pragma once
#include "CMyTableCtrl.h"

// CMain 对话框

class CMain : public CDialogEx
{
	DECLARE_DYNAMIC(CMain)

public:
	CMain(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMain();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyTableCtrl m_MyTable;
	virtual BOOL OnInitDialog();
	afx_msg void OnWxLogout();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnPayAuthor();
	afx_msg void OnAboutAuthor();
	afx_msg void OnClose();
	afx_msg void OnSaveFriendList();
};
