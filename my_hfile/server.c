#include "server.h"

#define normal_muen_size 3
#define change_muen_size 7
#define edit_muen_size 3
#define sort_muen_size_for_STR 4
#define sort_muen_size (cell_data[table_cursor.y - 1][table_cursor.x - 1].cell == STR ? sort_muen_size_for_STR : sort_muen_size_for_STR-1)
#define copy_muen_size 3
_Bool if_enable;
_Bool if_select_cmd;
_Bool if_check;
_Bool if_Vertical;
_Bool if_rise;
int readProc_precent = 0;

_Bool* set[sort_muen_size_for_STR];

DWORD WINAPI serving(LPVOID pM)
{
	readProc_precent = 0;
	if_enable = TRUE;
	if_select_cmd = FALSE;
	set[0] = NULL;
	set[1] = &if_Vertical;
	set[2] = &if_rise;
	set[3] = &if_check;
	if_check = FALSE;
	if_Vertical = FALSE;
	if_rise = FALSE;
	keyin.rail = 0;
	change_tablecursor();
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
			My_process = CHANGED;
			break;
		case LOADING:
			cmd_load();
			My_process = CHANGED;
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
			case avr:
				change_sum(key);
				break;
			case max:
				change_max(key);
				break;
			case min:
				change_min(key);
				break;
			case copy:
				change_copy(key);
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
				change_avr(key);
				break;
			case max:
				change_max(key);
				break;
			case min:
				change_min(key);
				break;
			case copy:
				change_copy(key);
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
			My_process = ENDING;
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
	FILE* a = fopen("Longs_simple_table.txt", "wt"); // 打开文件
	readProc_precent = 0; // 设置全局变量：文件操作进度大小为0；
	for (size_t i = 0; i < 10; i++)// 对y轴遍历
	{
		for (size_t j = 0; j < 10; j++)// 对y轴遍历
		{
			// 存放单元格数据
			fwrite(&cell_data[i][j].cell, sizeof(type), 1, a);// 存放单元格数据类型的数据
			int len = strlen(cell_data[i][j].data_real);// 获得字符串data_real长度
			fwrite(&len, sizeof(int), 1, a);// 将data_real长度数据存入文件
			fwrite(cell_data[i][j].data_real, sizeof(char), len, a);// 将对应字符串data_real存入文件
			len = strlen(cell_data[i][j].str_print);// 获得字符串str_print长度
			fwrite(&len, sizeof(int), 1, a);// 将str_print长度数据存入文件
			fwrite(cell_data[i][j].str_print, sizeof(char), len, a);// 将对应字符串str_print存入文件
		}
		readProc_precent += 10;// 进度变量增大10(反映到字符界面即进度条增加)
		Sleep(50);
	}

	fclose(a);// 保存完成，关闭文件，防止文件损坏或占用程序内存
}
void cmd_load()
{
	FILE* a = fopen("Longs_simple_table.txt", "rt");
	int len = 0;
	if (!a)// 文件打开失败
	{
		readProc_precent = -1;// 进度变量设置特定负数值(反映到字符界面即对应报错信息)
		return;// 退出LOAD函数
	}
	readProc_precent = 0;// 设置全局变量：文件操作进度大小为0
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			fread((void*)(&cell_data[i][j].cell), sizeof(type), 1, a);// 读取单元格数据类型信息

			fread(&len, sizeof(int), 1, a);// 读取data_real长度信息
			if (cell_data[i][j].data_real != NULL)// 释放data_real旧字符串,重新开辟适合长度的字符串空间
			{
				free(cell_data[i][j].data_real);
			}
			cell_data[i][j].data_real = (char*)malloc(sizeof(char) * (len + 4));
			if (!cell_data[i][j].data_real)// 内存不足,开辟空间失败,结束程序
			{
				exit(-1);
			}
			fread(cell_data[i][j].data_real, sizeof(char), len, a); // 读取对应长度的新data_real字符串
			cell_data[i][j].data_real[len] = 0;// 末尾加'\0',防止字符串结尾异常(输出乱码/导致溢出/越界)

			fread(&len, sizeof(int), 1, a);// 读取str_print长度信息
			cell_data[i][j].str_print = (char*)malloc(sizeof(char) * (len + 4));// 释放旧str_print字符串,重新开辟适合长度的字符串空间
			if (!cell_data[i][j].str_print)// 内存不足,开辟空间失败,结束程序
			{
				exit(-1);
			}
			fread(cell_data[i][j].str_print, sizeof(char), len, a);// 读取对应长度的新data_real字符串
			cell_data[i][j].str_print[len] = 0;// 末尾加'\0',防止字符串结尾异常(输出乱码/导致溢出/越界)
		}
		readProc_precent += 10;// 进度变量增大10(反映到字符界面即进度条增加)
		Sleep(50);
	}

	fclose(a);// 读取完成，关闭文件，防止文件损坏或占用程序内存
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
			muem_cursor.x = 1;
			My_change = sort;
			break;
		case 3:
			muem_cursor.x = 1;
			My_change = sum;
			break;
		case 4:
			muem_cursor.x = 1;
			My_change = avr;
			break;
		case 5:
			muem_cursor.x = 1;
			My_change = max;
			break;
		case 6:
			muem_cursor.x = 1;
			My_change = min;
			break;
		case 7:
			muem_cursor.x = 1;
			My_change = copy;
			break;
		default:
			muem_cursor.x = 1;
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
		// 判断按下的键是什么(按键ascii码)
		switch (key)
		{
		case 75://键盘左键
			if (muem_cursor.x > 1)
			{
				muem_cursor.x--;
			}
			else
			{
				muem_cursor.x = 1;
			}
			break;
		case 77://键盘右键
			if (muem_cursor.x < edit_muen_size)
			{
				muem_cursor.x++;
			}
			else
			{
				muem_cursor.x = edit_muen_size - 1;
			}
			break;
		case 13:// 回车
			// 释放临时旧数据
			if (temp_str != NULL)
			{
				free(temp_str);
			}
			temp_str = (char*)malloc(sizeof(char) * (keyin.rail + strlen(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real) + 3));// 开辟新空间存放本次编辑单元格产生的新旧数据构成的的临时字符串
			if (!temp_str)
			{
				exit(-1);
			}
			temp_str[0] = 0;
			temp_str[keyin.rail] = 0;		// 为字符串尾部添加结束符'\0'防止字符串在使用时乱码或溢出
			// 用temp_str字符串来存放keyin的数据(以出队形式按序(先进先出)释放)
			for (size_t i = 0; keyin.rail; i++)
			{
				temp_str[i] = (char)out_queue(&keyin);
				//printf("%c", temp_str[i]);
			}
			// 释放data_real旧数据
			free(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real);
			cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real = (char*)malloc(sizeof(char) * (strlen(temp_str) + 3));// 开辟新空间存放新的data_real
			if (!cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real)// 开辟失败说明程序内存不足,结束程序
			{
				exit(-1);
			}
			// 为新开辟的字符串添加结束符'\0'防止字符串在使用时乱码或溢出
			// strcat()函数以结束符为标识将第二个参数的字符串接到第一个字符串'\0'处形成新字符串(需要第一个字符串存储空间足够长)
			cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real[0] = 0;
			// 用中间字符串temp_str来桥接新旧字符串
			strcat(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real, temp_str);

			// 通过光标muem_cursor结构体的成员 x 判断新数据应当是什么类型
			switch (muem_cursor.x)
			{
			case 1:
				cell_data[table_cursor.y - 1][table_cursor.x - 1].cell = NUM;// 为数字
				break;
			case 2:
				cell_data[table_cursor.y - 1][table_cursor.x - 1].cell = STR;// 为字符串(默认)
				break;
			case 3:
				cell_data[table_cursor.y - 1][table_cursor.x - 1].cell = FUN;// 为函数表达式
				break;
			default:
				break;
			}
			// 用get_funstr_print函数通过单元格实际数据data_real字符串获得应当在字符界面输出的字符串str_print
			cell_data[table_cursor.y - 1][table_cursor.x - 1].str_print = get_funstr_print(table_cursor.x, table_cursor.y);

			// 复原全局变量，方便下一次使用
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
	if (!temp_str)
	{
		exit(-1);
	}
	temp_str[0] = 0;
	strcat(temp_str, cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real);
	int len = strlen(cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real);
	keyin.rail = 0;
	for (size_t i = 0; i < len; i++)
	{
		in_queue(&keyin, cell_data[table_cursor.y - 1][table_cursor.x - 1].data_real[i]);
	}

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
void change_copy(int key)
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
		case 75://左		
			if (muem_cursor.x > 1)
			{
				muem_cursor.x--;
			}
			else
			{
				select_cursor.x = 1;
			}
			break;
		case 77://右
			if (muem_cursor.x < copy_muen_size)
			{
				muem_cursor.x++;
			}
			else
			{
				muem_cursor.x = copy_muen_size;
			}
			break;
		case 13://回车
			if (keyin.data[0] < 'A' || keyin.data[0]>'Z')
			{
				keyin.rail = 0;
				return;
			}
			copy_mode My_copy;
			switch (muem_cursor.x)
			{
			case 1:
				My_copy = cover;
				break;
			case 2:
				My_copy = add;
				break;
			case 3:
				My_copy = sub;
				break;
			default:
				break;
			}
			int len = 0;
			float temp_num = 0, a = 0;
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
			if ((tempmax_pos.x - tempmin_pos.x > 10 - temp_pos.x) || (tempmax_pos.y - tempmin_pos.y > 10 - temp_pos.y))
			{
				if_enable = FALSE;
				return;
			}

			int delta_x = temp_pos.x - tempmin_pos.x, delta_y = temp_pos.y - tempmin_pos.y;

			for (size_t i = tempmin_pos.y - 1; i < tempmax_pos.y; i++)
			{
				for (size_t j = tempmin_pos.x - 1; j < tempmax_pos.x; j++)
				{
					switch (My_copy)
					{
					case cover:
						if (cell_data[i + delta_y][j + delta_x].data_real)
						{
							free(cell_data[i + delta_y][j + delta_x].data_real);
						}
						if (cell_data[i + delta_y][j + delta_x].cell == FUN)
						{
							free(cell_data[i + delta_y][j + delta_x].str_print);
						}
						cell_data[i + delta_y][j + delta_x] = cell_data[j][i];
						cell_data[i + delta_y][j + delta_x].data_real = (char*)malloc(sizeof(char) * (strlen(cell_data[i][j].data_real) + 2));
						if (!cell_data[i + delta_y][j + delta_x].data_real)
						{
							exit(-1);
						}
						cell_data[i + delta_y][j + delta_x].data_real[0] = 0;
						strcat(cell_data[i + delta_y][j + delta_x].data_real, cell_data[i][j].data_real);
						cell_data[i + delta_y][j + delta_x].str_print = get_funstr_print(j + delta_x + 1, i + delta_y + 1);
						break;
					case add:
						if (cell_data[i][j].cell == NUM)
						{
							sscanf(cell_data[i + delta_y][j + delta_x].data_real, "%f", &temp_num);
							a = temp_num;
							sscanf(cell_data[i][j].data_real, "%f", &temp_num);
							a += temp_num;
							free(cell_data[i + delta_y][j + delta_x].data_real);
							cell_data[i + delta_y][j + delta_x].data_real = float2str(a, 3);
							cell_data[i + delta_y][j + delta_x].str_print = get_funstr_print(j + delta_x + 1, i + delta_y + 1);
						}
						else if (cell_data[i][j].cell == STR)
						{
							len = strlen(cell_data[i][j].data_real) + strlen(cell_data[i + delta_y][j + delta_x].data_real) + 1;
							temp_str = (char*)malloc(sizeof(char) * (len + 1));
							if (!temp_str)
							{
								exit(-1);
							}
							temp_str[0] = 0;
							strcat(temp_str, cell_data[i + delta_y][j + delta_x].data_real);
							strcat(temp_str, cell_data[i][j].data_real);
							free(cell_data[i + delta_y][j + delta_x].data_real);
							cell_data[i + delta_y][j + delta_x].data_real = (char*)malloc(sizeof(char) * (strlen(temp_str) + 1));
							if (!cell_data[i + delta_y][j + delta_x].data_real)
							{
								exit(-1);
							}
							cell_data[i + delta_y][j + delta_x].data_real[0] = 0;
							strcat(cell_data[i + delta_y][j + delta_x].data_real, temp_str);
							free(temp_str);
						}
						break;
					case sub:
						if (cell_data[i][j].cell == NUM)
						{
							sscanf(cell_data[i + delta_y][j + delta_x].data_real, "%f", &temp_num);
							a = temp_num;
							sscanf(cell_data[i][j].data_real, "%f", &temp_num);
							a -= temp_num;
							free(cell_data[i + delta_y][j + delta_x].data_real);
							cell_data[i + delta_y][j + delta_x].data_real = float2str(a, 3);
							cell_data[i + delta_y][j + delta_x].str_print = get_funstr_print(j + delta_x + 1, i + delta_y + 1);
						}
						break;
					default:
						break;
					}
				}
			}

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
void sort_str()// 选择排序（内循环每轮把剩下最大值和外循环的位置交换）
{
	int x = if_Vertical ? table_cursor.x - 1 : 0, y = if_Vertical ? 0 : table_cursor.y - 1;// 三目判断表达式：a ? b : c ，a成立返回（执行）表达式b，不成立执行c
	cell temp = { .cell = NONE_TYPE };//循环中的临时变量,起交换位置时临时存放单元格数据的作用
	if (if_check)// 大小写检测开启为真
	{
		if (if_Vertical)// 竖列排序为真,x轴不变
		{
			for (y = 0; y < 10; y++)
			{
				for (int i = y; i < 10; i++)
				{
					if (strcmp(cell_data[y][x].str_print, cell_data[i][x].str_print) > 0)// 上小下大（即升序）,当字符串1大于字符串2时strcmp函数返回值大于0
					{
						// 交换二维数组中的两个单元格的数据
						temp = cell_data[y][x];
						cell_data[y][x] = cell_data[i][x];
						cell_data[i][x] = temp;
					}
				}
			}
		}
		else// 横行排序,y轴不变
		{
			for (x = 0; x < 10; x++)// 左小右大
			{
				for (size_t i = x; i < 10; i++)
				{
					if (strcmp(cell_data[y][x].str_print, cell_data[y][i].str_print) > 0)// 左小右大(升序)
					{
						temp = cell_data[y][x];
						cell_data[y][x] = cell_data[y][i];
						cell_data[y][i] = temp;
					}
				}
			}
		}
	}
	else// 不检查大小写
	{
		if (if_Vertical)// 竖列排序
		{
			for (y = 0; y < 10; y++)
			{
				for (size_t i = y; i < 10; i++)
				{
					if (stricmp(cell_data[y][x].str_print, cell_data[i][x].str_print) > 0)//上小下大（升序）stricmp函数不区分大小写
					{
						temp = cell_data[y][x];
						cell_data[y][x] = cell_data[i][x];
						cell_data[i][x] = temp;
					}
				}
			}
		}
		else// 横行排序
		{
			for (x = 0; x < 10; x++)
			{
				for (size_t i = x; i < 10; i++)
				{
					if (stricmp(cell_data[y][x].str_print, cell_data[y][i].str_print) > 0)// 左小右大,stricmp不区分大小写
					{
						temp = cell_data[y][x];
						cell_data[y][x] = cell_data[y][i];
						cell_data[y][i] = temp;
					}
				}
			}
		}
	}
	if (!if_rise)// 升序为假(即要求降序排列),就把前面的升序结果反向(全交换)
	{
		if (if_Vertical)
		{
			for (y = 0; y < 10; y++)// 上大下小
			{
				for (size_t i = y; i < 10; i++)
				{
					if (stricmp(cell_data[y][x].str_print, cell_data[i][x].str_print) < 0)// 不区分大小写
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
			for (x = 0; x < 10; x++)// 左大右小
			{
				for (size_t i = x; i < 10; i++)
				{
					if (stricmp(cell_data[y][x].str_print, cell_data[y][i].str_print) < 0)
					{
						temp = cell_data[y][x];
						cell_data[y][x] = cell_data[y][i];
						cell_data[y][i] = temp;
					}
				}
			}
		}
	}
	// 复原相关配置全局布尔型变量,便于下次使用
	if_Vertical = FALSE;// 是否竖列排列
	if_rise = FALSE;// 是否升序排列
	if_check = FALSE;// 是否检查大小写
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
