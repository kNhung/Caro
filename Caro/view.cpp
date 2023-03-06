#include "control.h"
#include "model.h"
#include "view.h"

//Chưa chạy được :<
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
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
	GotoXY(40, 10); cout << "New";
	GotoXY(40, 12); cout << "Continue";
	GotoXY(40, 14); cout << "About";
	GotoXY(40, 16); cout << "Exit";
}

void DrawMatchList() {
	system("color 79");
	for (int i = 0; i < MATCH_LIST_SIZE; i++) {
		GotoXY(40, 10 + i * 2);
		cout << _MATCH_LIST[i].item;
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
	_X = 40;_Y = 10;
	while (1) {
		DrawMenu();
		word = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(word, 7 * 16 + 12);
		GotoXY(38, _Y); cout << ">";
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			MoveUp();
			GotoXY(38, _Y);
			cout << ">";
		}
		else if (_COMMAND == 'S') {
			MoveDown();
			GotoXY(38, _Y);
			cout << ">";
		}
		else if (_COMMAND == 13) {
			ShowLoadingPage();
			for (int i = 0;i < MENU_SIZE;i++)
				if (_Y == _MENU[i].y)
					ShowPage(_MENU[i].c);
		}
		system("cls");
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

}

void ShowFileGame() {
	HANDLE word;
	MODE = 3;
	_X = 40; _Y = 10;
	GetMatchListSize();
	while (1) {
		DrawMatchList();
		word = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(word, 7 * 16 + 12);
		GotoXY(38, _Y); cout << ">";
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			MoveUp();
			GotoXY(38, _Y);
			cout << ">";
		}
		else if (_COMMAND == 'S') {
			MoveDown();
			GotoXY(38, _Y);
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
		system("cls");
	}
}

void GetMatchListSize() {
	string line;
	ifstream file("game_files.txt");
	if (!file) {
		cout << "Cannot get match list size";
		return;
	}
	_X = 40;_Y = 10;
	if (MATCH_LIST_SIZE == 0) {
		while (getline(file, line)) {
			++MATCH_LIST_SIZE;
			_LIST list = { _X,_Y,line };
			_MATCH_LIST.push_back(list);
			_Y += 2;
		}
		_Y -= 2;
	}
	else {
		int i = -1;
		while (getline(file, line)) {
			++i;
			_Y += 2;
			if (i == MATCH_LIST_SIZE && CheckSameString(line,_MATCH_LIST[i-1].item)==0) {
				_Y -= 2;
				_LIST list = { _X,_Y,line };
				_MATCH_LIST.push_back(list);
				++MATCH_LIST_SIZE;
			}
		}
		_Y -= 2;
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