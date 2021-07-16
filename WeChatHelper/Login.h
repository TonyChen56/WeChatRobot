#pragma once
#include "stdafx.h"


void HookQrCode();	//HOOK二维码
void ShowPic();		//显示二维码
void __stdcall SaveImg(DWORD qrcode);	//保存二维码
void GotoQrCode(); //跳转到二维码

