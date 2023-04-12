#pragma once
#ifndef _MY_VIEW
#define _MY_VIEW
#include "header.h"

void fixConsoleWindows();
void showCursor(bool show);
void SetFontSize(int fontSize);
void GotoXY(int x, int y);
void SetColor(int backgoundColor, int textColor);

<<<<<<< HEAD
void Drawboard_game();
void Highlightwin(_POINT a[], int& n);
=======
void DrawBoard();
void Highlightwin(POINT* a);
void Button(int top, int left, int width, int height, string label);
>>>>>>> ada0df25204ed81707bd9b3c6ea7a5209e0fe960
void DrawExistedData();
void DrawMenu();
void DrawMatchList();
void DrawLetter(unsigned char letter[], int X, int Y);
void DrawPopUp(char quest);

void Button(int top, int left, int width, int height, string label);
void PrintMenuLogo();
void PrintHeart(int top, int left);
void PrintSmallHeart(int top, int left);
void PrintRectangle(int top, int left, int width, int height);
void PrintTree(int x, int y);
void PrintCloud(int left, int top, int type);


int ProcessFinish(int pWhoWin);
int AskContinue();
int AskSaveGame();
void SaveGame();
void SaveMatchInfo(string match);
void RemoveMatchFile(string matchName);

void ShowPage(int page);
void ShowLoadingPage();
void ShowMenu(); 
void ShowGame();
void ShowAbout(); 
void ShowFileGame(); 
void ShowAsk(WORD wVirtualKeyCode);
void ShowHelp();

void GetMatchListSize();
void LoadGame(string matchName);
void TextColor(int color);
void TT();
void Ox(int x1, int x2, int y);
#endif
