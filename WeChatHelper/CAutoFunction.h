#pragma once
#include <atlstr.h>

void AgreeUserRequest(wchar_t* v1, wchar_t* v2);	//同意好友请求
void AutoAgreeUserRequest(wstring msg);	//自动同意好友请求
void CllectMoney(wchar_t* transferid, wchar_t* wxid);	//收款
void AutoCllectMoney(wstring msg, wchar_t* wxid);	//自动收款
void AddCardUser(wchar_t* v1, wchar_t* msg);	//添加名片好友
void AutoAddCardUser(wstring msg);			//自动添加名片好友
void CreateDir(const char *dir);		//创建目录
void ExtractExpression();				//提取表情
void HookExtractExpression();//HOOK提取表情
void __stdcall OutputExpression(DWORD dwExpressionAddr);	//输出表情
void CreateFileWithCurrentTime(char* filedir, char* filepostfix, DWORD filedata, DWORD filedatalen);	//用当前时间创建文件
wstring GetXmlContent(wstring fullxmlcontent, wstring str1, wstring str2);	//获取需要的XML内容
