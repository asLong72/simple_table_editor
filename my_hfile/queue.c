#include "queue.h"
int in_queue(queue* a, int data)
{
	if (a->rail < queue_MAXSIZE)
	{
		a->data[a->rail++] = data;
	}
	return a->rail;
}
int out_queue(queue* a)
{
	int out = a->data[0];
	if (a->rail--)
	{
		int i = 0;
		while (i < a->rail)
		{
			a->data[i] = a->data[i + 1];
			i++;
		}
		a->data[i] = 0;
	}
	return out;
}