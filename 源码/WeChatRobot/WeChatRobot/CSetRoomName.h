#pragma once


// CSetRoomName 对话框

class CSetRoomName : public CDialogEx
{
	DECLARE_DYNAMIC(CSetRoomName)

public:
	CSetRoomName(LPCTSTR TempWxid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetRoomName();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_ROOM_NAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_ChatRoomWxid;		//从好友列表窗口传过来的群ID
	CString m_roomname;
	afx_msg void OnBnClickedSetroomname();
};
