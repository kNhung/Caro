#include "control.h"
#include "model.h"
#include "view.h"

bool FullBoard(_POINT _A[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0;i < BOARD_SIZE;i++)
		for (int j = 0;j < BOARD_SIZE;j++) {
			if (_A[i][j].c == 0)
				return 0;
		}
	return 1;
}

//Kiểm tra lượt đánh hiện tại là thắng chưa
//Kiểm tra _A[i][j].c 
//Đưa về đầu dãy rồi đếm
//5 cái liên tục thì thắng
bool WinCheck(_POINT _A[BOARD_SIZE][BOARD_SIZE], int pX, int pY) {
	int i = 0, j = 0, n = 1;
	//Tìm vị trí của người chơi trong mảng
	//Xét trục hoành x tương ứng với các cột j
	//Xét trục tung y tương ứng với các hàng i
	while (_A[i][j].x != pX)
		++j;
	while (_A[i][j].y != pY)
		++i;

	//Hàng ngang
	//Chạy hẳn sang bên trái rồi đếm 
	while (_A[i][j - 1].c == _A[i][j].c)
		--j;
	while (_A[i][j + 1].c == _A[i][j].c) {
		++j;
		++n;
	}
	if (n == GOAL) return 1;

	//Hàng dọc
	//Chạy hẳn lên trên rồi đếm
	n = 1;
	while (_A[i - 1][j].c == _A[i][j].c)
		--i;
	while (_A[i + 1][j].c == _A[i][j].c) {
		++i;
		++n;
	}
	if (n == GOAL) return 1;

	//Chéo chính
	//Chạy hẳn lên phía trên rồi xét chéo xuống
	n = 1;
	while (_A[i - 1][j - 1].c == _A[i][j].c) {
		--i;
		--j;
	}
	while (_A[i + 1][j + 1].c == _A[i][j].c) {
		++i;
		++j;
		++n;
	}
	if (n == GOAL) return 1;

	//Chéo phụ
	//Chạy hẳn lên phía trên rồi xét chéo xuống
	n = 1;
	while (_A[i - 1][j + 1].c == _A[i][j].c) {
		--i;
		++j;
	}
	while (_A[i + 1][j - 1].c == _A[i][j].c) {
		++i;
		--j;
		n++;
	}
	if (n == GOAL) return 1;

	return 0;
}

int TestBoard() {
	if (FullBoard(_A)) return 0;
	else {
		if (WinCheck(_A, _X, _Y) == 1)
			return (_TURN == true ? -1 : 1);
		else
			return 2;
	}
}

int CheckBoard(int pX, int pY) {
	for (int i = 0;i < BOARD_SIZE;i++) {
		for (int j = 0;j < BOARD_SIZE;j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true) _A[i][j].c = -1;
				else _A[i][j].c = 1;
				return _A[i][j].c;
			}
		}
	}
	return 0;
}