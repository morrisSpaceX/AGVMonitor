#pragma once

/*
	M6: ����Ŀ���
	21 08 41 (21 41 ��ʼ���� 08 ���峤��)
	4D 36 (4D 36��ʾ����Ϣ��M6��Ϣ) 
	01 (��Ϣ��ǩ1-255ѭ������) 
	01 (AGC����) 
	01 00 (��������λ��ָ��2�ֽ�) 
	06 00 (����Ŀ���2�ֽ�)
*/
struct Msg_M6
{
	const BYTE head[3] = { 0x21, 0x08, 0x41 };		// ��ͷ
	const BYTE type[2] = { 0x4D, 0x36 };			// ��Ϣ����
	BYTE tag;					// ��Ϣ��ǩ
	BYTE agvno;					// AGV����
	unsigned short taskno;				// ������
	unsigned short target;				// ����Ŀ���
};

/*
	M1: �ƶ�·��
	21(��ͷ��ʼ��־)10(���峤��) 41(��ͷ������־)
	4D 31(M1)
	01(��Ϣ��ǩ1-255)
	01(AGC����)
	01 00(����������λ�������M6���һ��)
	01(����Ŀ1-25)
	00 02(�����߶κ�,2Bһ��)
	00 03 00 04 00 05 00   ԭ���ϲ������57�ֽ�(0x39)�����������ᳬ��25
*/
struct Msg_M1
{
	const BYTE head[3] = { 0x21, 0x39, 0x41 };
	const BYTE type[2] = { 0x4D, 0x31 };
	BYTE tag;
	BYTE agvno;
	unsigned short taskno;
	BYTE secnum;			// �ε���Ŀ
	BYTE secno[50];
};


/*
	M2: ���������
	21 08 41
	4D 32(M2)
	01(��Ϣ��ǩ1-255)
	01(AGC����)
	01 00(����������λ�������M6���һ��)
	90 01(���������)
*/
struct Msg_M2
{
	const BYTE head[3] = { 0x21, 0x08, 0x41 };
	const BYTE type[2] = { 0x4D, 0x32 };
	BYTE tag;
	BYTE agvno;
	unsigned short taskno;
	BYTE taskopcode[2];			// ���������
};

