#include "control.h"
#include "model.h"
#include "view.h"
#include"header.h"

bool FullBoard(_POINT _A[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0;i < BOARD_SIZE;i++)
		for (int j = 0;j < BOARD_SIZE;j++) {
			if (_A[i][j].c == 0)
				return 0;
		}
	return 1;
}

////Kiểm tra lượt đánh hiện tại là thắng chưa
////Kiểm tra _A[i][j].c 
////Đưa về đầu dãy rồi đếm
////5 cái liên tục thì thắng
//bool WinCheck(_POINT _A[BOARD_SIZE][BOARD_SIZE], int pX, int pY) {
//	int i = 0, j = 0, n = 1;
//	char type = NULL;
//	vector <_POINT> winLine;
//	//Tìm vị trí của người chơi trong mảng
//	//Xét trục hoành x tương ứng với các cột j
//	//Xét trục tung y tương ứng với các hàng i
//	while (_A[i][j].x != pX)
//		++j;
//	while (_A[i][j].y != pY)
//		++i;
//
//	//Hàng ngang
//	//Chạy hẳn sang bên trái rồi đếm 
//	while (_A[i][j - 1].c == _A[i][j].c)
//		--j;
//	while (_A[i][j + 1].c == _A[i][j].c) {
//		++j;
//		++n;
//	}
//	if (n == GOAL) {
//		type = 'r'; //row
//		return 1;
//	}
//
//	//Hàng dọc
//	//Chạy hẳn lên trên rồi đếm
//	n = 1;
//	while (_A[i - 1][j].c == _A[i][j].c)
//		--i;
//	while (_A[i + 1][j].c == _A[i][j].c) {
//		++i;
//		++n;
//	}
//	if (n == GOAL) {
//		type = 'c'; //column
//		return 1;
//	}
//
//	//Chéo chính
//	//Chạy hẳn lên phía trên rồi xét chéo xuống
//	n = 1;
//	while (_A[i - 1][j - 1].c == _A[i][j].c) {
//		--i;
//		--j;
//	}
//	while (_A[i + 1][j + 1].c == _A[i][j].c) {
//		++i;
//		++j;
//		++n;
//	}
//	if (n == GOAL) {
//		type = 'd'; //main diagonal
//		return 1;
//	}
//
//	//Chéo phụ
//	//Chạy hẳn lên phía trên rồi xét chéo xuống
//	n = 1;
//	while (_A[i - 1][j + 1].c == _A[i][j].c) {
//		--i;
//		++j;
//	}
//	while (_A[i + 1][j - 1].c == _A[i][j].c) {
//		++i;
//		--j;
//		n++;
//	}
//	if (n == GOAL) {
//		type = 's'; //sub-diagonal
//		return 1;
//	}
//
//	GetWinLine(winLine, i, j, type);
//	HighlightWin(winLine);
//
//	return 0;
//}
//Dynamic Array for save HighlightWin
static int header = sizeof(int) + sizeof(int);
void* origin_addr(void* aData) {
	if (aData != nullptr)
		return (char*)aData - header;
	return NULL;
}

void* data_addr(void* aOrigin) {
	if (aOrigin != nullptr)
		return (char*)aOrigin + header;
	return NULL;
}

void* sizeItem_addr(void* aData) {
	if (aData != nullptr)
		return (char*)aData - sizeof(int);
	return NULL;
}

int memSize(int nItem, int sizeItem) {
	return header + nItem * sizeItem;
}

int ArrSize(void* aData) {
	if (aData != nullptr)
		return *(int*)((char*)aData - header);
	return 0;
}

int arrItemSize(void* aData) {
	if (aData != nullptr)
		return *(int*)((char*)aData - sizeof(int));
	return 0;
}
void arrFree(void* aData) {
	if (aData != nullptr)free(origin_addr(aData));
}

void* arrInit(int nItem, int sizeItem) {
	int sz = memSize(nItem, sizeItem);
	void* Origin = (void*)malloc(sz);
	if (Origin != nullptr) {
		memset(Origin, 0, sz);
		void* aData = data_addr(Origin);
		*(int*)((char*)aData - header) = nItem;
		*(int*)((char*)aData - sizeof(int)) = sizeItem;
		return aData;
	}
	return NULL;
}

void* arrResize(void* aData, int nItem) {
	if (aData == nullptr || nItem < 0) return NULL;
	void* Origin = origin_addr(aData);
	int sizeItem = arrItemSize(aData);
	int sz = memSize(nItem, sizeItem);
	void* aNew = realloc(Origin, sz);
	if (aNew != nullptr) {
		aData = data_addr(aNew);
		*(int*)origin_addr(aData) = nItem;
		return aData;
	}
	return NULL;
}

int arrPushBack(void** aData, void* x) {
	int nItem = ArrSize(*aData);
	int sizeItem = arrItemSize(*aData);
	void* aNew = arrResize(*aData, nItem + 1);
	if (aNew != nullptr) {
		memmove((char*)aNew + nItem * sizeItem, x, sizeItem);
		*aData = aNew;
		return 1;
	}
	return 0;
}
void Resetdata(POINT*& a, int& led1, int& led2) {
	a = (POINT*)arrResize(a, 1);
	led1 = 0; led2 = 0;
}

//Dựa vào vị trí con trỏ tìm phần tử được gán lượt đánh trong ma trận
void XYinMatrix(int& row, int& column, int x, int y) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			if (_A[i][j].x == x && _A[i][j].y == y) {
				row = i;
				column = j;
				return;
			}
	}
}

int TestInTestBoard(POINT*& a, int& led1, int& led2) {
	if (ArrSize(a) == 5 && (led1 == 0 || led2 == 0)) {
		HighlightWin(a);
		arrFree(a);
		return(_TURN = true ? -1 : 1);
	}
	if (ArrSize(a) > 5) {
		HighlightWin(a);
		arrFree(a);
		return(_TURN = true ? -1 : 1);
	}
	Resetdata(a, led1, led2);
	return 2;
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
}

void Resetdata(vector<_POINT>& a, int& led1, int& led2) {
	a.resize(1);
	led1 = 0; led2 = 0;
}

//Kiểm tra thắng thua, người 1 hay _Turn=true thắng thì trả về -1 người còn lại thắng trả về 1,
//hòa nhau trả về 0 còn chưa phân định ai thắng trả về 2
int TestBoard() {
	int row = 0, column = 0;
	int led1 = 0, led2 = 0;
	POINT x; int result = 2;
	//Mang luu toa do duong chien thang
	POINT* a = (POINT*)arrInit(1, sizeof(POINT));
	XYinMatrix(row, column, _X, _Y);
	a[0] = { _A[row][column].x,_A[row][column].y };


	//Kiểm tra trên dòng
	//Các đèn led tín hieu de kiem tra luat chan hai dau
	for (int i = column - 1; i >= 0 && i <= BOARD_SIZE; i--) {
		if (_A[row][i].c == _A[row][column].c) {
			x = { _A[row][i].x,_A[row][i].y };
			arrPushBack((void**)&a, &x);
		}
		else {
			if (_A[row][i].c != 0)
				led1 = 1;
			break;
		}
	}
	for (int i = column + 1; i >= 0 && i <= BOARD_SIZE; i++) {
		if (_A[row][i].c == _A[row][column].c) {
			x = { _A[row][i].x, _A[row][i].y };
			arrPushBack((void**)&a, &x);
		}
		else {
			if (_A[row][i].c != 0)
				led2 = 1;
			break;
		}
	}
	result = TestInTestBoard(a, led1, led2); if (result != 2)return result;

	for (int i = row + 1; i >= 0 && i <= BOARD_SIZE; i++) {
		if (_A[i][column].c == _A[row][column].c) {
			x = { _A[i][column].x, _A[i][column].y };
			arrPushBack((void**)&a, &x);
		}
		else {
			if (_A[i][column].c != 0)
				led1 = 1;
			break;
		}

	}
	for (int i = row - 1; i >= 0 && i <= BOARD_SIZE; i--) {
		if (_A[i][column].c == _A[row][column].c) {
			x = { _A[i][column].x,_A[i][column].y };
			arrPushBack((void**)&a, &x);
		}
		else {
			if (_A[i][column].c != 0)
				led2 = 1;
			break;
		}
	}
	result = TestInTestBoard(a, led1, led2); if (result != 2)return result;

	for (int i = row - 1, j = column - 1; i >= 0 && i <= BOARD_SIZE, j >= 0 && j <= BOARD_SIZE; i--, j--) {
		if (_A[i][j].c == _A[row][column].c) {
			x = { _A[i][j].x,_A[i][j].y };
			arrPushBack((void**)&a, &x);
		}
		else {
			if (_A[i][j].c != 0)
				led1 = 1;
			break;
		}
	}
	for (int i = row + 1, j = column + 1; i >= 0 && i <= BOARD_SIZE, j >= 0 && j <= BOARD_SIZE; i++, j++) {
		if (_A[i][j].c == _A[row][column].c) {
			x = { _A[i][j].x, _A[i][j].y };
			arrPushBack((void**)&a, &x);
		}
		else {
			if (_A[i][j].c != 0)
				led2 = 1;
			break;
		}
	}
	result = TestInTestBoard(a, led1, led2); if (result != 2)return result;

	for (int i = row + 1, j = column - 1; i >= 0 && i <= BOARD_SIZE, j >= 0 && j <= BOARD_SIZE; i++, j--) {
		if (_A[i][j].c == _A[row][column].c) {
			x = { _A[i][j].x,_A[i][j].y };
			arrPushBack((void**)&a, &x);
		}
		else {
			if (_A[i][j].c != 0)
				led1 = 1;
			break;
		}

	}
	for (int i = row - 1, j = column + 1; i >= 0 && i <= BOARD_SIZE, j >= 0 && j <= BOARD_SIZE; i--, j++) {
		if (_A[i][j].c == _A[row][column].c) {
			x = { _A[i][j].x, _A[i][j].y };
			arrPushBack((void**)&a, &x);
		}
		else {
			if (_A[i][j].c != 0)
				led2 = 1;
			break;
		}
	}
	result = TestInTestBoard(a, led1, led2); if (result != 2)return result;

	int flag = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (_A[i][j].c == 0)flag = 1;
	if (flag == 0)
		return 0;
	return 2;
}

int CheckBoard(int pX, int pY) {
	for (int i = 0;i < BOARD_SIZE;i++) {
		for (int j = 0;j < BOARD_SIZE;j++) {
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
		if (CheckSameString(line, fileName+".txt"))
			return 1;
	}
	return -1;
}

bool CheckValidName(string name) {
	for (int i = 0;i < name.size();i++) {
		if (name[i] == ' ' || name[i] == '/' || name[i] == ':' || name[i] == ' * ' || name[i] == ' ? ' || name[i] == '$')
			return 0;
	}
	return 1;
}

bool CheckSameString(string s1, string s2) {
	if (s1.size() != s2.size())
		return 0;
	for (int i = 0;i < s1.size();i++)
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