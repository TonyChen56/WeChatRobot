#pragma once


// CSendMsg 对话框

class CSendMsg : public CDialogEx
{
	DECLARE_DYNAMIC(CSendMsg)

public:
	CSendMsg(LPCTSTR TempWxid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSendMsg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SendMsg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public: 
	CString m_wxid;		//从好友列表窗口传过来的微信ID
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSend();
	int m_Radio;
	afx_msg void OnBnClickedRadio1();

	CString m_Content;
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
