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