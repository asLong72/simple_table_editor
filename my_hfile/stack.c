#include "stack.h"
int push_stack_int(stack_int* a, int data)
{
	if (a->top < stack_SIZE)
	{
		a->data[a->top++] = data;
	}
	return a->top;
}
int pop_stack_int(stack_int* a)
{
	if (a->top)
	{
		return a->data[--a->top];
	}
	return a->top;
}