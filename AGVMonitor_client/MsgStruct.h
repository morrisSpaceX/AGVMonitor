#pragma once

/*
	45 31 E1
	01 AGC����
	01 M1��Ϣ��ǩ
	01 M2��Ϣ��ǩ
	01 M6��Ϣ��ǩ
	00 01 ��ǰ���߶ξ��루mm��
	00 01 ��ǰ�κ�
	00 01 ��ǰ���
	00 01 AGC״̬λ
	01 AGC������
	01 Ԥ��
	00 01 ��ǰ�ٶȣ�mm/s��
	01 �ƶ����&�������
	00 01 ��ǰ�����
	�ϼƣ�21B sizeof() = 22B
*/
struct Msg_E1
{
	const BYTE head[3] = { 0x45, 0x31 };		// ��ͷ
	BYTE agcNo;
	BYTE m1Tag;
	BYTE m2Tag;
	BYTE m6Tag;
	UINT16 curDist;
	UINT16 curSecNo;
	UINT16 curPointNo;
	UINT16 agcStatus;
	BYTE agcErrNo;
	BYTE reverse;
	UINT16 curSpeed;
	BYTE moveOrOpt;
	UINT16 curTaskNo;
};