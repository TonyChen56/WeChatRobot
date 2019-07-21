#pragma once


// CRoomAnnouncement 对话框

class CRoomAnnouncement : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomAnnouncement)

public:
	CRoomAnnouncement(LPCTSTR TempWxid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRoomAnnouncement();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROOMANNOUNCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Announcement;
	afx_msg void OnBnClickedSendroomannouncement();

	CString m_ChatRoomWxid;		//从好友列表窗口传过来的群ID
};
