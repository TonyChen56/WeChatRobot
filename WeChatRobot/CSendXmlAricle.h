#pragma once


// CSendXmlAricle 对话框

class CSendXmlAricle : public CDialogEx
{
	DECLARE_DYNAMIC(CSendXmlAricle)

public:
	CSendXmlAricle(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSendXmlAricle();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SendXmlArticle };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_selfwxid;
	CString m_recverwxid;
	CString m_title;
	CString m_subtitle;
	CString m_linkurl;
	CString m_picpath;
	afx_msg void OnBnClickedSendxmlarticle();
};
