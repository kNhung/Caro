#include "control.h"
#include "model.h"
#include "view.h"
#include "page.h"

//Di chuyển
void MoveRight() {
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x) {
		_X += 4;
		GotoXY(_X, _Y);
	}
}
void MoveLeft() {
	if (_X > _A[0][0].x) {
		_X -= 4;
		GotoXY(_X, _Y);
	}
}
void MoveDown() {
	if ((MODE == 2 && _Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
		|| (MODE == 1 && _Y < _MENU[MENU_SIZE - 1].y)) {
		_Y += 4;
		GotoXY(_X, _Y);
	}
	if (MODE == 3 && _Y < _MATCH_LIST[MATCH_LIST_SIZE - 1].y) {
		_Y += 4;
		GotoXY(_X, _Y);
	}
}
void MoveUp() {
	if ((MODE == 2 && _Y > _A[0][0].y)
		|| (MODE == 1 && _Y > _MENU[0].y)) {
		_Y -= 4;
		GotoXY(_X, _Y);
	}
	if (MODE == 3 && _Y > _MATCH_LIST[0].y) {
		_Y -= 4;
		GotoXY(_X, _Y);
	}
}
void KeyMove(int* x, int* y, int col, int row, EDGE b, KEY_EVENT_RECORD a) {
//Di chuyển con trỏ chuột về các hướng bằng các phím A,W,S,D và các phím mũi tên
	_PlaySound(0);
	switch (a.wVirtualKeyCode) {
	case VK_UP:case 0x57: {
		*y = *y - row;
		if (*y < b.top)
			*y = b.bottom;
		GotoXY(*x, *y);
		break; }
	case VK_DOWN:case 0x53: {
		*y = *y + row;
		if (*y > b.bottom)
			*y = b.top;
		GotoXY(*x, *y);
		break; }
	case VK_LCONTROL:case 0x41: {
		*x = *x - col;
		if (*x < b.left)
			*x = b.right;
		GotoXY(*x, *y);
		break; }
	case VK_RCONTROL:case 0x44: {
		*x = *x + col;
		if (*x > b.right)
			*x = b.left;
		GotoXY(*x, *y);
		break; }
	}
}
void ReadInputKey(KEY_EVENT_RECORD & a) {

		DWORD lpcNumberOfEvents = 0;// size of read buffer
		DWORD cNumRead = 0;// number of records read
		DWORD fdwMode;
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);// Get the standard input handle.
		fdwMode = ENABLE_WINDOW_INPUT;
		SetConsoleMode(hStdin, fdwMode);

		lpcNumberOfEvents = 0;
		cNumRead = 0;
		int res = 0;
		//Receives the number of unread input records in the console's input buffer.
		GetNumberOfConsoleInputEvents(hStdin, &lpcNumberOfEvents);

		if (lpcNumberOfEvents) {
			INPUT_RECORD* irInBuf = new INPUT_RECORD[lpcNumberOfEvents];//Record event
			ReadConsoleInput(hStdin, irInBuf, lpcNumberOfEvents, &cNumRead);
			// Loop to read and handle input events.
			// Dispatch the events to the appropriate handler.
			for (DWORD i = 0; i < cNumRead; i++)
			{
				if (irInBuf[i].EventType == KEY_EVENT) {// keyboard input
					a = irInBuf[i].Event.KeyEvent;
				}
			}
			delete[] irInBuf;
		}
	}
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Điều chỉnh thuộc tính của màn hình
void SetFontInfo()
{
	HANDLE hdc = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(hdc, FALSE, &info);
	info.dwFontSize.X = 6;
	info.dwFontSize.Y = 12;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hdc, FALSE, &info);
}
void SetAndCenterWindow()
{
	HWND console = GetConsoleWindow();
	RECT rectClient, rectWindow;
	GetClientRect(console, &rectClient), GetWindowRect(console, &rectWindow);
	int width = 1920;
	int height = 1080;
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
	SetAndCenterWindow(); //Đặt màn hình ở giữa
	SetWindowSize(WIDTH, HEIGHT); //Cài đặt kích thước màn hình
	SetScreenBufferSize(WIDTH, HEIGHT);
	DisableSelection();
	DisableMaximize(); //Làm mờ nút phóng to thu nhỏ
	SetConsoleTitle(L"Caro"); 
	HideScrollBars(); //Ẩn thanh cuộn
	ShowCursor(0);
	DisableMouseInput(); //Vô hiệu hóa click chuột
}
void SetColor(int backgoundColor, int textColor) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorCode = backgoundColor * 16 + textColor;
	SetConsoleTextAttribute(hStdout, colorCode);
}