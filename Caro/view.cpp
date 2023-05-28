#include "control.h"
#include "model.h"
#include "view.h"
#include "page.h"


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
void PrintPencil(int top, int left) {
	int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wstring NEW[9] = { L"    ██████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████			",
						 L"  ██                                                                                                                          ████			",
						 L" ██                                                                                                                         ██    ████		",
						 L"██                                                                                                                         ██    █    █████   ",
						 L"██                                                                                                                        ██    █          ████   ",
						 L"██                                                                                                                         ██    █    █████   ",
						 L" ██                                                                                                                         ██    ████       ",
						 L"  ██                                                                                                                          ████			",
						 L"    ██████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████			" };
	for (int i = 0; i < 9; i++) {
		GotoXY(left, top + i);
		wcout << NEW[i];
	}
	int current_mode = _setmode(_fileno(stdout), old_mode);
}
void PrintHelicopter(int x, int y) {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	wstring logo1[5] = {
		L"▀▀▀▀█▀▀▀▀",
		L"─▄▀█▀▀█──────▄",
		L"█▄▄█▄▄██████▀",
		L"▀▀█▀▀▀█▀▀",
		L"─▀▀▀▀▀▀▀" };
	for (int i = 0; i < 5; i++) {
		GotoXY(x, i + y);
		wcout << logo1[i];
	}
	int currentMode = _setmode(_fileno(stdout), OldMode);
}
void PrintCastle(int x,int y) {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	wstring logo2[5] = {
		L"─────────█▄██▄█",
		L"█▄█▄█▄█▄█▐█┼██▌█▄█▄█▄█▄█",
		L"███┼█████▐████▌█████┼███",
		L"█████████▐████▌█████████" };
	for (int i = 0; i < 4; i++) {
		GotoXY(x, i + y);
		wcout << logo2[i];
	}
	int currentMode = _setmode(_fileno(stdout), OldMode);
}
void PrintX(int top, int left, int size) {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	if (size == 1) {
		wstring logo[21] = {
			L"████████                              ████████	",
			L"████████                              ████████	",
			L"████████                              ████████	",
			L"     ████████                    ████████			",
			L"     ████████                    ████████			",
			L"     ████████                    ████████			",
			L"          ████████          ████████				",
			L"          ████████          ████████				",
			L"          ████████          ████████				",
			L"               ████████████████					",
			L"               ████████████████					",
			L"               ████████████████					",
			L"          ████████          ████████				",
			L"          ████████          ████████				",
			L"          ████████          ████████				",
			L"     ████████                    ████████			",
			L"     ████████                    ████████			",
			L"     ████████                    ████████			",
			L"████████                              ████████	",
			L"████████                              ████████	",
			L"████████                              ████████	" };
		for (int i = 0; i < 21; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
	}
	else if (size == 2) {
		wstring logo[5] = {
			L"██   ██",
			L" ██ ██",
			L"  ███",
			L" ██ ██",
			L"██   ██" };
		for (int i = 0; i < 5; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
	}
	int currentMode = _setmode(_fileno(stdout), OldMode);
}
void PrintO(int top, int left, int size) {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	if (size == 1) {
		wstring logo[21] = {
			L"    ████████████████████████████████████████		",
			L"    ████████████████████████████████████████		",
			L"    ████████████████████████████████████████		",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"████████                                ████████	",
			L"    ████████████████████████████████████████		",
			L"    ████████████████████████████████████████		",
			L"    ████████████████████████████████████████		" };
		for (int i = 0; i < 21; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		top += 2, left += 7;
		SetColor(BRIGHT_WHITE, BLACK);
		wstring logo1[21] = {
			L"███████████████████████████████████",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███       SOUND ON/OFF: M       ███",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███                             ███",
			L"███████████████████████████████████" };
		for (int i = 0; i < 21; i++) {
			GotoXY(left, i + top);
			wcout << logo1[i];
		}
	}
	else if (size == 2) {
		wstring logo[5] = {
			L" █████",
			L"██   ██",
			L"██   ██",
			L"██   ██",
			L" █████" };
		for (int i = 0; i < 5; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
	}
	int currentMode = _setmode(_fileno(stdout), OldMode);
}
//Vẽ tỉ số thắng thua
void DrawScore(int score,int top, int left) {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	switch (score) {
	case 0: {
		wstring logo[6] = {
			L" █████╗ ",
			L"██╔══██╗",
			L"██║  ██║",
			L"██║  ██║",
			L"╚█████╔╝",
			L" ╚════╝ " };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break;
	}
	case 1: {
		wstring logo[6] = {
			L"  ███╗  ",
			L" ████║  ",
			L"██╔██║  ",
			L"╚═╝██║  ",
			L"███████╗",
			L"╚══════╝" };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break;
	}
	case 2: {
		wstring logo[6] = {
			L"██████╗ ",
			L"╚════██╗",
			L"  ███╔═╝",
			L"██╔══╝  ",
			L"███████╗",
			L"╚══════╝" };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break; 
	}
	case 3: {
		wstring logo[6] = {
			L"██████╗ ",
			L"╚════██╗",
			L" █████╔╝",
			L" ╚═══██╗",
			L"██████╔╝",
			L"╚═════╝ " };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break;
	}
	case 4: {
		wstring logo[6] = {
			L"  ██╗██╗",
			L" ██╔╝██║",
			L"██╔╝ ██║",
			L"███████║",
			L"╚════██║",
			L"     ╚═╝" };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break;
	}
	case 5: {
		wstring logo[6] = {
			L"███████╗",
			L"██╔════╝",
			L"██████╗ ",
			L"╚════██╗",
			L"██████╔╝",
			L"╚═════╝ " };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break;
	}
	case 6: {
		wstring logo[6] = {
			L" █████╗ ",
			L"██╔═══╝ ",
			L"██████╗ ",
			L"██╔══██╗",
			L"╚█████╔╝",
			L" ╚════╝ " };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break;
	}
	case 7: {
		wstring logo[6] = {
			L"███████╗",
			L"╚════██║",
			L"    ██╔╝",
			L"   ██╔╝ ",
			L"  ██╔╝  ",
			L"  ╚═╝   " };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break;
	}
	case 8: {
		wstring logo[6] = {
			L" █████╗ ",
			L"██╔══██╗",
			L"╚█████╔╝",
			L"██╔══██╗",
			L"╚█████╔╝",
			L" ╚════╝ " };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break;
	}
	case 9: {
		wstring logo[6] = {
			L" █████╗ ",
			L"██╔══██╗",
			L"╚██████║",
			L" ╚═══██║",
			L" █████╔╝",
			L" ╚════╝ " };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}
		break;
	}
	}
    int currentMode = _setmode(_fileno(stdout), OldMode);
}
void RemoveScore(int top, int left) {
	string logo[6] = {
			"        ",
			"        ",
			"        ",
			"        ",
			"        ",
			"        " };
	for (int i = 0; i < 6; i++) {
		GotoXY(left, i + top);
		cout << logo[i];
	}
}
void Animal(int top, int left,int animal) {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	switch (animal) {
	case 1: {
		SetColor(BRIGHT_WHITE, AQUA);
		wstring logo[6] = {
			L"       ██         ██		  ",
			L"      █ █         █ █		  ",
			L"      █  █████████  █		  ",
			L"      ███████████████		  ",
			L"      █████ ████ ████		  ",
			L"████  ██████▀  ▀█████  ████ " };
		for (int i = 0; i < 6; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}break;
	}
	case 2: {
		SetColor(BRIGHT_WHITE,AQUA);
		wstring logo[5] = {
			L"      ████       ████		  ",
			L"	    █  █████████  █		  ",
			L"	    ███████████████		  ",
			L"	    █████ ████ ████		  ",
			L"████  ███████  ██████  ████ ", };
		for (int i = 0; i < 5; i++) {
			GotoXY(left, i + top);
			wcout << logo[i];
		}break;
	}
	}
	int currentMode = _setmode(_fileno(stdout), OldMode);
}

void ByeBye() {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	wstring logo[7] = {
L" ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄   ▄    ▄▄   ▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄ ",
L"█       █  █ █  █      █  █  █ █   █ █ █  █  █ █  █       █  █ █  █",
L"█▄     ▄█  █▄█  █  ▄   █   █▄█ █   █▄█ █  █  █▄█  █   ▄   █  █ █  █",
L"  █   █ █       █ █▄█  █       █      ▄█  █       █  █ █  █  █▄█  █",
L"  █   █ █   ▄   █      █  ▄    █     █▄   █▄     ▄█  █▄█  █       █",
L"  █   █ █  █ █  █  ▄   █ █ █   █    ▄  █    █   █ █       █       █",
L"  █▄▄▄█ █▄▄█ █▄▄█▄█ █▄▄█▄█  █▄▄█▄▄▄█ █▄█    █▄▄▄█ █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█", };
	for (int i = 0; i < 7; i++) {
		GotoXY(80,i + 25);
		wcout << logo[i];
	}
	int currentMode = _setmode(_fileno(stdout), OldMode);
	SetColor(BRIGHT_WHITE, AQUA);
	PrintCloud(60, 5, 3);
	PrintCloud(160, 43, 3);
	SetColor(BRIGHT_WHITE, BLACK);
	PrintHelicopter(40, 10);
	PrintHelicopter(190, 40);
	Sleep(2000);
	//Close console
	HWND hmnd = GetConsoleWindow();
	SendMessage(hmnd, WM_CLOSE, 0, 0);
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
		L"██╗███╗  ██╗  ███╗   ███╗ █████╗ ████████╗ █████╗ ██╗  ██╗",
		L"██║████╗ ██║  ████╗ ████║██╔══██╗╚══██╔══╝██╔══██╗██║  ██║",
		L"██║██╔██╗██║  ██╔████╔██║███████║   ██║   ██║  ╚═╝███████║",
		L"██║██║╚████║  ██║╚██╔╝██║██╔══██║   ██║   ██║  ██╗██╔══██║",
		L"██║██║ ╚███║  ██║ ╚═╝ ██║██║  ██║   ██║   ╚█████╔╝██║  ██║",
		L"╚═╝╚═╝  ╚══╝  ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝    ╚════╝ ╚═╝  ╚═╝" };

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

void PrintHelpLogo(int top, int left) {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	wstring logo[6] = {
		L"██╗  ██╗███████╗██╗     ██████╗",
		L"██║  ██║██╔════╝██║     ██╔══██╗",
		L"███████║█████╗  ██║     ██████╔╝",
		L"██╔══██║██╔══╝  ██║     ██╔═══╝",
		L"██║  ██║███████╗███████╗██║",
		L"╚═╝  ╚═╝╚══════╝╚══════╝╚═╝" };
	for (int i = 0; i < 6; i++) {
		GotoXY(left, i + top);
		wcout << logo[i];
	}
	int currentMode = _setmode(_fileno(stdout), OldMode);
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
	wstring cursor[5] = {     L"█▄   ",
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
	wstring cursor[5] = {   L"   ▄█",
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
	//Vẽ tiêu đề trang menu
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintPencil(4, 52);
	SetColor(BRIGHT_WHITE, BLACK);
	PrintMenuLogo(CENTER_Y - 20, CENTER_X - 2);
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintX(CENTER_Y, 5,1);
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintO(CENTER_Y, WIDTH - 52,1);

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

void DesignBoard() {
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
	wstring logo1[2] = {
		L"█▀ █▀▀ █▀█ █▀█ █▀▀",
		L"▄█ █▄▄ █▄█ █▀▄ ██▄" };

	SetColor(BRIGHT_WHITE, BLACK);
	for (int i = 0; i < 2; i++) {
		GotoXY(LEFT + BOARD_SIZE * 4 + 57, i + TOP + 4);
		wcout << logo1[i];
	}
	wstring logo2[4] = {
		L"╭╮",
		L"╰╯",
		L"╭╮",
		L"╰╯" };
	SetColor(BRIGHT_WHITE, BLACK);
	for (int i = 0; i < 4; i++) {
		GotoXY(LEFT + BOARD_SIZE * 4 + 65, i + TOP + 9);
		wcout << logo2[i];
	}
	wstring logo3[2] = {
		L"█▀▀ █▀█ █▀█ █ █ █▀█   ▄█ █▀█",
		L"█▄█ █▀▄ █▄█ █▄█ █▀▀    █ █▄█" };
	for (int i = 0; i < 2; i++) {
		GotoXY(LEFT + BOARD_SIZE * 4 + 52, i + TOP + BOARD_SIZE + 3);
		wcout << logo3[i];
	}
	wstring logo4[7] = {
		L" ▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄  ▄▄▄▄▄▄    ▄▄▄▄▄▄▄      ▄▄    ▄ ",
		L"█       ██       ██       ██   ▄  █  █       █    █  █  █ █",
		L"█▄     ▄██    ▄▄▄██▄     ▄██  █ █ █  █   ▄   █    █   █▄█ █",
		L"  █   █  █   █▄▄▄   █   █  █   █▄▄█▄ █  █▄█  █ ██ █       █",
		L"  █   █  █    ▄▄▄█  █   █  █    ▄▄  ██       █    █  ▄    █",
		L"  █   █  █   █▄▄▄   █   █  █   █  █ ██   ▄   █    █ █ █   █",
		L"  █▄▄▄█  █▄▄▄▄▄▄▄█  █▄▄▄█  █▄▄▄█  █▄██▄▄█ █▄▄█    █▄█  █▄▄█" };
	for (int i = 0; i < 7; i++) {
		GotoXY(LEFT + BOARD_SIZE * 4 + 36, i + TOP + BOARD_SIZE + 7);
		wcout << logo4[i];
	}
	int currentMode = _setmode(_fileno(stdout), OldMode);
}


void DrawBoard() {
	system("color F1");
	//In logo
	SetColor(BRIGHT_WHITE, BLACK);
	PrintInMatch(3, CENTER_X - 20);
	PrintRectangle2lines(0, 1, WIDTH - 1, HEIGHT - 1);
	PrintRectangle2lines(TOP, LEFT + BOARD_SIZE * 4 + 34, 62, BOARD_SIZE - 1);
	PrintRectangle2lines(TOP + BOARD_SIZE + 1, LEFT + BOARD_SIZE * 4 + 34, 62, BOARD_SIZE - 1);
	SetColor(BRIGHT_WHITE, RED);
	PrintX(TOP + 2, LEFT + BOARD_SIZE * 4 + 47, 2);
	SetColor(BRIGHT_WHITE, GREEN);
	PrintO(TOP + 2, LEFT + BOARD_SIZE * 4 + 77, 2);
	DesignBoard();
	RemoveScore(TOP + 8, LEFT + BOARD_SIZE * 4 + 46);
	RemoveScore(TOP + 8, LEFT + BOARD_SIZE * 4 + 76);
	DrawScore(SCORE_X, TOP + 8, LEFT + BOARD_SIZE * 4 + 47);
	DrawScore(SCORE_O, TOP + 8, LEFT + BOARD_SIZE * 4 + 77);
	Sleep(400);
	GotoXY(LEFT, TOP); cout << char(201);
	GotoXY(LEFT, TOP + BOARD_SIZE * 2); cout << char(200);
	for (int j = 1; j < BOARD_SIZE * 4 + 30; j++) {
		Sleep(10);
		GotoXY(LEFT + j, TOP);
		if (j % 4 == 0 && j < BOARD_SIZE * 4)cout << char(209);
		else cout << char(205);
		GotoXY(LEFT + j, TOP + BOARD_SIZE * 2);
		if (j % 4 == 0 && j < BOARD_SIZE * 4)cout << char(207);
		else cout << char(205);
		if (j > BOARD_SIZE * 4) {
			GotoXY(LEFT + j, TOP + ((BOARD_SIZE * 2) / 2));
			cout << char(205);
		}
	}
	GotoXY(LEFT + BOARD_SIZE * 4 + 30, TOP); cout << char(187);
	GotoXY(LEFT + BOARD_SIZE * 4 + 30, TOP + BOARD_SIZE * 2); cout << char(188);
	GotoXY(LEFT + BOARD_SIZE * 4, TOP); cout << char(203);
	GotoXY(LEFT + BOARD_SIZE * 4, TOP + BOARD_SIZE * 2); cout << char(202);
	//Vẽ đường viền trái phải
	for (int j = 1; j < BOARD_SIZE * 2; j++) {
		Sleep(10);
		GotoXY(LEFT, j + TOP);
		if (j % 2 == 0)cout << char(199);
		else cout << char(186);
		GotoXY(LEFT + BOARD_SIZE * 4, j + TOP);
		if (j % 2 == 0)cout << char(182);
		else cout << char(186);
		GotoXY(LEFT + BOARD_SIZE * 4 + 30, j + TOP);
		cout << char(186);
	}
	//Vẽ các cột, dòng
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
	Sleep(5);
	for (int i = 1; i < BOARD_SIZE; i++)
		for (int j = 1; j < BOARD_SIZE * 4; j++) {
			GotoXY(LEFT + j, 2 * i + TOP);
			if (j % 4 == 0)cout << char(197);
		}
	//Vẽ hiệu ứng đổi lượt X O
	if (_TURN == 1 || NEW_GAME == 1) {
		SetColor(BRIGHT_WHITE, RED);
		PrintX(TOP + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
		SetColor(BRIGHT_WHITE, GRAY);
		PrintO(TOP + ((BOARD_SIZE * 2) / 2) + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
	}
	else if (_TURN == 0) {
		SetColor(BRIGHT_WHITE, GRAY);
		PrintX(TOP + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
		SetColor(BRIGHT_WHITE, GREEN);
		PrintO(TOP + ((BOARD_SIZE * 2)/ 2) + 6, LEFT + BOARD_SIZE * 4 + 12, 2);
	}

	SetColor(LIGHT_AQUA, BLACK);
	if (_MODEPLAY == _MENU[2].c) {
		GotoXY(LEFT, TOP + BOARD_SIZE * 2 + 1);
		cout << "UNAVAILABLE !!!";
	}
	GotoXY(LEFT + BOARD_SIZE * 4 + 10, TOP + 2); SetColor(BRIGHT_WHITE, RED); cout << "  PLAYER 1 : "; 
	int n = ceil((30 - PLAYER1.size() - 2) / 2 + 0.5);
	GotoXY(LEFT + BOARD_SIZE * 4 + n, TOP + 3); cout << PLAYER1;
	GotoXY(LEFT + BOARD_SIZE * 4 + 10, TOP + ((BOARD_SIZE * 2) / 2) + 2); SetColor(BRIGHT_WHITE, GREEN); 
	cout << "  PLAYER 2 : ";
	if (_MODEPLAY == _MENU[0].c) {
		n = ceil((30 - PLAYER2.size() - 2) / 2 + 0.5);
		GotoXY(LEFT + BOARD_SIZE * 4 + n, TOP + ((BOARD_SIZE * 2) / 2) + 3); cout << PLAYER2;
	}
	else {
		GotoXY(LEFT + BOARD_SIZE * 4 + n, TOP + ((BOARD_SIZE * 2) / 2) + 3);
		cout << "BOT CARO";
	}
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT, 15, 2, "U:Undo");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 + 2, 15, 2, "H:Help");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 2 + 4, 15, 2, "M:Sound");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 2 + 32, 15, 2, "L:Save");
	Button(TOP + BOARD_SIZE * 2 + 2, LEFT + 15 * 3 + 32 + 2, 15, 2, "ESC:Exit");
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
					SetColor(BRIGHT_WHITE, GREEN);
					cout << "O"; break; }
				}
			}
		}
	_X = _A[0][0].x; _Y = _A[0][0].y;
	GotoXY(_X, _Y);
	if (_LAST_POINT.x != 0 && _LAST_POINT.y != 0) {
		_X = _LAST_POINT.x; _Y = _LAST_POINT.y;
		GotoXY(_X, _Y);
	}
}
void DrawMatchList() {
	FixConsoleWindows();
	system("cls");
	system("color F0");
	//Vẽ nút Tr? v?
	SetColor(BRIGHT_WHITE, YELLOW);
	GotoXY(20, CENTER_Y + 20);
	cout << "Press ESC to back to menu !!!";
	//Vẽ hướng dẫn tìm file
	GotoXY(CENTER_X + 45, CENTER_Y + 2);
	cout << "- Press        to delete files";
	GotoXY(CENTER_X + 45, CENTER_Y + 4);
	cout << "- Press        to search files: ";
	GotoXY(CENTER_X + 45, CENTER_Y + 6);
	cout << "Press              to finish typing file's name";
	GotoXY(CENTER_X + 45, CENTER_Y + 8);
	cout << "and press          to turn off Search mode !!!";

	SetColor(BLACK, BRIGHT_WHITE);
	GotoXY(CENTER_X + 54, CENTER_Y + 2);
	cout << "  O  ";
	GotoXY(CENTER_X + 54, CENTER_Y + 4);
	cout << "  F  ";
	GotoXY(CENTER_X + 52, CENTER_Y + 6);
	cout << "  Enter  ";
	GotoXY(CENTER_X + 56, CENTER_Y + 8);
	cout << "  esc  ";


	SetColor(BRIGHT_WHITE, BLACK);
	//Vẽ chữ LOAD GAME
	int logo_x = CENTER_X - 25, logo_y = 10;
	int old_mode= _setmode(_fileno(stdout), _O_WTEXT);
	wstring loadgame[6] = {
		L"██╗      █████╗  █████╗ ██████╗    ██████╗  █████╗ ███╗   ███╗███████╗",
		L"██║     ██╔══██╗██╔══██╗██╔══██╗  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
		L"██║     ██║  ██║███████║██║  ██║  ██║  ██╗ ███████║██╔████╔██║█████╗  ",
		L"██║     ██║  ██║██╔══██║██║  ██║  ██║  ╚██╗██╔══██║██║╚██╔╝██║██╔══╝  ",
		L"███████╗╚█████╔╝██║  ██║██████╔╝  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
		L"╚══════╝ ╚════╝ ╚═╝  ╚═╝╚═════╝    ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝" };
	for (int i = 0; i < 6; i++) {
		GotoXY(logo_x, logo_y + i);
		wcout << loadgame[i];
	}
	int current_mode= _setmode(_fileno(stdout), old_mode);

	//Vẽ các phần tử của danh sách
	if (MATCH_LIST_SIZE != 0) {
		for (int i = 0; i < MATCH_LIST_SIZE; i++) {
			SetColor(BRIGHT_WHITE, LIGHT_AQUA);
			PrintRectangle(CENTER_Y - 1 + i * 4, CENTER_X, 30, 4);
			GotoXY(CENTER_X + 10, CENTER_Y - 1 + i * 4 + 2);
			SetColor(BRIGHT_WHITE, BLACK);
			cout << _MATCH_LIST[i].item;
			SetColor(BRIGHT_WHITE, LIGHT_AQUA);
		}
	}
		//Vẽ mây
		SetColor(BRIGHT_WHITE, LIGHT_AQUA);
		PrintCloud(40, 4, 3); //ở bên trên chữ caro tí
		PrintCloud(150, 16, 3); //ở ngay dưới chữ "O"
		PrintCloud(WIDTH - 17, HEIGHT - 7, 2); // Góc phải
		PrintCloud(2, HEIGHT - 17, 1); // bên trái
		GotoXY(CENTER_X, CENTER_Y);
}

void DrawBoardPopUp() {
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	for (int i = 0; i < 8; ++i) {
		GotoXY(CENTER_X - 5, CENTER_Y - 2 + i);
		for (int j = 0; j < 29; j++)
			cout << " ";
	}
	PrintRectangle2lines(CENTER_Y - 3, CENTER_X - 6, 30, 9);
	SetColor(BRIGHT_WHITE, BLACK);
}

void DrawPopUp(WORD wVirtualKeyCode) {
	DrawBoardPopUp();
	switch (wVirtualKeyCode) {
	case 0x4C: {
		GotoXY(CENTER_X - 1, CENTER_Y);
		cout << "Are you sure you want ";
		GotoXY(CENTER_X, CENTER_Y + 1);
		cout << "to save this match";
		GotoXY(CENTER_X + 1, CENTER_Y + 3);
		cout << "  Yes(Y)   No(N)";
		break; }
	case VK_ESCAPE: {
		GotoXY(CENTER_X - 1, CENTER_Y);
		cout << "Are you sure you want ";
		GotoXY(CENTER_X, CENTER_Y + 1);
		cout << "to quit this match";
		GotoXY(CENTER_X + 1, CENTER_Y + 3);
		cout << "  Yes(Y)   No(N)";
		break; }
	case 0x4F: {
		GotoXY(CENTER_X-1, CENTER_Y );
		cout << "Are you sure you want ";
		GotoXY(CENTER_X, CENTER_Y + 1);
		cout<<"to delete this file";
		GotoXY(CENTER_X + 1, CENTER_Y + 3);
		cout << "  Yes(Y)   No(N)";
		break; }
	}
}
void Draw_AskContinue() {
	int top = 25, left = CENTER_X - 30;
	PrintRectangle(top, left, 90, 6);
	GotoXY(left + 25, top + 1); cout << "Do you want to continue playing or exit ? ";
	int width = 15, height = 2;
	Button(top + 2, left + 25, width, height, "Continue");
	Button(top + 2, left + 50, width, height, "Exit");
	_X = left + 25, _Y = top + 2;
	GotoXY(_X, _Y);
	ShowCursor(false);
}
void DrawAbout(){
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
	 SetColor(BRIGHT_WHITE, PURPLE);
	 GotoXY(CENTER_X + 2, CENTER_Y + 20);
	 cout << "Press ESC to back to Menu";
}

void DrawHelp() {
	ShowCursor(false);
	SetColor(BRIGHT_WHITE, BLACK);
	int width = 40, height = 9, i = 0, n = 0;
	int top= CENTER_Y - 20, left= CENTER_X - 4;
	PrintRectangle2lines(0, 1, WIDTH - 1, HEIGHT - 1);
	PrintHelpLogo(top,left);
	SetColor(BRIGHT_WHITE, PURPLE);
	GotoXY(CENTER_X + 2, CENTER_Y + 20);
	cout << "Press ESC to back to match";

	//Phím di chuyển
	SetColor(BRIGHT_WHITE, BLACK);
	int move_x = CENTER_X - 50, move_y = top + 8;
	GotoXY(move_x+20, move_y);
	cout << "MOVE IN BOARD GAME";
	GotoXY(move_x, move_y+1);
	cout << "     ---    ";
	GotoXY(move_x, move_y + 2);
	cout << "    | W |         Player 1:             ";
	GotoXY(move_x, move_y + 3);
	cout << " --- --- ---      Use W, A, S, D to move";
	GotoXY(move_x, move_y + 4);
	cout << "| A | S | D |";
	GotoXY(move_x, move_y + 5);
	cout << " --- --- --- ";

	GotoXY(move_x, move_y + 7);
	cout << "     ---    ";
	GotoXY(move_x, move_y + 8);
	cout << "    | ^ |         Player 2:             ";
	GotoXY(move_x, move_y + 9);
	cout << " --- --- ---      Use W, A, S, D to move";
	GotoXY(move_x, move_y + 10);
	cout << "| < | V | > |";
	GotoXY(move_x, move_y + 11);
	cout << " --- --- --- ";

	//Phím Enter, Space
	GotoXY(move_x+5, move_y + 13 );
	cout << " ------------ ";
	GotoXY(move_x+5, move_y + 14);
	cout << "|          " << char(191) << " |";
	GotoXY(move_x+5, move_y + 15);
	cout << "| ENTER <" << char(196) << char(196) << char(217) << " |";
	GotoXY(move_x+5, move_y + 16);
	cout << " ------------ ";
	GotoXY(move_x+30, move_y + 14);
	cout << " ------------ ";
	GotoXY(move_x+30, move_y + 15);
	cout << "|    Space    |";
	GotoXY(move_x+30, move_y + 16);
	cout << " ------------ ";
	GotoXY(move_x+5, move_y + 17);cout<<" Press Enter or Space to place your mark";
	

	//Luật
	SetColor(BRIGHT_WHITE, BLACK);
	int rules_x = CENTER_X + 20, rules_y = top + 8;
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
	cout << "or diagonally without blocked both ends ";
	GotoXY(rules_x, rules_y + 12);
	cout<<"of that direction wins the game. If all the squares"; 
	GotoXY(rules_x, rules_y + 14);
	cout << "are filled and neither player has 5 in a row,";
	GotoXY(rules_x, rules_y + 16);
	cout << "the game is considered a Tie.";

	//Ðuờng chia đôi
	SetColor(BRIGHT_WHITE, BLACK);
	for (int i = 0; i < 18; i++) {
		GotoXY(CENTER_X + 8, top + 7 + i);
		cout << "|";
	}
	
	//Đám mây
	SetColor(BRIGHT_WHITE, LIGHT_AQUA);
	PrintCloud(WIDTH - 17, HEIGHT - 7, 2); // Góc phải
	PrintCloud(155, 10, 3);
	PrintCloud(2, HEIGHT - 17, 1); // bên trái 
	PrintHelicopter(20, top);
	PrintCastle(CENTER_X, HEIGHT - 18);
}