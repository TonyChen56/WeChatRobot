#pragma once


// CDecryptDatabase 对话框

class CDecryptDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(CDecryptDatabase)

public:
	CDecryptDatabase(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDecryptDatabase();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DECRYPT_DB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDecrypt();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CString m_filepath;
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	CString m_databasedir;
	virtual BOOL OnInitDialog();
	CString m_databasekey;

public:
	CString ByteToCString(BYTE *str, DWORD dwLength);	//把BYTE* 转为十六进制显示的CString

	void DecryptDatabase(char* databasepath, BYTE* databasekey);	//解密数据库
	CString m_tip;
};
