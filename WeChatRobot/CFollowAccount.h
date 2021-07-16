#pragma once


// CFollowAccount 对话框

class CFollowAccount : public CDialogEx
{
	DECLARE_DYNAMIC(CFollowAccount)

public:
	CFollowAccount(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFollowAccount();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FollowAccount };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_accountid;
	afx_msg void OnBnClickedFollow();
};
