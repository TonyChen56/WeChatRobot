#include "stdafx.h"
#include "WndMsgLoop.h"
#include "InitWeChat.h"
#include "Login.h"
#include "MainWindow.h"
#include "MainWindow.h"
#include "FriendList.h"
#include "ChatRecord.h"
#include "Function.h"
#include "ChatRoomOperate.h"
#include "CAutoFunction.h"

extern BOOL g_AutoChat;


//************************************************************
// ��������: RegisterWindow
// ����˵��: ��ʼ������ 
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: HMODULE hModule ���
// �� �� ֵ: void 
//************************************************************
void InitWindow(HMODULE hModule)
{
	//��鵱ǰ΢�Ű汾
	if (IsWxVersionValid())
	{
		Sleep(100);
		//��ȡWeChatWin�Ļ�ַ
		DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	
		//���΢���Ƿ��½
		DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset + 0x194;
		if (*(DWORD*)dwIsLogin == 0)	//����0˵��΢��δ��¼
		{
			//���̳߳������΢�ŵ�½״̬
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CheckIsLogin, 0, 0, NULL);

			//HOOK��ȡ�����б��call
			HookGetFriendList();

			//HOOK������Ϣ
			HookChatRecord();

			//HOOK������
			AntiRevoke();

			//HOOK��ȡ����
			HookExtractExpression(WxGetExpressionsAddr);

			//ע�ᴰ��
			RegisterWindow(hModule);
		}
		else
		{
			//���΢���Ѿ���½ ������Ϣ���ͻ���
			//���ҵ�½���ھ��
			HWND hLogin = FindWindow(NULL, L"Login");
			if (hLogin == NULL)
			{
				MessageBoxA(NULL, "δ���ҵ�Login����", "����", MB_OK);
				return;
			}
			COPYDATASTRUCT login_msg;
			login_msg.dwData = WM_AlreadyLogin;
			login_msg.lpData = NULL;
			login_msg.cbData = 0;
			//������Ϣ�����ƶ�
			SendMessage(hLogin, WM_COPYDATA, (WPARAM)hLogin, (LPARAM)&login_msg);
		}
	}
	else
	{
		MessageBoxA(NULL, "��ǰ΢�Ű汾��ƥ�䣬������WeChat2.6.8.52", "����", MB_OK);
	}

}


//************************************************************
// ��������: RegisterWindow
// ����˵��: ע�ᴰ��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: HMODULE hModule ���ھ��
// �� �� ֵ: void 
//************************************************************

void RegisterWindow(HMODULE hModule)
{
	//1  ���һ��������
	WNDCLASS wnd;
	wnd.style = CS_VREDRAW | CS_HREDRAW;//���
	wnd.lpfnWndProc = WndProc;//���ڻص�����ָ��.
	wnd.cbClsExtra = NULL;
	wnd.cbWndExtra = NULL;
	wnd.hInstance = hModule;
	wnd.hIcon = NULL;
	wnd.hCursor = NULL;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = TEXT("WeChatHelper");
	//2  ע�ᴰ����
	RegisterClass(&wnd);
	//3  ��������
	HWND hWnd = CreateWindow(
		TEXT("WeChatHelper"),  //��������
		TEXT("WeChatHelper"),//������
		WS_OVERLAPPEDWINDOW,//���ڷ��
		10, 10, 500, 300, //����λ��
		NULL,             //�����ھ��
		NULL,             //�˵����
		hModule,        //ʵ�����
		NULL              //����WM_CREATE��Ϣʱ�ĸ��Ӳ���
	);
	//4  ������ʾ����
	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);
	//5  ��Ϣѭ������Ϣ�ã�
	MSG  msg = {};
	//   5.1��ȡ��Ϣ
	while (GetMessage(&msg, 0, 0, 0))
	{
		//   5.2������Ϣ
		TranslateMessage(&msg);
		//   5.3ת������Ϣ�ص�����
		DispatchMessage(&msg);
	}
}


//************************************************************
// ��������: WndProc
// ����˵��: �ص����� ���ںͿ��ƶ�ͨ�� 
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam
// �� �� ֵ: LRESULT 
//************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_COPYDATA)
	{
		COPYDATASTRUCT *pCopyData = (COPYDATASTRUCT*)lParam;
		switch (pCopyData->dwData)
		{
			//��ʾ��ά��
		case WM_ShowQrPicture:
		{
			GotoQrCode();
			HookQrCode(QrCodeOffset);
		}
		break;
		//�˳�΢��
		case WM_Logout:
		{
			LogoutWeChat();
		}
		break;
		//�����ı���Ϣ
		case WM_SendTextMessage:
		{
			MessageStruct *textmessage = (MessageStruct*)pCopyData->lpData;
			SendTextMessage(textmessage->wxid,textmessage->content);
			
		}
		//�����ļ���Ϣ
		case WM_SendFileMessage:
		{
			MessageStruct *textmessage = (MessageStruct*)pCopyData->lpData;
			SendFileMessage(textmessage->wxid, textmessage->content);	
		}
		break;
		//��ȡ������Ϣ
		case WM_GetInformation:
		{
			GetInformation();
		}
		break;
		//����ͼƬ��Ϣ
		case WM_SendImageMessage:
		{
			MessageStruct *textmessage = (MessageStruct*)pCopyData->lpData;
			SendImageMessage(textmessage->wxid, textmessage->content);
		}
		break;
		//����Ⱥ����
		case WM_SetRoomAnnouncement:
		{
			MessageStruct *textmessage = (MessageStruct*)pCopyData->lpData;
			SetWxRoomAnnouncement(textmessage->wxid, textmessage->content);
		}
		break;
		//ɾ������
		case WM_DeleteUser:
		{
			DeleteUser((wchar_t*)pCopyData->lpData);
		}
		break;
		//�˳�Ⱥ��
		case WM_QuitChatRoom:
		{
			QuitChatRoom((wchar_t*)pCopyData->lpData);
		}
		break;
		//���Ⱥ��Ա
		case WM_AddGroupMember:
		{
			struct AddGroupMem
			{
				wchar_t chatroomid[50];
				wchar_t wxid[50];
			};

			AddGroupMem *addgroupmember = (AddGroupMem*)pCopyData->lpData;
			AddGroupMember(addgroupmember->chatroomid, addgroupmember->wxid);
		}
		break;
		//������Ƭ
		case WM_SendXmlCard:
		{
			struct XmlCardMessage
			{
				wchar_t RecverWxid[50];		//�����ߵ�΢��ID
				wchar_t SendWxid[50];		//��Ҫ���͵�΢��ID
				wchar_t NickName[50];		//�ǳ�
			};

			XmlCardMessage* pCardMessage = (XmlCardMessage*)pCopyData->lpData;
			SendXmlCard(pCardMessage->RecverWxid, pCardMessage->SendWxid, pCardMessage->NickName);
		}
		break;
		//��ʾȺ��Ա
		case WM_ShowChatRoomMembers:
		{
			ShowChatRoomUser((wchar_t*)pCopyData->lpData);
		}
		break;
		//��Ӻ���
		case WM_AddUser:
		{
			struct AddUserStruct
			{
				wchar_t wxid[50];
				wchar_t content[50];
			};
			AddUserStruct* addUser = (AddUserStruct*)pCopyData->lpData;
			AddWxUser(addUser->wxid, addUser->content);
		}
		break;
		//�޸�Ⱥ����
		case WM_SetRoomName:
		{
			struct SetRoomNameStruct
			{
				wchar_t roomwxid[50];
				wchar_t roomname[50];
			};
			SetRoomNameStruct *setroomname = (SetRoomNameStruct*)pCopyData->lpData;
			SetRoomName(setroomname->roomwxid, setroomname->roomname);
		}
		break;
		//�Զ�����
		case WM_AutoChat:
		{
			g_AutoChat = TRUE;
		}
		break;
		//ȡ���Զ�����
		case WM_CancleAutoChat:
		{
			g_AutoChat = FALSE;
		}
		break;
		//���Ͱ�����Ϣ
		case WM_SendAtMsg:
		{
			struct AtMsg
			{
				wchar_t chatroomid[50] = { 0 };
				wchar_t memberwxid[50] = { 0 };
				wchar_t membernickname[50] = { 0 };
				wchar_t msgcontent[100] = { 0 };
			};
			AtMsg *msg = (AtMsg*)pCopyData->lpData;
			SendRoomAtMsg(msg->chatroomid,msg->memberwxid,msg->membernickname,msg->msgcontent);

		}
		break;
		//ɾ��Ⱥ��Ա
		case WM_DelRoomMember:
		{
			struct DelMemberStruct
			{
				wchar_t roomid[50];
				wchar_t memberwxid[50];
			};
			DelMemberStruct *msg = (DelMemberStruct*)pCopyData->lpData;
			DelRoomMember(msg->roomid, msg->memberwxid);
		}
		break;


		default:
			break;
		}
	}
	return DefWindowProc(hWnd, Message, wParam, lParam);
}




