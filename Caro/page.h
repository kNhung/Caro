#pragma once
#ifndef _MY_PAGE
#define _MY_PAGE
#include "header.h"

//Các hàm dùng để mở ra các trang
void ShowPage(int page);
void ShowLoadingPage(); //Trang Loading...
void ShowMenu(); //Trang Menu
void InputName();//Nhập tên người chơi
void ShowGame(); //Trang chơi game
void ShowAbout(); //Trang chứa thông tin nhóm
void ShowFileGame(); //Trang mở file đã lưu
void ShowAsk(WORD wVirtualKeyCode); //Hiện câu hỏi
void ShowHelp(); //Trang hướng dẫn chơi

#endif // !_MY_PAGE
