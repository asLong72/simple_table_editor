#include "hashmap.h"

extern Hashmap my_table;
void init_tabel()
{
	my_table.a = Hash_array_size;
	my_table.t_array = (map_indicat*)malloc(my_table.a * sizeof(map_indicat));
	for (int i = 0; i < my_table.a; i++)
	{
		my_table.t_array[i].head = NULL;
		my_table.t_array[i].next = NULL;
	}
}