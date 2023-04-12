#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <time.h>
using namespace std;

#define BOARD_SIZE 10
#define LEFT 3
#define TOP 1
#define GOAL 5
#define MENU_OPTIONS 4

struct _POINT { int x, y, c; };

extern _POINT _A[BOARD_SIZE][BOARD_SIZE];
extern _POINT _MENU[MENU_OPTIONS];

extern bool _TURN; //Lượt đánh
extern int _COMMAND; //Phím mà người chơi nhấn
extern int _X, _Y;
extern int MODE; //1:menu 2:game 3:file game