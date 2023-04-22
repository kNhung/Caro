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
	DrawLoadingPage();
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
	MODE = 2; _LOADMARK = false;
	StartGame();
	ShowCursor(0);
	int flag = 0;
	KEY_EVENT_RECORD keyevent;
	EDGE bien = { TOP + 1,TOP + BOARD_SIZE * 2 - 1,LEFT + 2,LEFT + BOARD_SIZE * 4 - 2 };
	bool validEnter = true;
	while (1) {
			ReadInputKey(keyevent);
			if (keyevent.bKeyDown) {
				KeyMove(&_X, &_Y, 4, 2, bien, keyevent);
				switch (keyevent.wVirtualKeyCode) {
				case (VK_ESCAPE): case (0x4C): { //ESC or L
					ShowAsk(keyevent.wVirtualKeyCode);
					break;
				}
				case (0x48): { //H
					_LOADMARK = true;
					ShowHelp();
					break; }
				case (VK_RETURN): { //Enter
					switch (CheckBoard(_X, _Y)) {
					case -1: {
						SetColor(BRIGHT_WHITE, RED);
						cout << "X";
						//Hiệu ứng đổi lượt
						SetColor(BRIGHT_WHITE, GRAY);
						PrintX(TOP + 4, LEFT + BOARD_SIZE * 4 + 12, 2);
						SetColor(BRIGHT_WHITE, GOAL);
						PrintO(TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 4, LEFT + BOARD_SIZE * 4 + 12, 2);
						GotoXY(_LAST_POINT.x, _LAST_POINT.y);
						break;
					}
					case 1: {
						SetColor(BRIGHT_WHITE, GOAL);
						cout << "O";
						//Hiệu ứng đổi lượt
						SetColor(BRIGHT_WHITE, RED);
						PrintX(TOP + 4, LEFT + BOARD_SIZE * 4 + 12, 2);
						SetColor(BRIGHT_WHITE, GRAY);
						PrintO(TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 4, LEFT + BOARD_SIZE * 4 + 12, 2);
						GotoXY(_LAST_POINT.x, _LAST_POINT.y);
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
				case (0x55): { //U - Undo
					if (_LAST_POINT.c != 0) { //Xét trường hợp Undo 2 lần trên 1 ô
						//Hiệu ứng đổi lượt
						if (_TURN == 1) {
							SetColor(BRIGHT_WHITE, GRAY);
							PrintX(TOP + 4, LEFT + BOARD_SIZE * 4 + 12, 2);
							SetColor(BRIGHT_WHITE, GOAL);
							PrintO(TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 4, LEFT + BOARD_SIZE * 4 + 12, 2);
							GotoXY(_LAST_POINT.x, _LAST_POINT.y);
						}
						else if (_TURN == -1) {
							SetColor(BRIGHT_WHITE, RED);
							PrintX(TOP + 4, LEFT + BOARD_SIZE * 4 + 12, 2);
							SetColor(BRIGHT_WHITE, GRAY);
							PrintO(TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 4, LEFT + BOARD_SIZE * 4 + 12, 2);
							GotoXY(_LAST_POINT.x, _LAST_POINT.y);
						}

						_X = _LAST_POINT.x, _Y = _LAST_POINT.y;
						GotoXY(_X, _Y);
						cout << " ";
						for (int i = 0;i < BOARD_SIZE;++i)
							if (_A[i][0].y == _Y) {
								for (int j = 0;j < BOARD_SIZE;++j)
									if (_A[i][j].x == _X) {
										_A[i][j].c = 0;
										_LAST_POINT.c = 0;
										break;
									}
								break;
							}
						GotoXY(_X, _Y);
						_TURN = !_TURN;
						break;
					}
				}
				}
			}
			keyevent.bKeyDown = false;
			validEnter = true;
			if (flag == 2)break;
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
	int backgroundColor = BRIGHT_WHITE, textColor = BLACK;
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
	DrawPopUp(wVirtualKeyCode);
	switch (wVirtualKeyCode) {
	case 0x4C: //L
		SaveGame();
		Sleep(800);
		ShowGame();
		break;
	case VK_ESCAPE: //ESC
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
	DrawHelp();
	while (1) {
		_COMMAND = toupper(_getch()); //_getch() chu khong phai getch()
		if (_COMMAND == 27) {
			NEW_GAME = 0;
			ShowGame();
		}
	}
}