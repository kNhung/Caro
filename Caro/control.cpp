#include "control.h"
#include "model.h"
#include "view.h"


void StartGame() {
	system("cls");
	DrawBoard();
	if (NEW_GAME == 1)
		ResetData();
	else
		DrawExistedData();
}

void GabageCollect() {
}

void Exit() {
	system("cls");
	GabageCollect();
	return;
}

void MoveRight() {
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x) {
		_X += 4;
		GotoXY(_X, _Y);
	}
}

void MoveLeft() {
	if (_X > _A[0][0].x) {
		_X -= 4;
		GotoXY(_X, _Y);
	}
}

void MoveDown() {
	if ((MODE == 2 && _Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
		|| (MODE == 1 && _Y < _MENU[MENU_SIZE - 1].y)) {
		_Y += 2;
		GotoXY(_X, _Y);
	}
	if (MODE == 3 && _Y < _MATCH_LIST[MATCH_LIST_SIZE - 1].y) {
		_Y += 3;
		GotoXY(_X, _Y);
	}
}

void MoveUp() {
	if ((MODE == 2 && _Y > _A[0][0].y)
		|| (MODE == 1 && _Y > _MENU[0].y)) {
		_Y -= 2;
		GotoXY(_X, _Y);
	}
	if (MODE == 3 && _Y > _MATCH_LIST[0].y) {
		_Y -= 3;
		GotoXY(_X, _Y);
	}
}

//Di chuyển con trỏ chuột về các hướng bằng các phím A,W,S,D và các phím mũi tên
void KeyMove(int* x, int* y, int col, int row, EDGE b, KEY_EVENT_RECORD a) {
	switch (a.wVirtualKeyCode) {
	case VK_UP:case 0x57: {
		*y = *y - row;
		if (*y < b.top)
			*y = b.bottom;
		GotoXY(*x, *y);
		break; }
	case VK_DOWN:case 0x53: {
		*y = *y + row;
		if (*y > b.bottom)
			*y = b.top;
		GotoXY(*x, *y);
		break; }
	case VK_LCONTROL:case 0x41: {
		*x = *x - col;
		if (*x < b.left)
			*x = b.right;
		GotoXY(*x, *y);
		break; }
	case VK_RCONTROL:case 0x44: {
		*x = *x + col;
		if (*x > b.right)
			*x = b.left;
		GotoXY(*x, *y);
		break; }
	}
}

	void ReadInputKey(KEY_EVENT_RECORD & a) {

		DWORD lpcNumberOfEvents = 0;// size of read buffer
		DWORD cNumRead = 0;// number of records read
		DWORD fdwMode;
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);// Get the standard input handle.
		fdwMode = ENABLE_WINDOW_INPUT;
		SetConsoleMode(hStdin, fdwMode);

		lpcNumberOfEvents = 0;
		cNumRead = 0;
		int res = 0;
		//Receives the number of unread input records in the console's input buffer.
		GetNumberOfConsoleInputEvents(hStdin, &lpcNumberOfEvents);

		if (lpcNumberOfEvents) {
			INPUT_RECORD* irInBuf = new INPUT_RECORD[lpcNumberOfEvents];//Record event
			ReadConsoleInput(hStdin, irInBuf, lpcNumberOfEvents, &cNumRead);
			// Loop to read and handle input events.
			// Dispatch the events to the appropriate handler.
			for (DWORD i = 0; i < cNumRead; i++)
			{
				if (irInBuf[i].EventType == KEY_EVENT) {// keyboard input
					a = irInBuf[i].Event.KeyEvent;
				}
			}
			delete[] irInBuf;
		}
	}