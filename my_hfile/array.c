#include "array.h"
int pushback_array(int_array* a, int data)
{
	if (a->num < array_MAXSIZE)
	{
		a->data[a->num++] = data;
	}
	return a->num;
}
int insert_array(int_array* a, int data, int path)
{
	if (a->num < array_MAXSIZE && path < a->num)
	{
		for (int i = a->num++; i > path; i--)
		{

		}
		a->data[path] = data;
		return path;
	}
	return 0;
}
int replace_array(int_array* a, int data, int path)
{
	if (path < a->num)
	{
		a->data[path] = data;
		return path;
	}
	return 0;
}