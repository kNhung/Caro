#pragma once
#ifndef _MY_VIEW
#define _MY_VIEW
#include "header.h"

//void FixConsoleWindow();
void setFontInfo();
void setAndCenterWindow();
void SetWindowSize(SHORT width, SHORT height);
void disableMaximize();
void setConsoleTitle();
void hideScrollBars();
void showCursor(bool show);
void disableMouseInput();
void fixConsoleWindows();




void SetFontSize(int fontSize);
void GotoXY(int x, int y);
void SetColor(int backgoundColor, int textColor);

void Drawboard_game();
void Highlightwin(POINT* a);
void Button(int top, int left, int width, int height, string label);
void DrawExistedData();
void DrawMenu();
void DrawMatchList();
void DrawLetter(unsigned char letter[], int X, int Y);
void DrawPopUp(char quest);

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
void ShowAsk(char key);
void ShowHelp();

void GetMatchListSize();
void LoadGame(string matchName);
void TextColor(int color);
void TT();
void Ox(int x1, int x2, int y);
#endif
