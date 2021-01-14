#pragma once
#ifndef _CLIENT_
#define _CLIENT_

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "My_struct.h"

extern cursor table_cursor;
extern cursor muem_cursor;
extern cursor select_cursor;
extern cell cell_data[10][10];
extern change_selete My_change;
extern process My_process;
extern char* temp_str;
extern queue keyin;

void color(WORD a);
void print_table();
void print_stream();
void print_meun();
void print_normal_muen();
void print_change_muen();
void process_turningto();
DWORD WINAPI print(LPVOID pM);

#endif // !_CLIENT_