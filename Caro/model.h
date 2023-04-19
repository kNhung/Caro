#pragma once
#ifndef _MY_MODEL
#define _MY_MODEL
#include "header.h"

//Lưu game
void SaveGame();
void SaveMatchInfo(string match);
int CheckExistedFile(string fileName);
bool CheckValidName(string name);
bool CheckSameString(string s1, string s2);

//Tải dữ liệu game
void GetMatchListSize();
void LoadGame(string matchName);
void ResetData();

//Chơi game
void StartGame();

//Kiểm tra bàn cờ
int CheckBoard(int pX, int pY);
int TestBoard();
int test_inTestBoard(_POINT a[], int& n, int& led1, int& led2);
void ResetToCheck(_POINT a[], int& n, int& led1, int& led2);

//Xử lí chiến thắng
void HighlightWin(_POINT a[], int& n);
int ProcessFinish(int pWhoWin);

//Hỏi
int AskContinue();
int AskSaveGame();
void HLChoice(int& x, int& y, int width);

//Các chức năng khác
_POINT XYinMatrix(int& x, int& y, int& row, int& col);
void Save_1_move(int& y, int& x);
void ExitGame();
void RemoveMatchFile(string matchName);
void GabageCollect();

#endif

