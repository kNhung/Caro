#pragma once
#include "header.h"

void FixConsoleWindow();
void SetFontSize(int fontSize);
void GotoXY(int x, int y);
void ResetData();
void LoadGame(string matchName);

void Drawboard_game();
void DrawExistedData();
void DrawMenu();
void PrintMenuLogo();
void PrintHeart(int top, int left);
void PrintRectangle(int top, int left, int width, int height);
void DrawMatchList();
void DrawLetter(unsigned char letter[], int X, int Y);
void GetWinLine(vector <_POINT>& winLine, int i,int j, char type);
void SetColor(int backgoundColor, int textColor);
void HighlightWin(vector <_POINT>& winLine);

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
void GetMatchListSize();
void LoadGame(string matchName);
