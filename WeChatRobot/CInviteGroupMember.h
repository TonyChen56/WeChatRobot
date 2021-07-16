#pragma once


// CInviteGroupMember 对话框

class CInviteGroupMember : public CDialogEx
{
	DECLARE_DYNAMIC(CInviteGroupMember)

public:
	CInviteGroupMember(LPCTSTR TempGroupId, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInviteGroupMember();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_InviteMember };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_ChatRoomWxid;		//从好友列表窗口传过来的群ID
	CString m_wxid;
	afx_msg void OnBnClickedInvite();
};
