#pragma once
#ifndef _MY_VIEW
#define _MY_VIEW
#include "header.h"

//Điều chỉnh thuộc tính của màn hình
void SetFontInfo();
void SetAndCenterWindow(int width, int height);
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
void GotoXY(int x, int y);
void SetColor(int backgoundColor, int textColor);

void DrawBoard();
void Highlightwin(_POINT a[], int& n);
void Button(int top, int left, int width, int height, string label);
void DrawExistedData();
void DrawMenu();
void DrawMatchList();
void DrawPopUp(char quest);

void PrintMenuLogo(int top, int left);
void PrintHeart(int top, int left);
void PrintRectangle2lines(int top, int left, int width, int height);
void PrintRectangle(int top, int left, int width, int height);
void PrintTree(int x, int y);
void PrintCloud(int left, int top, int type);
void PrintLine(int top, int left, int length);
void PrintLeftCursor(int top, int left);
void PrintRightCursor(int top, int left);
void PrintNEW();
void PrintCONTINUE();
void PrintABOUT();
void PrintEXIT();
void PrintPVC();
void ClearPreviousHightlight(int& a);
void PrintCurrentHighlight(int& a);
void PrintPencil();
void PrintContinueLogo(int top, int left);
void PrintOnMarch(int top, int left);
void PrintAboutLogo(int top, int left);


int ProcessFinish(int pWhoWin);
void ExitGame();
void HLChoice(int& x, int& y, int width);
void Draw_AskContinue();
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
void DrawAbout();
#endif
