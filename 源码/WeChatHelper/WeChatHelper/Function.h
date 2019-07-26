#pragma once
void GetInformation();	//获取个人信息
wchar_t * UTF8ToUnicode(const char* str); //将UTF8编码转为Unicode(微信默认编码为UTF8)
void AddWxUser(wchar_t* wxid, wchar_t* msg);	//添加好友
void AntiRevoke();	//防撤回




