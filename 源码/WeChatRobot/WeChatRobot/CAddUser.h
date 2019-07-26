#pragma once


// CAddUser 对话框

class CAddUser : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUser)

public:
	CAddUser(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddUser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_wxid;
	CString m_content;
	afx_msg void OnBnClickedAddUser();
};
