#include "control.h"
#include "model.h"
#include "view.h"

void StartGame() {
	system("cls");
	ResetData();
	DrawBoard(BOARD_SIZE);
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
		 || (MODE == 1  && _Y < _MENU[MENU_OPTIONS-1].y)) {
		_Y += 2;
		GotoXY(_X, _Y);
	}
}

void MoveUp() {
	if ((MODE == 2 && _Y > _A[0][0].y)
		|| (MODE == 1 && _Y > _MENU[0].y)) {
		_Y -= 2;
		GotoXY(_X, _Y);
	}
}