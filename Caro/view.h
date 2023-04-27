#pragma once
#ifndef _MY_VIEW
#define _MY_VIEW
#include "header.h"

//In hình ảnh, icon
void PrintHeart(int top, int left);
void PrintRectangle2lines(int top, int left, int width, int height);
void PrintRectangle(int top, int left, int width, int height);
void PrintTree(int left, int top);
void PrintCloud(int left, int top, int type);
void PrintLine(int top, int left, int length);
void Button(int top, int left, int width, int height, string label);
void PrintPencil(int top, int left);
void PrintHelicopter(int x, int y);
void PrintCastle(int x, int y);
void PrintX(int top, int left, int size);
void PrintO(int top, int left, int size);
void DrawScore(int score, int top, int left);
void RemoveScore(int top, int left);

//In tiêu đề các lựa chọn ở trang Menu
void PrintNEW();
void PrintCONTINUE();
void PrintABOUT();
void PrintEXIT();
void PrintPVC();

//In tiêu đề trang
void PrintContinueLogo(int top, int left);
void PrintInMatch(int top, int left);
void PrintAboutLogo(int top, int left);
void PrintMenuLogo(int top, int left);
void PrintLoadingLogo(int top, int left);
void PrintHelpLogo(int top, int left);

//Hiệu ứng
void ClearPreviousHightlight(int& a);
void PrintCurrentHighlight(int& a);
void PrintLeftCursor(int top, int left);
void PrintRightCursor(int top, int left);

//Vẽ giao diện các trang
void DrawMenu();
void DrawBoard();
void DrawExistedData();
void DrawMatchList();
void DrawPopUp(WORD wVirtualKeyCode);
void Draw_AskContinue();
void DrawAbout();
void DrawLoadingPage();
void DrawHelp();
#endif
