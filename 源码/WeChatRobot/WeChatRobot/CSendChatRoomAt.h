#pragma once


// CSendChatRoomAt 对话框

class CSendChatRoomAt : public CDialogEx
{
	DECLARE_DYNAMIC(CSendChatRoomAt)

public:
	CSendChatRoomAt(LPCTSTR TempWxid, LPCTSTR TempNickName, LPCTSTR TempChatRoomid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSendChatRoomAt();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SENDAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_msg;
	afx_msg void OnBnClickedSendat();


	CString m_MemberWxid;		//从好友列表窗口传过来的微信ID
	CString m_MemberNickName;		//从好友列表窗口传过来的微信昵称
	CString m_ChatRoomid;		//从好友列表窗口传过来的群ID
};
