#pragma once
#ifndef _SERVER_
#define _SERVER_
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "My_struct.h"
#include "str.h"

extern process My_process;
extern change_selete My_change;
extern queue keyin;
extern char* temp_str;
extern cursor table_cursor;
extern cursor select_cursor;
extern cursor muem_cursor;
extern cursor stream_cursor;
extern cell cell_data[10][10];

DWORD WINAPI serving(LPVOID pM);

void normal_input(int key);
void cmd_save();
void cmd_load();
void cmd_exit();
void change_select(int key);
void change_tablecursor();
void change_selectcursor();
void change_edit(int key);
char* get_funstr_print(int x, int y);
void change_sort(int key);
void sort_num();//Î´Íê³É
void sort_str();
void change_sum(int key);
#endif // !_SERVER_


