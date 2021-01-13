#include "server.h"

#define normal_muen_size 3
#define change_muen_size 4
#define sort_muen_size_for_STR  4 
#define sort_muen_size (cell_data[table_cursor.y - 1][table_cursor.x - 1].cell == STR ? sort_muen_size_for_STR : sort_muen_size_for_STR-1)
_Bool if_check;
_Bool if_Vertical;
_Bool if_rise;

_Bool* set[sort_muen_size_for_STR];

DWORD WINAPI serving(LPVOID pM)
{
	set[0] = NULL;
	set[1] = &if_Vertical;
	set[2] = &if_rise;
	set[3] = &if_check;
	if_check = FALSE;
	if_Vertical = FALSE;
	if_rise = FALSE;
	My_process = CHANGED;
	//My_process = VEIWING;
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
		if (key == 27)
		{
			cmd_exit();
		}
		switch (My_process)
		{
		case NONE_PROC:
			break;
		case LOADING:
			break;
		case VEIWING:
			switch (My_change)
			{
			case none_change:
			case select_cmd:
				normal_input(key);
				break;
			default:
				My_process = CHANGING;
				break;
			}

			break;
		case SAVING:
			My_process;

			My_process = VEIWING;
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
				break;
			case sort:
				break;
			default:
				My_process = CHANGED;
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
			default:
				My_process = CHANGED;
				break;
			}

			break;
		case CHANGED:
			switch (My_change)
			{
			case none_change:
				select_cursor.x = 1;
				select_cursor.y = 1;
				break;
			case select_change:
				My_process = TOCHANGE;
				break;
			case move_cursor:
				break;
			case edit:
				My_process = CHANGING;
				break;
			case sort:
				My_process = CHANGING;
				break;
			default:
				break;
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
		if (select_cursor.x > 1)
		{
			select_cursor.x--;
			My_change = select_cmd;
			My_process = CHANGED;
		}
		break;
	case 116://ctrl+右
		if (select_cursor.x < normal_muen_size)
		{
			select_cursor.x++;
			My_change = select_cmd;
			My_process = CHANGED;
		}
		break;
	case 13://回车
		My_process = TOCHANGE;
		My_change = select_change;
		break;
	case 10://ctrl+回车
		switch (select_cursor.x)
		{
		case 1:
			My_process = SAVING;
			break;
		case 2:
			My_process = LOADING;
			break;
		case 3:
			exit(0);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
void change_select(int key)
{
	switch (key)
	{
	case 72://上
		if (select_cursor.x > 1)
		{
			select_cursor.x--;
			My_process = CHANGED;
		}
		break;
	case 80://下 
		if (select_cursor.x < change_muen_size)
		{
			select_cursor.x++;
			My_process = CHANGED;
		}
		break;
	case 75://左		
		if (select_cursor.x > 1)
		{
			select_cursor.x--;
			My_process = CHANGED;
		}
		break;
	case 77://右
		if (select_cursor.x < change_muen_size)
		{
			select_cursor.x++;
			My_process = CHANGED;
		}
		break;
	case 13://回车
		switch (select_cursor.x)
		{
		case 0:
			My_change = select_change;
			break;
		case 1:
			keyin.rail = strlen(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real);
			int i = 0;
			for (; i < keyin.rail; i++)
			{
				keyin.data[i] = cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real[i];
			}
			My_change = edit;
			break;
		case 2:
			My_change = sort;
			break;
		case 3:
			My_change = sum;
			break;
		default:
			My_change = select_change;
			break;
		}
		select_cursor.x = 1;
		select_cursor.y = 1;
		My_process = CHANGING;
		return;
		break;
	default:
		break;
	}

}
void cmd_save()
{
	FILE* a = fopen("", "wt");



	fclose(a);
	printf("SAVED");
}
void cmd_load()
{

}
void cmd_exit()
{
	char a[] = "程序退出";
	int len = strlen(a);
	My_process = ENDING;
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

void change_edit(int key)
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
		if (select_cursor.x > 1)
		{
			select_cursor.x--;
			My_process = CHANGED;
		}
		break;
	case 77://右
		if (select_cursor.x)
		{
			select_cursor.x++;
			My_process = CHANGED;
		}
		break;
	case 13://回车
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
		cell_data[table_cursor.y - 1][table_cursor.x - 1].str_print = cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real;

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
	My_process = CHANGED;
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
		if (select_cursor.x > 1)
		{
			select_cursor.x--;
			My_process = CHANGED;
		}
		break;
	case 77://右
		if (select_cursor.x < sort_muen_size)
		{
			select_cursor.x++;
			My_process = CHANGED;
		}
		break;
	case 13://回车
		switch (select_cursor.x)
		{
		case 1:
			sort_str();
			My_change = none_change;
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
void change_sum(int key)
{
	switch (key)
	{
	case 72://上
		if (select_cursor.y > 1)
		{
			select_cursor.y--;
			My_process = CHANGED;
		}
		break;
	case 80://下 
		if (select_cursor.y < 10)
		{
			select_cursor.y++;
			My_process = CHANGED;
		}
		break;
	case 75://左		
		if (select_cursor.x > 1)
		{
			select_cursor.x--;
			My_process = CHANGED;
		}
		break;
	case 77://右
		if (select_cursor.x < 10)
		{
			select_cursor.x++;
			My_process = CHANGED;
		}
		break;
	case 13://回车
		;
		int sum = 0;
		int tempmax_x = table_cursor.x > select_cursor.x ? table_cursor.x : select_cursor.x, tempmax_y = table_cursor.y > select_cursor.y ? table_cursor.y : select_cursor.y;

		for (size_t i = table_cursor.y < select_cursor.y ? table_cursor.y : select_cursor.y; i < tempmax_y; i++)
		{
			for (size_t j = table_cursor.x < select_cursor.x ? table_cursor.x : select_cursor.x; j < tempmax_x; j++)
			{
				if (cell_data[i][j].cell == NUM)
				{
					//sum += cell_data[i][j].data_real;
				}
			}
		}
		cell temp = { .cell = NUM,.data_real = strchr("",sum) };

		My_process = CHANGING;
		break;
	default:
		break;
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
char* get_funstr_print()
{
	for (size_t i = 0; i < 1; i++)
	{

	}

}
