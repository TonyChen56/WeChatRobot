#pragma once


// CPay 对话框

class CPay : public CDialogEx
{
	DECLARE_DYNAMIC(CPay)

public:
	CPay(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPay();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
