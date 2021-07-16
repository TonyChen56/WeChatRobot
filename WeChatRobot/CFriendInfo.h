#pragma once


// CFriendInfo 对话框

class CFriendInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CFriendInfo)

public:
	CFriendInfo(LPCTSTR TempWxid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFriendInfo();

	CString m_Wxid;		//从好友列表窗口传过来的微信ID

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FRIENDINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_wxid;
	CString m_wxnumber;
	CString m_wxv1;
	CString m_wxremark;
	CString m_wxnickname;
	CString wxsmallheader;
	CString wxbigheader;
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};
