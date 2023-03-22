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

void Resetdata(vector<_POINT>& a, int& led1, int& led2) {
	a.resize(1);
	led1 = 0; led2 = 0;
}

//Kiểm tra thắng thua, người 1 hay _Turn=true thắng thì trả về -1 người còn lại thắng trả về 1,
//hòa nhau trả về 0 còn chưa phân định ai thắng trả về 2
int TestBoard() {
	vector <_POINT> a;
	_POINT k;
	int cot = 0, dong = 0, res = 0;
	int led1 = 0, led2 = 0;
	//Dựa vào vị trí con trỏ tìm phần tử được gán lượt đánh trong ma trận
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			if (_A[i][j].x == _X && _A[i][j].y == _Y) {
				dong = i;
				cot = j;
				res = 1; break;
			}
		if (res == 1)break;
	}
	//Đưa phần tử tìm được vào vecto
	k.x = _A[dong][cot].x; k.y = _A[dong][cot].y;
	a.push_back(k);

	//Kiểm tra trên dòng
	//Các đèn led tín hiệu kiểm tra xem 
	for (int i = cot - 1; i >= 0 && i <= BOARD_SIZE; i--) {
		if (_A[dong][i].c == _A[dong][cot].c) {
			k.x = _A[dong][i].x; k.y = _A[dong][i].y;
			a.push_back(k);
		}
		else if (_A[dong][i].c != 0 && _A[dong][i].c != _A[dong][cot].c) {
			led1 = 1;
			break;
		}
		else break;
	}
	for (int i = cot + 1; i >= 0 && i <= BOARD_SIZE; i++) {
		if (_A[dong][i].c == _A[dong][cot].c) {
			k.x = _A[dong][i].x; k.y = _A[dong][i].y;
			a.push_back(k);
		}
		else if (_A[dong][i].c != 0 && _A[dong][i].c != _A[dong][cot].c) {
			led2 = 1;
			break;
		}
		else break;
	}
	if (a.size() == 5 && (led1 == 0 || led2 == 0)) {
		Highlightwin(a); return(_TURN = true ? -1 : 1);
	}
	if (a.size() > 5) {
		Highlightwin(a); return(_TURN = true ? -1 : 1);
	}
	Resetdata(a, led1, led2);

	for (int i = dong + 1; i >= 0 && i <= BOARD_SIZE; i++) {
		if (_A[i][cot].c == _A[dong][cot].c) {
			k.x = _A[i][cot].x; k.y = _A[i][cot].y;
			a.push_back(k);
		}
		else if (_A[i][cot].c != 0 && _A[i][cot].c != _A[dong][cot].c) {
			led1 = 1;
			break;
		}
		else break;
	}
	for (int i = dong - 1; i >= 0 && i <= BOARD_SIZE; i--) {
		if (_A[i][cot].c == _A[dong][cot].c) {
			k.x = _A[i][cot].x; k.y = _A[i][cot].y;
			a.push_back(k);
		}
		else if (_A[i][cot].c != 0 && _A[i][cot].c != _A[dong][cot].c) {
			led2 = 1;
			break;
		}
		else break;
	}
	if (a.size() == 5 && (led1 == 0 || led2 == 0)) {
		Highlightwin(a); return(_TURN = true ? -1 : 1);
	}
	if (a.size() > 5) {
		Highlightwin(a); return(_TURN = true ? -1 : 1);
	}
	Resetdata(a, led1, led2);

	for (int i = dong - 1, j = cot - 1; i >= 0 && i <= BOARD_SIZE, j >= 0 && j <= BOARD_SIZE; i--, j--) {
		if (_A[i][j].c == _A[dong][cot].c) {
			k.x = _A[i][j].x; k.y = _A[i][j].y;
			a.push_back(k);
		}
		else if (_A[i][j].c != 0 && _A[i][j].c != _A[dong][cot].c) {
			led1 = 1;
			break;
		}
		else break;
	}
	for (int i = dong + 1, j = cot + 1; i >= 0 && i <= BOARD_SIZE, j >= 0 && j <= BOARD_SIZE; i++, j++) {
		if (_A[i][j].c == _A[dong][cot].c) {
			k.x = _A[i][j].x; k.y = _A[i][j].y;
			a.push_back(k);
		}
		else if (_A[i][j].c != 0 && _A[i][j].c != _A[dong][cot].c) {
			led2 = 1;
			break;
		}
		else break;
	}
	if (a.size() == 5 && (led1 == 0 || led2 == 0)) {
		Highlightwin(a); return(_TURN = true ? -1 : 1);
	}
	if (a.size() > 5) {
		Highlightwin(a); return(_TURN = true ? -1 : 1);
	}
	Resetdata(a, led1, led2);

	for (int i = dong + 1, j = cot - 1; i >= 0 && i <= BOARD_SIZE, j >= 0 && j <= BOARD_SIZE; i++, j--) {
		if (_A[i][j].c == _A[dong][cot].c) {
			k.x = _A[i][j].x; k.y = _A[i][j].y;
			a.push_back(k);
		}
		else if (_A[i][j].c != 0 && _A[i][j].c != _A[dong][cot].c) {
			led1 = 1;
			break;
		}
		else break;
	}
	for (int i = dong - 1, j = cot + 1; i >= 0 && i <= BOARD_SIZE, j >= 0 && j <= BOARD_SIZE; i--, j++) {
		if (_A[i][j].c == _A[dong][cot].c) {
			k.x = _A[i][j].x; k.y = _A[i][j].y;
			a.push_back(k);
		}
		else if (_A[i][j].c != 0 && _A[i][j].c != _A[dong][cot].c) {
			led2 = 1;
			break;
		}
		else break;
	}
	if (a.size() == 5 && (led1 == 0 || led2 == 0)) {
		Highlightwin(a); return(_TURN = true ? -1 : 1);
	}
	if (a.size() > 5) {
		Highlightwin(a); return(_TURN = true ? -1 : 1);
	}
	Resetdata(a, led1, led2);

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