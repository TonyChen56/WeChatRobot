// CDecryptDatabase.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "CDecryptDatabase.h"
#include "afxdialogex.h"
#include <iostream>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/hmac.h>
#include <afxpriv.h>
#include <string.h>

using namespace std;

#pragma comment(lib, "..\\openssl-1.0.2l-win32-msvc100\\ssleay32.lib")
#pragma comment(lib, "..\\openssl-1.0.2l-win32-msvc100\\libeay32.lib")

#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE* __cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}
#endif /* _MSC_VER>=1900 */



#undef _UNICODE
#define SQLITE_FILE_HEADER "SQLite format 3" 
#define IV_SIZE 16
#define HMAC_SHA1_SIZE 20
#define KEY_SIZE 32

#define SL3SIGNLEN 20


#ifndef ANDROID_WECHAT
#define DEFAULT_PAGESIZE 4096       //4048数据 + 16IV + 20 HMAC + 12
#define DEFAULT_ITER 64000
#else
#define NO_USE_HMAC_SHA1
#define DEFAULT_PAGESIZE 1024
#define DEFAULT_ITER 4000
#endif



// CDecryptDatabase 对话框

IMPLEMENT_DYNAMIC(CDecryptDatabase, CDialogEx)

CDecryptDatabase::CDecryptDatabase(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DECRYPT_DB, pParent)
	, m_filepath(_T(""))
	, m_databasedir(_T(""))
	, m_databasekey(_T(""))
	, m_tip(_T(""))
{

}

CDecryptDatabase::~CDecryptDatabase()
{
}

void CDecryptDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_filepath);
	DDX_Text(pDX, IDC_EDIT2, m_databasedir);
	DDX_Text(pDX, IDC_EDIT6, m_databasekey);
	DDX_Text(pDX, IDC_EDIT3, m_tip);
}


BEGIN_MESSAGE_MAP(CDecryptDatabase, CDialogEx)
	ON_BN_CLICKED(IDC_DECRYPT, &CDecryptDatabase::OnBnClickedDecrypt)
	ON_WM_DROPFILES()
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CDecryptDatabase 消息处理程序



BOOL CDecryptDatabase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_databasedir = L"C:\\Users\\XXX\\Documents\\WeChat Files\\XXX\\Msg";
	m_tip = L"请拖拽当前登陆微信号的数据库文件进行解密";
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




//************************************************************
// 函数名称: OnBnClickedDecrypt
// 函数说明: 响应解密按钮
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: void
// 返 回 值: void
//***********************************************************
void CDecryptDatabase::OnBnClickedDecrypt()
{
	UpdateData(TRUE);
	//检查文件是否存在
	if (GetFileAttributes(m_filepath) == INVALID_FILE_ATTRIBUTES)
	{
		MessageBox(L"文件不存在 请重试");
		return;
	}

	CWnd *pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT decryptdatabase;
	decryptdatabase.dwData = WM_DecryptDatabase;
	decryptdatabase.cbData = 0;
	decryptdatabase.lpData = NULL;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&decryptdatabase);

}



//************************************************************
// 函数名称: OnDropFiles
// 函数说明: 响应拖拽文件事件
// 作    者: GuiShou
// 时    间: 2019/7/13
// 参    数: hDropInfo 文件句柄
// 返 回 值: void
//***********************************************************
void CDecryptDatabase::OnDropFiles(HDROP hDropInfo)
{
	//获取文件路径
	TCHAR szPath[MAX_PATH] = { 0 };
	DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);

	//显示密钥到控件
	m_filepath = szPath;
	UpdateData(FALSE);

	CDialogEx::OnDropFiles(hDropInfo);
}


BOOL CDecryptDatabase::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//拷贝密钥
	BYTE databasekey[0x20] = {0};
	memcpy(databasekey, pCopyDataStruct->lpData, 0x20);

	//显示密钥到控件
	m_databasekey = ByteToCString(databasekey, 0x20);
	UpdateData(FALSE);

	//复制数据库文件到当前目录下
	USES_CONVERSION;
	//首先获取文件名
	char* pfilename = strrchr(W2A(m_filepath), '\\') + 1;
	//拷贝文件到当前目录下 为了解决文件被微信占用的问题
	CopyFileA(W2A(m_filepath), pfilename, FALSE);

	//解密数据库
	DecryptDatabase(pfilename, databasekey);

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


//************************************************************
// 函数名称: DecryptDatabase
// 函数说明: 解密数据库
// 作	 者: GuiShou
// 时	 间: 2019/7/18
// 参	 数: databasepath 路径 databasekey密钥
//************************************************************
void CDecryptDatabase::DecryptDatabase(char* databasepath, BYTE* databasekey)
{
	FILE* fpdb;
	fopen_s(&fpdb, databasepath, "rb+");
	if (!fpdb) 
	{
		MessageBoxA(NULL, "打开文件错误", "Tip", 0);
		return;
	}
	fseek(fpdb, 0, SEEK_END);
	long nFileSize = ftell(fpdb);
	fseek(fpdb, 0, SEEK_SET);
	unsigned char* pDbBuffer = new unsigned char[nFileSize];
	fread(pDbBuffer, 1, nFileSize, fpdb);
	fclose(fpdb);

	unsigned char salt[16] = { 0 };
	memcpy(salt, pDbBuffer, 16);

#ifndef NO_USE_HMAC_SHA1
	unsigned char mac_salt[16] = { 0 };
	memcpy(mac_salt, salt, 16);
	for (int i = 0; i < sizeof(salt); i++) {
		mac_salt[i] ^= 0x3a;
	}
#endif

	int reserve = IV_SIZE;      //校验码长度,PC端每4096字节有48字节
#ifndef NO_USE_HMAC_SHA1
	reserve += HMAC_SHA1_SIZE;
#endif
	reserve = ((reserve % AES_BLOCK_SIZE) == 0) ? reserve : ((reserve / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;

	unsigned char key[KEY_SIZE] = { 0 };
	unsigned char mac_key[KEY_SIZE] = { 0 };

	OpenSSL_add_all_algorithms();

	PKCS5_PBKDF2_HMAC_SHA1((const char*)databasekey, 32, salt, sizeof(salt), DEFAULT_ITER, sizeof(key), key);
#ifndef NO_USE_HMAC_SHA1
	PKCS5_PBKDF2_HMAC_SHA1((const char*)key, sizeof(key), mac_salt, sizeof(mac_salt), 2, sizeof(mac_key), mac_key);
#endif

	unsigned char* pTemp = pDbBuffer;
	unsigned char pDecryptPerPageBuffer[DEFAULT_PAGESIZE];
	int nPage = 1;
	int offset = 16;
	while (pTemp < pDbBuffer + nFileSize) 
	{
#ifndef NO_USE_HMAC_SHA1
		unsigned char hash_mac[HMAC_SHA1_SIZE] = { 0 };
		unsigned int hash_len = 0;
		HMAC_CTX hctx;
		HMAC_CTX_init(&hctx);
		HMAC_Init_ex(&hctx, mac_key, sizeof(mac_key), EVP_sha1(), NULL);
		HMAC_Update(&hctx, pTemp + offset, DEFAULT_PAGESIZE - reserve - offset + IV_SIZE);
		HMAC_Update(&hctx, (const unsigned char*)& nPage, sizeof(nPage));
		HMAC_Final(&hctx, hash_mac, &hash_len);
		HMAC_CTX_cleanup(&hctx);
		if (0 != memcmp(hash_mac, pTemp + DEFAULT_PAGESIZE - reserve + IV_SIZE, sizeof(hash_mac))) {
			MessageBoxA(NULL, "哈希值错误", "Tip", 0);
			return;
		}
#endif
		//
		if (nPage == 1) {
			memcpy(pDecryptPerPageBuffer, SQLITE_FILE_HEADER, offset);
		}

		EVP_CIPHER_CTX* ectx = EVP_CIPHER_CTX_new();
		EVP_CipherInit_ex(ectx, EVP_get_cipherbyname("aes-256-cbc"), NULL, NULL, NULL, 0);
		EVP_CIPHER_CTX_set_padding(ectx, 0);
		EVP_CipherInit_ex(ectx, NULL, NULL, key, pTemp + (DEFAULT_PAGESIZE - reserve), 0);

		int nDecryptLen = 0;
		int nTotal = 0;
		EVP_CipherUpdate(ectx, pDecryptPerPageBuffer + offset, &nDecryptLen, pTemp + offset, DEFAULT_PAGESIZE - reserve - offset);
		nTotal = nDecryptLen;
		EVP_CipherFinal_ex(ectx, pDecryptPerPageBuffer + offset + nDecryptLen, &nDecryptLen);
		nTotal += nDecryptLen;
		EVP_CIPHER_CTX_free(ectx);

		memcpy(pDecryptPerPageBuffer + DEFAULT_PAGESIZE - reserve, pTemp + DEFAULT_PAGESIZE - reserve, reserve);
		char decFile[1024] = { 0 };
		sprintf_s(decFile, "dec_%s", databasepath);
		FILE * fp;
		fopen_s(&fp, decFile, "ab+");
		{
			fwrite(pDecryptPerPageBuffer, 1, DEFAULT_PAGESIZE, fp);
			fclose(fp);
		}

		nPage++;
		offset = 0;
		pTemp += DEFAULT_PAGESIZE;
	}
	MessageBoxA(NULL, "解密成功 请在当前目录下查看", "Tip", 0);
	
}



//************************************************************
// 函数名称: ByteToCString
// 函数说明: 把BYTE* 转为十六进制显示的CString
// 作	 者: GuiShou
// 时	 间: 2019/7/18
// 参	 数: BYTE * str需要转换的BYTE* DWORD dwLength 长度
//************************************************************
CString CDecryptDatabase::ByteToCString(BYTE *str, DWORD dwLength)
{
	//拷贝压缩之后的数据到数组
	BYTE tempStr[4096] = { 0 };
	memcpy(tempStr, str, dwLength);

	//将解压缩的数据转为十六进制 显示到界面
	CString cStr;
	CString data;
	DWORD i = 0;

	for (i = 0; i < dwLength; i++)
	{
		cStr.Format(L"%02x", tempStr[i]);
		data += cStr;

	}
	return data;
}