#include "header.h"
#include "control.h"
#include "model.h"
#include "view.h"
#include "page.h"

int main() {
	_EXIT = 0;
	FixConsoleWindows(); //View
	GetMatchListSize();
	ShowMenu(); //View
	system("cls");
	return 0;
}