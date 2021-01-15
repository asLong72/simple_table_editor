#include "client.h"
#define normal_muen_size 3
#define change_muen_size 7
#define edit_muen_size 3 
#define sort_muen_size_for_STR  4 
#define sort_muen_size (cell_data[table_cursor.y - 1][table_cursor.x - 1].cell == STR ? sort_muen_size_for_STR : sort_muen_size_for_STR-1)
#define copy_muen_size 3

extern _Bool* set[];
extern _Bool if_select_cmd;
extern int readProc_precent;
char* normal_muen[] = { "保存", "加载", "退出", };
char* change_muen[] = { "编辑", "排序", "求和" ,"求平均","最大值","最小值" , "复制" , };
char* edit_muen[] = { "数字","字符","函数", };
char* sort_muen[] = { "开始","按列排序","升序","大小写区分", };
char* copy_muen[] = { "覆盖","相加","相减", };
int x1 = 1, y1 = 1;
int x2 = 1, y2 = 1;
DWORD WINAPI print(LPVOID pM)
{

	/*
	GLinit();
	Texture2D a = Loadimage("cell.png");
	float deltetime, lasttime = glfwGetTime(), time = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);

		//glDrawElementsInstancedBaseInstance();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	*/
	while (My_process == NONE_PROC);
	while (My_process != ENDING)
	{
		if (My_process == VEIWING)
		{
			if (_kbhit() && My_change != none_change)
			{
				if (if_select_cmd == TRUE)
				{
					My_process = CHANGING;
				}
				else
				{
					My_process = TOCHANGE;
				}
			}
			else if (
				x1 != (table_cursor.x < select_cursor.x ? table_cursor.x : select_cursor.x) ||
				y1 != (table_cursor.y < select_cursor.y ? table_cursor.y : select_cursor.y) ||

				x2 != (table_cursor.x > select_cursor.x ? table_cursor.x : select_cursor.x) ||
				y2 != (table_cursor.y > select_cursor.y ? table_cursor.y : select_cursor.y))
			{
				x1 = table_cursor.x < select_cursor.x ? table_cursor.x : select_cursor.x;
				y1 = table_cursor.y < select_cursor.y ? table_cursor.y : select_cursor.y;

				x2 = table_cursor.x > select_cursor.x ? table_cursor.x : select_cursor.x;
				y2 = table_cursor.y > select_cursor.y ? table_cursor.y : select_cursor.y;
			}
			else
			{
				continue;
			}
		}
		else if (My_process == LOADING && readProc_precent != 100)
		{
			continue;
		}



		system("cls");

		print_table();
		print_stream();
		print_meun();
		if (My_process == CHANGED)
		{

		}My_process = VEIWING;
	}

	My_process = ENDED;
}
void color(WORD a)      //自定义函根据参数改变颜色 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void print_table()
{
	printf("       |");
	for (size_t j = 0; j < 10; j++)
	{
		if (table_cursor.x == j + 1)
		{

			if (strlen(cell_data[0][j].str_print))
			{
				int len = strlen(cell_data[0][j].str_print) + 1;
				len = (len > 6) ? len : 6;
				for (size_t i = 0; i < len - 1; i++)
				{
					printf(" ");
				}

			}
			else
			{
				printf("     ");
			}
		}
		else
		{
			printf("     ");
		}
		if (j < 9)
		{
			printf(" %c|", '1' + j);
		}
		else
		{
			printf("10|");
		}
	}
	printf("\n");
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 11; j++)
		{
			if (table_cursor.y == i + 1 && table_cursor.x == j + 1)
			{

				if (strlen(cell_data[i][j].str_print))
				{
					int len = strlen(cell_data[i][j].str_print) + 1;
					len = (len > 9) ? len : 9;
					for (size_t i = 0; i < len; i++)
					{
						printf("-");
					}
				}
				else
				{
					printf("--------");
				}
			}
			else
			{
				printf("--------");
			}

		}
		printf("\n");
		printf("      ");
		printf("%c|", 'A' + i);
		for (size_t j = 0; j < 10; j++)
		{
			if ((y1 <= i + 1 && x1 <= j + 1) && (y2 >= i + 1 && x2 >= j + 1))
			{
				color(0 | FOREGROUND_INTENSITY | 112 | BACKGROUND_INTENSITY);
				printf("%7s", cell_data[i][j].data_real);
				color(7);
				printf("|");
			}
			else
			{
				printf("%7.7s|", cell_data[i][j].str_print);
			}

		}
		printf("\n");
	}
	//printf("%d|%d\n", table_cursor.x, table_cursor.y);
	//printf("%d|%d", select_cursor.x, select_cursor.y);
}
void print_stream()
{
	int now_precent = readProc_precent >= 0 ? readProc_precent / 10 : readProc_precent;
	switch (My_process)
	{
	case NONE_PROC:
		break;
	case VEIWING:
		break;
	case LOADING:
		switch (now_precent)
		{
		case -1:
			printf("读取失败！文件不存在");
			break;
		default:
			printf("[");
			for (size_t i = 0; i < 10; i++)
			{
				if (i < now_precent)
				{
					printf("#");
				}
				else
				{
					printf(" ");
				}
			}
			printf("]");
			break;
		}
		printf("\n");
		break;
	case SAVING:
		switch (now_precent)
		{
		case -1:
			printf("保存失败！");
			break;
		default:
			printf("[");
			for (size_t i = 0; i < 10; i++)
			{
				if (i < now_precent)
				{
					printf("#");
				}
				else
				{
					printf(" ");
				}
			}
			printf("]");
			break;
		}
		printf("\n");
		break;
	case CHANGED:
		printf("单元格数据：");
		for (size_t i = 0; i < keyin.rail; i++)
		{
			printf("%c", keyin.data[i]);
		}
		printf("\n");
		break;
	case TOCHANGE:
		printf("单元格数据：");
		for (size_t i = 0; i < keyin.rail; i++)
		{
			printf("%c", keyin.data[i]);
		}
		printf("\n");
		break;
	case CHANGING:
		printf("数据将放到以 ");
		for (size_t i = 0; i < keyin.rail; i++)
		{
			printf("%c", keyin.data[i]);
		}
		printf(" 为起点的单元格（区域）中");
		printf("\n");
		break;
	}

}
void print_meun()
{
	switch (My_process)
	{
	case CHANGED:
		if (My_change == none_change || My_change == select_cmd)
		{
			print_normal_muen();
		}
		else
		{
			print_change_muen();
		}
		break;
	case TOCHANGE:
	case CHANGING:
		print_change_muen();
		break;
	default:
		break;
	}

}
void print_normal_muen()
{
	for (size_t i = 0; i < normal_muen_size; i++)
	{
		for (size_t j = strlen(normal_muen[i]) + 4; j; j--)
		{
			printf("=");
		}
		printf("\t");
	}
	printf("\n");
	for (size_t i = 0; i < normal_muen_size; i++)
	{
		if (i == muem_cursor.x - 1)
		{
			printf("||");
			color(0 | FOREGROUND_INTENSITY | 112 | BACKGROUND_INTENSITY);
			printf("%s", normal_muen[i]);
			color(7);
			printf("||");
		}
		else
		{
			printf("||");
			printf("%s", normal_muen[i]);
			printf("||");
		}
		printf("\t");
	}
	printf("\n");
	for (size_t i = 0; i < normal_muen_size; i++)
	{
		for (size_t j = strlen(normal_muen[i]) + 4; j; j--)
		{
			printf("=");
		}
		printf("\t");
	}
	printf("\n");
}
void print_change_muen()
{
	switch (My_change)
	{
	case select_change:
		for (size_t i = 0; i < change_muen_size; i++)
		{
			for (size_t j = strlen(change_muen[i]) + 4; j; j--)
			{
				printf("=");
			}
			printf("\t");
		}
		printf("\n");
		for (size_t i = 0; i < change_muen_size; i++)
		{
			if (i == muem_cursor.x - 1)
			{
				printf("||");
				color(0 | FOREGROUND_INTENSITY | 112 | BACKGROUND_INTENSITY);
				printf("%s", change_muen[i]);
				color(7);
				printf("||");
			}
			else
			{
				printf("||");
				printf("%s", change_muen[i]);
				printf("||");
			}
			printf("\t");
		}
		printf("\n");
		for (size_t i = 0; i < change_muen_size; i++)
		{
			for (size_t j = strlen(change_muen[i]) + 4; j; j--)
			{
				printf("=");
			}
			printf("\t");
		}
		printf("\n");
		break;
	case edit:
		for (size_t i = 0; i < edit_muen_size; i++)
		{
			for (size_t j = strlen(edit_muen[i]) + 4; j; j--)
			{
				printf("=");
			}
			printf("\t");
		}
		printf("\n");
		for (size_t i = 0; i < edit_muen_size; i++)
		{
			if (i == muem_cursor.x - 1)
			{
				printf("||");
				color(0 | FOREGROUND_INTENSITY | 112 | BACKGROUND_INTENSITY);
				printf("%s", edit_muen[i]);
				color(7);
				printf("||");
			}
			else
			{
				printf("||");
				printf("%s", edit_muen[i]);
				printf("||");
			}
			printf("\t");
		}
		printf("\n");
		for (size_t i = 0; i < edit_muen_size; i++)
		{
			for (size_t j = strlen(edit_muen[i]) + 4; j; j--)
			{
				printf("=");
			}
			printf("\t");
		}
		printf("\n");
		break;
	case sort:
		for (size_t i = 0; i < sort_muen_size; i++)
		{
			for (size_t j = strlen(sort_muen[i]) + ((i > 0) ? 8 : 4); j; j--)
			{
				printf("=");
			}
			printf("\t");
		}
		printf("\n");
		for (size_t i = 0; i < sort_muen_size; i++)
		{
			if (i == muem_cursor.x - 1)
			{
				printf("||");
				color(0 | FOREGROUND_INTENSITY | 112 | BACKGROUND_INTENSITY);
				printf("%s", sort_muen[i]);
				if (i > 0)
				{
					if (*set[i])
					{
						printf("  ON");
					}
					else
					{
						printf(" OFF");
					}

				}
				color(7);
				printf("||");
			}
			else
			{
				printf("||");
				printf("%s", sort_muen[i]);
				if (i > 0)
				{
					if (*set[i])
					{
						printf("  ON");
					}
					else
					{
						printf(" OFF");
					}

				}
				printf("||");
			}
			printf("\t");
		}
		printf("\n");
		for (size_t i = 0; i < sort_muen_size; i++)
		{
			for (size_t j = strlen(sort_muen[i]) + ((i > 0) ? 8 : 4); j; j--)
			{
				printf("=");
			}
			printf("\t");
		}
		printf("\n");
		break;
	case copy:
		for (size_t i = 0; i < copy_muen_size; i++)
		{
			for (size_t j = strlen(copy_muen[i]) + 4; j; j--)
			{
				printf("=");
			}
			printf("\t");
		}
		printf("\n");
		for (size_t i = 0; i < copy_muen_size; i++)
		{
			if (i == muem_cursor.x - 1)
			{
				printf("||");
				color(0 | FOREGROUND_INTENSITY | 112 | BACKGROUND_INTENSITY);
				printf("%s", copy_muen[i]);
				color(7);
				printf("||");
			}
			else
			{
				printf("||");
				printf("%s", copy_muen[i]);
				printf("||");
			}
			printf("\t");
		}
		printf("\n");
		for (size_t i = 0; i < copy_muen_size; i++)
		{
			for (size_t j = strlen(copy_muen[i]) + 4; j; j--)
			{
				printf("=");
			}
			printf("\t");
		}
		printf("\n");
		break;
	case sum:
		break;
	default:
		break;
	}
}