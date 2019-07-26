#pragma once


// CFunctions 对话框

class CFunctions : public CDialogEx
{
	DECLARE_DYNAMIC(CFunctions)

public:
	CFunctions(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFunctions();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FUNCTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInformation();
	afx_msg void OnBnClickedDecryptPic();

	afx_msg void OnBnClickedMultiOpen();
	afx_msg void OnBnClickedAddUser();
	afx_msg void OnBnClickedAutoChat();
	afx_msg void OnBnClickedGetExpression();
};
