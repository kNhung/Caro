#include "control.h"
#include "model.h"
#include "view.h"

void FixConsoleWindow() {
	HWND myConsole = GetConsoleWindow();
	HDC mdc = GetDC(myConsole);

	RECT rectClient, rectWindow;
	GetClientRect(myConsole, &rectClient), GetWindowRect(myConsole, &rectWindow);
	int width = 1216;
	int height = 784;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(myConsole, posX, posY, width, height, TRUE);

	SetWindowLong(myConsole, GWL_STYLE,
		GetWindowLong(myConsole, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));

	ShowScrollBar(myConsole, SB_BOTH, 0);

	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);

	// Lấy handle của menu system
	HMENU hMenu = GetSystemMenu(myConsole, FALSE);
	// Lấy ID của nút Maximum
	UINT uID = SC_MAXIMIZE;
	// Làm mờ nút Maximum bằng ID
	EnableMenuItem(hMenu, uID, MF_BYCOMMAND | MF_GRAYED);
	// Cập nhật lại menu
	DrawMenuBar(myConsole);
}

void SetFontSize(int fontSize) {
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.nFont = 0;
	info.dwFontSize.X = fontSize; // Chiều rộng của mỗi ký tự trong font
	info.dwFontSize.Y = fontSize; // Chiều cao
	info.FontFamily = FF_DONTCARE;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ResetData() {
	for (int i = 0;i < BOARD_SIZE;i++) {
		for (int j = 0;j < BOARD_SIZE;j++) {
			_A[i][j].x = 4 * j + LEFT + 2;
			_A[i][j].y = 2 * i + TOP + 1;
			_A[i][j].c = 0;
		}
	}
	_TURN = true; _COMMAND = -1;
	_X = _A[0][0].x; _Y = _A[0][0].y;
}


void DrawBoard(int pSize) {
	for (int i = 0;i <= pSize;i++) {
		for (int j = 0;j <= pSize;j++) {
			GotoXY(LEFT + 4 * i, TOP + 2 * j);
			cout << ".";
		}
	}
	GotoXY(pSize * 4 + 10, pSize + 4);
	cout << "Nhan ESC de tro ve menu";
}

void DrawExistedData() {
	for(int i=0;i<BOARD_SIZE;i++)
		for (int j = 0;j < BOARD_SIZE;j++) {
			if (_A[i][j].c != 0) {
				GotoXY(_A[i][j].x, _A[i][j].y);
				switch (_A[i][j].c) {
				case -1: cout << "X"; break;
				case 1: cout << "O"; break;
				}
			}
		}
}

void DrawMenu() {
	system("color 79");
	GotoXY(CENTER_X, CENTER_Y); cout << "New";
	GotoXY(CENTER_X, CENTER_Y + 2); cout << "Continue";
	GotoXY(CENTER_X, CENTER_Y + 4); cout << "About";
	GotoXY(CENTER_X, CENTER_Y + 6); cout << "Exit";
}

void DrawMatchList() {
	system("color 16");
	//Vẽ nút Trở về
	GotoXY(90, 25);
	cout << "Press ESC to back to menu";

	//Vẽ chữ LOAD GAME
	int logo_x = 22, logo_y = 3;
	DrawLetter(L, logo_x, logo_y);
	DrawLetter(O, logo_x + 9, logo_y);
	DrawLetter(A, logo_x + 9 * 2, logo_y);
	DrawLetter(D, logo_x + 9 * 3, logo_y);
	DrawLetter(G, logo_x + 9 * 4 + 3, logo_y);
	DrawLetter(A, logo_x + 9 * 5 + 3, logo_y);
	DrawLetter(M, logo_x + 9 * 6 + 3, logo_y);
	DrawLetter(E, logo_x + 9 * 7 + 3, logo_y);

	//Vẽ các phần tử của danh sách
	for (int i = 0; i < MATCH_LIST_SIZE; i++) {
		GotoXY(CENTER_X - 3, CENTER_Y + i * 3 - 1);
		cout << char(218); //Góc trên trái

		GotoXY(CENTER_X - 2, CENTER_Y + i * 3 - 1);
		for (int i = 0;i < 15;i++)
			cout << char(2500); //Đường ngang trên

		GotoXY(CENTER_X + 13, CENTER_Y + i * 3 - 1);
		cout << char(191); //Góc trên phải

		GotoXY(CENTER_X - 3, CENTER_Y + i * 3);
		cout << char(179); //Đường thẳng trái

		GotoXY(CENTER_X, CENTER_Y + i * 3);
		cout << _MATCH_LIST[i].item; 

		GotoXY(CENTER_X + 13, CENTER_Y + i * 3);
		cout << char(179); //Đường thẳng phải

		GotoXY(CENTER_X - 3, CENTER_Y + i * 3 + 1);
		cout << char(192); //Góc dưới trái

		GotoXY(CENTER_X - 2, CENTER_Y + i * 3 + 1);
		for (int i = 0;i < 15;i++)
			cout << char(2500); //Đường ngang dưới

		GotoXY(CENTER_X + 13, CENTER_Y + i * 3 + 1);
		cout << char(217); //Góc dưới phải
	}

	//Vẽ mây trái
	SetColor(1, 7);
	GotoXY(0, 19);
	for (int i = 0;i < 6;i++)
		cout << char(219);
	GotoXY(0, 20);
	for(int i=0;i<8;i++)
		cout << char(219);
	GotoXY(0, 20 + 1);
	for(int i=0;i<10;i++)
		cout << char(219);
	GotoXY(0, 20 + 2);
	for (int i = 0;i < 12;i++)
		cout << char(219);
	GotoXY(0, 20 + 3);
	for (int i = 0;i < 12;i++)
		cout << char(219);
	GotoXY(0, 20 + 4);
	for (int i = 0;i < 11;i++)
		cout << char(219);

	//Vẽ mây phải
	GotoXY(112, 12);
	for (int i = 0;i < 8;i++)
		cout << char(219);
	GotoXY(109, 13);
	for (int i = 0;i < 11;i++)
		cout << char(219);
	GotoXY(108, 14);
	for (int i = 0;i < 12;i++)
		cout << char(219);
	GotoXY(104, 15);
	for (int i = 0;i < 16;i++)
		cout << char(219);
	GotoXY(104, 16);
	for (int i = 0;i < 16;i++)
		cout << char(219);
	GotoXY(107, 17);
	for (int i = 0;i < 13;i++)
		cout << char(219);
	
	GotoXY(CENTER_X, CENTER_Y);
}

void DrawLetter(unsigned char letter[], int X, int Y) {
	int m = 0;
	for (int k = 0;k < LETTER_LIST_SIZE;k++) {
		if (LETTER_LIST[k]==letter) {
			m = 0;
			GotoXY(X, Y);
			for (int i = 1;i <= 5;i++) {
				for (int j = 1;j <= 7;j++) {
					cout << LETTER_LIST[k][m];
					++m;
				}
				GotoXY(X, ++Y);
			}
		}
	}
	
}

void GetWinLine(vector <_POINT>& winLine, int i, int j, char type) {
	if (type == 'r') { //Ngang
		while (_A[i][j - 1].c == _A[i][j].c) {
			winLine.push_back(_A[i][j]);
			--j;
		}
	}

	else if (type == 'c') { //Dọc
		while (_A[i - 1][j].c == _A[i][j].c) {
			winLine.push_back(_A[i][j]);
			--i;
		}
	}

	else if (type == 'd') { //Chéo chính
		while (_A[i - 1][j - 1].c == _A[i][j].c) {
			winLine.push_back(_A[i][j]);
			--i;
			--j;
		}
	}

	else if (type == 's') { //Chéo phụ
		while (_A[i - 1][j + 1].c == _A[i][j].c) {
			winLine.push_back(_A[i][j]);
			--i;
			++j;
		}
	}
}

void SetColor(int backgoundColor, int textColor) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorCode = backgoundColor * 16 + textColor;
	SetConsoleTextAttribute(hStdout, colorCode);
}

void HighlightWin(vector <_POINT>& winLine) {
	for (int i = 0;i < winLine.size();i++) {
		GotoXY(winLine[i].x, winLine[i].y);
		SetColor(7, 13);
		if (_TURN == 1) cout << "X";
		else cout << "O";
	}
}


int ProcessFinish(int pWhoWin) {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
	switch (pWhoWin) {
	case -1:
		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", true, false);
		break;
	case 1:
		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", false, true);
		break;

	case 0:
		printf("Hai nguoi choi hoa nhau");
		break;
	case 2:
		_TURN = !_TURN;
	}
	GotoXY(_X, _Y);
	return pWhoWin;
}

int AskContinue() {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	printf("Nhan 'y/n' de tiep tuc/dung: ");
	return toupper(_getch());
}

int AskSaveGame() {
	//Khung hỏi lưu game...
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	cout << "Ban co muon luu tran dau nay lai khong? Y/N";
	return toupper(_getch());
}

void SaveGame() {
	string matchName;
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	cout << "File name: ";
	getline(cin, matchName);
	_MATCH_LIST_FILE.open("game_files.txt",ios::app);
	if (!_MATCH_LIST_FILE) {
		cout << "Khong mo duoc tap tin" << endl;
		return;
	}
	while (CheckExistedFile(matchName) == 1) {
		cout <<endl<< "File da ton tai";
		cin.ignore();
		getline(cin, matchName);
		//Khi code tran hoàn chỉnh thì thêm cls,GotoXY để getline
	}
	while (CheckValidName(matchName) == 0) {
		cout <<endl<< "Ten khong hop le";
		cin.ignore();
		getline(cin, matchName);
		//Khi code tran hoàn chỉnh thì thêm cls,GotoXY để getline

	}
	_MATCH_LIST_FILE << matchName + ".txt"<<endl;
	SaveMatchInfo(matchName);
	_MATCH_LIST_FILE.close();
}

void SaveMatchInfo(string matchName) {
	matchName += ".txt";
	ofstream matchFile(matchName);
	if (!matchFile) {
		cout << "Cannot open matchFile";
		return;
	}
	 cout << "Opened matchFile";
	 for (int i = 0;i < BOARD_SIZE;i++) {
		 for (int j = 0;j < BOARD_SIZE;j++) {
			 matchFile << _A[i][j].c<<endl;
		 }
	 }
	 matchFile.close();
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


//Hiện trang chuyển
void ShowLoadingPage() {
	system("cls");
	//Code backgroud, khung menu...
	system("color 79");
	GotoXY(40, 15);
	cout << "This is loading page...";
	Sleep(500);
	system("cls");
}

//Chuyển trang
void ShowPage(int page) {
	switch (page) {
	case 1: ShowGame(); break;
	case 2: ShowFileGame(); break;
	case 3: ShowAbout(); break;
	case 4: Exit();
	}
}

void ShowMenu() {
	HANDLE word;
	MODE = 1;
	NEW_GAME = 1;
	_X = CENTER_X;_Y = CENTER_Y;
	DrawMenu();
	SetColor(7, 12);
	GotoXY(CENTER_X - 2, CENTER_Y);
	cout << ">";
	while (1) {
		word = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(word, 7 * 16 + 12);
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			MoveUp();
			SetColor(7, 7);
			GotoXY(CENTER_X - 2, _Y + 2); cout << ">";
			SetColor(7, 12);
			GotoXY(CENTER_X - 2, _Y);
			cout << ">";
		}
		else if (_COMMAND == 'S') {
			MoveDown();
			SetColor(7, 7);
			GotoXY(CENTER_X - 2, _Y - 2); cout << ">";
			SetColor(7, 12);
			GotoXY(CENTER_X - 2, _Y);
			cout << ">";
		}
		else if (_COMMAND == 13) {
			ShowLoadingPage();
			for (int i = 0;i < MENU_SIZE;i++)
				if (_Y == _MENU[i].y)
					ShowPage(_MENU[i].c);
		}
		//system("cls");
	}
}

void ShowGame() {
	MODE = 2;
	StartGame();
	_X = _A[0][0].x; _Y = _A[0][0].y ;
	GotoXY(_X, _Y);
	bool validEnter = true;
	while (1) {
		_COMMAND = toupper(_getch()); //_getch() chu khong phai getch()
		if (_COMMAND == 27) {
			ShowLoadingPage();
			ShowMenu();
			return;
		}
		else {
			if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 13) { //Enter
				switch (CheckBoard(_X, _Y)) {
				case -1:
					cout << "X"; break;
				case 1:
					cout << "O"; break;
				case 0:
					validEnter = false;
				}

				if (validEnter == true) {
					switch (ProcessFinish(TestBoard())) {
					case -1:case 1:case 0:
						if (AskSaveGame() == 'Y') {
							SaveGame();
						}
						else {
							ShowLoadingPage();
							ShowMenu();
							return;
						}
						
					}
				}
				validEnter = true;
			}
		}
	}
}

void ShowAbout() {
	//Vẽ About ở đây...
	
	_COMMAND = toupper(_getch()); //_getch() chu khong phai getch()
	if (_COMMAND == 27) {
		ShowLoadingPage();
		ShowMenu();
		return;
	}
}

void ShowFileGame() {
	HANDLE word;
	MODE = 3;
	_X = CENTER_X; _Y = CENTER_Y;
	GetMatchListSize();
	DrawMatchList();
	while (1) {
		word = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(word, 1 * 16 + 6);
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			MoveUp();
			SetColor(1, 1);
			GotoXY(CENTER_X - 5, _Y + 3);cout << ">";
			SetColor(1, 6);
			GotoXY(CENTER_X - 5, _Y);
			cout << ">";
		}
		else if (_COMMAND == 'S') {
			MoveDown();
			SetColor(1, 1);
			GotoXY(CENTER_X - 5, _Y - 3);cout << ">";
			SetColor(1, 6);
			GotoXY(CENTER_X - 5, _Y);
			cout << ">";
		}
		else if (_COMMAND == 27) {
			ShowLoadingPage();
			ShowMenu();
		}
		else if (_COMMAND == 13) {
			ShowLoadingPage();
			for (int i = 0;i < MATCH_LIST_SIZE;i++) {
				if (_Y == _MATCH_LIST[i].y) {
					NEW_GAME = 0;
					LoadGame(_MATCH_LIST[i].item);
					ShowGame();
				}
			}
		}
		else if (_COMMAND == 0x7F) {
			ShowLoadingPage();
			for (int i = 0;i < MATCH_LIST_SIZE;i++) {
				if (_Y == _MATCH_LIST[i].y) {
					RemoveMatchFile(_MATCH_LIST[i].item);
				}
			}
		}
		//system("cls");
	}
}

void GetMatchListSize() {
	string line;
	ifstream file("game_files.txt");
	if (!file) {
		cout << "Cannot get match list size";
		return;
	}
	_X = CENTER_X;_Y = CENTER_Y;
	if (MATCH_LIST_SIZE == 0) {
		while (getline(file, line)) {
			++MATCH_LIST_SIZE;
			_LIST list = { _X,_Y,line };
			_MATCH_LIST.push_back(list);
			_Y += 3;
		}
		_Y -= 3;
	}
	else {
		int i = -1;
		while (getline(file, line)) {
			++i;
			_Y += 3;
			if (i == MATCH_LIST_SIZE && CheckSameString(line,_MATCH_LIST[i-1].item)==0) {
				_Y -= 3;
				_LIST list = { _X,_Y,line };
				_MATCH_LIST.push_back(list);
				++MATCH_LIST_SIZE;
			}
		}
		_Y -= 9;
	}
	file.close();
}

void LoadGame(string matchName) {
	int i = 0, j = 0, m = 0,value=0;
	int numbers[BOARD_SIZE * BOARD_SIZE];
	ifstream matchFile(matchName);
	if (!matchFile) {
		cout << "Cannot open match file";
		return;
	}
	while (!matchFile.eof()) {
		matchFile >> numbers[m];
		++m;
	}
	m = 0;
	for (int i = 0;i < BOARD_SIZE;i++) 
		for (int j = 0;j < BOARD_SIZE;j++) {
			_A[i][j].x = 4 * j + LEFT + 2;
			_A[i][j].y = 2 * i + TOP + 1;
			_A[i][j].c = numbers[m];
			++m;
		}
	_TURN = true; _COMMAND = -1;
	_X = _A[0][0].x; _Y = _A[0][0].y;
}