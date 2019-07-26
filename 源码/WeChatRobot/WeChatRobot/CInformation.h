#pragma once


// CInformation 对话框

class CInformation : public CDialogEx
{
	DECLARE_DYNAMIC(CInformation)

public:
	CInformation(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInformation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFORMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	CString m_header;
	CString m_city;
	CString m_province;
	CString m_nation;
	CString m_device;
	CString m_phone;
	CString m_nickname;
	CString m_count;
	CString m_wxid;
	CString m_sex;
};
