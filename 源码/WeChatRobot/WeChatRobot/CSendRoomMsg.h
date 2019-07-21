#pragma once


// CSendRoomMsg 对话框

class CSendRoomMsg : public CDialogEx
{
	DECLARE_DYNAMIC(CSendRoomMsg)

public:
	CSendRoomMsg(LPCTSTR TempWxid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSendRoomMsg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEND_ROOM_MSG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CString m_ChatRoomWxid;		//从好友列表窗口传过来的群ID
public:
	CString m_chatroommmsg;
	afx_msg void OnBnClickedSendchatroommsg();
};
