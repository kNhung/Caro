#pragma once
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

#define BOARD_SIZE 10
#define LEFT 3
#define TOP 1
#define CENTER_X 40
#define CENTER_Y 10
#define GOAL 5
#define MENU_SIZE 4

struct _POINT { int x, y, c; };
struct _LIST {
	int x, y;
	string item;
};

extern _POINT _A[BOARD_SIZE][BOARD_SIZE];
extern _POINT _MENU[MENU_SIZE];

extern bool _TURN; //Lượt đánh 1:X  0:O
extern int _COMMAND; //Phím mà người chơi nhấn
extern int _X, _Y;
extern int MODE; //1:menu 2:game 3:file game
extern bool NEW_GAME; //1:reset data 2:mở game từ file
extern ofstream _MATCH_LIST_FILE;
extern int MATCH_LIST_SIZE;
extern vector<_LIST> _MATCH_LIST;
