#pragma once


// CCreateChatRoom 对话框

class CCreateChatRoom : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateChatRoom)

public:
	CCreateChatRoom(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCreateChatRoom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CreateChatRoom };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_wxid1;
	CString m_wxid2;
	afx_msg void OnBnClickedCreatechatroom();
};
