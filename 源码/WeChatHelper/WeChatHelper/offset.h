<<<<<<< HEAD
#pragma once

#define LoginSign_Offset 0x126D860		//��½��־λ

#define QrCodeOffset 0x1F110B			//��ά��
#define QrCodeContectOffset 0x127F618	//��ά������
#define GoToQrCode1 0x1EEE30			//��ת����ά��
#define GoToQrCode2 0x2E3070			//��ת����ά��

#define Logout 0x3F2530;				//�˳�

#define FriendList 0x428965				//�����б�
#define FriendListCall 0x481F20			//�����б�

#define ReciveMessage 0x315E98			//������Ϣ
#define ReciveMessageParam 0x126D7F8		//������Ϣ�Ĳ���ƫ��

#define WxSendMessage 0x2EB4E0				//������Ϣ��call

#define WxFileMessage1 0x4818C0				//�����ļ���Ϣ
#define WxFileMessage2 0x481900				//�����ļ���Ϣ
#define WxFileMessage3 0x6BAC0				//�����ļ���Ϣ
#define WxFileMessage4 0x237DF0				//�����ļ���Ϣ
#define WxFileMessageParam 0x10A7C04		//�����ļ���Ϣ

#define WxSendImageCall1 0x817F0			//����ͼƬ��Ϣ
#define WxSendImageCall2 0x2EAED0			//����ͼƬ��Ϣ
#define WxPatchAddr 0x2E7CB5				//����ͼƬ��Ϣ

#define WxSetRoomAnnouncement 0x26CFF0			//����Ⱥ����
#define WxDeleteUser 0x274660		//ɾ������
#define WxQuitChatRoom 0x26A2F0		//�˳�Ⱥ��

#define WxAddGroupMemberCall1 0x55F10	//���Ⱥ��Ա
#define WxAddGroupMemberCall2 0x481A10	//���Ⱥ��Ա
#define WxAddGroupMemberCall3 0x67290	//���Ⱥ��Ա
#define WxAddGroupMemberCall4 0x2650D0	//���Ⱥ��Ա
#define WxAddGroupMemberParam1 0x126D8A4	//���Ⱥ��Ա
#define WxAddGroupMemberParam2 0x126DDC0	//���Ⱥ��Ա

#define WxSendXmlCard 0x2EB4E0	//������Ƭ

#define WxGetRoomUserWxidCall1 0x414680	//��ȡȺ��Ա΢��ID
#define WxGetRoomUserWxidCall2 0x2BCF20	//��ȡȺ��Ա΢��ID
#define WxGetRoomUserWxidCall3 0x41CAE0	//��ȡȺ��Ա΢��ID
#define WxGetRoomUserWxidCall4 0x415170	//��ȡȺ��Ա΢��ID

#define WxGetUserInfoByWxidCall1 0x481900	//����΢��ID��ȡ�û���Ϣ
#define WxGetUserInfoByWxidCall2 0x4FFB0	//����΢��ID��ȡ�û���Ϣ
#define WxGetUserInfoByWxidCall3 0x273280	//����΢��ID��ȡ�û���Ϣ

#define WxDatabaseKey 0x126DCE0	//΢�����ݿ���Կƫ��

#define WxAddWxUserParam1 0x1006CA8	//��Ӻ���
#define WxAddWxUserCall1 0x69C90		//��Ӻ���
#define WxAddWxUserCall2 0x58D70		//��Ӻ���
#define WxAddWxUserCall3 0x4818C0		//��Ӻ���
#define WxAddWxUserCall4 0x481900		//��Ӻ���
#define WxAddWxUserCall5 0x2715B0		//��Ӻ���

#define WxSetRoomName 0x2698A0		//�޸�Ⱥ����


#define WxCllectMoneyCall1 0x676B10		//�տ�
#define WxCllectMoneyCall2 0x676B90		//�տ�
#define WxAntiRevoke 0x312565			//������


#define WxAgreeUserRequestCall1 0x1865B0;	  //ͬ���������
#define WxAgreeUserRequestCall2 0x4F4F0;	  //ͬ���������
#define WxAgreeUserRequestCall3 0xCE4F0;	  //ͬ���������
#define WxAgreeUserRequestCall4 0x16BD40;	  //ͬ���������
#define WxAgreeUserRequestParam 0x126E050;	  //ͬ���������

#define WxGetExpressionsAddr 0x279C2E	//��ȡ΢�ű���
#define WxGetExpressionsCallAddr 0x27DE10	//��ȡ΢�ű���


#define WxDelRoomMemberCall1 0x481900	  //ɾ��Ⱥ��Ա
#define WxDelRoomMemberCall2 0x50010	  //ɾ��Ⱥ��Ա
#define WxDelRoomMemberCall3 0x2652F0	  //ɾ��Ⱥ��Ա
=======
#pragma once

#define LoginSign_Offset 0x126D860		//��½��־λ

#define QrCodeOffset 0x1F110B			//��ά��
#define QrCodeContectOffset 0x127F618	//��ά������
#define GoToQrCode1 0x1EEE30			//��ת����ά��
#define GoToQrCode2 0x2E3070			//��ת����ά��

#define Logout 0x3F2530;				//�˳�

#define FriendList 0x428965				//�����б�
#define FriendListCall 0x481F20			//�����б�

#define ReciveMessage 0x315E98			//������Ϣ
#define ReciveMessageParam 0x126D7F8		//������Ϣ�Ĳ���ƫ��

#define WxSendMessage 0x2EB4E0				//������Ϣ��call

#define WxFileMessage1 0x4818C0				//�����ļ���Ϣ
#define WxFileMessage2 0x481900				//�����ļ���Ϣ
#define WxFileMessage3 0x6BAC0				//�����ļ���Ϣ
#define WxFileMessage4 0x237DF0				//�����ļ���Ϣ
#define WxFileMessageParam 0x10A7C04		//�����ļ���Ϣ

#define WxSendImageCall1 0x817F0			//����ͼƬ��Ϣ
#define WxSendImageCall2 0x2EAED0			//����ͼƬ��Ϣ
#define WxPatchAddr 0x2E7CB5				//����ͼƬ��Ϣ

#define WxSetRoomAnnouncement 0x26CFF0			//����Ⱥ����
#define WxDeleteUser 0x274660		//ɾ������
#define WxQuitChatRoom 0x26A2F0		//�˳�Ⱥ��

#define WxAddGroupMemberCall1 0x55F10	//���Ⱥ��Ա
#define WxAddGroupMemberCall2 0x481A10	//���Ⱥ��Ա
#define WxAddGroupMemberCall3 0x67290	//���Ⱥ��Ա
#define WxAddGroupMemberCall4 0x2650D0	//���Ⱥ��Ա
#define WxAddGroupMemberParam1 0x126D8A4	//���Ⱥ��Ա
#define WxAddGroupMemberParam2 0x126DDC0	//���Ⱥ��Ա

#define WxSendXmlCard 0x2EB4E0	//������Ƭ

#define WxGetRoomUserWxidCall1 0x414680	//��ȡȺ��Ա΢��ID
#define WxGetRoomUserWxidCall2 0x2BCF20	//��ȡȺ��Ա΢��ID
#define WxGetRoomUserWxidCall3 0x41CAE0	//��ȡȺ��Ա΢��ID
#define WxGetRoomUserWxidCall4 0x415170	//��ȡȺ��Ա΢��ID

#define WxGetUserInfoByWxidCall1 0x481900	//����΢��ID��ȡ�û���Ϣ
#define WxGetUserInfoByWxidCall2 0x4FFB0	//����΢��ID��ȡ�û���Ϣ
#define WxGetUserInfoByWxidCall3 0x273280	//����΢��ID��ȡ�û���Ϣ

#define WxDatabaseKey 0x126DCE0	//΢�����ݿ���Կƫ��

#define WxAddWxUserParam1 0x1006CA8	//��Ӻ���
#define WxAddWxUserCall1 0x69C90		//��Ӻ���
#define WxAddWxUserCall2 0x58D70		//��Ӻ���
#define WxAddWxUserCall3 0x4818C0		//��Ӻ���
#define WxAddWxUserCall4 0x481900		//��Ӻ���
#define WxAddWxUserCall5 0x2715B0		//��Ӻ���

#define WxSetRoomName 0x2698A0		//�޸�Ⱥ����


#define WxCllectMoneyCall1 0x676B10		//�տ�
#define WxCllectMoneyCall2 0x676B90		//�տ�
#define WxAntiRevoke 0x312565			//�տ�


#define WxAgreeUserRequestCall1 0x1865B0;	  //ͬ���������
#define WxAgreeUserRequestCall2 0x4F4F0;	  //ͬ���������
#define WxAgreeUserRequestCall3 0xCE4F0;	  //ͬ���������
#define WxAgreeUserRequestCall4 0x16BD40;	  //ͬ���������
#define WxAgreeUserRequestParam 0x126E050;	  //ͬ���������

#define WxGetExpressionsAddr 0x279C2E	//��ȡ΢�ű���
#define WxGetExpressionsCallAddr 0x27DE10	//��ȡ΢�ű���


>>>>>>> 06c014d... Add files via upload
