#pragma once
#define stack_SIZE 100
typedef struct stack_int
{
	int data[stack_SIZE];
	unsigned top;
}stack_int;
typedef struct stack_float
{
	int data[100];
	unsigned top;
}stack_float;

int push_stack_int(stack_int* a, int data);
int pop_stack_int(stack_int* a);