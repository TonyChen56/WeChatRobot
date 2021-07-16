#pragma once
#include "stdafx.h"


void InitWindow(HMODULE hModule);	//初始化窗口
void RegisterWindow(HMODULE hModule);		//注册窗口
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);	//窗口回调