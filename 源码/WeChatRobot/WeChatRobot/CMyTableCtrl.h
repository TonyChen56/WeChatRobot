#pragma once


// CMyTableCtrl

class CMyTableCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTableCtrl)

public:
	CMyTableCtrl();
	virtual ~CMyTableCtrl();
	CDialogEx* m_Dia[3];

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


