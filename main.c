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
������Ҫ��
1��	������񡣽����հױ��ͬʱ����Ļ����ʾ��ʹ�䴦�ڿ���������״̬��
2��	����������༭���ݡ�ͨ�����̽��������뵽��ʾ����Ļ�ϵĵ��ӱ���У�ͬʱҪ֧�ֻ�������������༭���ܡ�
3��	����ͳ�Ƽ��㡣ͳ�Ƽ��������������ϼơ���ƽ���������/Сͳ�Ƽ��㷽ʽ�������/��ͳ�Ƽ��㣻��񰴿�ͳ�Ƽ��㡣
4��	����ʹ��һ��/���е����ݰ���С�����򽵣����У����ַ��������ݣ���Ҫ��ѡ��Сд���С�
5��	��񱣴档ʹ���ӱ��洢�ڴ����ϣ������ļ�����������ʱ���룬����������
6��	���ݸ��ơ����������һ�����ݣ����Ƶ���һ���С����Ƶ�Ŀ���ʱ����Ŀ�����ԭ���ݣ���ѡ�����м��ִ���ʽ�����桢��ӡ�������������滻��
7��	��ʽ֧�֡���Ԫ���ڿ����빫ʽ�����ʽ����ʹ��Ӧ��Ԫ�����������Ϊ��ʽ�ļ���������ʽ���������ʽ���������㹫ʽ����ʽ�п��԰�������������Ԫ��
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
