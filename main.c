#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#pragma warning(disable:4996)

#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

#include "my_hfile/My_struct.h"
// #include "my_hfile/GUI.h"
#include "my_hfile/client.h"
#include "my_hfile/server.h"

// GLFWwindow* window = NULL;
Hashmap my_table;
process My_process;
change_selete My_change;
queue keyin;
cell cell_data[10][10];
cursor table_cursor;
cursor select_cursor;
cursor muem_cursor;
char* temp_str = NULL;
/*
【基本要求】
1）	建立表格。建立空白表格，同时在屏幕上显示，使其处于可输入数据状态。
2）	输入数据与编辑数据。通过键盘将数据输入到显示在屏幕上的电子表格中，同时要支持基本的数据输入编辑功能。
3）	基本统计计算。统计计算的种类包括：合计、求平均、求最大/小统计计算方式；表格按行/列统计计算；表格按块统计计算。
4）	排序。使任一行/列中的数据按大小（升或降）排列，对字符串型数据，还要可选大小写敏感。
5）	表格保存。使电子表格存储在磁盘上（磁盘文件），并可随时读入，供继续处理。
6）	数据复制。将表格中任一块数据，复制到另一块中。复制到目标块时，对目标块中原内容，可选择下列几种处理方式：代替、相加、相减、按条件替换。
7）	公式支持。单元格内可输入公式（表达式），使对应单元格的最终内容为公式的计算结果。公式最基本的形式是算术计算公式。公式中可以按名引用其他单元格。
*/


void init_array()
{
	My_process = VEIWING;
	My_change = none_change;
	keyin.rail = 0;
	table_cursor.x = 1, table_cursor.y = 1;
	select_cursor.x = 1, select_cursor.y = 1;
	muem_cursor.x = 1, muem_cursor.y = 1;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			cell_data[i][j].cell = STR;
			cell_data[i][j].data_real = (char*)malloc(sizeof(char) * 100);
			cell_data[i][j].str_print = cell_data[i][j].data_real;
			if (!cell_data[i][j].data_real)
			{
				exit(-1);
			}
			cell_data[i][j].data_real[0] = '\0';
			if (rand()%20>15)
			{
				
			}//strcat(cell_data[i][j].data_real,"123");
		}
	}
}
int main()
{
	My_process = VEIWING;
	init_array();
	//serving(NULL);
	HANDLE back_handle = CreateThread(NULL, 0, serving, NULL, 0, NULL);
	HANDLE print_handle = CreateThread(NULL, 0, print, NULL, 0, NULL);
	while (1);
	return 0;
}
