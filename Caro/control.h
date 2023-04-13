#pragma once
#ifndef _MY_CONTROL
#define _MY_CONTROL
#include "header.h"

void StartGame();
void GabageCollect();
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();
void KeyMove(int* x, int* y, int col, int row, EDGE b, KEY_EVENT_RECORD a);
void ReadInputKey(KEY_EVENT_RECORD& a);

#endif