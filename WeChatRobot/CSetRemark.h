#pragma once


// CSetRemark 对话框

class CSetRemark : public CDialogEx
{
	DECLARE_DYNAMIC(CSetRemark)

public:
	CSetRemark(LPCTSTR TempWxid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetRemark();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SetRemark };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_wxid;		//从好友列表窗口传过来的微信ID
	CString m_remark;
	afx_msg void OnBnClickedSetremark();
};
