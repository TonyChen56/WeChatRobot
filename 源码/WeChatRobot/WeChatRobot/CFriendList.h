#pragma once


// CFriendList 对话框

class CFriendList : public CDialogEx
{
	DECLARE_DYNAMIC(CFriendList)

public:
	CFriendList(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFriendList();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FRIEND_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_FriendList;
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
protected:
	afx_msg LRESULT OnShowfriendlist(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnRclickFriendlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickFriendlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSendMsg();
	afx_msg void OnSetRoomAnnouncement();
	afx_msg void OnCopyWxid();
	afx_msg void OnCopyChatRoomWxid();
	afx_msg void OnDeleteUser();
	afx_msg void OnQuitChatRoom();
	afx_msg void OnAddGroupMember();
	afx_msg void OnSendRoomMessage();
	afx_msg void OnSendXmlCard();
	afx_msg void OnShowChatRoomMember();
	afx_msg void OnSetRoomName();
};
