#pragma once
#ifndef _ENUM_
#define _ENUM_
typedef enum celltype
{
	NONE_TYPE = 0,
	STR,
	NUM,
	FUN,
}type;
typedef enum process
{
	NONE_PROC = 0,
	LOADING,
	VEIWING,
	SAVING,
	TOCHANGE,
	CHANGING,
	CHANGED = 6,
	ENDING,
	ENDED,
}process;
typedef enum change_selete
{
	none_change = -4,
	select_cmd,
	move_cursor,
	select_change,
	edit,
	sort,
	sum,
	max,
	min,
	avr,
	copy,
}change_selete;
typedef enum FUN_TYPE//合计、求平均、求最大 / 小
{
	NONE_FUN,
	SUM,
	AVR,
	MIN,
	MAX,
}FUN_TYPE;

#endif // !_ENUM_
