#pragma once
#ifndef _MY_MODEL
#define _MY_MODEL
#include "header.h"

bool FullBoard(_POINT _A[BOARD_SIZE][BOARD_SIZE]);
//bool WinCheck(_POINT _A[BOARD_SIZE][BOARD_SIZE], int pX, int pY);
void ResetData();
void Resetdata(vector<_POINT>& a, int& led1, int& led2);
int TestBoard();
int CheckBoard(int pX, int pY);
int CheckExistedFile(string fileName);
bool CheckValidName(string name);
bool CheckSameString(string s1, string s2);

#endif

