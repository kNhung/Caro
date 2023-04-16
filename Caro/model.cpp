#include "control.h"
#include "model.h"
#include "view.h"
#include"header.h"


void Resetdata(_POINT a[], int& n, int& led1, int& led2) {
	a[n] = { 0 };
	n = 1;
	led1 = 0; led2 = 0;
}

//Dựa vào vị trí con trỏ tìm phần tử được gán lượt đánh trong ma trận
_POINT XYinMatrix(int& x, int& y,int& row,int& col) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			if (_A[i][j].x == x && _A[i][j].y == y) {
				row = i;
				col = j;
				return _A[i][j];
			}
	}
}

void ResetData() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			_A[i][j].x = 4 * j + LEFT + 2;
			_A[i][j].y = 2 * i + TOP + 1;
			_A[i][j].c = 0;
		}
	}
	_TURN = true; _COMMAND = -1;
	_X = _A[0][0].x; _Y = _A[0][0].y;
	GotoXY(_X, _Y);
}


int test_inTestBoard(_POINT a[], int& n, int& led1, int& led2) {
	if (n == 5 && (led1 == 0 || led2 == 0)) {
		Highlightwin(a, n);
		return(_TURN = true ? -1 : 1);
	}
	if (n > 5) {
		Highlightwin(a, n);
		return(_TURN = true ? -1 : 1);
	}
	Resetdata(a, n, led1, led2);
	return 2;
}

//Kiểm tra thắng thua, người 1 hay _Turn=true thắng thì trả về -1 người còn lại thắng trả về 1,
//hòa nhau trả về 0 còn chưa phân định ai thắng trả về 2
int TestBoard() {
	int led1 = 0, led2 = 0, row = 0, col = 0;
	int result = 2, n = 0;
	//Mang luu toa do duong chien thang
	_POINT a[9];
	_POINT p=XYinMatrix(_X, _Y,row,col);
	a[n++] = p;


	//Kiểm tra trên dòng
	//Các đèn led tín hieu de kiem tra luat chan hai dau
	for (int i = col - 1; i >= 0 && i < BOARD_SIZE; i--) {
		if (_A[row][i].c == _A[row][col].c) {
			a[n++] = _A[row][i];
		}
		else {
			if (_A[row][i].c != 0)
				led1 = 1;
			break;
		}
	}
	for (int i = col + 1; i >= 0 && i < BOARD_SIZE; i++) {
		if (_A[row][i].c == _A[row][col].c) {
			a[n++] = _A[row][i];
		}
		else {
			if (_A[row][i].c != 0)
				led2 = 1;
			break;
		}
	}
	result = test_inTestBoard(a, n, led1, led2); if (result != 2)return result;

	for (int i = row + 1; i >= 0 && i < BOARD_SIZE; i++) {
		if (_A[i][col].c == _A[row][col].c) {
			a[n++] = _A[i][col];
		}
		else {
			if (_A[i][col].c != 0)
				led1 = 1;
			break;
		}

	}
	for (int i = row - 1; i >= 0 && i < BOARD_SIZE; i--) {
		if (_A[i][col].c == _A[row][col].c) {
			a[n++] = _A[i][col];
		}
		else {
			if (_A[i][col].c != 0)
				led2 = 1;
			break;
		}
	}
	result = test_inTestBoard(a, n, led1, led2); if (result != 2)return result;

	for (int i = row - 1, j = col - 1; i >= 0 && i < BOARD_SIZE, j >= 0 && j < BOARD_SIZE; i--, j--) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			if (_A[i][j].c != 0)
				led1 = 1;
			break;
		}
	}
	for (int i =row + 1, j = col + 1; i >= 0 && i < BOARD_SIZE, j >= 0 && j < BOARD_SIZE; i++, j++) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			if (_A[i][j].c != 0)
				led2 = 1;
			break;
		}
	}
	result = test_inTestBoard(a, n, led1, led2); if (result != 2)return result;

	for (int i = row + 1, j = col - 1; i >= 0 && i < BOARD_SIZE, j >= 0 && j < BOARD_SIZE; i++, j--) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			if (_A[i][j].c != 0)
				led1 = 1;
			break;
		}

	}
	for (int i = row - 1, j = col + 1; i >= 0 && i < BOARD_SIZE, j >= 0 && j < BOARD_SIZE; i--, j++) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			if (_A[i][j].c != 0)
				led2 = 1;
			break;
		}
	}
	result = test_inTestBoard(a, n, led1, led2); if (result != 2)return result;

	int flag = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (_A[i][j].c == 0)flag = 1;
	if (flag == 0)
		return 0;
	return 2;
}

int CheckBoard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true) _A[i][j].c = -1;
				else _A[i][j].c = 1;
				_LAST_POINT = { pX,pY,_A[i][j].c };
				return _A[i][j].c;
			}
		}
	}
	return 0;
}

//0:không mở được file  -1:file không tồn tại  1:file đã tồn tại
int CheckExistedFile(string fileName) {
	string line;
	ifstream file("game_files.txt");
	if (!file) {
		cout << "Cannot open game file";
		return 0;
	}
	while (!file.eof()) {
		getline(file, line);
		if (CheckSameString(line, fileName + ".txt"))
			return 1;
	}
	return -1;
}

bool CheckValidName(string name) {
	for (int i = 0; i < name.size(); i++) {
		if (name[i] == ' ' || name[i] == '/' || 
			name[i] == ':' || name[i] == ' * ' || 
			name[i] == ' ? ' || name[i] == '$')
			return 0;
	}
	return 1;
}

bool CheckSameString(string s1, string s2) {
	if (s1.size() != s2.size())
		return 0;
	for (int i = 0; i < s1.size(); i++)
		if (s1[i] != s2[i])
			return 0;
	return 1;
}


void Save_1_move(int& y, int& x) {
	y = _Y;
	x = _X;
}

void Playgame() {
	DrawBoard();
	ResetData();
	int row_matrix = 0, column_matrix = 0;
	int row_console = 0, column_console = 0;

	KEY_EVENT_RECORD keyevent;
	EDGE bien = { TOP + 1,LEFT + 2,LEFT + BOARD_SIZE * 4 - 2,TOP + BOARD_SIZE * 2 - 1 };
	bool validEnter = true;
	while (1) {
		ReadInputKey(keyevent);
		if (keyevent.bKeyDown) {
			KeyMove(&_X, &_Y, 4, 2, bien, keyevent);
			switch (keyevent.wVirtualKeyCode) {
			case(VK_RETURN): {
				switch (CheckBoard(_X, _Y)) {
				case -1:
				{cout << "X";
				Save_1_move(row_console, column_console);
				break; }
				case 1:
				{cout << "O";
				Save_1_move(row_console, column_console);
				break; }
				case 0: validEnter = false;
				}
				if (validEnter == true) {
					TestBoard();
					_TURN = !_TURN;
				}
				break;
			}
			case(0x55): {
				_X = column_console;
				_Y = row_console;
				GotoXY(_X, _Y);
				cout << char(32);
				GotoXY(_X, _Y);
				XYinMatrix(row_matrix, column_matrix, column_console, row_console);
				_A[row_matrix][column_matrix].c = 0;
				_TURN = !_TURN;
				break;
			}
			}

		}
		keyevent.bKeyDown = false;
		validEnter = true;
	}
}