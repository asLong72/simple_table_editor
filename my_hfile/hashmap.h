#pragma once
#include <stdlib.h>
typedef struct triple
{
	unsigned x;
	unsigned y;
	char* cell_data;
	int cell_data_type;
}triple;
typedef struct triple_node
{
	triple data;
	struct triple_node* next;
}triple_node;
typedef struct map_indicat
{
	triple_node* head;
	struct map_indicat* next;
}map_indicat;

#define Hash_array_size 7
typedef struct Hashmap
{
	map_indicat* t_array;
	unsigned a;
}Hashmap;
void init_tabel();