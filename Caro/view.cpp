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
void SetColor(int backgoundColor, int textColor) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorCode = backgoundColor * 16 + textColor;
	SetConsoleTextAttribute(hStdout, colorCode);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Drawboard_game() {
	system("color F1");
	unsigned char logo[] = { 177,219,223,223,223,219,' ',177,219,220,176,177,219,' ',' ',' ',177,219,223,220,223,219,' '
		,176,219,223,223,219,' ',223,223,219,223,223,' ',177,219,223,223,219,' ',177,219,176,177,219,'\n',177,219,176,176,
	   177,219,' ',177,219,177,219,177,219,' ',' ',' ',177,219,177,219,177,219,' ',177,219,220,220,219,' ',176,177,219,176,176,
	  ' ',177,219,176,176,176,' ',177,219,223,223,219,'\n',177,219,220,220,220,219,' ',177,219,176,176,223,219,' ',' ',' ',177,219,
	   176,176,177,219,' ',177,219,176,177,219,' ',176,177,219,176,176,' ',177,219,220,220,219,' ',177,219,176,177,219 };
	int top = 5;
	int left = 45;
	for (int i = 0, j = left; i < sizeof(logo) / sizeof(logo[0]); i++, j++) {
		GotoXY(j, top);
		cout << logo[i];
		if (logo[i] == '\n') {
			top++;
			j = left - 1;
		}
	}
	//Vẽ khung ngoài
	//Vẽ đường viền trên dưới
	Sleep(500);
	GotoXY(LEFT, TOP); cout << char(201);
	GotoXY(LEFT, TOP + BOARD_SIZE * 2); cout << char(200);
	for (int j = 1; j < BOARD_SIZE * 4 + 30; j++) {
		Sleep(30);
		GotoXY(LEFT + j, TOP);
		if (j % 4 == 0 && j < BOARD_SIZE * 4)cout << char(209);
		else cout << char(205);
		GotoXY(LEFT + j, TOP + BOARD_SIZE * 2);
		if (j % 4 == 0 && j < BOARD_SIZE * 4)cout << char(207);
		else cout << char(205);
		if (j > BOARD_SIZE * 4) {
			GotoXY(LEFT + j, TOP + (BOARD_SIZE * 2 - (4 * 2)) / 2);
			cout << char(205);
			GotoXY(LEFT + j, TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2);
			cout << char(205);
		}
	}
	GotoXY(LEFT + BOARD_SIZE * 4 + 30, TOP); cout << char(187);
	GotoXY(LEFT + BOARD_SIZE * 4 + 30, TOP + BOARD_SIZE * 2); cout << char(188);
	GotoXY(LEFT + BOARD_SIZE * 4, TOP); cout << char(203);
	GotoXY(LEFT + BOARD_SIZE * 4, TOP + BOARD_SIZE * 2); cout << char(202);
	//Vẽ đường viền trái phải
	for (int j = 1; j < BOARD_SIZE * 2; j++) {
		Sleep(30);
		GotoXY(LEFT, j + TOP);
		if (j % 2 == 0)cout << char(199);
		else cout << char(186);
		GotoXY(LEFT + BOARD_SIZE * 4, j + TOP);
		if (j % 2 == 0)cout << char(182);
		else cout << char(186);
		GotoXY(LEFT + BOARD_SIZE * 4 + 30, j + TOP);
		cout << char(186);
	}
	//Vẽ các cột,dòng
	for (int i = 1; i < BOARD_SIZE; i++)
		for (int j = 1; j < BOARD_SIZE * 4; j++) {
			if (j < BOARD_SIZE * 2 && j % 2 == 1) {
				GotoXY(LEFT + i * 4, j + TOP);
				cout << char(179);
			}
			if (j % 4 !=0) {
				GotoXY(LEFT + j, 2 * i + TOP);
				cout << char(196);
			}
		}
	Sleep(10);
	for (int i = 1; i < BOARD_SIZE; i++)
		for (int j = 1; j < BOARD_SIZE * 4; j++) {
			GotoXY(LEFT + j, 2 * i + TOP);
			if (j % 4 == 0)cout << char(197);
		}
	GotoXY(LEFT + BOARD_SIZE * 4 + 11, TOP + 2); SetColor(AQUA, RED); cout << "  PLAYER X  "; SetColor(BRIGHT_WHITE, BLUE);
	GotoXY(LEFT + BOARD_SIZE * 4 + 2, TOP + 4); cout << "WINNING SCORE : ";
	GotoXY(LEFT + BOARD_SIZE * 4 + 2, TOP + 6); cout << "MOVES : ";
	GotoXY(LEFT + BOARD_SIZE * 4 + 11, TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 2); SetColor(AQUA, RED); cout << "  PLAYER O  "; SetColor(BRIGHT_WHITE, BLUE);
	GotoXY(LEFT + BOARD_SIZE * 4 + 2, TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 4); cout << "WINNING SCORE : ";
	GotoXY(LEFT + BOARD_SIZE * 4 + 2, TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 6); cout << "MOVES : ";
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT, 15, 2, "U:Undo");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 + 5, 15, 2, "R:Redo");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 2 + 5 * 2, 15, 2, "H:Help");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 3 + 5 * 3, 15, 2, "L:Save");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 4 + 5 * 4, 15, 2, "esc:Exit");
}

void Highlightwin(const vector <_POINT>& a) {
	int color = 1;
	for (int i = 0; i < a.size(); i++) {
		GotoXY(a[i].x, a[i].y);
		SetColor(7, color++);
		if (_TURN == true)cout << "X";
		else cout << "O";
	}
}
void PrintRectangle(int top, int left, int width, int height) {
	GotoXY(left, top);
	for (int i = 1; i <= width; i++) {
		cout << char(196);
	}
	GotoXY(left, top);
	cout << char(218);
	for (int i = 1; i <= height; i++) {
		GotoXY(left, top + i);
		cout << char(179) << endl;
	}
	GotoXY(left, top + height);
	for (int i = 1; i <= width; i++) {
		cout << char(196);
	}
	GotoXY(left, top + height);
	cout << char(192);
	GotoXY(left + width, top);
	cout << char(191);
	for (int i = 1; i < height; i++) {
		GotoXY(left + width, top + i);
		cout << char(179) << endl;
	}
	GotoXY(left + width, top + height);
	cout << char(217);
}

void Button(int top, int left, int width, int height,string label) {
	PrintRectangle(top, left, width, height);
	int n = ceil((width - label.size() - 2) / 2 + 0.5);
	GotoXY(left + n + 1, top + (height / 2));
	cout << label;
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
	system("color E1");
	int left = CENTER_X - 3, top = CENTER_Y - 1;

	//Vẽ tiêu đề trang menu
	PrintMenuLogo();
	PrintHeart(CENTER_Y - 10, CENTER_X - 43);
	PrintHeart(CENTER_Y - 10, CENTER_X + 39);


	//In góc trên bên trái thanh menu
	GotoXY(left, top);
	putchar(201);
	//In ra bề rộng của thanh menu
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	//In góc trên bên phải thanh menu
	putchar(187);
	//In ra bề dài của thanh menu
	for (int i = 1; i < 8; i++) // Số 4 ở đây là số option hiện trong bảng menu 
	{
		GotoXY(left ,top + i);
		if (i % 2 != 0)
		{
			putchar(186);
			GotoXY(left + 12, top + i);
			putchar(186);
		}
		else
		{
			putchar(199);
			for (int i = 1; i < 12; i++)
			{
				putchar(196);
			}
			putchar(182);
		}

		//Vẽ khung trang menu
		PrintRectangle(0, 1, 116, 28);
		
	}
	//Vẽ các lựa chọn
	GotoXY(CENTER_X, CENTER_Y); cout << "New";
	GotoXY(CENTER_X, CENTER_Y + 2); cout << "Continue";
	GotoXY(CENTER_X, CENTER_Y + 4); cout << "About";
	GotoXY(CENTER_X, CENTER_Y + 6); cout << "Exit";
	//In ra góc dưới trái
	GotoXY(left, top + 8);///dn24
	putchar(200);
	//In ra bề rộng ở phía dưới của bảng menu
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
}

void PrintMenuLogo() {
	unsigned char logo[] = {
		32,219,219,219,219,219,219,187,32,219,219,219,219,219,219,187,32,32,32,32,32,32,32,219,219,219,219,219,219,187,32,219,219,219,219,219,187,32,219,219,219,219,219,219,187,32,32,219,219,219,219,219,219,187,32,
219,219,201,205,205,205,205,188,219,219,201,205,205,205,219,219,187,32,32,32,32,32,219,219,201,205,205,205,205,188,219,219,201,205,205,219,219,187,219,219,201,205,205,219,219,187,219,219,201,205,205,205,219,219,187,
219,219,186,32,32,32,32,32,219,219,186,32,32,32,219,219,186,32,32,32,32,32,219,219,186,32,32,32,32,32,219,219,219,219,219,219,219,186,219,219,219,219,219,219,201,188,219,219,186,32,32,32,219,219,186,
219,219,186,32,32,32,32,32,219,219,186,32,32,32,219,219,186,32,32,32,32,32,219,219,186,32,32,32,32,32,219,219,201,205,205,219,219,186,219,219,201,205,205,219,219,187,219,219,186,32,32,32,219,219,186,
200,219,219,219,219,219,219,187,200,219,219,219,219,219,219,201,188,32,32,32,32,32,200,219,219,219,219,219,219,187,219,219,186,32,32,219,219,186,219,219,186,32,32,219,219,186,200,219,219,219,219,219,219,201,188,
32,200,205,205,205,205,205,188,32,200,205,205,205,205,205,188,32,32,32,32,32,32,32,200,205,205,205,205,205,188,200,205,188,32,32,200,205,188,200,205,188,32,32,200,205,188,32,200,205,205,205,205,205,188,32 };
	int top = CENTER_Y - 10, left = CENTER_X - 23;
	int num_lines = 6, num_chars = 55;
	for (int i = 0; i < num_lines; i++)
	{
		GotoXY(left, i + top);
		for (int j = 0; j < num_chars; j++)
			putchar(logo[i * num_chars + j]);
	}

}

void PrintHeart(int top, int left) {
	unsigned char logo[] = {//32,32,32,219,32,219,32,32,32
		32,32,219,219,219,32,32,32,219,219,219,32,32
		,32,219,219,219,219,219,32,219,219,219,219,219,32
		,219,219,219,219,219,219,219,219,219,219,219,219,219
		,219,219,219,219,219,219,219,219,219,219,219,219,219
		,32,219,219,219,219,219,219,219,219,219,219,219,32
		,32,32,219,219,219,219,219,219,219,219,219,32,32
		,32,32,32,32,219,219,219,219,219,32,32,32,32 };
	int num_lines = 7, num_chars = 13;
	for (int i = 0; i < num_lines; i++)
	{
		GotoXY(left, i + top);
		for (int j = 0; j < num_chars; j++)
			putchar(logo[i * num_chars + j]);
	}

}

void PrintSmallHeart(int x, int y) {
	int m = 0;
	unsigned char heart_s[] = {32,254,32,32,32,254,32,
							   219,254,254,32,254,254,254,
							   32,254,254,254,254,254,32,
							   32,32,254,254,254,32,32,
							   32,32,32,254,32,32,32};
	GotoXY(x, y);
	for (int i = 0;i < 5;i++) {
		for (int i = 0;i < 7;i++) {
			cout << heart_s[m++];
		}
		GotoXY(x, y++);
	}
}


void PrintTree(int x, int y) {
	GotoXY(x, y);cout << "               ,@@@@@@@,";
	GotoXY(x, y + 1);cout << "      ,,,.   ,@@@@@@/@@,  .oo8888o.";
	GotoXY(x, y + 2);cout << "    ,&%%&%&&%,@@@@@/@@@@@@,8888\88/8o";
	GotoXY(x, y + 3);cout << "   ,%&\%&&%&&%,@@@\@@@/@@@88\88888/88'";
	GotoXY(x, y + 4);cout << "   %&&%&%&/%&&%@@\@@/ /@@@88888\88888'";
	GotoXY(x, y + 5);cout << "   %&&%/ %&%%&&@@\ V /@@' `88\8 `/88'";
	GotoXY(x, y + 6);cout << "   `&%\ ` /%&'    |.|        \ '|8'";
	GotoXY(x, y + 7);cout << "       |o|        | |         | |";
	GotoXY(x, y + 8);cout << "       |.|        | |         | |";
	GotoXY(x, y + 9);cout << "/_. \\/ ._\//_/__/  ,\_//__\\/.  \_//__/_";
}

void PrintCloud(int left, int top, int type) {
	//Type 1: nửa trái ; 2: nửa phải ; 3: nguyên đám
	int m = 0;
	unsigned char cloud_left[] = {	   219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,32 ,32 ,32 ,32 ,32 , 32,
									   219 ,219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,32,32,32,32,
									   219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,32,32,
									   219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,219,219,
									   219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,219,219,
									   219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,32,32 };
	unsigned char cloud_right[]={32,32,32,32,32,32,32,32,219,219,219,219,219,219,219,219,219,
								32,32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,
								32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,219 };
	unsigned char cloud_full[]= { 32,32,32,32,32,32,32,32,219,219,219,219,219,219,32,32,32,32,
								32,32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,32,32,
								32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,32,
								32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,32,32,32 };
	switch (type) {
	case 1:
		for (int i = 0;i < 6;i++) {
			GotoXY(left, top + i);
			for (int j = 0;j < 14;j++) {
				cout << cloud_left[m];
				++m;
			}
		}
		break;
	case 2:
		for (int i = 0;i < 6;i++) {
			GotoXY(left, top + i);
			for (int j = 0;j < 17;j++) {
				cout << cloud_right[m];
				++m;
			}
		}
		break;
	case 3:
		for (int i = 0;i < 6;i++) {
			GotoXY(left, top + i);
			for (int j = 0;j < 18;j++) {
				cout << cloud_full[m];
				++m;
			}
		}
		break;
	}
}

void DrawMatchList() {
	system("color E1");
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

	//Vẽ mây
	SetColor(LIGHT_YELLOW, BRIGHT_WHITE);
	PrintCloud(0, 20, 1);
	PrintCloud(103, 10, 2);
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

void DrawPopUp(char quest) {
	//Vẽ khung
	system("cls");
	PrintRectangle(CENTER_Y+3 , CENTER_X +8, 30, 3);
	GotoXY(CENTER_X+11, CENTER_Y +4);
	switch (quest) {
	case 'L':
		cout << " Enter match name";
		GotoXY(CENTER_X, CENTER_Y - 1);
		SaveGame();
		ShowLoadingPage();
		ShowMenu();
		break;
	case 27:
		cout << "Are you sure to quit?";
		GotoXY(CENTER_X +13, CENTER_Y +5);
		cout << "  Yes(Y)   No(N)";
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
	system("cls");
	PrintRectangle(CENTER_Y - 3, CENTER_X - 10, 30, 3);
	GotoXY(CENTER_X - 5, CENTER_Y - 2);
	cout << "Want to save the match?";
	GotoXY(CENTER_X - 5, CENTER_Y - 1);
	cout << "  Yes(Y)    No(N)";
	return toupper(_getch());
}

void SaveGame() {
	string matchName;
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
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


void ShowLoadingPage() {
	system("cls");
	system("color E1");
	//Vẽ khung
	PrintRectangle(0, 1, 116, 28);
	//Vẽ chữ LOADING
	int logo_x = 25, logo_y = 5;
	DrawLetter(L, logo_x, logo_y);
	DrawLetter(O, logo_x + 9, logo_y);
	DrawLetter(A, logo_x + 9 * 2, logo_y);
	DrawLetter(D, logo_x + 9 * 3, logo_y);
	DrawLetter(I, logo_x + 9 * 4, logo_y);
	DrawLetter(N, logo_x + 9 * 5, logo_y);
	DrawLetter(G, logo_x + 9 * 6, logo_y);
	for (int i = 0;i <= 2;i++) {
		GotoXY(logo_x + 9 * 7 + 4 * i, logo_y + 4);
		cout << char(219) << char(219);
	}
	//Vẽ 3 trái tim nhỏ
	for (int i = 0;i < 3;i++) {
		//PrintSmallHeart(logo_x + 5*i, logo_y - 4);
		GotoXY(logo_x + 20 + 12*i, logo_y - 3);
		cout << char(003) << "  ";
	}
	//Vẽ cây
	PrintTree(logo_x+15, logo_y + 10);

	Sleep(500);
	system("cls");
}

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
	int backgroundColor = LIGHT_YELLOW, textColor = BLUE;
	DrawMenu();
	SetColor(backgroundColor, textColor);
	GotoXY(CENTER_X - 5, CENTER_Y);
	cout << ">";
	while (1) {
		word = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(word, textColor * 16 + backgroundColor);
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			MoveUp();
			SetColor(backgroundColor, backgroundColor);
			GotoXY(CENTER_X - 5, _Y + 2); cout << ">";
			SetColor(backgroundColor, textColor);
			GotoXY(CENTER_X - 5, _Y);
			cout << ">";
		}
		else if (_COMMAND == 'S') {
			MoveDown();
			SetColor(backgroundColor, backgroundColor);
			GotoXY(CENTER_X - 5, _Y - 2); cout << ">";
			SetColor(backgroundColor, textColor);
			GotoXY(CENTER_X - 5, _Y);
			cout << ">";
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
	MODE = 2;
	StartGame();
	_X = _A[0][0].x; _Y = _A[0][0].y ;
	GotoXY(_X, _Y);
	bool validEnter = true;
	while (1) {
		_COMMAND = toupper(_getch()); //_getch() chu khong phai getch()
		if (_COMMAND == 27 || _COMMAND == 'L') {
			/*ShowLoadingPage();
			ShowMenu();*/
			ShowAsk(_COMMAND);
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
							DrawPopUp('L');
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
	int backgroundColor = LIGHT_YELLOW, textColor = BLUE;
	MODE = 3;
	_X = CENTER_X; _Y = CENTER_Y;
	GetMatchListSize();
	DrawMatchList();
	SetColor(backgroundColor, textColor);
	GotoXY(CENTER_X - 5, CENTER_Y);
	cout << ">";
	while (1) {
		word = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(word, backgroundColor * 16 + textColor);
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			MoveUp();
			SetColor(backgroundColor, backgroundColor);
			GotoXY(CENTER_X - 5, _Y + 3);cout << ">";
			SetColor(backgroundColor, textColor);
			GotoXY(CENTER_X - 5, _Y);
			cout << ">";
		}
		else if (_COMMAND == 'S') {
			MoveDown();
			SetColor(backgroundColor, backgroundColor);
			GotoXY(CENTER_X - 5, _Y - 3);cout << ">";
			SetColor(backgroundColor, textColor);
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
	}
}

void ShowAsk(char key) {
	NEW_GAME = 0;
	//Vẽ giao diện trang ShowAsk...
	//Vẽ khung rồi cout hỏi thoát trận hoặc nhập tên file lưu
	DrawPopUp(key);
	switch (key) {
	case 'L':
		SaveGame();
		break;
	case 27:
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'Y') {
			ShowLoadingPage();
			ShowMenu();
		}
		else if (_COMMAND == 'N')
			ShowGame();
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
		_Y -= 3*MATCH_LIST_SIZE;
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