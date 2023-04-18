#pragma once
#ifndef _MY_CONTROL
#define _MY_CONTROL
#include "header.h"

//Di chuyển
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();
void KeyMove(int* x, int* y, int col, int row, EDGE b, KEY_EVENT_RECORD a);
void ReadInputKey(KEY_EVENT_RECORD& a);
void GotoXY(int x, int y);

//Điều chỉnh thuộc tính của màn hình
void SetFontInfo();
void SetAndCenterWindow();
void SetWindowSize(SHORT width, SHORT height);
void SetScreenBufferSize(SHORT width, SHORT height);
void DisableSelection();
void DisableMaximize();
void HideScrollBars();
void ShowCursor(bool show);
void DisableMouseInput();
void FixConsoleWindows();
void SetColor(int backgoundColor, int textColor);
void TextColor(int color);
void SetColor(int backgoundColor, int textColor);

#endif