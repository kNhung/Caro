#pragma once
#ifndef _MY_MODEL
#define _MY_MODEL
#include "header.h"
#pragma comment(lib, "Winmm.lib")

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
void ResetScore();

//Chơi game
void StartGame();

//Kiểm tra bàn cờ
int CheckBoard(int pX, int pY);
int TestBoard(/*KEY_EVENT_RECORD key*/);
int CheckWin(_POINT a[], int& n, _POINT& led1, _POINT& led2);
void ResetToCheck(_POINT a[], int& n, _POINT& led1, _POINT& led2);

//Xử lí chiến thắng
void HighlightWin(_POINT a[], int& n);
int ProcessFinish(int pWhoWin);

//Hỏi
int AskContinue();
int AskSaveGame();
void HLChoice(int& x, int& y, int width);

//Các chức năng khác
_POINT XYinMatrix(const int& x, const int& y, int& row, int& col);
void ExitGame();
void RemoveMatchFile(string& matchName,int& pos);
void RemoveFile();
bool InputFileName(char& c);
bool _True(char& c);
void Input_Data(string& s, const int& max, const int& x, const int& y, bool (*condition)(char&)=_True);
void _PlaySound(int i);
void PVC(TURN_BOT tb[]);//Đấu với máy
void SearchFile(); //Tìm file
bool CheckSubStr(string sub, string src); //Kiểm tra chuỗi con
#endif

