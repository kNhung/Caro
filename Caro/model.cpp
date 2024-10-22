﻿#include "control.h"
#include "model.h"
#include "view.h"
#include "page.h"


 static bool InputFileName(char& c) {
	if (48 <= c && c <= 57 || 65 <= c && c <= 90 || 97 <= c && c <= 122 || c == '_' || c == '-')
		return 1;
	return 0;
}
bool _True(char& c) {
	return 1;
}

void Input_Data(string& s, const int& max, const int& x, const int& y, bool (*condition)(char&)) {
	s.clear();
	int x_tmp = x;
	GotoXY(x, y);
	int i = 0;
	char c = '\0';
	while (1) {
		c = (char)_getch();
		if (c == 0x0D) break;
		if (c == 8) {
			s.clear();
			i = 0;
			x_tmp = x;
			GotoXY(x, y);
			for (int j = 0; j < max; j++) cout << " ";
			GotoXY(x, y);
			continue;
		}
		if (i == max) continue;
		if (condition(c)) {
			s.push_back(c);
			cout << s[i++];
			GotoXY(++x_tmp, y);
		}
	}
}

//Lưu game
void SaveGame() {
	SetColor(BRIGHT_WHITE, BLACK);
	string matchName;
	while (1) {
		Input_Data(matchName, 10, CENTER_X + 2, CENTER_Y + 2, InputFileName);
		if (matchName != "")break;
	}
	_MATCH_LIST_FILE.open("game_files.txt", ios::app);
	if (!_MATCH_LIST_FILE) {
		GotoXY(CENTER_X + 2, CENTER_Y + 3);
		cout << "Cannot save";
		return;
	}
	while (CheckExistedFile(matchName) == 1) {
		matchName = "";
		GotoXY(CENTER_X + 2, CENTER_Y + 3);
		cout << "  File existed!";
		GotoXY(CENTER_X + 2, CENTER_Y + 2);
		for (int i = 0;i < 10;++i)
			cout << " ";
		GotoXY(CENTER_X + 2, CENTER_Y + 2);
		while (1) {
			Input_Data(matchName, 10, CENTER_X + 2, CENTER_Y + 2, InputFileName);
			if (matchName != "")break;
		}
	}
	if(MATCH_LIST_SIZE==0)_MATCH_LIST_FILE<< matchName + ".txt";
	else {
		_MATCH_LIST_FILE.seekg(0, ios::end);
		_MATCH_LIST_FILE << endl << matchName + ".txt";
	}
	SaveMatchInfo(matchName);
	_MATCH_LIST_FILE.close();
	GetMatchListSize();
	_MATCH_LIST_FILE.close();
}

void SaveMatchInfo(string matchName) {
	matchName += ".txt";
	ofstream matchFile(matchName);
	if (!matchFile) {
		cout << "  Cannot save!";
		return;
	}
	cout << "  Saved";
	for (int i = 0;i < BOARD_SIZE;i++) {
		for (int j = 0;j < BOARD_SIZE;j++) {
			matchFile << _A[i][j].c << endl;
		}
	}
	matchFile << _LAST_POINT.x << endl << _LAST_POINT.y << endl;
	if (_MODEPLAY == _MENU[2].c)matchFile << 0 << endl;
	else matchFile << _LAST_POINT.c << endl;
	matchFile << _MODEPLAY << endl
		<< PLAYER1 << endl
		<< PLAYER2 << endl
		<< SCORE_X << endl
		<< SCORE_O;
	matchFile.close();
}
int CheckExistedFile(string fileName) {
	//0:không mở được file  -1:file không tồn tại  1:file đã tồn tại
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

//Tải dữ liệu game
void GetMatchListSize() {
	string line;
	ifstream file("game_files.txt");
	if (!file) {
		cout << "Cannot get match list size";
		return;
	}
	_X = CENTER_X;_Y = CENTER_Y - 1;
	if (MATCH_LIST_SIZE == 0) {
		while (getline(file, line)) {
			++MATCH_LIST_SIZE;
			_LIST list = { _X,_Y,line };
			_MATCH_LIST.push_back(list);
			_Y += 4;
		}
		_Y -= 4;
	}
	else {
		int i = -1;
		while (getline(file, line)) {
			++i;
			_Y += 4;
			if (i == MATCH_LIST_SIZE && CheckSameString(line, _MATCH_LIST[i - 1].item) == 0) {
				_Y -= 4;
				_LIST list = { _X,_Y,line };
				_MATCH_LIST.push_back(list);
				++MATCH_LIST_SIZE;
			}
		}
		_Y -= 4 * MATCH_LIST_SIZE;
	}
	file.close();
}

static void RemoveMatchFile(string& matchName,int& pos) {
	//Xoa ten file trong file luu ten cac file
	ifstream input("game_files.txt");
	if (!input) return;
	ofstream output("new_game_files.txt");
	string line;
	int i = 0;
	while (getline(input, line)) {
		if (line != matchName) {
			if (i == 0)output << line;
			else output << endl << line;
			i++;
		}
	}
	input.close();
	output.close();
	remove("game_files.txt");
	bool file = rename("new_game_files.txt", "game_files.txt");
	remove(matchName.c_str());//Xóa file lưu dữ liệu

	//xoa file trong mang cau truc & cap nhat lai toa do
	for (int j =pos+1; j < MATCH_LIST_SIZE; j++) {
		_MATCH_LIST[j].y -= 4;
	}
	_MATCH_LIST.erase(_MATCH_LIST.begin() + pos);
	MATCH_LIST_SIZE--;
	
}

void RemoveFile() {
	for (int i = 0; i < MATCH_LIST_SIZE; i++) {
		if (_Y == _MATCH_LIST[i].y) {
			RemoveMatchFile(_MATCH_LIST[i].item, i);
			DrawMatchList();
			if (MATCH_LIST_SIZE == 0)FileNotFound();
			if (i != 0) _Y -= 4;//đặt mũi tên đúng vị trí ds file
			break;
		}
	}
}

void LoadGame(string matchName) {
	int i = 0, j = 0, m = 0, value = 0;
	int numbers[BOARD_SIZE * BOARD_SIZE + 4];
	ifstream matchFile(matchName);
	if (!matchFile) {
		cout << "Cannot open match file";
		return;
	}
	while (m< BOARD_SIZE * BOARD_SIZE + 4) {
		matchFile >> numbers[m++];
	}
	m = 0;
	for (int i = 0;i < BOARD_SIZE;i++)
		for (int j = 0;j < BOARD_SIZE;j++) {
			_A[i][j].x = 4 * j + LEFT + 2;
			_A[i][j].y = 2 * i + TOP + 1;
			_A[i][j].c = numbers[m];
			++m;
		}
	_LAST_POINT.x = numbers[m];++m;
	_LAST_POINT.y = numbers[m];++m;
	_LAST_POINT.c = numbers[m];++m;
	_MODEPLAY = numbers[m];
	matchFile >> PLAYER1;
	matchFile >> PLAYER2;
	matchFile >> SCORE_X;
	matchFile >> SCORE_O;
	if (_LAST_POINT.c == -1)
		_TURN = false;
	else _TURN = true;
	_COMMAND = -1;
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
void ResetScore() {
	SCORE_X = 0; SCORE_O = 0;
}

//Khởi động game
void StartGame() {
	system("cls");
	DrawBoard();
	ShowCursor(true);
	if (NEW_GAME == 1 || _LAST_POINT.x==0&&_LAST_POINT.y==0) 
		ResetData();
	else 
		DrawExistedData();
}

//Kiểm tra bàn cờ
int CheckBoard(int pX, int pY) {
	//Kiểm tra vị trí hiện tại có trống không
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
int TestBoard() {
//Kiểm tra thắng thua, người 1 hay _Turn=true thắng thì trả về -1 người còn lại thắng trả về 1,
//hòa nhau trả về 0 còn chưa phân định ai thắng trả về 2
	_POINT led1 = { 0,0,2 }, led2 = { 0,0,2 };
	int row = 0, col = 0;
	int result = 2, n = 0, m = 0;

	//Mảng lưu tọa độ đường chiến thắng
	_POINT a[9];
	_POINT p = XYinMatrix(_X, _Y, row, col);
	a[n++] = p;
	TURN_BOT tb[4];
	for (int i = 0; i < 4; i++) 
		tb[i] = { 0,{led1,led2} };
	

	//Kiểm tra trên dòng
	//Các đèn led tín hiệu để kiểm tra luật chặn hai đầu
	for (int i = col - 1; i >= 0 && i < BOARD_SIZE; i--) {
		if (_A[row][i].c == _A[row][col].c)
			a[n++] = _A[row][i];
		else {
			led1 = _A[row][i];
			break;
		}
	}
	for (int i = col + 1; i >= 0 && i < BOARD_SIZE; i++) {
		if (_A[row][i].c == _A[row][col].c)
			a[n++] = _A[row][i];
		else {
			led2 = _A[row][i];
			break;
		}
	}
	if (_MODEPLAY == _MENU[2].c && _TURN == true)
		tb[m++] = { n,{led1,led2} };
	result = CheckWin(a, n, led1, led2); if (result != 2)return result;

	//Kiểm tra trên cột
	for (int i = row + 1; i >= 0 && i < BOARD_SIZE; i++) {
		if (_A[i][col].c == _A[row][col].c) {
			a[n++] = _A[i][col];
		}
		else {
			led1 = _A[i][col];
			break;
		}

	}
	for (int i = row - 1; i >= 0 && i < BOARD_SIZE; i--) {
		if (_A[i][col].c == _A[row][col].c) {
			a[n++] = _A[i][col];
		}
		else {
			led2 = _A[i][col];
			break;
		}
	}
	if (_MODEPLAY == _MENU[2].c && _TURN == true)
		tb[m++] = { n,{led1,led2} };
	result = CheckWin(a, n, led1, led2); if (result != 2)return result;

	//Kiểm tra đường chéo chính
	for (int i = row - 1, j = col - 1; i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE; i--, j--) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			led1 = _A[i][j];
			break;
		}
	}
	for (int i = row + 1, j = col + 1; i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE; i++, j++) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			led2 = _A[i][j];
			break;
		}
	}
	if (_MODEPLAY == _MENU[2].c && _TURN == true)
		tb[m++] = { n,{led1,led2} };
	result = CheckWin(a, n, led1, led2); if (result != 2)return result;

	//Kiểm tra đường chéo phụ
	for (int i = row + 1, j = col - 1; i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE; i++, j--) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			led1 = _A[i][j];
			break;
		}

	}
	for (int i = row - 1, j = col + 1; i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE; i--, j++) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			led2 = _A[i][j];
			break;
		}
	}
	if (_MODEPLAY == _MENU[2].c && _TURN == true) {
		tb[m++] = { n,{led1,led2} };
		PVC(tb);
	}
	result = CheckWin(a, n, led1, led2); if (result != 2)return result;

	int flag = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (_A[i][j].c == 0)flag = 1;
	if (flag == 0)
		return 0;
	return 2;
}

int CheckWin(_POINT a[], int& n, _POINT& led1, _POINT& led2) {
	if ((n == 5 && (led1.c == 0 || led2.c == 0))||n>5) {
		_PlaySound(6);
		HighlightWin(a, n);
		_TURN == true ? SCORE_X++ : SCORE_O++;
		if (SCORE_X == 10 || SCORE_O == 10)
			ResetScore();
		return(_TURN == true ? 1 : -1);
	}
	ResetToCheck(a, n, led1, led2);
	return 2;
}
void ResetToCheck(_POINT a[], int& n, _POINT& led1, _POINT& led2) {
	a[n] = { 0 };
	n = 1;
	led1 = { 0,0,2 }; led2 = { 0,0,2};
}

//Xử lí hiệu ứng thắng/thua/hòa
void HighlightWin(_POINT a[], int& n) {
	for (int i = 1; i<10; i++) {
		int color = i; Sleep(600);
		for (int j = 0; j < n; j++) {
			GotoXY(a[j].x, a[j].y);
			if(i==9)SetColor(LIGHT_AQUA,PURPLE);
			else SetColor(BRIGHT_WHITE, color++);
			if (_TURN == true)cout << "X";
			else cout << "O";
		}
	}
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	Sleep(2500);
}
int ProcessFinish(int pWhoWin) {
	int top = 5, left = CENTER_X - 30;
	int bg_color = BRIGHT_WHITE, text_color = LIGHT_AQUA;
	ShowCursor(false);
	switch (pWhoWin) {
	case 1: {
		system("cls");
		PrintRectangle2lines(0, 1, WIDTH - 1, HEIGHT - 1);
		int old_mode = _setmode(_fileno(stdout), _O_WTEXT);
		SetColor(BRIGHT_WHITE, BLACK);
		wstring logo[14] = {
			 L"   ██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗     ██╗  ██╗              ",
			 L"   ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ╚██╗██╔╝              ",
			 L"   ██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     ╚███╔╝               ",
			 L"   ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     ██╔██╗               ",
			 L"   ██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║    ██╔╝╚██╗              ",
			 L"   ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝    ╚═╝  ╚═╝              ",
			 L"                                                                              ",
			 L"                                                                              ",
			 L"                                           ██╗       ██╗██╗███╗  ██╗	██╗  ",
			 L"                                           ██║  ██╗  ██║██║████╗ ██║	██║  ",
			 L"                                           ╚██╗████╗██╔╝██║██╔██╗██║	██║  ",
			 L"                                            ████╔═████║ ██║██║╚████║	╚═╝  ",
			 L"                                            ╚██╔╝ ╚██╔╝ ██║██║ ╚███║	██╗  ",
			 L"                                             ╚═╝   ╚═╝  ╚═╝╚═╝  ╚══╝	╚═╝  " };
		PrintHelicopter(55, 15);
		PrintHelicopter(155, 5);
		int count = 0;
		int color[] = { RED,BRIGHT_WHITE,GREEN,BRIGHT_WHITE, RED };
		while (count < 5) {
			SetColor(BRIGHT_WHITE, color[count]);
			for (int i = 0; i < 7; i++) {
				GotoXY(left, top + i);
				wcout << logo[i];
				GotoXY(left, top + 8 + i);
				wcout << logo[7 + i];
				Sleep(75);
			}
			count++;
			Sleep(200);
		}
		SetColor(BRIGHT_WHITE, BLACK);
		int current_mode = _setmode(_fileno(stdout), old_mode);
		break;
	}
	case -1: {
		system("cls");
		PrintRectangle2lines(0, 1, WIDTH - 1, HEIGHT - 1);
		int old_mode = _setmode(_fileno(stdout), _O_WTEXT);
		SetColor(bg_color, text_color);
		wstring logo[14] = {
			 L"   ██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗       █████╗              ",
			 L"   ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗     ██╔══██╗              ",
			 L"   ██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     ██║  ██║              ",
			 L"   ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     ██║  ██║              ",
			 L"   ██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║     ╚█████╔╝              ",
			 L"   ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝      ╚════╝              ",
			 L"                                                                              ",
			 L"                                                                              ",
			 L"                                           ██╗       ██╗██╗███╗  ██╗	██╗  ",
			 L"                                           ██║  ██╗  ██║██║████╗ ██║	██║  ",
			 L"                                           ╚██╗████╗██╔╝██║██╔██╗██║	██║  ",
			 L"                                            ████╔═████║ ██║██║╚████║	╚═╝  ",
			 L"                                            ╚██╔╝ ╚██╔╝ ██║██║ ╚███║	██╗  ",
			 L"                                             ╚═╝   ╚═╝  ╚═╝╚═╝  ╚══╝	╚═╝  " };
		PrintHelicopter(55, 15);
		PrintHelicopter(155, 5);
		int count = 0;
		int color[] = {GREEN,BRIGHT_WHITE, RED,BRIGHT_WHITE,GREEN};
		while (count< 5) {
			SetColor(BRIGHT_WHITE, color[count]);
			for (int i = 0; i < 7; i++) {
				GotoXY(left, top + i);
				wcout << logo[i];
				GotoXY(left, top + 8 + i);
				wcout << logo[7 + i];
				Sleep(75);
			}
			count++;
			Sleep(200);
		}
		SetColor(BRIGHT_WHITE, BLACK);
		int current_mode = _setmode(_fileno(stdout), old_mode);
		break;
	}
	case 0: {
		system("cls");
		PrintRectangle2lines(0, 1, WIDTH - 1, HEIGHT - 1);
		int old_mode = _setmode(_fileno(stdout), _O_WTEXT);
		SetColor(bg_color, text_color);
		_PlaySound(7);
		wstring logo[12] = {
			 L"                                    ██╗  ██╗  █████╗   	             	     	 ",
			 L"                                    ╚██╗██╔╝ ██╔══██╗  	             	     	 ",
			 L"                                     ╚███╔╝  ██║  ██║  	             	     	 ",
			 L"                                     ██╔██╗  ██║  ██║  	             	     	 ",
			 L"                                    ██╔╝╚██╗ ╚█████╔╝  	             	     	 ",
			 L"                                    ╚═╝  ╚═╝  ╚════╝   	             	         ",
			 L"                      ██████╗  ██████╗   █████╗  ██╗       ██╗  ██╗██╗██╗            ",
			 L"                      ██╔══██╗ ██╔══██╗ ██╔══██╗ ██║  ██╗  ██║  ██║██║██║            ",
			 L"                      ██║  ██║ ██████╔╝ ███████║ ╚██╗████╗██╔╝  ██║██║██║            ",
			 L"                      ██║  ██║ ██╔══██╗ ██╔══██║  ████╔═████║   ╚═╝╚═╝╚═╝            ",
			 L"                      ██████╔╝ ██║  ██║ ██║  ██║  ╚██╔╝ ╚██╔╝   ██╗██╗██╗            ",
			 L"                      ╚═════╝  ╚═╝  ╚═╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝    ╚═╝╚═╝╚═╝            " };
		PrintHelicopter(55, 15);
		PrintHelicopter(155, 5);
		int count = 0;
		int color[] = { RED,BRIGHT_WHITE,GREEN,BRIGHT_WHITE, RED};
		while (count < 5) {
			SetColor(BRIGHT_WHITE, color[count]);
			for (int i = 0; i < 6; i++) {
				GotoXY(left, top + i);
				wcout << logo[i];
				GotoXY(left, top + 8 + i);
				wcout << logo[6 + i];
				Sleep(130);
			}
			count++;
			Sleep(200);
		}
		SetColor(BRIGHT_WHITE, BLACK);
		int current_mode = _setmode(_fileno(stdout), old_mode);
		break;
	}
	case 2:
	{_TURN = !_TURN; break; }
	}
	return pWhoWin;
}

//Hỏi
int AskContinue() {
	int top = 15, left = CENTER_X - 30;
	int flag = 0;
	int bg_color = BRIGHT_WHITE, text_color = BLUE;
	KEY_EVENT_RECORD keyevent;
	EDGE bien = { 0,0,left + 25, left + 50 };
	int width = 15, height = 2;
	Draw_AskContinue();
	SetColor(bg_color, text_color);
	HLChoice(_X, _Y, width + 1);
	while (1) {
		ReadInputKey(keyevent);
		if (keyevent.bKeyDown) {
			switch (keyevent.wVirtualKeyCode) {
			case VK_LCONTROL:case 0x41:case VK_RCONTROL:case 0x44: {
				SetColor(bg_color, bg_color);
				HLChoice(_X, _Y, width + 1);
				KeyMove(&_X, &_Y, 25, 0, bien, keyevent);
				SetColor(bg_color, text_color);
				HLChoice(_X, _Y, width + 1);
				break;
			}
			case VK_RETURN: {
				_PlaySound(3);
				switch (_X) {
				case (CENTER_X-5): {
					flag = 1;
					NEW_GAME = 1;
					StartGame();
					break;
				}
				default: {
					flag = 2;
					ExitGame(); break;
				}
				}
			}
			}
		}
		keyevent.bKeyDown = false;
		if (flag == 1 || flag == 2)
			return flag;
	}
}
int AskSaveGame() {
	system("cls");
	PrintRectangle(CENTER_Y - 3, CENTER_X - 10, 30, 3);
	GotoXY(CENTER_X - 5, CENTER_Y - 2);
	cout << "Would you like to save the match?";
	GotoXY(CENTER_X - 5, CENTER_Y - 1);
	cout << "  Yes(Y)    No(N)";
	return toupper(_getch());
}
void HLChoice(int& x, int& y, int width) {
	GotoXY(x - 1, y + 1); cout << char(16);
	GotoXY(x + width, y + 1); cout << char(17);
}

//Các chức năng khác
_POINT XYinMatrix(const int& x,const int& y,int& row,int& col) {
//Dựa vào vị trí con trỏ tìm phần tử được gán lượt đánh trong ma trận
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			if (_A[i][j].x == x && _A[i][j].y == y) {
				row = i;
				col = j;
				return _A[i][j];
			}
	}
}
void ExitGame() {
	ResetPage();
	_PlaySound(4);
	ShowMenu();
}

void _PlaySound(int i)
{
	vector<const wchar_t*> soundFile{ L"moveO.wav", L"moveX.wav",
		L"move.wav", L"enter.wav", L"error.wav", L"placed.wav", L"win.wav", L"lose.wav",  L"background.wav", L"effect.wav" };
	if (SOUND == 1) {
		PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
	}
}

void PVC(TURN_BOT tb[]) {
	srand((unsigned char)time(0));
	int max = 0, number = 0;
	_POINT turn_b = { 0,0,2 };
	TURN_BOT turn_bot;
	for (int i = 0; i < 4; i++) {
		if (tb[i].led[0].c == 0 || tb[i].led[1].c == 0) {
			if ((tb[i].led[0].c == 0 && tb[i].led[1].c == 0 && tb[i].sz >= max) || tb[i].sz > max) {
				max = tb[i].sz;
				turn_bot = tb[i];
			}
		}
	}
	number = rand() % 2;
	turn_b = turn_bot.led[number];
	if (turn_b.c != 0) turn_b = turn_bot.led[1-number];
	bool stop = 0;
	if (turn_b.x < 0 || turn_b.y < 0) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			if (stop == 1) break;
			for (int j = 0; j < BOARD_SIZE; j++)
				if (_A[i][j].c == 0) {
					_X = _A[0][0].x + j * 4;
					_Y = _A[0][0].y + i * 2;
					stop = 1;
					break;
				}
		}
	}
	else {
		_X = turn_b.x;
		_Y = turn_b.y;
	}
	_TURN = false;
	Sleep(400);
	SetColor(BRIGHT_WHITE, GREEN);
	GotoXY(_X, _Y);
	_PlaySound(1);
	cout << "O";
	CheckBoard(_X, _Y);
	switch (ProcessFinish(TestBoard())) {
	case -1:case 1: {
		_PlaySound(4);
		AskContinue();
		if (_EXIT) return;
		break;
	}
	case 0: {
		AskContinue();
		if (_EXIT) return;
		break;
	}
	}
	_TURN = false;

	SetColor(BRIGHT_WHITE, RED);
	PrintX(TOP + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
	SetColor(BRIGHT_WHITE, GRAY);
	PrintO(TOP + ((BOARD_SIZE * 2) / 2) + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
	GotoXY(_LAST_POINT.x, _LAST_POINT.y);
	_LAST_POINT.c = 0;
}

void CoutListFile() {
	for (int i = 0; i < MATCH_LIST_SIZE; i++) {
		if (_MATCH_LIST[i].item == "\0")continue;
		SetColor(BRIGHT_WHITE, LIGHT_AQUA);
		PrintRectangle(CENTER_Y - 1 + i * 4, CENTER_X, 30, 4);
		GotoXY(CENTER_X + 10, CENTER_Y - 1 + i * 4 + 2);
		SetColor(BRIGHT_WHITE, BLACK);
		cout << _MATCH_LIST[i].item;
		SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	}
}

void ClearListFile(int starPoint) {
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	for (int i = starPoint; i < MATCH_LIST_SIZE; ++i) {
		GotoXY(CENTER_X, CENTER_Y - 1 + i * 4);
		for (int j = 0; j < 5; ++j) {
			GotoXY(CENTER_X, CENTER_Y + i * 4 + j);
			for (int k = 0; k < 31; ++k) {
				cout << " ";
			}
		}
	}
}

void SearchFile() {
	if (_EXIT) return;
	MODE = 4;
	string subName = "";
	char c = '\0';
	SUB_ML_SIZE = 0;
	SetColor(BRIGHT_WHITE, BLACK);
	PrintRectangle2lines(CENTER_Y - 7, CENTER_X, 30, 4);

	ClearListFile(SUB_ML_SIZE);
	CoutListFile();

	SetColor(BRIGHT_WHITE, BLACK);
	GotoXY(CENTER_X + 8, CENTER_Y - 5);
	for (int i = 0; i < 15; i++) cout << " ";
	GotoXY(CENTER_X + 1, CENTER_Y - 5);
	cout << " Find: ";
	do { //Nhập tên file
		c = _getch();
		if (c == 13) {
			if (SUB_ML_SIZE == 0) continue;
			else {
				//Di chuyển con trỏ 
				SetColor(BRIGHT_WHITE, BLACK);
				PrintLeftCursor(_Y, CENTER_X - 6);
				PrintRightCursor(_Y, CENTER_X + 32);
			}
			if (subName == "") MODE = 3;
			return;
		}
		if (48 <= c && c <= 57 || 65 <= c && c <= 90 || 97 <= c && c <= 122 || c == '_' || c == '-') {
			subName += c;
			cout << c;
		}
		if (c == 8) {
			if (subName.length() > 0) {
				subName.erase(subName.end() - 1);
				cout << c << ' ' << c;
			}
		}
		SUB_ML_SIZE = 0;
		_SUB_ML.clear();
		if (subName != "") {
			GotoXY(CENTER_X + 8, CENTER_Y);
			cout << "                  ";
			for (int i = 0; i < MATCH_LIST_SIZE; ++i) {
				if (CheckSubStr(subName, _MATCH_LIST[i].item)) {
					_SUB_ML.push_back({ _MATCH_LIST[i].x,_MATCH_LIST[SUB_ML_SIZE].y,_MATCH_LIST[i].item });
					++SUB_ML_SIZE;
				}
			}
			ClearListFile(SUB_ML_SIZE);
		}
		if (subName == "" && c == 8) {
			GotoXY(CENTER_X + 8, CENTER_Y);
			cout << "                  ";
			CoutListFile();
		}
		if (c == 27) {
			SUB_ML_SIZE = 0;
			_SUB_ML.clear();
			ShowFileGame();
		}
		if (SUB_ML_SIZE) {
			for (int i = 0; i < SUB_ML_SIZE; i++) {
				if (_SUB_ML[i].item == "\0")continue;
				PrintRectangle(CENTER_Y - 1 + i * 4, CENTER_X, 30, 4);
				GotoXY(CENTER_X + 10, CENTER_Y - 1 + i * 4 + 2);
				SetColor(BRIGHT_WHITE, BLACK);
				cout << _SUB_ML[i].item;
				SetColor(BRIGHT_WHITE, LIGHT_AQUA);
			}
			_Y = _SUB_ML[0].y;
		}
		else {
			if (subName != "") {
				GotoXY(CENTER_X + 8, CENTER_Y);
				cout << "No files found !";
			}
		}
		GotoXY(CENTER_X + 8 + subName.length(), CENTER_Y - 5);
		SetColor(BRIGHT_WHITE, BLACK);
	} while (1);
}

bool CheckSubStr(string sub, string src) {
	int i = 0, j = 0;
	while (i < src.length()) {
		while (sub[j] == src[i]) {
			++j;
			++i;
			if (j == sub.length())
				return 1;
		}
		i -= j;
		j = 0;
		++i;
	}
	return 0;
}