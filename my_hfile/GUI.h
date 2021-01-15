#pragma once
#ifndef __GUI_H__
#define __GUI_H__
#include <stdlib.h>
#include <stdio.h>
#include "..\include\glad\glad.h"
#include "..\include\GLFW\glfw3.h"
GLFWwindow* Mywindow;
typedef struct Texture2D
{
	unsigned textID;
	float width;
	float height;

}Texture2D;
unsigned Loadprogma(const char vertex[], const char fragment[]);
Texture2D Loadimage(const char* path);
void processInput(GLFWwindow* window);
void GLinit();


#endif // !__GUI_H__