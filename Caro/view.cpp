#include "control.h"
#include "model.h"
#include "view.h"
#include "page.h"

//In hình ảnh, icon
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
void PrintRectangle2lines(int top, int left, int width, int height)
{
	GotoXY(left, top);
	for (int i = 1; i <= width; i++) {
		cout << char(205);
	}
	GotoXY(left, top);
	cout << char(201);
	for (int i = 1; i <= height; i++) {
		GotoXY(left, top + i);
		cout << char(186) << endl;
	}
	GotoXY(left, top + height);
	for (int i = 1; i <= width; i++) {
		cout << char(205);
	}
	GotoXY(left, top + height);
	cout << char(200);
	GotoXY(left + width, top);
	cout << char(187);
	for (int i = 1; i < height; i++) {
		GotoXY(left + width, top + i);
		cout << char(186) << endl;
	}
	GotoXY(left + width, top + height);
	cout << char(188);
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
	unsigned char cloud_left[] = { 219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,32 ,32 ,32 ,32 ,32 , 32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,32,32,32,32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,32,32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,219,219,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,219,219,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,32,32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,219,219,219,219,219,32,32,
									219, 219, 219, 219, 219 ,219 ,219 ,219 ,219 ,219 ,219 ,32,32,32,32,32,32,32
	};
	unsigned char cloud_right[] = { 32,32,32,32,32,32,32,32,219,219,219,219,219,219,219,219,219,
								32,32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,
								32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
								32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,219 };
	unsigned char cloud_full[] = { 32,32,32,32,32,32,32,32,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,32,32,32,32,
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
void PrintLine(int top, int left, int length)
{
	GotoXY(left, top);
	cout << char(195);
	for (int i = 0; i < length - 1; i++) {
		cout << char(196);
	}
	cout << char(180);
}
void Button(int top, int left, int width, int height, string label) {
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintRectangle(top, left, width, height);
	SetColor(BRIGHT_WHITE, BLACK);
	int n = ceil((width - label.size() - 2) / 2 + 0.5);
	GotoXY(left + n + 1, top + (height / 2));
	cout << label;
}

//In tiêu đề các lựa chọn ở trang Menu
void PrintNEW() 
{
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring NEW[3] = {  L"                 ████  ██  ██▀▀  ██     ██                ",
						L"                 ██ ██ ██  ████  ██ ███ ██                ",
						L"                 ██  ████  ██▄▄   ███ ███                 " };
	for (int i = 0; i < 3; i++) {
		GotoXY(CENTER_X - 14, CENTER_Y - 2 + i);
		wcout << NEW[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);

}
void PrintCONTINUE()
{
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring NEW[3] = {  L"  ▄█▀██  ████   ██▄  ██  ██████  ██  ██▄  ██  ██  ██  ██▀▀",
						L"  ██    ██  ██  ██▀█▄██    ██    ██  ██▀█▄██  ██  ██  ████",
						L"  ▀█▄██  ████   ██  ▀██    ██    ██  ██  ▀██  ▀████▀  ██▄▄" };
	for (int i = 0; i < 3; i++) {
		GotoXY(CENTER_X - 14, CENTER_Y + 2 + i);
		wcout << NEW[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);

}
void PrintABOUT()
{
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring NEW[3] = {  L"             ▄███▄  ██▀█▄  ████   ██  ██  ██████          ",
						L"             ██▄██  █████ ██  ██  ██  ██    ██            ",
						L"             ██ ██  ██▄█▀  ████   ▀████▀    ██            " };
	for (int i = 0; i < 3; i++) {
		GotoXY(CENTER_X - 14, CENTER_Y + 10 + i);
		wcout << NEW[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);

}
void PrintEXIT()
{
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring NEW[3] = {   L"                   ██▀▀  ██ ██  ██  ██████               ",
						 L"                   ████   ███   ██    ██                 ",
						 L"                   ██▄▄  ██ ██  ██    ██                 " };
	for (int i = 0; i < 3; i++) {
		GotoXY(CENTER_X - 14, CENTER_Y + 14 + i);
		wcout << NEW[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);

}
void PrintPVC()
{
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring NEW[3] = {   L"                    ██▀▀█▌ ██   ██ ▄█▀██                 ",
						 L"                    ██▄▄█▌  ██ ██  ██                    ",
						 L"                    ██       ███   ▀█▄██                 " };
	for (int i = 0; i < 3; i++) {
		GotoXY(CENTER_X - 14, CENTER_Y + 6 + i);
		wcout << NEW[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);

}

//In tiêu đề trang
void PrintPencil() {
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring NEW[3] = {   L"                   ██▀▀  ██ ██  ██  ██████               ",
						 L"                   ████   ███   ██    ██                 ",
						 L"                   ██▄▄  ██ ██  ██    ██                 " };
	for (int i = 0; i < 3; i++) {
		GotoXY(CENTER_X - 14, CENTER_Y + 14 + i);
		wcout << NEW[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);
}
void PrintContinueLogo(int top, int left) {
	SetColor(BRIGHT_WHITE, BLACK);
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring loadgame[6] = {
		L"██╗      █████╗  █████╗ ██████╗    ██████╗  █████╗ ███╗   ███╗███████╗",
		L"██║     ██╔══██╗██╔══██╗██╔══██╗  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
		L"██║     ██║  ██║███████║██║  ██║  ██║  ██╗ ███████║██╔████╔██║█████╗  ",
		L"██║     ██║  ██║██╔══██║██║  ██║  ██║  ╚██╗██╔══██║██║╚██╔╝██║██╔══╝  ",
		L"███████╗╚█████╔╝██║  ██║██████╔╝  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
		L"╚══════╝ ╚════╝ ╚═╝  ╚═╝╚═════╝    ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝" };
	for (int i = 0; i < 6; i++) {
		GotoXY(left, top + i);
		wcout << loadgame[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);
}
void PrintInMatch(int top, int left) {
	int old_mode = _setmode(_fileno(stdout), _O_WTEXT);
	wstring logo[6] = {
		L" █████╗ ███╗  ██╗  ███╗   ███╗ █████╗ ██████╗  █████╗ ██╗  ██╗",
		L"██╔══██╗████╗ ██║  ████╗ ████║██╔══██╗██╔══██╗██╔══██╗██║  ██║",
		L"██║  ██║██╔██╗██║  ██╔████╔██║███████║██████╔╝██║  ╚═╝███████║",
		L"██║  ██║██║╚████║  ██║╚██╔╝██║██╔══██║██╔══██╗██║  ██╗██╔══██║",
		L"╚█████╔╝██║ ╚███║  ██║ ╚═╝ ██║██║  ██║██║  ██║╚█████╔╝██║  ██║",
		L" ╚════╝ ╚═╝  ╚══╝  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚════╝ ╚═╝  ╚═╝" };
	for (int i = 0; i < 6; i++) {
		GotoXY(left, top + i);
		wcout << logo[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);
}
void PrintAboutLogo(int top, int left) {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	wstring logo[6] = {
		L" █████╗ ██████╗  █████╗ ██╗   ██╗████████╗",
		L"██╔══██╗██╔══██╗██╔══██╗██║   ██║╚══██╔══╝",
		L"███████║██████╦╝██║  ██║██║   ██║   ██║   ",
		L"██╔══██║██╔══██╗██║  ██║██║   ██║   ██║   ",
		L"██║  ██║██████╦╝╚█████╔╝╚██████╔╝   ██║   ",
		L"╚═╝  ╚═╝╚═════╝  ╚════╝  ╚═════╝    ╚═╝   " };
	for (int i = 0; i < 6; i++) {
		GotoXY(left, i + top);
		wcout << logo[i];
	}
	int currentMode = _setmode(_fileno(stdout), OldMode);
}
void PrintMenuLogo(int top, int left) {
	unsigned char logo[] = {
		32,219,219,219,219,219,219,187,  32,219,219,219,219,219,187,32,   219,219,219,219,219,219,187,32,  32,219,219,219,219,219,219,187,32,
		219,219,201,205,205,205,205,188, 219,219,201,205,205,219,219,187, 219,219,201,205,205,219,219,187, 219,219,201,205,205,205,219,219,187,
		219,219,186,32,32,32,32,32,      219,219,219,219,219,219,219,186, 219,219,219,219,219,219,201,188, 219,219,186,32,32,32,219,219,186,
		219,219,186,32,32,32,32,32,      219,219,201,205,205,219,219,186, 219,219,201,205,205,219,219,187, 219,219,186,32,32,32,219,219,186,
		200,219,219,219,219,219,219,187, 219,219,186,32,32,219,219,186,   219,219,186,32,32,219,219,186,   200,219,219,219,219,219,219,201,188,
		32,200,205,205,205,205,205,188,  200,205,188,32,32,200,205,188,   200,205,188,32,32,200,205,188,   32,200,205,205,205,205,205,188,32
	};
	int num_lines = 6, num_chars = 8 * 3 + 9;
	for (int i = 0; i < num_lines; i++)
	{
		GotoXY(left, i + top);
		for (int j = 0; j < num_chars; j++)
			putchar(logo[i * num_chars + j]);
	}

}

//Hiệu ứng
void ClearPreviousHightlight(int& a) {
	if (a < 0) a = 0;
	if (a > 4) a = 4;
	switch (a) {
	case 0: {
		SetColor(BRIGHT_WHITE, LIGHT_AQUA);
		PrintNEW();
		break;
	}
	case 1: {
		SetColor(BRIGHT_WHITE, LIGHT_AQUA);
		PrintCONTINUE();
		break;
	}
	case 2: {
		SetColor(BRIGHT_WHITE, LIGHT_AQUA);
		PrintPVC();
		break;
	}
	case 3: {
		SetColor(BRIGHT_WHITE, LIGHT_AQUA);
		PrintABOUT();
		break;
	}
	case 4: {
		SetColor(BRIGHT_WHITE, LIGHT_AQUA);
		PrintEXIT();
		break;
	}
	}
}
void PrintCurrentHighlight(int& a) {
	if (a < 0) a = 0;
	if (a > 4) a = 4;
	switch (a) {
	case 0: {
		SetColor(LIGHT_AQUA, BLACK);
		PrintNEW();
		break;
	}
	case 1: {
		SetColor(LIGHT_AQUA, BLACK);
		PrintCONTINUE();
		break;
	}
	case 2: {
		SetColor(LIGHT_AQUA, BLACK);
		PrintPVC();
		break;
	}
	case 3: {
		SetColor(LIGHT_AQUA, BLACK);
		PrintABOUT();
		break;
	}
	case 4: {
		SetColor(LIGHT_AQUA, BLACK);
		PrintEXIT();
		break;
	}
	}
}
void PrintLeftCursor(int top, int left)
{
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring cursor[5] = { L"█▄   ",
							  L"███▄ ",
							  L"█████",
							  L"███▀ ",
							  L"█▀   " };
	for (int i = 0; i < 5; i++) {
		GotoXY(left, top + i);
		wcout << cursor[i] << endl;
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);
}
void PrintRightCursor(int top, int left) {
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring cursor[5] = { L"   ▄█",
							L" ▄███",
							L"█████",
							L" ▀███",
							L"   ▀█" };
	for (int i = 0; i < 5; i++) {
		GotoXY(left, top + i);
		wcout << cursor[i] << endl;
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);
}

//Vẽ giao diện các trang
void DrawMenu() {
	system("color F1");
	ShowCursor(0);

	//Vẽ tiêu đề trang menu
	SetColor(BRIGHT_WHITE, BLACK);
	PrintMenuLogo(CENTER_Y - 20, CENTER_X - 2);
	//PrintHeart(CENTER_Y - 20, CENTER_X - 28);
	//PrintHeart(CENTER_Y - 20, CENTER_X + 24);


	//Vẽ khung trang menu
	SetColor(BRIGHT_WHITE, BLACK);
	PrintRectangle2lines(0, 1, WIDTH - 1, HEIGHT - 1);
	//Vẽ khung bự in option
	SetColor(BRIGHT_WHITE, BLACK);
	PrintRectangle2lines(CENTER_Y - 5, CENTER_X - 25, 80, 25);

	//Vẽ khung nhỏ in option
	PrintRectangle(CENTER_Y - 3, CENTER_X - 15, 60, 20);
	PrintLine(CENTER_Y + 1, CENTER_X - 15, 60);
	PrintLine(CENTER_Y + 5, CENTER_X - 15, 60);
	PrintLine(CENTER_Y + 9, CENTER_X - 15, 60);
	PrintLine(CENTER_Y + 13, CENTER_X - 15, 60);

	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	//Vẽ các lựa chọn
	//Chữ New 
	SetColor(LIGHT_AQUA, BLACK );
	PrintNEW();
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	//Chữ Continue
	PrintCONTINUE();
	//Chữ PVC
	PrintPVC();
	//Chữ About
	PrintABOUT();
	//Chữ Exit
	PrintEXIT();
}
void DrawBoard() {
	system("color F1");
	//In logo
	SetColor(BRIGHT_WHITE, BLACK);
	PrintInMatch(1, 45);
	//SetColor(BRIGHT_WHITE, BLUE);
	//V? khung ngoài
	//V? du?ng vi?n trên du?i
	//Sleep(500);
	GotoXY(LEFT, TOP); cout << char(201);
	GotoXY(LEFT, TOP + BOARD_SIZE * 2); cout << char(200);
	for (int j = 1; j < BOARD_SIZE * 4 + 30; j++) {
		//Sleep(20);
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
	//Sleep(10);
	for (int i = 1; i < BOARD_SIZE; i++)
		for (int j = 1; j < BOARD_SIZE * 4; j++) {
			GotoXY(LEFT + j, 2 * i + TOP);
			if (j % 4 == 0)cout << char(197);
		}
	GotoXY(LEFT + BOARD_SIZE * 4 + 11, TOP + 2); SetColor(LIGHT_AQUA, BLACK); cout << "  PLAYER X  "; SetColor(BRIGHT_WHITE, BLACK);
	GotoXY(LEFT + BOARD_SIZE * 4 + 2, TOP + 4); cout << "WINNING SCORE : ";
	GotoXY(LEFT + BOARD_SIZE * 4 + 2, TOP + 6); cout << "MOVES : ";
	GotoXY(LEFT + BOARD_SIZE * 4 + 11, TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 2); SetColor(LIGHT_AQUA, BLACK); cout << "  PLAYER O  "; SetColor(BRIGHT_WHITE, BLACK);
	GotoXY(LEFT + BOARD_SIZE * 4 + 2, TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 4); cout << "WINNING SCORE : ";
	GotoXY(LEFT + BOARD_SIZE * 4 + 2, TOP + ((BOARD_SIZE * 2 - (4 * 2)) / 2) + 4 * 2 + 6); cout << "MOVES : ";
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT, 15, 2, "U:Undo");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 + 2, 15, 2, "H:Help");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 2 + 4, 15, 2, "F:Flip");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 2 + 32, 15, 2, "L:Save");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 3 + 32 + 2, 15, 2, "ESC:Exit");
	if (_LOADMARK)
	{
		DrawExistedData();
		_LOADMARK = 0;
	}
}
void DrawExistedData() {
	for (int i = 0;i < BOARD_SIZE;i++)
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
void DrawMatchList() {
	FixConsoleWindows();
	system("color F1");
	//Vẽ nút Tr? v?
	GotoXY(CENTER_X + 3, CENTER_Y + 20);
	cout << "Press ESC to back to menu";

	//Vẽ chữ LOAD GAME
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

	//Vẽ các phần tử của danh sách
	for (int i = 0; i < MATCH_LIST_SIZE; i++) {
		PrintRectangle(CENTER_Y - 1 + i * 4, CENTER_X, 30, 4 );
		GotoXY(CENTER_X + 10, CENTER_Y - 1 + i * 4 + 2);
		SetColor(BRIGHT_WHITE, BLACK);
		cout << _MATCH_LIST[i].item; 
		SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	}

	//Vẽ mây
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintCloud(40, 4, 3); //ở bên trên chữ caro tí
	PrintCloud(150, 12, 3); //ở ngay dưới chữ "O"
	PrintCloud(WIDTH - 17, HEIGHT-7, 2); // Góc phải
	PrintCloud(2, HEIGHT - 17, 1); // bên trái
	GotoXY(CENTER_X, CENTER_Y);
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
void DrawAbout()
{
	SetColor(BRIGHT_WHITE, BLACK);
	int width = 40, height = 9, i = 0, n = 0;
	int top = CENTER_Y - 20, left = CENTER_X - 6 ;
	PrintRectangle2lines(0, 1, WIDTH - 1, HEIGHT - 1);
	PrintAboutLogo(top, left);
	string name[4] = { "22120259 - Nguyen Phat Kim Nhung","22120256 - Ma Thanh Nhi","22120252 - Giang Duc Nhat","22120257 - Dinh Le Gia Nhu"};
	string cd[4] = { "Leader - Developer 1","Developer 2","Developer 3","Developer 4" };
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

	 SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	 PrintCloud(WIDTH - 17, HEIGHT - 7, 2); // Góc phải
	 PrintCloud(155, 10, 3); 
	 PrintCloud(2, HEIGHT - 17, 1); // bên trái 
	 SetColor(BRIGHT_WHITE, BLACK);
}
