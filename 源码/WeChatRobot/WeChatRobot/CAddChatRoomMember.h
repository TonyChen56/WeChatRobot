#pragma once


// CAddChatRoomMember 对话框

class CAddChatRoomMember : public CDialogEx
{
	DECLARE_DYNAMIC(CAddChatRoomMember)

public:
	CAddChatRoomMember(LPCTSTR TempWxid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddChatRoomMember();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_MEMBER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_wxid;				//用户输入的微信ID
	CString m_ChatRoomWxid;		//从好友列表窗口传过来的群ID
	afx_msg void OnBnClickedMakeSure();
};
