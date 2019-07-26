#pragma once


// CSendXmlCard 对话框

class CSendXmlCard : public CDialogEx
{
	DECLARE_DYNAMIC(CSendXmlCard)

public:
	CSendXmlCard(LPCTSTR TempWxid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSendXmlCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SendCard };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CString m_Wxid;		//从好友列表窗口传过来的微信ID
public:
	CString m_SendWxid;
	CString m_SendNickName;
	afx_msg void OnBnClickedSendcard();
};
