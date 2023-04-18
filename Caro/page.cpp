#include "control.h"
#include "model.h"
#include "view.h"
#include "page.h"

void ShowPage(int page) {
	switch (page) {
	case 1: ShowGame(); break;
	case 2: ShowFileGame(); break;
	case 3: /*Danh voi may;*/ break;
	case 4: ShowAbout(); break;
	}
}
void ShowLoadingPage() {
	system("cls");
	system("color F1");
	//V? khung
	PrintRectangle(0, 1, 116, 28);
	//Vẽ chữ LOADING
	int logo_x = 25, logo_y = 5;

	for (int i = 0;i <= 2;i++) {
		GotoXY(logo_x + 9 * 7 + 4 * i, logo_y + 4);
		cout << char(219) << char(219);
	}
	//V? 3 trái tim nh?
	for (int i = 0;i < 3;i++) {
		GotoXY(logo_x + 20 + 12 * i, logo_y - 3);
		cout << char(003) << "  ";
	}
	//V? cây
	PrintTree(logo_x + 15, logo_y + 10);
	Sleep(700);
	system("cls");
}
void ShowMenu() {
	ShowCursor(0);
	HANDLE word;
	MODE = 1;
	NEW_GAME = 1;
	_X = CENTER_X - 14;_Y = CENTER_Y - 3;
	int backgroundColor = BRIGHT_WHITE, textColor = BLUE;
	DrawMenu();
	SetColor(BRIGHT_WHITE, BLACK);
	PrintLeftCursor(CENTER_Y - 3, CENTER_X - 21);
	PrintRightCursor(CENTER_Y - 3, CENTER_X + 47);
	SetColor(backgroundColor, textColor);
	int previousOption = 0;
	while (1) {
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			MoveUp();
			//Xóa con trỏ ở vị trí cũ + unhighlight option trước
			SetColor(backgroundColor, backgroundColor);
			PrintLeftCursor(_Y + 5, CENTER_X - 21);
			PrintRightCursor(_Y + 5, CENTER_X + 47);
			ClearPreviousHightlight(previousOption);
			//Di chuyển con trỏ và hightlight option hiện tại
			SetColor(backgroundColor, BLACK);
			PrintLeftCursor(_Y, CENTER_X - 21);
			PrintRightCursor(_Y, CENTER_X + 47);
			previousOption--;
			PrintCurrentHighlight(previousOption);
		}
		else if (_COMMAND == 'S') {
			MoveDown();
			//Xóa con trỏ ở vị trí cũ + unhighlight  option trước
			SetColor(backgroundColor, backgroundColor);
			PrintLeftCursor(_Y - 5, CENTER_X - 21);
			PrintRightCursor(_Y - 5, CENTER_X + 47);
			ClearPreviousHightlight(previousOption);
			SetColor(backgroundColor, BLACK);
			//Di chuyển con trỏ và hightlight option hiện tại
			PrintLeftCursor(_Y, CENTER_X - 21);
			PrintRightCursor(_Y, CENTER_X + 47);
			previousOption++;
			PrintCurrentHighlight(previousOption);
		}
		else if (_COMMAND == 13 && _Y == _MENU[4].y) {
			SetColor(BRIGHT_WHITE, BLACK);
			system("cls");
			GabageCollect();
			return;
		}
		else if (_COMMAND == 13) {
			ShowLoadingPage();
			for (int i = 0;i < MENU_SIZE;i++)
				if (_Y == _MENU[i].y)
					ShowPage(_MENU[i].c);
		}
	}
}
void ShowGame() {
	bool _loop = true;
	MODE = 2;
	_LOADMARK = false;
	StartGame();
	ShowCursor(0);
	int row_console = 0, column_console = 0, row = 0;
	int flag = 0;
	KEY_EVENT_RECORD keyevent;
	EDGE bien = { TOP + 1,TOP + BOARD_SIZE * 2 - 1,LEFT + 2,LEFT + BOARD_SIZE * 4 - 2 };
	bool validEnter = true;
	while (_loop) {
		bool pause = false;
		DrawBoard();
		GotoXY(_A[0][0].x, _A[0][0].y);
		while (!pause) {
			ReadInputKey(keyevent);
			if (keyevent.bKeyDown) {
				KeyMove(&_X, &_Y, 4, 2, bien, keyevent);
				switch (keyevent.wVirtualKeyCode) {
				case (VK_ESCAPE): case (0x4C): {
					ShowAsk(keyevent.wVirtualKeyCode);
					break;
				}
				case (0x48): {
					pause = 1;
					_LOADMARK = true;
					ShowHelp();
					break; }
				case (VK_RETURN): {
					switch (CheckBoard(_X, _Y)) {
					case -1: {
						SetColor(BRIGHT_WHITE, RED);
						cout << "X";
						Save_1_move(row_console, column_console);
						break;
					}
					case 1: {
						SetColor(BRIGHT_WHITE, GOAL);
						cout << "O";
						Save_1_move(row_console, column_console);
						break;
					}
					case 0: validEnter = false;
					}
					if (validEnter == true) {
						switch (ProcessFinish(TestBoard())) {
						case -1:case 1:case 0: {
							flag = AskContinue();
							break;
						}
						}
					}
					break;
				}
				case (0x55): {
					_X = column_console;
					_Y = row_console;
					GotoXY(_X, _Y);
					cout << char(32);
					GotoXY(_X, _Y);
					_POINT p = XYinMatrix(column_console, row_console, row, row);
					p.c = 0;
					_TURN = !_TURN;
					break;
				}
				}
			}
			keyevent.bKeyDown = false;
			validEnter = true;
			if (flag == 2)break;
		}
		if (pause)
			continue;
	}
	ShowMenu();

}
void ShowAbout() {
	//V? About ? dây...
	DrawAbout();
	while (1) {
		_COMMAND = toupper(_getch()); //_getch() chu khong phai getch()
		if (_COMMAND == 27) {
			ShowLoadingPage();
			ShowMenu();
			return;
		}
	}
}
void ShowFileGame() {
	HANDLE word;
	int backgroundColor = BRIGHT_WHITE, textColor = BLUE;
	MODE = 3;
	GetMatchListSize();
	DrawMatchList();
	_X = CENTER_X; _Y = CENTER_Y - 1;
	SetColor(BRIGHT_WHITE, BLACK);
	PrintLeftCursor(_Y, CENTER_X - 6);
	PrintRightCursor(_Y, CENTER_X + 32);
	//int currentOption = 0;
	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			MoveUp();
			//Xóa con trỏ ở vị trí cũ 
			SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			PrintLeftCursor(_Y + 5, CENTER_X - 6);
			PrintRightCursor(_Y + 5, CENTER_X + 32);
			//Di chuyển con trỏ 
			SetColor(BRIGHT_WHITE, BLACK);
			PrintLeftCursor(_Y, CENTER_X - 6);
			PrintRightCursor(_Y, CENTER_X + 32);
		}
		else if (_COMMAND == 'S') {
			MoveDown();
			//Xóa con trỏ ở vị trí cũ 
			SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			PrintLeftCursor(_Y - 5, CENTER_X - 6);
			PrintRightCursor(_Y - 5, CENTER_X + 32);
			//Di chuyển con trỏ 
			SetColor(BRIGHT_WHITE, BLACK);
			PrintLeftCursor(_Y, CENTER_X - 6);
			PrintRightCursor(_Y, CENTER_X + 32);
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
	}
}
void ShowAsk(WORD wVirtualKeyCode) {
	NEW_GAME = 0;
	//V? giao di?n trang ShowAsk...
	//V? khung r?i cout h?i thoát tr?n ho?c nh?p tên file luu
	DrawPopUp(wVirtualKeyCode);
	switch (wVirtualKeyCode) {
	case 0x4C:
		SaveGame();
		break;
	case VK_ESCAPE:
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'Y') {
			ExitGame();
		}
		else if (_COMMAND == 'N')
			ShowGame();
	}
}
void ShowHelp() {
	system("cls");
	SetColor(BRIGHT_WHITE, BLUE);
	//Vẽ chữ Help
	int logo_x = CENTER_X - 11, logo_y = 3;

	//Phím di chuy?n
	SetColor(BRIGHT_WHITE, GREEN);
	int move_x = 12, move_y = logo_y + 8;
	GotoXY(move_x, move_y);
	cout << "     ---    ";
	GotoXY(move_x, move_y + 1);
	cout << "    | W |   ";
	GotoXY(move_x, move_y + 2);
	cout << " --- --- ---      Use W, A, S, D to move";
	GotoXY(move_x, move_y + 3);
	cout << "| A | S | D |";
	GotoXY(move_x, move_y + 4);
	cout << " --- --- --- ";
	//Phím Enter
	GotoXY(move_x, move_y + 8);
	cout << " ";
	for (int i = 0; i < move_x; i++)
		cout << char(95);
	GotoXY(move_x, move_y + 8 + 1);
	cout << "|          " << char(191) << " |     Press Enter to";
	GotoXY(move_x, move_y + 8 + 2);
	cout << "| ENTER <" << char(196) << char(196) << char(217) << " |     place your mark";
	GotoXY(move_x, move_y + 8 + 3);
	cout << " ------------ ";
	//Lu?t
	SetColor(BRIGHT_WHITE, GREEN);
	int rules_x = CENTER_X + 12, rules_y = logo_y + 8;
	GotoXY(rules_x, rules_y);
	cout << "X starts first.";
	GotoXY(rules_x, rules_y + 2);
	cout << "Players take turns placing their Mark,";
	GotoXY(rules_x, rules_y + 4);
	cout << "X or O, on an open square in the grid.";
	GotoXY(rules_x, rules_y + 6);
	cout << "The first player to make 5 of their ";
	GotoXY(rules_x, rules_y + 8);
	cout << "own mark in a row vertically, horizontally,";
	GotoXY(rules_x, rules_y + 10);
	cout << "or diagonally wins the game. If all the squares";
	GotoXY(rules_x, rules_y + 12);
	cout << "are filled and neither player has 5 in a row,";
	GotoXY(rules_x, rules_y + 14);
	cout << "the game is considered a Tie.";
	//Ðu?ng chia dôi
	SetColor(BRIGHT_WHITE, BLUE);
	for (int i = 0; i < 17; i++) {
		GotoXY(CENTER_X + 5, logo_y + 7 + i);
		cout << "|";
	}
	//Con chim
	SetColor(BRIGHT_WHITE, YELLOW);
	int bird_x = 9, bird_y = move_y + 8 + 5;
	GotoXY(bird_x, bird_y);
	cout << "        " << char(92) << char(92);
	GotoXY(bird_x, bird_y + 1);
	cout << " " << char(92) << char(92) << "      (o>";
	GotoXY(bird_x, bird_y + 2);
	cout << " (o>     //" << char(92);
	GotoXY(bird_x, bird_y + 3);
	cout << "_(()_____v_/_____";
	GotoXY(bird_x, bird_y + 4);
	cout << " ||      ||";
	GotoXY(bird_x, bird_y + 5);
	cout << "         ||";


	_COMMAND = toupper(_getch());
	while (_COMMAND != 13) { //13 = enter
		//Playsound here?
	}
	system("cls");
}