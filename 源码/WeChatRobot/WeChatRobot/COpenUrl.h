#pragma once


// COpenUrl 对话框

class COpenUrl : public CDialogEx
{
	DECLARE_DYNAMIC(COpenUrl)

public:
	COpenUrl(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COpenUrl();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OpenUrl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_urls;
	afx_msg void OnBnClickedOpen();
};
