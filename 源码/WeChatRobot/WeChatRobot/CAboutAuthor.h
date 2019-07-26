#pragma once


// CAboutAuthor 对话框

class CAboutAuthor : public CDialogEx
{
	DECLARE_DYNAMIC(CAboutAuthor)

public:
	CAboutAuthor(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAboutAuthor();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUT_AUTHOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_kanxue;
	CString m_wuaipojie;
	CString m_csdn;
	CString m_email;
	CString m_github;
};
