#include "control.h"
#include "model.h"
#include "view.h"
#include "page.h"

void ShowPage(int page) {
	if (_EXIT) return;
	switch (page) {
	case 1: {
		_MODEPLAY = _MENU[0].c; 
		ResetScore();
		InputName(); 
		ShowGame();
		break; }
	case 2: ShowFileGame(); break;
	case 3: {
		_MODEPLAY = _MENU[2].c; 
		ResetScore();
		InputName(); 
		ShowGame(); 
		break; }
	case 4: ShowAbout(); break;
	}
}
void ShowLoadingPage() {
	_PlaySound(4);
	system("cls");
	DrawLoadingPage();
	Sleep(700);
	system("cls");
}
void ShowMenu() {
	if (_EXIT) return;
	_PlaySound(4);
	HANDLE word;
	SOUND = 1;
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
		ShowCursor(false);
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			_PlaySound(3);
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
			_PlaySound(3);
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
			_EXIT = 1;
			_PlaySound(4);
			SetColor(BRIGHT_WHITE, BLACK);
			system("cls");
			GabageCollect();
			return;
		}
		else if (_COMMAND == 13) {
			_PlaySound(3);
			ShowLoadingPage();
			for (int i = 0;i < MENU_SIZE;i++) {
				if (_EXIT) return;
				if (_Y == _MENU[i].y)
					ShowPage(_MENU[i].c);
			}
		}
		else if (_COMMAND == 'M') {
			if (SOUND == 0)
				SOUND = 1;
			else
				SOUND = 0;
		}
	}
}
void InputName(){
	system("cls");
	//Vẽ tiêu đề trang menu
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintPencil(4, 52);
	SetColor(BRIGHT_WHITE, BLACK);
	PrintMenuLogo(CENTER_Y - 20, CENTER_X - 2);
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintX(CENTER_Y, 5, 1);
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintO(CENTER_Y, WIDTH - 52, 1);

	//Vẽ khung trang menu
	SetColor(BRIGHT_WHITE, BLACK);
	PrintRectangle2lines(0, 1, WIDTH - 1, HEIGHT - 1);
	SetColor(BRIGHT_WHITE, PURPLE);
	GotoXY(CENTER_X-3, CENTER_Y + 20); 
	cout << "Press ENTER to start game !!!";

	Animal(CENTER_Y - 6, CENTER_X, 1);
	GotoXY(CENTER_X - 2, CENTER_Y);
	SetColor(BRIGHT_WHITE, RED);
	cout << "(X) PLAYER 1 's name : ";
	getline(cin, PLAYER1);
	Animal(CENTER_Y + 6, CENTER_X, 2);
	GotoXY(CENTER_X - 2, CENTER_Y + 11);
	SetColor(BRIGHT_WHITE, GREEN);
	cout << "(O) PLAYER 2 's name : ";
	if (_MODEPLAY == _MENU[0].c)
		getline(cin, PLAYER2);
	else {
		cout << "BOT CARO !!!";
		PLAYER2 = "BOT CARO";
		cin.get();
	}
	
}
void ShowGame() {
	if (_EXIT) return;
	else {
		_PlaySound(4);
		StartGame();
		int row_console = 0, column_console = 0, row = 0, col = 0, flag = 0, res = 0;
		KEY_EVENT_RECORD keyevent;
		EDGE bien = { TOP + 1,TOP + BOARD_SIZE * 2 - 1,LEFT + 2,LEFT + BOARD_SIZE * 4 - 2 };
		bool validEnter = true;
		while (1) {
			ShowCursor(true);
			ReadInputKey(keyevent);
			if (keyevent.bKeyDown) {
				KeyMove(&_X, &_Y, 4, 2, bien, keyevent);
				switch (keyevent.wVirtualKeyCode) {
				case (VK_ESCAPE): case (0x4C): {
					_PlaySound(3);
					ShowAsk(keyevent.wVirtualKeyCode);
					if (_EXIT) return;
					break;
				}
				case (0x48): { //H: Help
					_PlaySound(4);
					ShowHelp();
					if (_EXIT) return;
					break; }
				case (VK_RETURN): {
					_PlaySound(1);
					switch (CheckBoard(_X, _Y)) {
					case -1: {
						SetColor(BRIGHT_WHITE, RED);
						cout << "X";
						//Hiệu ứng đổi lượt
						SetColor(BRIGHT_WHITE, GRAY);
						PrintX(TOP + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
						SetColor(BRIGHT_WHITE, GREEN);
						PrintO(TOP + ((BOARD_SIZE * 2) / 2) + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
						GotoXY(_LAST_POINT.x, _LAST_POINT.y);
						break;
					}
					case 1: {
						SetColor(BRIGHT_WHITE, GREEN);
						cout << "O";
						//Hiệu ứng đổi lượt
						SetColor(BRIGHT_WHITE, RED);
						PrintX(TOP + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
						SetColor(BRIGHT_WHITE, GRAY);
						PrintO(TOP + ((BOARD_SIZE * 2) / 2) + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
						GotoXY(_LAST_POINT.x, _LAST_POINT.y);
						break;
					}
					case 0: validEnter = false;
					}
					if (validEnter == true) {
						switch (ProcessFinish(TestBoard(keyevent))) {
						case -1:case 1: {
							_PlaySound(4);
							flag = AskContinue();
							if (_EXIT) return;
							break;
						}
						case 0: {
							flag = AskContinue();
							if (_EXIT) return;
							break;
						}
						}
					}
					break;
				}
				case (0x55): {
					if (_MODEPLAY == _MENU[0].c) {
						_PlaySound(4);
						if (_LAST_POINT.c != 0) { //Xét trường hợp Undo 2 lần trên 1 ô
							//Hiệu ứng đổi lượt
							if (_TURN == true) {
								SetColor(BRIGHT_WHITE, GRAY);
								PrintX(TOP + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
								SetColor(BRIGHT_WHITE, GREEN);
								PrintO(TOP + ((BOARD_SIZE * 2) / 2) + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
								GotoXY(_LAST_POINT.x, _LAST_POINT.y);
							}
							else if (_TURN == false) {
								SetColor(BRIGHT_WHITE, RED);
								PrintX(TOP + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
								SetColor(BRIGHT_WHITE, GRAY);
								PrintO(TOP + ((BOARD_SIZE * 2) / 2) + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
								GotoXY(_LAST_POINT.x, _LAST_POINT.y);
							}

							_X = _LAST_POINT.x;
							_Y = _LAST_POINT.y;
							GotoXY(_X, _Y);
							cout << char(32);
							GotoXY(_X, _Y);
							XYinMatrix(_X, _Y, row, col);
							_A[row][col].c = 0;
							_TURN = !_TURN;
							_LAST_POINT.c = 0;
						}
					}
					break;
				}
				case (0x4D): {
					if (SOUND == 0)
						SOUND = 1;
					else
						SOUND = 0;
					break;
				}
				}
			}
			if ((_TURN == true && _MODEPLAY == _MENU[2].c) || _MODEPLAY == _MENU[0].c)
				keyevent.bKeyDown = false;
			validEnter = true;
			if (flag == 2)break;
		}
		ShowLoadingPage();
		ShowMenu();
		if (_EXIT) return;
	}
}
void ShowAbout() {
	if (_EXIT) return;
	_PlaySound(4);
	DrawAbout();
	while (1) {
		_COMMAND = toupper(_getch()); //_getch() chu khong phai getch()
		if (_COMMAND == 27) {
			_PlaySound(4);
			ShowLoadingPage();
			ShowMenu();
			return;
		}
	}
}
void ShowFileGame() {
	if (_EXIT) return;
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
			_PlaySound(3);
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
			_PlaySound(3);
			//Xóa con trỏ ở vị trí cũ 
			SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			PrintLeftCursor(_Y - 5, CENTER_X - 6);
			PrintRightCursor(_Y - 5, CENTER_X + 32);
			//Di chuyển con trỏ 
			SetColor(BRIGHT_WHITE, BLACK);
			PrintLeftCursor(_Y, CENTER_X - 6);
			PrintRightCursor(_Y, CENTER_X + 32);
		}
		else if (_COMMAND == 27) { //ESC
			_PlaySound(4);
			ShowLoadingPage();
			ShowMenu();
			if (_EXIT) return;
			_PlaySound(4);
		}
		else if (_COMMAND == 13) { //Enter
			ShowLoadingPage();
			for (int i = 0;i < MATCH_LIST_SIZE;i++) {
				if (_Y == _MATCH_LIST[i].y) {
					NEW_GAME = 0;
					LoadGame(_MATCH_LIST[i].item);
					ShowGame();
					if (_EXIT) return;
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
	int flag = 0;
	if (_EXIT) return ;
	else {
		NEW_GAME = 0;
		DrawPopUp(wVirtualKeyCode);
		switch (wVirtualKeyCode) {
		case 0x4C: //L
			SaveGame();
			Sleep(800);
			ExitGame();
			break;
		case VK_ESCAPE: //ESC
			_COMMAND = toupper(_getch());
			if (_COMMAND == 'Y') {
				_PlaySound(4);
				ExitGame();
			}
			else if (_COMMAND == 'N')
				_PlaySound(4);
			ShowGame();
			DrawExistedData();
		}
	}
}
void ShowHelp() {
	if (_EXIT) return;
	system("cls");
	DrawHelp();
	while (1) {
		_COMMAND = toupper(_getch()); //_getch() chu khong phai getch()
		if (_COMMAND == 27) {
			NEW_GAME = 0;
			ShowGame();
			if (_EXIT) return;
		}
	}
}