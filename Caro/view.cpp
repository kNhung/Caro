#include "control.h"
#include "model.h"
#include "view.h"



//Fix the size of the console window

void SetFontInfo()
{
	HANDLE hdc = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(hdc, FALSE, &info);
	info.dwFontSize.X = 10;
	info.dwFontSize.Y = 15;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hdc, FALSE, &info);
}

void SetAndCenterWindow()
{
	HWND console = GetConsoleWindow();
	RECT rectClient, rectWindow;
	GetClientRect(console, &rectClient), GetWindowRect(console, &rectWindow);
	int width = 1216;
	int height = 784;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(console, posX, posY, width, height, TRUE);
}

void SetWindowSize(SHORT width, SHORT height)
{
	HANDLE hdc = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT WindowSize; //SMALL_RECT cấu trúc chỉ định các góc trên bên trái và góc dưới bên phải cho cửa số mới
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;
	SetConsoleWindowInfo(hdc, 1, &WindowSize);// Đặt góc trên bên trái là góc tọa độ, thay đổi góc dưới theo width và height
}

void SetScreenBufferSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD NewSize;
	NewSize.X = width;
	NewSize.Y = height;
	SetConsoleScreenBufferSize(hStdout, NewSize);
}

void DisableSelection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

void DisableMaximize()
{ // Hàm này để tắt cái nút maximize trên cửa sổ console
	HWND console = GetConsoleWindow();
	SetWindowLong(console, GWL_STYLE,
		GetWindowLong(console, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void HideScrollBars()
{ // Ẩn thanh cuộn của console
	HWND console = GetConsoleWindow();
	ShowScrollBar(console, SB_BOTH, 0);
}

void ShowCursor(bool show)
{
	HANDLE hdc = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(hdc, &info);
}

void DisableMouseInput()
{ // Hàm này có công dụng là làm cho chuột hong bấm dô được màn hình
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void FixConsoleWindows() {
	HANDLE hdc = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	SetFontInfo();
	SetAndCenterWindow();
	SetWindowSize(200, 45);
	SetScreenBufferSize(200, 45);
	DisableSelection();
	DisableMaximize();
	SetConsoleTitle(L"Caro");
	HideScrollBars();
	ShowCursor(0);
	DisableMouseInput();
}

void SetColor(int backgoundColor, int textColor) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorCode = backgoundColor * 16 + textColor;
	SetConsoleTextAttribute(hStdout, colorCode);
}

void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void DrawBoard() {
	system("color F1");
	int top = 1, left = 45;
	int old_mode = _setmode(_fileno(stdout), _O_WTEXT);
	wstring logo[6] = {
		L"░█████╗░███╗░░██╗  ███╗░░░███╗░█████╗░██████╗░░█████╗░██╗░░██╗",
		L"██╔══██╗████╗░██║  ████╗░████║██╔══██╗██╔══██╗██╔══██╗██║░░██║",
		L"██║░░██║██╔██╗██║  ██╔████╔██║███████║██████╔╝██║░░╚═╝███████║",
		L"██║░░██║██║╚████║  ██║╚██╔╝██║██╔══██║██╔══██╗██║░░██╗██╔══██║",
		L"╚█████╔╝██║░╚███║  ██║░╚═╝░██║██║░░██║██║░░██║╚█████╔╝██║░░██║",
		L"░╚════╝░╚═╝░░╚══╝  ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝" };
	for (int i = 0; i < 6; i++) {
		GotoXY(left, top + i);
		wcout << logo[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);
	//V? khung ngoài
	//V? du?ng vi?n trên du?i
	Sleep(500);
	GotoXY(LEFT, TOP); cout << char(201);
	GotoXY(LEFT, TOP + BOARD_SIZE * 2); cout << char(200);
	for (int j = 1; j < BOARD_SIZE * 4 + 30; j++) {
		Sleep(20);
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
	//V? du?ng vi?n trái ph?i
	for (int j = 1; j < BOARD_SIZE * 2; j++) {
		//Sleep(20);
		GotoXY(LEFT, j + TOP);
		if (j % 2 == 0)cout << char(199);
		else cout << char(186);
		GotoXY(LEFT + BOARD_SIZE * 4, j + TOP);
		if (j % 2 == 0)cout << char(182);
		else cout << char(186);
		GotoXY(LEFT + BOARD_SIZE * 4 + 30, j + TOP);
		cout << char(186);
	}
	//V? các c?t,dòng
	for (int i = 1; i < BOARD_SIZE; i++)
		for (int j = 1; j < BOARD_SIZE * 4; j++) {
			if (j < BOARD_SIZE * 2 && j % 2 == 1) {
				GotoXY(LEFT + i * 4, j + TOP);
				cout << char(179);
			}
			if (j % 4 != 0) {
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
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 + 2, 15, 2, "H:Help");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 2 + 4, 15, 2, "F:Flip");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 2 + 32, 15, 2, "L:Save");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 3 + 32 + 2, 15, 2, "ESC:Exit");
}

void Highlightwin(_POINT a[], int& n) {
	for (int i = 1; i < 10; i++) {
		int color = i; Sleep(600);
		for (int j = 0; j < n; j++) {
			GotoXY(a[j].x, a[j].y);
			//if (color == 7)color++;
			SetColor(BRIGHT_WHITE, color++);
			if (_TURN == true)cout << "X";
			else cout << "O";
		}
	}
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
				case -1: {
					SetColor(BRIGHT_WHITE, RED);
					cout << "X"; break; }
				case 1: {
					SetColor(BRIGHT_WHITE, GOAL);
					cout << "O"; break; }
				}
			}
		}
	_X = _LAST_POINT.x;_Y = _LAST_POINT.y;
	GotoXY(_X, _Y);
}

void DrawMenu() {
	system("color F1");
	int left = CENTER_X - 3, top = CENTER_Y - 1;

	//V? tiêu d? trang menu
	PrintMenuLogo();
	PrintHeart(CENTER_Y - 10, CENTER_X - 28);
	PrintHeart(CENTER_Y - 10, CENTER_X + 24);


	//In góc trên bên trái thanh menu
	GotoXY(left, top);
	putchar(201);
	//In ra b? r?ng c?a thanh menu
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	//In góc trên bên ph?i thanh menu
	putchar(187);
	//In ra b? dài c?a thanh menu
	for (int i = 1; i < 8; i++) // S? 4 ? dây là s? option hi?n trong b?ng menu 
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

		//V? khung trang menu
		PrintRectangle(0, 1, 116, 28);
		
	}
	//V? các l?a ch?n
	GotoXY(CENTER_X, CENTER_Y); cout << "New";
	GotoXY(CENTER_X, CENTER_Y + 2); cout << "Continue";
	GotoXY(CENTER_X, CENTER_Y + 4); cout << "About";
	GotoXY(CENTER_X, CENTER_Y + 6); cout << "Exit";
	//In ra góc du?i trái
	GotoXY(left, top + 8);///dn24
	putchar(200);
	//In ra b? r?ng ? phía du?i c?a b?ng menu
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
}

void DrawMatchList() {
	system("color F1");
	//V? nút Tr? v?
	GotoXY(90, 25);
	cout << "Press ESC to back to menu";

	//V? ch? LOAD GAME
	int logo_x = 22, logo_y = 1;
	int old_mode= _setmode(_fileno(stdout), _O_WTEXT);
	wstring loadgame[6] = {
		L"██╗░░░░░░█████╗░░█████╗░██████╗░  ░██████╗░░█████╗░███╗░░░███╗███████╗",
		L"██║░░░░░██╔══██╗██╔══██╗██╔══██╗  ██╔════╝░██╔══██╗████╗░████║██╔════╝",
		L"██║░░░░░██║░░██║███████║██║░░██║  ██║░░██╗░███████║██╔████╔██║█████╗░░",
		L"██║░░░░░██║░░██║██╔══██║██║░░██║  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░",
		L"███████╗╚█████╔╝██║░░██║██████╔╝  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗",
		L"╚══════╝░╚════╝░╚═╝░░╚═╝╚═════╝░  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝" };
	for (int i = 0; i < 6; i++) {
		GotoXY(logo_x, logo_y + i);
		wcout << loadgame[i];
	}
	int current_mode= _setmode(_fileno(stdout), old_mode);
	//V? các ph?n t? c?a danh sách
	//Vẽ chữ LOAD GAME
	logo_x = 22; logo_y = 3;
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
			cout << char(2500); //Ðu?ng ngang trên

		GotoXY(CENTER_X + 13, CENTER_Y + i * 3 - 1);
		cout << char(191); //Góc trên ph?i

		GotoXY(CENTER_X - 3, CENTER_Y + i * 3);
		cout << char(179); //Ðu?ng th?ng trái

		GotoXY(CENTER_X, CENTER_Y + i * 3);
		cout << _MATCH_LIST[i].item; 

		GotoXY(CENTER_X + 13, CENTER_Y + i * 3);
		cout << char(179); //Ðu?ng th?ng ph?i

		GotoXY(CENTER_X - 3, CENTER_Y + i * 3 + 1);
		cout << char(192); //Góc du?i trái

		GotoXY(CENTER_X - 2, CENTER_Y + i * 3 + 1);
		for (int i = 0;i < 15;i++)
			cout << char(2500); //Ðu?ng ngang du?i

		GotoXY(CENTER_X + 13, CENTER_Y + i * 3 + 1);
		cout << char(217); //Góc du?i ph?i
	}

	//V? mây
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintCloud(0, 20, 3);
	PrintCloud(103, 10, 2);
	GotoXY(CENTER_X, CENTER_Y);
}

void DrawLetter(unsigned char letter[], int X, int Y){
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

void DrawPopUp(WORD wVirtualKeyCode) {
	//V? khung
	system("cls");
	system("color F1");
	PrintRectangle(CENTER_Y + 3, CENTER_X + 8, 30, 3);
	GotoXY(CENTER_X + 11, CENTER_Y + 4);
	switch (wVirtualKeyCode) {
	case 0x4C:
		cout << " Enter match name";
		GotoXY(CENTER_X, CENTER_Y - 1);
		SaveGame();
		ShowLoadingPage();
		ShowMenu();
		break;
	case VK_ESCAPE:
		cout << "Are you sure to quit?";
		GotoXY(CENTER_X + 13, CENTER_Y + 5);
		cout << "  Yes(Y)   No(N)";
	}
}


void PrintMenuLogo() {
	unsigned char logo[] = { 
		32,219,219,219,219,219,219,187,  32,219,219,219,219,219,187,32,   219,219,219,219,219,219,187,32,  32,219,219,219,219,219,219,187,32,
		219,219,201,205,205,205,205,188, 219,219,201,205,205,219,219,187, 219,219,201,205,205,219,219,187, 219,219,201,205,205,205,219,219,187,
		219,219,186,32,32,32,32,32,      219,219,219,219,219,219,219,186, 219,219,219,219,219,219,201,188, 219,219,186,32,32,32,219,219,186,
		219,219,186,32,32,32,32,32,      219,219,201,205,205,219,219,186, 219,219,201,205,205,219,219,187, 219,219,186,32,32,32,219,219,186,
		200,219,219,219,219,219,219,187, 219,219,186,32,32,219,219,186,   219,219,186,32,32,219,219,186,   200,219,219,219,219,219,219,201,188,
		32,200,205,205,205,205,205,188,  200,205,188,32,32,200,205,188,   200,205,188,32,32,200,205,188,   32,200,205,205,205,205,205,188,32
		};
	int top = CENTER_Y - 10, left = CENTER_X - 12;
	int num_lines = 6, num_chars = 8*3 + 9;
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
	//Type 1: n?a trái ; 2: n?a ph?i ; 3: nguyên dám
	int m = 0;
	unsigned char cloud_left[] = {	219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,32 ,32 ,32 ,32 ,32 , 32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,32,32,32,32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,32,32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,219,219,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,219,219,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,32,32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,32,32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,32,32,32,32,32,32,32
	};
	unsigned char cloud_right[]={32,32,32,32,32,32,32,32,219,219,219,219,219,219,219,219,219,
								32,32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,
								32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,219 };
	unsigned char cloud_full[]= { 32,32,32,32,32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,32,32,32,32,
								32,32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,32,32,
								32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,32,
								32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,32,32,32 };
	switch (type) {
	case 1:
		for (int i = 0;i < 8;i++) {
			GotoXY(left, top + i);
			for (int j = 0;j < 18;j++) {
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
			for (int j = 0;j < 27;j++) {
				cout << cloud_full[m];
				++m;
			}
		}
		break;
	}
}


int ProcessFinish(int pWhoWin) {
	int top = 15, left = 43;
	int bg_color = BRIGHT_WHITE, text_color = BLUE;
	switch (pWhoWin) {
	case -1: {
		system("cls");
		int old_mode = _setmode(_fileno(stdout), _O_WTEXT);
		SetColor(bg_color, text_color);
		wstring logo[6] = {
		     L" ██████╗░██╗░░░░░░█████╗░██╗░░░██╗███████╗██████╗░  ██╗░░██╗  ░██╗░░░░░░░██╗██╗███╗░░██╗	",
			 L" ██╔══██╗██║░░░░░██╔══██╗╚██╗░██╔╝██╔════╝██╔══██╗  ╚██╗██╔╝  ░██║░░██╗░░██║██║████╗░██║	",
			 L" ██████╔╝██║░░░░░███████║░╚████╔╝░█████╗░░██████╔╝  ░╚███╔╝░  ░╚██╗████╗██╔╝██║██╔██╗██║	",
			 L" ██╔═══╝░██║░░░░░██╔══██║░░╚██╔╝░░██╔══╝░░██╔══██╗  ░██╔██╗░  ░░████╔═████║░██║██║╚████║	",
			 L" ██║░░░░░███████╗██║░░██║░░░██║░░░███████╗██║░░██║  ██╔╝╚██╗  ░░╚██╔╝░╚██╔╝░██║██║░╚███║	",
			 L" ╚═╝░░░░░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝  ╚═╝░░╚═╝  ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝	" };

		for (int i = 0; i < 6; i++){
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		int current_mode = _setmode(_fileno(stdout), old_mode);
		break; 
	}
	case 1: {
		system("cls");
		int old_mode = _setmode(_fileno(stdout), _O_WTEXT);
		SetColor(bg_color, text_color);
		wstring logo[6] = {
			L"██████╗░██╗░░░░░░█████╗░██╗░░░██╗███████╗██████╗░  ░█████╗░  ░██╗░░░░░░░██╗██╗███╗░░██╗",
			L"██╔══██╗██║░░░░░██╔══██╗╚██╗░██╔╝██╔════╝██╔══██╗  ██╔══██╗  ░██║░░██╗░░██║██║████╗░██║",
			L"██████╔╝██║░░░░░███████║░╚████╔╝░█████╗░░██████╔╝  ██║░░██║  ░╚██╗████╗██╔╝██║██╔██╗██║",
			L"██╔═══╝░██║░░░░░██╔══██║░░╚██╔╝░░██╔══╝░░██╔══██╗  ██║░░██║  ░░████╔═████║░██║██║╚████║",
			L"██║░░░░░███████╗██║░░██║░░░██║░░░███████╗██║░░██║  ╚█████╔╝  ░░╚██╔╝░╚██╔╝░██║██║░╚███║",
			L"╚═╝░░░░░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝  ░╚════╝░  ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝" };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		int current_mode = _setmode(_fileno(stdout), old_mode);
		break;
	}
	case 0:{
		system("cls");
		int old_mode = _setmode(_fileno(stdout), _O_WTEXT);
		SetColor(bg_color, text_color);
		wstring logo[13] = {
			L"               ██╗░░██╗░█████╗░  			 ",
			L"               ╚██╗██╔╝██╔══██╗  			 ",
			L"               ░╚███╔╝░██║░░██║  			 ",
			L"               ░██╔██╗░██║░░██║  			 ",
			L"               ██╔╝╚██╗╚█████╔╝  			 ",
			L"               ╚═╝░░╚═╝░╚════╝░  		     ",
			L"												 ",
			L"██████╗░░█████╗░██████╗░░██╗░░░░░░░██╗██╗██╗██╗",
			L"██╔══██╗██╔══██╗██╔══██╗░██║░░██╗░░██║██║██║██║",
			L"██║░░██║███████║██████╔╝░╚██╗████╗██╔╝██║██║██║",
			L"██║░░██║██╔══██║██╔══██╗░░████╔═████║░╚═╝╚═╝╚═╝",
			L"██████╔╝██║░░██║██║░░██║░░╚██╔╝░╚██╔╝░██╗██╗██╗",
			L"╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═╝", };
			
		for (int i = 0; i < 13; i++) {
			GotoXY(left+10, i + (top-5));
			wcout << logo[i];
		}
		int current_mode = _setmode(_fileno(stdout), old_mode);
		break; 
		}
	case 2:
		_TURN = !_TURN;
	}
	return pWhoWin;
}

void ExitGame() {
	ShowLoadingPage();
	ShowMenu();
}

void HLChoice(int& x,int& y,int width) {
	GotoXY(x-1, y+1); cout << char(16);
	GotoXY(x + width, y+1); cout << char(17);
}

void Draw_AskContinue() {
	int top = 25, left = 43;
	PrintRectangle(top, left, 90, 6);
	GotoXY(left + 25, top + 1); cout << "Do you want to continue playing or exit ? ";
	int width = 15, height = 2;
	Button(top + 2, left + 10, width, height, "New Game");
	Button(top + 2, left + 50, width, height, "Exit");
	_X = left + 10, _Y = top + 2;
	GotoXY(_X, _Y);
	ShowCursor(0);
}

int AskContinue() {
	int top = 25, left = 43, flag = 0;
	int bg_color = BRIGHT_WHITE, text_color = BLUE;
	KEY_EVENT_RECORD keyevent;
	EDGE bien = { 0,0,left + 10, left + 50 };
	int width = 15, height = 2;
	Draw_AskContinue();
	while (1) {
		ReadInputKey(keyevent);
		if (keyevent.bKeyDown) {
			switch (keyevent.wVirtualKeyCode) {
			case VK_LCONTROL:case 0x41:case VK_RCONTROL:case 0x44: {
				SetColor(bg_color, bg_color);
				HLChoice(_X, _Y, width+1);
				KeyMove(&_X, &_Y, 40, 0, bien, keyevent);
				SetColor(bg_color, text_color);
				HLChoice(_X, _Y, width + 1);
				break;
			}
			case VK_RETURN: {
				switch (_X) {
				case 53: {
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
		//Khi code tran hoàn ch?nh thì thêm cls,GotoXY d? getline
	}
	while (CheckValidName(matchName) == 0) {
		cout <<endl<< "Ten khong hop le";
		cin.ignore();
		getline(cin, matchName);
		//Khi code tran hoàn ch?nh thì thêm cls,GotoXY d? getline

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
	 matchFile << _LAST_POINT.x << endl << _LAST_POINT.y << endl << _LAST_POINT.c;
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


void ShowPage(int page) {
	switch (page) {
	case 1: ShowGame(); break;
	case 2: ShowFileGame(); break;
	case 3: ShowAbout(); break;
	}
}

void ShowLoadingPage() {
	system("cls");
	system("color F1");
	//V? khung
	PrintRectangle(0, 1, 116, 28);
	//V? ch? LOADING
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
	//V? 3 trái tim nh?
	for (int i = 0;i < 3;i++) {
		GotoXY(logo_x + 20 + 12*i, logo_y - 3);
		cout << char(003) << "  ";
	}
	//V? cây
	PrintTree(logo_x+15, logo_y + 10);

	Sleep(500);
	system("cls");
}

void ShowMenu() {
	HANDLE word;
	MODE = 1;
	NEW_GAME = 1;
	_X = CENTER_X;_Y = CENTER_Y;
	int backgroundColor = BRIGHT_WHITE, textColor = BLUE;
	DrawMenu();
	SetColor(backgroundColor, textColor);
	GotoXY(CENTER_X - 5, CENTER_Y);
	cout << ">";
	while (1) {
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'W') {
			MoveUp();
			SetColor(backgroundColor, backgroundColor);
			GotoXY(CENTER_X - 5, _Y + 2); cout << " ";
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
		else if (_COMMAND == 13 && _Y == _MENU[3].y) {
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
	MODE = 2;
	StartGame();
	ShowCursor(1);
	int row_console = 0, column_console = 0, row = 0;
	int flag = 0;
	KEY_EVENT_RECORD keyevent;
	EDGE bien = { TOP + 1,TOP + BOARD_SIZE * 2 - 1,LEFT + 2,LEFT + BOARD_SIZE * 4 - 2 };
	bool validEnter = true;
	while (1) {
		ReadInputKey(keyevent);
		if (keyevent.bKeyDown) {
			KeyMove(&_X, &_Y, 4, 2, bien, keyevent);
			switch (keyevent.wVirtualKeyCode) {
			case (VK_ESCAPE): case (0x4C): {
				ShowAsk(keyevent.wVirtualKeyCode);
				break; 
			} 
			case (0x48): {
				ShowHelp(); break; }
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
					case -1:case 1:case 0:{ 
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
				_POINT p = XYinMatrix(column_console, row_console,row,row);
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
	_X = CENTER_X; _Y = CENTER_Y;
	GetMatchListSize();
	DrawMatchList();
	SetColor(backgroundColor, textColor);
	GotoXY(CENTER_X - 5, CENTER_Y);
	cout << ">";
	while (1) {
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
	//Logo
	int logo_x = CENTER_X - 11, logo_y = 3;
	DrawLetter(H, logo_x, logo_y);
	DrawLetter(E, logo_x + 9, logo_y);
	DrawLetter(L, logo_x + 9 * 2, logo_y);
	DrawLetter(P, logo_x + 9 * 3, logo_y);
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
	if (_COMMAND == 27) {
		ShowLoadingPage();
		ShowMenu();
		return;
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
	int numbers[BOARD_SIZE * BOARD_SIZE + 3];
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
	_LAST_POINT.x = numbers[m];++m;
	_LAST_POINT.y = numbers[m];++m;
	_LAST_POINT.c = numbers[m];
	_TURN = !_LAST_POINT.c; _COMMAND = -1;
}

void DrawAbout()
{
	int top = 3, left = 64;
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	wstring logo[6] = {
		L"░█████╗░██████╗░░█████╗░██╗░░░██╗████████╗",
		L"██╔══██╗██╔══██╗██╔══██╗██║░░░██║╚══██╔══╝",
		L"███████║██████╦╝██║░░██║██║░░░██║░░░██║░░░",
		L"██╔══██║██╔══██╗██║░░██║██║░░░██║░░░██║░░░",
		L"██║░░██║██████╦╝╚█████╔╝╚██████╔╝░░░██║░░░",
		L"╚═╝░░╚═╝╚═════╝░░╚════╝░░╚═════╝░░░░╚═╝░░░" };
	for (int i = 0; i < 6; i++){
		GotoXY(left, i + top);
		wcout << logo[i];
	}
	_setmode(_fileno(stdout), OldMode);

	int width = 40, height = 9, i = 0, n = 0;
	string name[4] = { "22120259 - Nguyen Phat Kim Nhung","22120256 - Ma Thanh Nhi","22120252 - Giang Duc Nhat","22120257 - Dinh Le Gia Nhu"};
	string cd[4] = { "Lead-Developer 1","Developer 2","Developer 3","Developer 4" };
	int top1 = top + 7, left1 = left - 20;
     for(int j=0;j<4;j++){
		PrintRectangle(top1, left1, width, height);
		n = ceil((width - name[i].size() - 2) / 2 + 0.5);
		GotoXY(left1 + n + 1, top1+4);
		cout << name[i];
		n = ceil((width - cd[i].size() - 2) / 2 + 0.5);
		GotoXY(left1 + n + 1, top1 + 5);
		cout << cd[i];
		i++;
		if (j == 1) {
			left1 = left1- width - 5;
			top1 = top1+height + 2; continue;
		}
		if (j == 3)continue;
		left1 = left1+ width + 5;
	}
	 left1 = left1 - width - 5;
	 top1 = top1 + height + 2;
	 PrintRectangle(top1, left1, 85, 5);
	 string teacher = "Advisor - Teacher";
	 n = ceil((85 - teacher.size() - 2) / 2 + 0.5);
	 GotoXY(left1 + n + 1, top1 + 2); cout << teacher;
	 string name1 = "TRUONG TOAN THINH";
	 n = ceil((85 - teacher.size() - 2) / 2 + 0.5);
	 GotoXY(left1 + n + 1, top1 + 3); cout << name1;

	/* PrintCloud(top1, 3, 3);
	 PrintCloud(top + 10, left1 + 5, 3);*/
}


