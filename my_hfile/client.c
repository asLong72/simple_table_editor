#include "client.h"
#define normal_muen_size 3
#define change_muen_size 4
#define sort_muen_size_for_STR  4 
#define sort_muen_size (cell_data[table_cursor.y - 1][table_cursor.x - 1].cell == STR ? sort_muen_size_for_STR : sort_muen_size_for_STR-1)

extern _Bool* set[];

char* normal_muen[] = { "保存", "加载", "退出", };
char* change_muen[] = { "编辑", "排序", "求和" , "复制" , };
char* sort_muen[] = { "开始","按列排序","升序","大小写区分", };

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
	while (My_process != ENDING)
	{
		if (My_process == VEIWING)
		{
			if (My_change != none_change && _kbhit())
			{
				My_process = TOCHANGE;
			}
			else
			{
				continue;
			}
		}
		system("cls");

		print_table();
		print_stream();
		print_meun();
		My_process = VEIWING;
	}

	My_process = ENDED;
}
void color(WORD a)      //自定义函根据参数改变颜色 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void print_table()
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
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
					printf("---------");
				}
			}
			else
			{
				printf("--------");
			}

		}
		printf("\n");
		for (size_t j = 0; j < 10; j++)
		{
			if (table_cursor.y == i + 1 && table_cursor.x == j + 1)
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
}
void print_stream()
{
	switch (My_process)
	{
	case NONE_PROC:
		break;
	case VEIWING:
		break;
	case LOADING:
		break;
	case SAVING:
		break;
	case CHANGED:
		if (temp_str)
		{
			printf("%s\n", temp_str);
		}
		break;
	case TOCHANGE:
		if (temp_str)
		{
			printf("%s\n", temp_str);
		}
		break;
	case CHANGING:
		for (size_t i = 0; i < keyin.rail; i++)
		{
			printf("%c", keyin.data[i]);
		}
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
		if (i == select_cursor.x - 1)
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
			if (i == select_cursor.x - 1)
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
			if (i == select_cursor.x - 1)
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
	case sum:
		break;
	default:
		break;
	}
}