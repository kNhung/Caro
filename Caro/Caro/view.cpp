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

//Dịch chuyển đến điểm
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Xóa dữ liệu bàn cờ và trả vị trí về góc bàn cờ
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

//Vẽ bàn cờ
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

//Vẽ khung menu
void DrawMenu() {
	system("color 79");
	GotoXY(40, 10); cout << "New";
	GotoXY(40, 12); cout << "Continue";
	GotoXY(40, 14); cout << "About";
	GotoXY(40, 16); cout << "Exit";
}

//Kiểm tra ai thắng
//kiểm tra _TURN
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
	DrawMenu();
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
			for (int i = 0;i < MENU_OPTIONS;i++)
				if (_Y == _MENU[i].y)
					ShowPage(_MENU[i].c);
		}
		system("cls");
	}
}

//Show trận đấu
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
						if (AskContinue() == 'Y')
							StartGame(); 
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
	
}