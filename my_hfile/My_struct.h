#pragma once
#ifndef _STRUCT_
#define _STRUCT_
#include "My_enum.h"
#include "queue.h"
#include "array.h"
#include "hashmap.h"

#define TRUE 1;
#define FALSE 1;
typedef struct cell
{
	type cell;
	char* str_print;
	char* data_real;
}cell;
typedef struct cursor
{
	unsigned x;
	unsigned y;
}cursor;

#endif // _STRUCT_
