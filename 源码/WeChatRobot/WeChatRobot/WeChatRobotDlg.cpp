
// WeChatRobotDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "WeChatRobotDlg.h"
#include "afxdialogex.h"
#include "CInjectTools.h"
#include "CMain.h"

HANDLE wxPid = NULL;		//微信的PID

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWeChatRobotDlg 对话框



CWeChatRobotDlg::CWeChatRobotDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WECHATROBOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWeChatRobotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWeChatRobotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_SHOW_QRPIC, &CWeChatRobotDlg::OnBnClickedShowQrpic)
END_MESSAGE_MAP()


// CWeChatRobotDlg 消息处理程序

BOOL CWeChatRobotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//防多开
	RunSingle();



	if (InjectDll(wxPid)==FALSE)
	{
		ExitProcess(-1);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWeChatRobotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == SC_CLOSE)//对话框关闭 消息
	{
		//AfxMessageBox(L"closed");
		//CloseHandle(wxPid);
		TerminateProcess(wxPid, 0);
		CDialogEx::OnSysCommand(nID, lParam);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWeChatRobotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWeChatRobotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//************************************************************
// 函数名称: OnCopyData
// 函数说明: 接收CopyData消息
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct
// 返 回 值: BOOL
//***********************************************************
BOOL CWeChatRobotDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	if (pCopyDataStruct->dwData==WM_Login)
	{
		EndDialog(0);
		CMain mainWindow;
		mainWindow.DoModal();
	}
	else if (pCopyDataStruct->dwData == WM_AlreadyLogin)
	{
		MessageBoxA(NULL, "已经登陆微信 请重启微信 在未登录状态下运行程序", "Tip", 0);
		ExitProcess(-1);
	}

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}



//************************************************************
// 函数名称: OnBnClickedShowQrpic
// 函数说明: 响应显示二维码按钮
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: void
// 返 回 值: void
//***********************************************************
void CWeChatRobotDlg::OnBnClickedShowQrpic()
{
	//查找窗口
	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT show_qrpic;
	show_qrpic.dwData = WM_ShowQrPicture;
	show_qrpic.cbData = 0;
	show_qrpic.lpData = NULL;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&show_qrpic);

	Sleep(200);
	//显示图片
	ShowPicture();
}


//************************************************************
// 函数名称: ShowPicture
// 函数说明: 显示二维码
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: void
// 返 回 值: void
//***********************************************************
void CWeChatRobotDlg::ShowPicture()
{
	char szTempPath[MAX_PATH] = { 0 };
	char szPicturePath[MAX_PATH] = { 0 };

	//获取Temp目录
	GetTempPathA(MAX_PATH, szTempPath);
	//拼接图片完整路径
	sprintf_s(szPicturePath, "%s%s", szTempPath, "qrcode.png");

	USES_CONVERSION;
	CImage QrPic;
	QrPic.Load(A2W(szPicturePath));
	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_QRPIC);
	CDC *pDC = pWnd->GetDC();
	pWnd->GetClientRect(&rect);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	QrPic.Draw(pDC->m_hDC, rect);
	ReleaseDC(pDC);
	QrPic.Destroy();

	//删除临时文件夹下的图片
	DeleteFileA(szPicturePath);
}




//************************************************************
// 函数名称: RunSingle
// 函数说明: 防多开
// 作    者: GuiShou
// 时    间: 2019/7/9
// 参    数: void
// 返 回 值: void
//***********************************************************
void CWeChatRobotDlg::RunSingle()
{
	HANDLE hMutex = NULL;
	hMutex = CreateMutexA(NULL, FALSE, "GuiShou");
	if (hMutex)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			ExitProcess(-1);
		}
	}
}