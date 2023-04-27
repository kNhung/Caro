#include "control.h"
#include "model.h"
#include "view.h"
#include "page.h"


//Lưu game
void SaveGame() {
	SetColor(BRIGHT_WHITE, BLACK);
	string matchName;
	char c;
	do{ //Nhập tên file
		c = _getch();
		if (48 <= c && c <= 57 || 65 <= c && c <= 90 || 97 <= c && c <= 122 || c == '_' || c == '-') {
			matchName += c;
			cout << c;
		}
		else if (c == 8) {
			if (matchName.length() > 0) {
				matchName.erase(matchName.end() - 1);
				cout << c << ' ' << c;
			}
		}
		else if (c == 27)
			ShowGame();
	} while(c!=13);

	_MATCH_LIST_FILE.open("game_files.txt", ios::app);
	if (!_MATCH_LIST_FILE) {
		GotoXY(CENTER_X + 2, CENTER_Y + 3);
		cout << "Cannot save";
		return;
	}
	while (CheckExistedFile(matchName) == 1) {
		GotoXY(CENTER_X + 2, CENTER_Y + 3);
		cout << "  File existed!";
		GotoXY(CENTER_X + 2, CENTER_Y + 2);
		for (int i = 0;i < 10;++i)
			cout << " ";
		GotoXY(CENTER_X + 2, CENTER_Y + 2);
		do { //Nhập tên file
			c = _getch();
			if (48 <= c && c <= 57 || 65 <= c && c <= 90 || 97 <= c && c <= 122 || c == '_' || c == '-') {
				matchName += c;
				cout << c;
			}
			else if (c == 8) {
				if (matchName.length() > 0) {
					matchName.erase(matchName.end() - 1);
					cout << c << ' ' << c;
				}
			}
			else if (c == 27) {
				ShowGame();
			}
		} while (c != 13||CheckExistedFile(matchName)==1);
	}
	_MATCH_LIST_FILE.seekg(0, ios::end);
	_MATCH_LIST_FILE << endl << matchName + ".txt";
	SaveMatchInfo(matchName);
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
int TestBoard(KEY_EVENT_RECORD key) {
//Kiểm tra thắng thua, người 1 hay _Turn=true thắng thì trả về -1 người còn lại thắng trả về 1,
//hòa nhau trả về 0 còn chưa phân định ai thắng trả về 2
	_POINT led1 = { 0,0,2 }, led2 = { 0,0,2 };
	int row = 0, col = 0;
	int result = 2, n = 0, m = 0;

	//Mang luu toa do duong chien thang
	_POINT a[9];
	_POINT p = XYinMatrix(_X, _Y, row, col);
	TURN_BOT tb[4];
	a[n++] = p;

	//Kiểm tra trên dòng
	//Các đèn led tín hieu de kiem tra luat chan hai dau
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
	for (int i = row - 1, j = col - 1; i >= 0 && i < BOARD_SIZE, j >= 0 && j < BOARD_SIZE; i--, j--) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			led1 = _A[i][j];
			break;
		}
	}
	for (int i = row + 1, j = col + 1; i >= 0 && i < BOARD_SIZE, j >= 0 && j < BOARD_SIZE; i++, j++) {
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
	for (int i = row + 1, j = col - 1; i >= 0 && i < BOARD_SIZE, j >= 0 && j < BOARD_SIZE; i++, j--) {
		if (_A[i][j].c == _A[row][col].c) {
			a[n++] = _A[i][j];
		}
		else {
			led1 = _A[i][j];
			break;
		}

	}
	for (int i = row - 1, j = col + 1; i >= 0 && i < BOARD_SIZE, j >= 0 && j < BOARD_SIZE; i--, j++) {
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
		PVC(key, tb);
	}
	result = CheckWin(a, n, led1, led2); if (result != 2)return result;
	for (int i = 0; i < 4; i++) tb[i] = { 0,{{0,0},{0,0}} };

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
	led1.c = 2; led2.c = 2;
}

//Xử lí hiệu ứng thắng/thua/hòa
void HighlightWin(_POINT a[], int& n) {
	int tmp = 6;
	for (int i = 1; tmp; i++) {
		int color = i; Sleep(100);
		if (i == 10) {
			tmp--;
			i = 0;
		}
		for (int j = 0; j < n; j++) {
			GotoXY(a[j].x, a[j].y);
			SetColor(BRIGHT_WHITE, color++);
			if (_TURN == true)cout << "X";
			else cout << "O";
		}
	}
}
int ProcessFinish(int pWhoWin) {
	PrintRectangle2lines(0, 1, WIDTH - 1, HEIGHT - 1);
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
		int color[] = { RED,BRIGHT_WHITE,GREEN,BRIGHT_WHITE, RED,BRIGHT_WHITE,GREEN,BRIGHT_WHITE,RED };
		while (count++ < 8) {
			SetColor(BRIGHT_WHITE, color[count]);
			for (int i = 0; i < 7; i++) {
				GotoXY(left, top + i);
				wcout << logo[i];
				GotoXY(left, top + 8 + i);
				wcout << logo[7 + i];
				Sleep(75);
			}
			Sleep(250);
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
		int color[] = { RED,BRIGHT_WHITE,GREEN,BRIGHT_WHITE, RED,BRIGHT_WHITE,GREEN,BRIGHT_WHITE,RED };
		while (count++ < 8) {
			SetColor(BRIGHT_WHITE, color[count]);
			for (int i = 0; i < 7; i++) {
				GotoXY(left, top + i);
				wcout << logo[i];
				GotoXY(left, top + 8 + i);
				wcout << logo[7 + i];
				Sleep(75);
			}
			Sleep(250);
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
		int color[] = { RED,BRIGHT_WHITE,GREEN,BRIGHT_WHITE, RED,BRIGHT_WHITE,GREEN,BRIGHT_WHITE,RED };
		while (count++ < 8) {
			SetColor(BRIGHT_WHITE, color[count]);
			for (int i = 0; i < 6; i++) {
				GotoXY(left, top + i);
				wcout << logo[i];
				GotoXY(left, top + 8 + i);
				wcout << logo[6 + i];
				Sleep(130);
			}
			Sleep(250);
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
	cout << "Want to save the match?";
	GotoXY(CENTER_X - 5, CENTER_Y - 1);
	cout << "  Yes(Y)    No(N)";
	return toupper(_getch());
}
void HLChoice(int& x, int& y, int width) {
	GotoXY(x - 1, y + 1); cout << char(16);
	GotoXY(x + width, y + 1); cout << char(17);
}

//Các chức năng khác
_POINT XYinMatrix(int& x, int& y,int& row,int& col) {
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
	ShowLoadingPage();
	_PlaySound(4);
	ShowMenu();
}
void RemoveMatchFile(string matchName) {
	int n = matchName.length();
	char* c = new char[n + 1];
	for (int i = 0;i < n;i++) {
		c[i] = matchName[i];
	}
	c[n] = '\0';
	remove(c);
}
void GabageCollect() {
	return;
}
void _PlaySound(int i)
{
	vector<const wchar_t*> soundFile{ L"moveO.wav", L"moveX.wav",
		L"move.wav", L"enter.wav", L"error.wav", L"placed.wav", L"win.wav", L"lose.wav",  L"background.wav", L"effect.wav" };
	if (SOUND == 1) {
		PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
	}
}
void PVC(KEY_EVENT_RECORD key, TURN_BOT tb[]) {
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> uni(0, 1);
	int max = 0;
	_POINT turn_b;
	for (int i = 0; i < 4; i++) {
		if (tb[i].led[0].c == 0 || tb[i].led[1].c == 0) {
			if ((tb[i].led[0].c == 0 && tb[i].led[1].c == 0 && tb[i].sz >= max) || tb[i].sz > max) {
				max = tb[i].sz;
				do {
					int rd = uni(rng);
					turn_b = tb[i].led[rd];
					if (turn_b.c == 0)break;
				} while (1);
			}
		}
	}
	_X = turn_b.x; _Y = turn_b.y;
	GotoXY(_X, _Y);
	SetColor(BRIGHT_WHITE, GREEN);
	cout << "O";
	_LAST_POINT.c = 0;
	key.bKeyDown = true;
	key.wVirtualKeyCode = VK_RETURN;
}