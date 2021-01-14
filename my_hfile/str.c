#include"str.h"
char* float2str(float in, unsigned len_after_dot)
{
	int int_len = 0;
	for (int i = in; i; i /= 10)
	{
		int_len++;
	}
	int a = (in * (int)powf(10, len_after_dot));
	stack_int str = { .top = 0 };
	char* temp_str = (char*)malloc(sizeof(char) * (len_after_dot + 4));
	if (!temp_str)
	{
		exit(-1);
	}
	int i = 0;
	if (a < 0)
	{
		temp_str[i++] = '-';
	}
	for (int j = 0; j < len_after_dot + int_len; j++)
	{
		push_stack_int(&str, a % 10);
		a /= 10;
	}
	for (; i < int_len && str.top != 0; i++)
	{
		temp_str[i] = pop_stack_int(&str) + '0';
	}
	temp_str[i++] = '.';
	for (; str.top != 0; i++)
	{
		temp_str[i] = pop_stack_int(&str) + '0';
	}
	temp_str[i] = 0;
	return temp_str;
}