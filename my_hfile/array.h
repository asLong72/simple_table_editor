#pragma once
#ifndef _ARRAY_
#define _ARRAY_
#define array_MAXSIZE 100
typedef struct int_array
{
	int data[array_MAXSIZE];
	unsigned num;
}int_array;
int pushback_array(int_array* a, int data);
int insert_array(int_array* a, int data, int path);
int replace_array(int_array* a, int data, int path);
#endif // !_ARRAY_
