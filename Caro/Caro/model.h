#pragma once
#include "header.h"

bool FullBoard(_POINT _A[BOARD_SIZE][BOARD_SIZE]);
bool WinCheck(_POINT _A[BOARD_SIZE][BOARD_SIZE], int pX, int pY);
int TestBoard();
int CheckBoard(int pX, int pY);