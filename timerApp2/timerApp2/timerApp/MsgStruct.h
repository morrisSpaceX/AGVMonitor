#pragma once

/*
	M6: 任务目标点
	21 08 41 (21 41 开始结束 08 包体长度)
	4D 36 (4D 36表示本消息是M6消息) 
	01 (消息标签1-255循环利用) 
	01 (AGC车号) 
	01 00 (任务编号上位机指定2字节) 
	06 00 (任务目标点2字节)
*/
struct Msg_M6
{
	const BYTE head[3] = { 0x21, 0x08, 0x41 };		// 包头
	const BYTE type[2] = { 0x4D, 0x36 };			// 消息类型
	BYTE tag;					// 消息标签
	BYTE agvno;					// AGV车号
	unsigned short taskno;				// 任务编号
	unsigned short target;				// 任务目标点
};

/*
	M1: 移动路径
	21(包头开始标志)10(包体长度) 41(包头结束标志)
	4D 31(M1)
	01(消息标签1-255)
	01(AGC车号)
	01 00(任务编号与下位机缓存的M6编号一致)
	01(段数目1-25)
	00 02(可行走段号,2B一段)
	00 03 00 04 00 05 00   原则上不会操作57字节(0x39)，即段数不会超过25
*/
struct Msg_M1
{
	const BYTE head[3] = { 0x21, 0x39, 0x41 };
	const BYTE type[2] = { 0x4D, 0x31 };
	BYTE tag;
	BYTE agvno;
	unsigned short taskno;
	BYTE secnum;			// 段的数目
	BYTE secno[50];
};


/*
	M2: 任务操作码
	21 08 41
	4D 32(M2)
	01(消息标签1-255)
	01(AGC车号)
	01 00(任务编号与下位机缓存的M6编号一致)
	90 01(任务操作码)
*/
struct Msg_M2
{
	const BYTE head[3] = { 0x21, 0x08, 0x41 };
	const BYTE type[2] = { 0x4D, 0x32 };
	BYTE tag;
	BYTE agvno;
	unsigned short taskno;
	BYTE taskopcode[2];			// 任务操作码
};

