#include "server.h"

#define normal_muen_size 3
#define change_muen_size 7
#define edit_muen_size  3 
#define sort_muen_size_for_STR  4 
#define sort_muen_size (cell_data[table_cursor.y - 1][table_cursor.x - 1].cell == STR ? sort_muen_size_for_STR : sort_muen_size_for_STR-1)
_Bool if_select_cmd;
_Bool if_check;
_Bool if_Vertical;
_Bool if_rise;
int readProc_precent = 0;

_Bool* set[sort_muen_size_for_STR];

DWORD WINAPI serving(LPVOID pM)
{
	readProc_precent = 0;
	if_select_cmd = FALSE;
	set[0] = NULL;
	set[1] = &if_Vertical;
	set[2] = &if_rise;
	set[3] = &if_check;
	if_check = FALSE;
	if_Vertical = FALSE;
	if_rise = FALSE;
	keyin.rail = 0;
	My_process = CHANGED;
	//My_change = sum;
	temp_str = (char*)malloc(sizeof(char) * strlen(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real) + 1);
	if (!temp_str)
	{
		exit(-1);
	}
	temp_str[0] = 0;
	strcat(temp_str, cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real);
	int key = 0;
	while (1)
	{
		if (_kbhit())
		{
			key = getch();
		}
		else
		{
			key = 0;
		}
		//printf("%d\n", My_process);
		//printf("%d\n", My_change);
		//printf("%d\n", key);
		//printf("%s\n", temp_str);
		//printf("%d\n", select_cursor.x);
		//printf("%d\n", muem_cursor.x);
		switch (key)
		{
		case 27:
			My_process = ENDING;
			cmd_exit();
			break;
		default:
			break;
		}
		switch (My_process)
		{
		case NONE_PROC:
			break;
		case SAVING:
			cmd_save();

			My_process = VEIWING;
			break;
		case LOADING:
			cmd_load();
			break;
		case ENDING:
			cmd_exit();
			break;
		case VEIWING:
			switch (My_change)
			{
			case none_change:
				normal_input(key);
				break;
			default:
				break;
			}

			break;
		case TOCHANGE:
			switch (My_change)
			{
			case select_change:
				change_select(key);
				break;
			case move_cursor:
				break;
			case edit:
				change_edit(key);
				break;
			case sort:
				change_sort(key);
				break;
			case sum:
				change_sum(key);
				break;
			default:
				break;
			}
			break;
		case CHANGING:
			switch (My_change)
			{
			case move_cursor:
				change_tablecursor();
				break;
			case edit:
				change_edit(key);
				break;
			case sort:
				change_sort(key);
				break;
			case sum:
				change_sum(key);
				break;
			case avr:
				break;
			case max:
				break;
			case min:
				break;
			case copy:
				break;
			default:
				break;
			}
			//
			break;
		case CHANGED:
			if (My_change == none_change)
			{
				//My_process = VEIWING;
			}
			break;
		default:
			break;
		}
		//Sleep(500);
	}
}

void normal_input(int key)
{
	switch (key)
	{
	case 72://上
		if (table_cursor.y != 1)
		{
			table_cursor.y--;
			My_change = move_cursor;
			My_process = CHANGING;
		}
		break;
	case 80://下 
		if (table_cursor.y != 10)
		{
			table_cursor.y++;
			My_change = move_cursor;
			My_process = CHANGING;
		}
		break;
	case 75://左
		if (table_cursor.x != 1)
		{
			table_cursor.x--;
			My_change = move_cursor;
			My_process = CHANGING;
		}
		break;
	case 77://右
		if (table_cursor.x != 10)
		{
			table_cursor.x++;
			My_change = move_cursor;
			My_process = CHANGING;
		}
		break;
	case 115://ctrl+左
		if (muem_cursor.x > 1)
		{
			muem_cursor.x--;
		}
		else
		{
			muem_cursor.x = 1;
		}
		My_change = move_cursor;
		My_process = CHANGING;
		break;
	case 116://ctrl+右
		if (muem_cursor.x < normal_muen_size)
		{
			muem_cursor.x++;
		}
		else
		{
			muem_cursor.x = normal_muen_size;
		}
		My_change = move_cursor;
		My_process = CHANGING;
		break;
	case 13://回车
		My_process = TOCHANGE;
		My_change = select_change;
		break;
	case 10://ctrl+回车
		switch (muem_cursor.x)
		{
		case 1:
			My_process = SAVING;
			break;
		case 2:
			My_process = LOADING;
			break;
		case 3:
			My_process = ENDED;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	select_cursor = table_cursor;
}

void cmd_save()
{
	FILE* a = fopen("Longs_simple_table.txt", "wt");
	readProc_precent = 0;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			fwrite(&cell_data[i][j].cell, sizeof(cell), 1, a);
			int len = strlen(cell_data[i][j].data_real);
			fwrite(&len, sizeof(int), 1, a);
			fwrite(cell_data[i][j].data_real, sizeof(char), len, a);
			len = strlen(cell_data[i][j].str_print);
			fwrite(&len, sizeof(int), 1, a);
			fwrite(cell_data[i][j].str_print, sizeof(char), len, a);
		}
		readProc_precent++;
	}

	fclose(a);
}
void cmd_load()
{
	FILE* a = fopen("Longs_simple_table.txt", "rt");
	if (!a)
	{
		readProc_precent = -1;
		return;
	}
	readProc_precent = 0;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			fread(&cell_data[i][j].cell, sizeof(cell), 1, a);
			int len = 0;
			fread(&len, sizeof(int), 1, a);
			free(cell_data[i][j].data_real);
			cell_data[i][j].data_real = (char)malloc(sizeof(char) * (len + 4));
			if (!cell_data[i][j].data_real)
			{
				exit(-1);
			}
			fread(cell_data[i][j].data_real, sizeof(char), len, a);
			fread(&len, sizeof(int), 1, a);
			free(cell_data[i][j].str_print);
			cell_data[i][j].str_print = (char)malloc(sizeof(char) * (len + 4));
			if (!cell_data[i][j].str_print)
			{
				exit(-1);
			}
			fread(cell_data[i][j].str_print, sizeof(char), len, a);
		}
		readProc_precent++;
	}

	fclose(a);
}
void cmd_exit()
{
	char a[] = "程序退出";
	int len = strlen(a);
	while (My_process != ENDED);
	system("cls");
	for (size_t i = 0; i < len; i++)
	{
		printf("=");
	}
	printf("\n");
	printf("%s\n", a);
	for (size_t i = 0; i < len; i++)
	{
		printf("=");
	}
	printf("\n");
	exit(0);
}

void change_select(int key)
{
	switch (key)
	{
	case 72://上
		if (muem_cursor.x > 1)
		{
			muem_cursor.x--;
		}
		else
		{
			muem_cursor.x = 1;
		}
		My_process = TOCHANGE;
		break;
	case 80://下 
		if (muem_cursor.x < change_muen_size)
		{
			muem_cursor.x++;
		}
		else
		{
			muem_cursor.x = change_muen_size;
		}
		My_process = TOCHANGE;
		break;
	case 75://左		
		if (muem_cursor.x > 1)
		{
			muem_cursor.x--;
		}
		else
		{
			muem_cursor.x = 1;
		}
		My_process = TOCHANGE;
		break;
	case 77://右
		if (muem_cursor.x < change_muen_size)
		{
			muem_cursor.x++;
		}
		else
		{
			muem_cursor.x = change_muen_size;
		}
		My_process = TOCHANGE;
		break;
	case 13://回车
		switch (muem_cursor.x)
		{
		case 0:
			My_change = select_change;
			break;
		case 1:
			change_selectcursor();
			switch (cell_data[table_cursor.y - 1][table_cursor.x - 1].cell)
			{
			case NUM:
				muem_cursor.x = 1;
				break;
			case STR:
				muem_cursor.x = 2;
				break;
			case FUN:
				muem_cursor.x = 3;
				break;
			default:
				muem_cursor.x = 1;
				break;
			}
			My_change = edit;
			break;
		case 2:
			My_change = sort;
			break;
		case 3:
			My_change = sum;
			break;
		case 4:
			My_change = avr;
			break;
		case 5:
			My_change = max;
			break;
		case 6:
			My_change = min;
			break;
		case 7:
			My_change = copy;
			break;
		default:
			My_change = select_change;
			break;
		}
		return;
		break;
	default:
		break;
	}

}
void change_edit(int key)
{
	if (My_process == TOCHANGE)
	{
		switch (key)
		{
		case 0:
			break;
		case 8:
			if (keyin.rail)
			{
				keyin.rail--;
			}
			break;
			//case 75://左
			//	if (stream_cursor.x > 1)
			//	{
			//		stream_cursor.x--;
			//	}
			//	else
			//	{
			//		stream_cursor.x = 1;
			//	}
			//	break;
			//case 77://右
			//	if (stream_cursor.x < keyin.rail)
			//	{
			//		stream_cursor.x++;
			//	}
			//	else
			//	{
			//		stream_cursor.x = keyin.rail;
			//	}
			//	break;
		case 13://回车
			if_select_cmd = TRUE;
			My_process = CHANGING;
			break;
		default:
			if (key >= 32 && key <= 127)
			{
				in_queue(&keyin, key);
			}
			break;
		}
	}
	else
	{
		switch (key)
		{
		case 75://左
			if (muem_cursor.x > 1)
			{
				muem_cursor.x--;
			}
			else
			{
				muem_cursor.x = 1;
			}
			break;
		case 77://右
			if (muem_cursor.x < edit_muen_size)
			{
				muem_cursor.x++;
			}
			else
			{
				muem_cursor.x = edit_muen_size - 1;
			}
			break;
		case 13:
			if (temp_str != NULL)
			{
				free(temp_str);
			}
			temp_str = (char*)malloc(sizeof(char) * (keyin.rail + strlen(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real) + 3));
			if (!temp_str)
			{
				exit(-1);
			}
			temp_str[0] = 0;
			temp_str[keyin.rail] = 0;
			for (size_t i = 0; keyin.rail; i++)
			{
				temp_str[i] = (char)out_queue(&keyin);
				//printf("%c", temp_str[i]);
			}
			free(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real);
			cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real = (char*)malloc(sizeof(char) * (strlen(temp_str) + 3));
			if (!cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real)
			{
				exit(-1);
			}
			cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real[0] = 0;
			strcat(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real, temp_str);

			switch (muem_cursor.x)
			{
			case 1:
				cell_data[table_cursor.y - 1][table_cursor.x - 1].cell = NUM;
				break;
			case 2:
				cell_data[table_cursor.y - 1][table_cursor.x - 1].cell = STR;
				break;
			case 3:
				cell_data[table_cursor.y - 1][table_cursor.x - 1].cell = FUN;
				break;
			default:
				break;
			}
			cell_data[table_cursor.y - 1][table_cursor.x - 1].str_print = get_funstr_print(table_cursor.x, table_cursor.y);

			if_select_cmd = FALSE;
			muem_cursor.x = 1;
			My_change = none_change;
			My_process = CHANGED;
		default:
			break;
		}
	}

}
void change_tablecursor()
{
	if (temp_str)
	{
		free(temp_str);
	}
	temp_str = (char*)malloc(sizeof(char) * strlen(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real) + 1);
	temp_str[0] = 0;
	strcat(temp_str, cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real);
	My_change = none_change;
	My_process = CHANGED;
}
void change_selectcursor()
{
	keyin.rail = strlen(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real);
	int i = 0;
	for (; i < keyin.rail; i++)
	{
		keyin.data[i] = cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real[i];
	}
}
void change_sort(int key)
{
	switch (key)
	{
	case 0:
		break;
	case 72://上
		break;
	case 80://下
		break;
	case 75://左
		if (muem_cursor.x > 1)
		{
			muem_cursor.x--;
			My_process = CHANGED;
		}
		break;
	case 77://右
		if (muem_cursor.x < sort_muen_size)
		{
			muem_cursor.x++;
			My_process = CHANGED;
		}
		break;
	case 13://回车
		switch (muem_cursor.x)
		{
		case 1:
			sort_str();

			if_select_cmd = FALSE;
			My_change = none_change;
			muem_cursor.x = 1;
			break;
		case 2:
			if_Vertical = 1 - if_Vertical;
			break;
		case 3:
			if_rise = 1 - if_rise;
			break;
		case 4:
			if_check = 1 - if_check;
			break;
		default:
			break;
		}

		My_process = CHANGED;
		break;
	default:

		break;
	}
}
cursor str2postion(char* str)
{
	cursor a;
	char temp_c;
	sscanf(str, "%c%d", &temp_c, &a.x);
	a.y = (temp_c - 'A' + 1);
	return a;
}
void change_sum(int key)
{
	if (My_process == TOCHANGE)
	{
		switch (key)
		{
		case 72://上
			if (select_cursor.y > 1)
			{
				select_cursor.y--;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.y = 1;
			}
			break;
		case 80://下 
			if (select_cursor.y < 10)
			{
				select_cursor.y++;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.y = 10;
			}
			break;
		case 75://左		
			if (select_cursor.x > 1)
			{
				select_cursor.x--;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.x = 1;
			}
			break;
		case 77://右
			if (select_cursor.x < 10)
			{
				select_cursor.x++;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.x = 10;
			}
			break;
		case 13:
			keyin.rail = 0;
			if_select_cmd = TRUE;
			My_process = CHANGING;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case 8:
			if (keyin.rail)
			{
				keyin.rail--;
			}
			break;
		case 13://回车
			if (keyin.data[0] < 'A' || keyin.data[0]>'Z')
			{
				keyin.rail = 0;
				return;
			}
			float temp_num = 0;
			float sum = 0;
			char* temp_str = (char*)malloc(sizeof(char) * (keyin.rail + 2));
			if (!temp_str)
			{
				exit(-1);
			}
			temp_str[keyin.rail] = 0;
			for (size_t i = 0; keyin.rail; i++)
			{
				temp_str[i] = (char)out_queue(&keyin);
			}
			cursor temp_pos = str2postion(temp_str);
			free(temp_str);
			cursor tempmax_pos = { .x = (table_cursor.x > select_cursor.x ? table_cursor.x : select_cursor.x),.y = (table_cursor.y > select_cursor.y ? table_cursor.y : select_cursor.y) }
			, tempmin_pos = { .x = (table_cursor.x < select_cursor.x ? table_cursor.x : select_cursor.x), .y = (table_cursor.y < select_cursor.y ? table_cursor.y : select_cursor.y) };
			if (cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real)
			{
				free(cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real);
			}
			cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real = (char*)malloc(sizeof(char) * (strlen("SUM(%c%d:%c%d)") + 2));
			if (!cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real)
			{
				exit(-1);
			}
			cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real[0] = 0;
			sprintf(cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real, "SUM(%c%d:%c%d)", tempmin_pos.y + 'A' - 1, tempmin_pos.x, tempmax_pos.y + 'A' - 1, tempmax_pos.x);
			cell_data[temp_pos.y - 1][temp_pos.x - 1].cell = FUN;
			cell_data[temp_pos.y - 1][temp_pos.x - 1].str_print = get_funstr_print(temp_pos.x, temp_pos.y);


			if_select_cmd = FALSE;
			My_change = none_change;
			My_process = CHANGED;
			break;
		default:
			if (key >= 32 && key <= 127)
			{
				in_queue(&keyin, key);
			}
			break;
		}
	}
}
void change_avr(int key)
{
	if (My_process == TOCHANGE)
	{
		switch (key)
		{
		case 72://上
			if (select_cursor.y > 1)
			{
				select_cursor.y--;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.y = 1;
			}
			break;
		case 80://下 
			if (select_cursor.y < 10)
			{
				select_cursor.y++;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.y = 10;
			}
			break;
		case 75://左		
			if (select_cursor.x > 1)
			{
				select_cursor.x--;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.x = 1;
			}
			break;
		case 77://右
			if (select_cursor.x < 10)
			{
				select_cursor.x++;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.x = 10;
			}
			break;
		case 13:
			keyin.rail = 0;
			if_select_cmd = TRUE;
			My_process = CHANGING;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case 8:
			if (keyin.rail)
			{
				keyin.rail--;
			}
			break;
		case 13://回车
			;
			if (keyin.data[0] < 'A' || keyin.data[0]>'Z')
			{
				keyin.rail = 0;
				return;
			}
			float temp_num = 0;
			float sum = 0;
			char* temp_str = (char*)malloc(sizeof(char) * (keyin.rail + 2));
			if (!temp_str)
			{
				exit(-1);
			}
			temp_str[keyin.rail] = 0;
			for (size_t i = 0; keyin.rail; i++)
			{
				temp_str[i] = (char)out_queue(&keyin);
			}
			cursor temp_pos = str2postion(temp_str);
			free(temp_str);
			cursor tempmax_pos = { .x = (table_cursor.x > select_cursor.x ? table_cursor.x : select_cursor.x),.y = (table_cursor.y > select_cursor.y ? table_cursor.y : select_cursor.y) }
			, tempmin_pos = { .x = (table_cursor.x < select_cursor.x ? table_cursor.x : select_cursor.x), .y = (table_cursor.y < select_cursor.y ? table_cursor.y : select_cursor.y) };
			if (cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real)
			{
				free(cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real);
			}
			cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real = (char*)malloc(sizeof(char) * (strlen("AVR(%c%d:%c%d)") + 2));
			if (!cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real)
			{
				exit(-1);
			}
			cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real[0] = 0;
			sprintf(cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real, "AVR(%c%d:%c%d)", tempmin_pos.y + 'A' - 1, tempmin_pos.x, tempmax_pos.y + 'A' - 1, tempmax_pos.x);
			cell_data[temp_pos.y - 1][temp_pos.x - 1].cell = FUN;
			cell_data[temp_pos.y - 1][temp_pos.x - 1].str_print = get_funstr_print(temp_pos.x, temp_pos.y);


			if_select_cmd = FALSE;
			My_change = none_change;
			My_process = CHANGED;
			break;
		default:
			if (key >= 32 && key <= 127)
			{
				in_queue(&keyin, key);
			}
			break;
		}
	}
}
void change_max(int key)
{
	if (My_process == TOCHANGE)
	{
		switch (key)
		{
		case 72://上
			if (select_cursor.y > 1)
			{
				select_cursor.y--;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.y = 1;
			}
			break;
		case 80://下 
			if (select_cursor.y < 10)
			{
				select_cursor.y++;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.y = 10;
			}
			break;
		case 75://左		
			if (select_cursor.x > 1)
			{
				select_cursor.x--;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.x = 1;
			}
			break;
		case 77://右
			if (select_cursor.x < 10)
			{
				select_cursor.x++;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.x = 10;
			}
			break;
		case 13:
			keyin.rail = 0;
			if_select_cmd = TRUE;
			My_process = CHANGING;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case 8:
			if (keyin.rail)
			{
				keyin.rail--;
			}
			break;
		case 13://回车
			;
			if (keyin.data[0] < 'A' || keyin.data[0]>'Z')
			{
				keyin.rail = 0;
				return;
			}
			float temp_num = 0;
			float sum = 0;
			char* temp_str = (char*)malloc(sizeof(char) * (keyin.rail + 2));
			if (!temp_str)
			{
				exit(-1);
			}
			temp_str[keyin.rail] = 0;
			for (size_t i = 0; keyin.rail; i++)
			{
				temp_str[i] = (char)out_queue(&keyin);
			}
			cursor temp_pos = str2postion(temp_str);
			free(temp_str);
			cursor tempmax_pos = { .x = (table_cursor.x > select_cursor.x ? table_cursor.x : select_cursor.x),.y = (table_cursor.y > select_cursor.y ? table_cursor.y : select_cursor.y) }
			, tempmin_pos = { .x = (table_cursor.x < select_cursor.x ? table_cursor.x : select_cursor.x), .y = (table_cursor.y < select_cursor.y ? table_cursor.y : select_cursor.y) };
			if (cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real)
			{
				free(cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real);
			}
			cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real = (char*)malloc(sizeof(char) * (strlen("MAX(%c%d:%c%d)") + 2));
			if (!cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real)
			{
				exit(-1);
			}
			cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real[0] = 0;
			sprintf(cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real, "MAX(%c%d:%c%d)", tempmin_pos.y + 'A' - 1, tempmin_pos.x, tempmax_pos.y + 'A' - 1, tempmax_pos.x);
			cell_data[temp_pos.y - 1][temp_pos.x - 1].cell = FUN;
			cell_data[temp_pos.y - 1][temp_pos.x - 1].str_print = get_funstr_print(temp_pos.x, temp_pos.y);


			if_select_cmd = FALSE;
			My_change = none_change;
			My_process = CHANGED;
			break;
		default:
			if (key >= 32 && key <= 127)
			{
				in_queue(&keyin, key);
			}
			break;
		}
	}
}
void change_min(int key)
{
	if (My_process == TOCHANGE)
	{
		switch (key)
		{
		case 72://上
			if (select_cursor.y > 1)
			{
				select_cursor.y--;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.y = 1;
			}
			break;
		case 80://下 
			if (select_cursor.y < 10)
			{
				select_cursor.y++;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.y = 10;
			}
			break;
		case 75://左		
			if (select_cursor.x > 1)
			{
				select_cursor.x--;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.x = 1;
			}
			break;
		case 77://右
			if (select_cursor.x < 10)
			{
				select_cursor.x++;
				My_process = CHANGED;
			}
			else
			{
				select_cursor.x = 10;
			}
			break;
		case 13:
			keyin.rail = 0;
			if_select_cmd = TRUE;
			My_process = CHANGING;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case 8:
			if (keyin.rail)
			{
				keyin.rail--;
			}
			break;
		case 13://回车
			;
			if (keyin.data[0] < 'A' || keyin.data[0]>'Z')
			{
				keyin.rail = 0;
				return;
			}
			float temp_num = 0;
			float sum = 0;
			char* temp_str = (char*)malloc(sizeof(char) * (keyin.rail + 2));
			if (!temp_str)
			{
				exit(-1);
			}
			temp_str[keyin.rail] = 0;
			for (size_t i = 0; keyin.rail; i++)
			{
				temp_str[i] = (char)out_queue(&keyin);
			}
			cursor temp_pos = str2postion(temp_str);
			free(temp_str);
			cursor tempmax_pos = { .x = (table_cursor.x > select_cursor.x ? table_cursor.x : select_cursor.x),.y = (table_cursor.y > select_cursor.y ? table_cursor.y : select_cursor.y) }
			, tempmin_pos = { .x = (table_cursor.x < select_cursor.x ? table_cursor.x : select_cursor.x), .y = (table_cursor.y < select_cursor.y ? table_cursor.y : select_cursor.y) };
			if (cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real)
			{
				free(cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real);
			}
			cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real = (char*)malloc(sizeof(char) * (strlen("MIN(%c%d:%c%d)") + 2));
			if (!cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real)
			{
				exit(-1);
			}
			cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real[0] = 0;
			sprintf(cell_data[temp_pos.y - 1][temp_pos.x - 1].data_real, "MIN(%c%d:%c%d)", tempmin_pos.y + 'A' - 1, tempmin_pos.x, tempmax_pos.y + 'A' - 1, tempmax_pos.x);
			cell_data[temp_pos.y - 1][temp_pos.x - 1].cell = FUN;
			cell_data[temp_pos.y - 1][temp_pos.x - 1].str_print = get_funstr_print(temp_pos.x, temp_pos.y);


			if_select_cmd = FALSE;
			My_change = none_change;
			My_process = CHANGED;
			break;
		default:
			if (key >= 32 && key <= 127)
			{
				in_queue(&keyin, key);
			}
			break;
		}
	}
}


void sort_num()
{
	int  x, y;
	char* temp;
	if (if_rise)
	{
		if (if_Vertical)//按列排
		{
			x = table_cursor.x - 1;
			y = 0;
			for (; y < 10; y++)
			{
				if (cell_data[y][x].cell == STR)
				{
					continue;
				}
				for (size_t i = 0; i < 10; i++)
				{
					if (cell_data[i][x].cell == STR)
					{
						continue;
					}
				}
			}
		}
		else
		{

		}
	}
	else
	{

	}
}//未完成
void sort_str()
{
	int x = if_Vertical ? table_cursor.x - 1 : 0, y = if_Vertical ? 0 : table_cursor.y - 1;
	cell temp = { .cell = NONE_TYPE };
	if (if_check)//大小写检测
	{
		if (if_Vertical)//竖行排序
		{
			for (; y < 10; y++)//上小下大（升序）
			{
				for (size_t i = 0; i < 10; i++)
				{
					if (strcmp(cell_data[y][x].str_print, cell_data[i][x].str_print) > 0)
					{
						temp = cell_data[y][x];
						cell_data[y][x] = cell_data[i][x];
						cell_data[i][x] = temp;
					}
				}
			}
		}
		else
		{
			for (; x < 10; x++)//左小右大
			{
				for (size_t i = 0; i < 10; i++)
				{
					if (strcmp(cell_data[y][x].str_print, cell_data[y][i].str_print) > 0 && strlen(cell_data[y][x].str_print) > strlen(cell_data[y][i].str_print))
					{
						temp = cell_data[y][x];
						cell_data[y][x] = cell_data[y][i];
						cell_data[y][i] = temp;
					}
				}
			}
		}
	}
	else
	{
		if (if_Vertical)//竖行排序
		{
			for (; y < 10; y++)//上小下大（升序）
			{
				for (size_t i = 0; i < 10; i++)
				{
					if (strcmp(cell_data[y][x].str_print, cell_data[i][x].str_print) > 0)
					{
						temp = cell_data[y][x];
						cell_data[y][x] = cell_data[i][x];
						cell_data[i][x] = temp;
					}
				}
			}
		}
		else
		{
			for (; x < 10; x++)//左小右大
			{
				for (size_t i = 0; i < 10; i++)
				{
					if (strcmp(cell_data[y][x].str_print, cell_data[y][i].str_print) < 0)
					{
						temp = cell_data[y][x];
						cell_data[y][x] = cell_data[y][i];
						cell_data[y][i] = temp;
					}
				}
			}
		}
	}
	if (!if_rise)//降序把前面的结果反向处理
	{

	}
	if_Vertical = FALSE;
	if_rise = FALSE;
	if_check = FALSE;
}
char* eeror_fun()
{
	char* str_print = NULL;
	str_print = (char*)malloc(sizeof(char) * strlen("ERROR_FUN") + 1);
	if (!str_print)
	{
		exit(-1);
	}
	str_print[0] = 0;
	strcat(str_print, "ERROR_FUN");
	return str_print;
}
char* get_funstr_print(int x, int y)
{
	if (cell_data[y - 1][x - 1].cell == FUN)
	{
		char* temp_str = cell_data[y - 1][x - 1].data_real;
		FUN_TYPE thiscell = NONE_FUN;
		if (temp_str[0] == 'S' && temp_str[1] == 'U' && temp_str[2] == 'M')
		{
			thiscell = SUM;
		}
		else if (temp_str[0] == 'A' && temp_str[1] == 'V' && temp_str[2] == 'R')
		{
			thiscell = AVR;
		}
		else if (temp_str[0] == 'M' && temp_str[1] == 'A' && temp_str[2] == 'X')
		{
			thiscell = MAX;
		}
		else if (temp_str[0] == 'M' && temp_str[1] == 'I' && temp_str[2] == 'N')
		{
			thiscell = MIN;
		}
		else
		{
			return eeror_fun();
		}
		int len = strlen(cell_data[y - 1][x - 1].data_real);
		if (temp_str[3] != '(' || temp_str[len - 1] != ')')
		{
			return eeror_fun();
		}
		cursor lefton, rigthtdown;
		int i = 4;
		char temp_c;
		if (sscanf(temp_str + i, "%c%d", &temp_c, &lefton.x) == EOF || !(temp_c >= 'A' && lefton.x >= 1))
		{
			return eeror_fun();
		}
		lefton.y = temp_c - ('A' - 1);
		do
		{
			i++;
		} while (temp_str[i] != ':');
		i++;
		if (sscanf(temp_str + i, "%c%d", &temp_c, &rigthtdown.x) == EOF || !(temp_c >= 'A' && rigthtdown.x >= 1))
		{
			return eeror_fun();
		}
		rigthtdown.y = temp_c - ('A' - 1);
		if (lefton.y > rigthtdown.y || lefton.x > rigthtdown.x)
		{
			return eeror_fun();
		}
		float a = 0, b = 0, temp_num = 0;
		for (size_t i = lefton.y - 1; i < rigthtdown.y; i++)
		{
			for (size_t j = lefton.x - 1; j < rigthtdown.x; j++)
			{
				if (cell_data[i][j].cell == NUM)
				{
					sscanf(cell_data[i][j].data_real, "%f", &temp_num);
					switch (thiscell)
					{
					case SUM:
						a += temp_num;
						break;
					case AVR:
						a += temp_num;
						b++;
						break;
					case MAX:
						if (a < temp_num)
						{
							a = temp_num;
						}
						break;
					case MIN:
						if (a > temp_num)
						{
							a = temp_num;
						}
						break;
					default:
						break;
					}
				}
			}
		}
		if (thiscell == AVR)
		{
			a /= b;
		}
		return float2str(a, 3);
	}
	else
	{
		return cell_data[y - 1][x - 1].data_real;
	}
}
