<<<<<<< HEAD
#pragma once
#include <string>
using namespace std;
void AgreeUserRequest(wchar_t* v1, wchar_t* v2);	//ͬ���������
void AutoAgreeUserRequest(wstring msg);	//�Զ�ͬ���������

void CllectMoney(wchar_t* transferid, wchar_t* wxid);	//�տ�
void AutoCllectMoney(wstring msg, wchar_t* wxid);	//�Զ��տ�

void AddCardUser(wchar_t* v1, wchar_t* msg);	//�����Ƭ����
void AutoAddCardUser(wstring msg);			//�Զ������Ƭ����

void CreateDir(const char *dir);		//����Ŀ¼
void ExtractExpression();				//��ȡ����
void HookExtractExpression(DWORD dwHookOffset);//HOOK��ȡ����
void OutputExpression(DWORD dwExpressionAddr);	//�������
=======
#pragma once
#include <string>
using namespace std;
void AgreeUserRequest(wchar_t* v1, wchar_t* v2);	//ͬ���������
void AutoAgreeUserRequest(wstring msg);	//�Զ�ͬ���������

void CllectMoney(wchar_t* transferid, wchar_t* wxid);	//�տ�
void AutoCllectMoney(wstring msg, wchar_t* wxid);	//�Զ��տ�

void AddCardUser(wchar_t* v1, wchar_t* msg);	//�����Ƭ����
void AutoAddCardUser(wstring msg);			//�Զ������Ƭ����

void CreateDir(const char *dir);		//����Ŀ¼
void ExtractExpression();				//��ȡ����
void HookExtractExpression(DWORD dwHookOffset);//HOOK��ȡ����
void OutputExpression(DWORD dwExpressionAddr);	//�������
>>>>>>> 06c014d... Add files via upload
