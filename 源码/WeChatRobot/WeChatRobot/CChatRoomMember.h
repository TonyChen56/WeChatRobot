#pragma once


// CChatRoomMember 对话框

class CChatRoomMember : public CDialogEx
{
	DECLARE_DYNAMIC(CChatRoomMember)

public:
	CChatRoomMember(LPCTSTR TempWxid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChatRoomMember();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATROOM_MEMBER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_ChatRoomWxid;		//从好友列表窗口传过来的群ID
	CListCtrl m_ChatRoomMembers;
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSendChatRoomAt();
	afx_msg void OnCopyWxid();
	afx_msg void OnDelRoomMember();
};
