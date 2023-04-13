#pragma once
#ifndef _MY_MODEL
#define _MY_MODEL
#include "header.h"

void Resetdata(_POINT a[], int& n, int& led1, int& led2);
_POINT XYinMatrix(int& x, int& y, int& row, int& col);
int test_inTestBoard(_POINT a[], int& n, int& led1, int& led2);
void ResetData();
int TestBoard();
void Save_1_move(int& y, int& x);

int CheckBoard(int pX, int pY);
int CheckExistedFile(string fileName);
bool CheckValidName(string name);
bool CheckSameString(string s1, string s2);


#endif

