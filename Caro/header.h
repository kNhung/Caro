#pragma once
#ifndef _MY_HEADER
#define _MY_HEADER
#include <iostream>
#include <io.h>
#include <fcntl.h>
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

#define BOARD_SIZE 16
#define LEFT 28
#define TOP 8
#define CENTER_X 55
#define CENTER_Y 15
#define GOAL 5
#define MENU_SIZE 4
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15


struct _POINT { int x, y, c; };
struct _LIST {
	int x, y;
	string item;
};
struct ToaDo { int x, y; };
struct EDGE {
	int top = 0, bottom = 0, left = 0, right = 0;
};

extern _POINT _A[BOARD_SIZE][BOARD_SIZE];
extern _POINT _MENU[MENU_SIZE];
extern _POINT _LAST_POINT; //Nằm trong CheckBoard(int pX, int pY) để lưu điểm cuối mà người chơi đánh

extern bool _TURN; //Lượt đánh 1:X  0:O
extern int _COMMAND; //Phím mà người chơi nhấn
extern int _X, _Y;
extern int MODE; //1:menu 2:game 3:file game
extern bool NEW_GAME; //1:reset data 2:mở game từ file
extern ofstream _MATCH_LIST_FILE;
extern int MATCH_LIST_SIZE;
extern vector<_LIST> _MATCH_LIST;

extern unsigned char L[], O[], A[], D[], G[], M[], E[], I[], N[], H[], P[];
extern unsigned char* LETTER_LIST[];
extern int LETTER_LIST_SIZE;

#endif
