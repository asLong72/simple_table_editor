#pragma once
#ifndef _QUEUE_
#define _QUEUE_
#define queue_MAXSIZE 100
typedef struct queue
{
	int data[queue_MAXSIZE];
	unsigned rail;
}queue;

int in_queue(queue* a, int data);
int out_queue(queue* a);
#endif // _QUEUE_