<<<<<<< HEAD
#pragma once
#include "stdafx.h"



//���յ��ı���Ϣ�ṹ��
struct MessageStruct
{
	wchar_t wxid[40];
	wchar_t content[MAX_PATH];
};


void InitWindow(HMODULE hModule);	//��ʼ������
void RegisterWindow(HMODULE hModule);		//ע�ᴰ��
=======
#pragma once
#include "stdafx.h"



//���յ��ı���Ϣ�ṹ��
struct MessageStruct
{
	wchar_t wxid[40];
	wchar_t content[MAX_PATH];
};


void InitWindow(HMODULE hModule);	//��ʼ������
void RegisterWindow(HMODULE hModule);		//ע�ᴰ��
>>>>>>> 06c014d... Add files via upload
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);	//���ڻص�