// CDecryptImage.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CDecryptImage.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <atlconv.h>


// CDecryptImage 对话框

IMPLEMENT_DYNAMIC(CDecryptImage, CDialogEx)

CDecryptImage::CDecryptImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DECRYPT_IMAGE, pParent)
	, m_ImagePath(_T(""))
	, m_imagepath(_T(""))
	, m_key(_T(""))
{

}

CDecryptImage::~CDecryptImage()
{
}

void CDecryptImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ImagePath);
	DDX_Text(pDX, IDC_EDIT2, m_imagepath);
	DDX_Text(pDX, IDC_EDIT3, m_key);
}


BEGIN_MESSAGE_MAP(CDecryptImage, CDialogEx)
	ON_BN_CLICKED(IDC_DecryptImage, &CDecryptImage::OnBnClickedDecryptimage)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CDecryptImage 消息处理程序


BOOL CDecryptImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_imagepath = L"C:\\Users\\XXX\\Documents\\WeChat Files\\XXX\\Data";
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//************************************************************
// 函数名称: OnBnClickedRadio1
// 函数说明: 响应点击解密按钮
// 作    者: GuiShou
// 时    间: 2019/7/8
// 参    数: void
// 返 回 值: void
//***********************************************************
void CDecryptImage::OnBnClickedDecryptimage()
{
	//检查文件是否存在
	if (GetFileAttributes(m_ImagePath) == INVALID_FILE_ATTRIBUTES)
	{
		MessageBox(L"图片不存在 请重试");
		return;
	}
	//检测密钥是否存在
	if (m_key=="")
	{
		MessageBox(L"密钥不能为空 请重试");
		return;
	}

	//打开文件
	HANDLE hFile = CreateFileW(m_ImagePath, GENERIC_ALL, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile==INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "打开文件失败", "错误", 0);
		return;
	}

	//获取文件大小
	DWORD dwSize = GetFileSize(hFile, NULL);

	//根据文件大小申请空间
	char *lpBuff = new char[dwSize] {0};

	//读取文件到内存
	if (ReadFile(hFile, lpBuff, dwSize, NULL, NULL)==0)
	{
		MessageBoxA(NULL, "读取文件失败", "错误", 0);
		return;
	}
	UpdateData(TRUE);
	unsigned int hexkey = 0;
	USES_CONVERSION;
	sscanf_s(W2A(m_key), "%x", &hexkey);
	//循环异或
	for (DWORD i = 0; i < dwSize; i++)
	{
		lpBuff[i] ^= hexkey;
	}
	//关闭句柄
	CloseHandle(hFile);
	
	wchar_t NewFilePath[MAX_PATH] = { 0 };
	wcscpy_s(NewFilePath, wcslen(m_ImagePath)+1, m_ImagePath);
	for (DWORD i = wcslen(m_ImagePath); i > wcslen(m_ImagePath)-4; i--)
	{
		NewFilePath[i] = 0;
	}
	wcscat_s(NewFilePath, L"png");

	//打开文件
	HANDLE hNewFile = CreateFileW(NewFilePath, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hNewFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "创建文件失败", "错误", 0);
		return;
	}

	WriteFile(hNewFile, lpBuff, dwSize, NULL, NULL);
	CloseHandle(hNewFile);

	MessageBoxA(NULL, "解密成功 请在同目录下查看", "Tip", MB_OK);

	m_ImagePath = "";
	UpdateData(FALSE);
}



//************************************************************
// 函数名称: OnDropFiles 
// 函数说明: 响应拖拽文件
// 作	 者: GuiShou
// 时	 间: 2019/7/8
// 参	 数: HDROP hDropInfo 拖拽文件句柄
// 返 回 值: void
//************************************************************
void CDecryptImage::OnDropFiles(HDROP hDropInfo)
{
	//获取文件路径
	TCHAR szPath[MAX_PATH] = { 0 };
	DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);

	//显示到控件
	m_ImagePath = szPath;

	UpdateData(FALSE);

	CDialogEx::OnDropFiles(hDropInfo);
}



