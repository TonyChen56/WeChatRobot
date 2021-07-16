#pragma once


// CModifyVersion 对话框

class CModifyVersion : public CDialogEx
{
	DECLARE_DYNAMIC(CModifyVersion)

public:
	CModifyVersion(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CModifyVersion();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ModifyVersion };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_version;
	afx_msg void OnBnClickedModify();
};
