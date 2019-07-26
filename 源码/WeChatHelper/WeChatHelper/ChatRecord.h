#pragma once

void HookChatRecord();		//HOOK聊天记录
void RecieveWxMesage();		//接收微信消息
void SendWxMessage();		//发送微信消息到客户端
LPCWSTR GetMsgByAddress(DWORD memAddress);	//从地址中获取消息内容
