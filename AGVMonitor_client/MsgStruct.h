#pragma once

/*
	45 31 E1
	01 AGC车号
	01 M1消息标签
	01 M2消息标签
	01 M6消息标签
	00 01 当前所走段距离（mm）
	00 01 当前段号
	00 01 当前点号
	00 01 AGC状态位
	01 AGC错误码
	01 预留
	00 01 当前速度（mm/s）
	01 移动完成&操作完成
	00 01 当前任务号
	合计：21B sizeof() = 22B
*/
struct Msg_E1
{
	const BYTE head[3] = { 0x45, 0x31 };		// 包头
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