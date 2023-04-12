#pragma once
#include "header.h"

void FixConsoleWindow();
void GotoXY(int x, int y);
void ResetData();

void DrawBoard(int pSize);
void DrawMenu(); 

int ProcessFinish(int pWhoWin);
int AskContinue();

void ShowLoadingPage();
void ShowPage(int page);
void ShowMenu(); //Hiển thị trang chủ có menu
void ShowGame(); //Hiển thị trận caro
void ShowAbout(); //Hiển thị thông tin nhóm 
void ShowFileGame(); //Hiển thị các file game đã lưu