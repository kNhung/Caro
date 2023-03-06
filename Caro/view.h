#pragma once
#include "header.h"

void FixConsoleWindow();
void GotoXY(int x, int y);
void ResetData();
void LoadGame(string matchName);

void DrawBoard(int pSize);
void DrawExistedData();
void DrawMenu(); 
void DrawMatchList();

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
