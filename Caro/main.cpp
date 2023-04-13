#include "header.h"
#include "control.h"
#include "model.h"
#include "view.h"

int main() {
	FixConsoleWindows(); //View
	GetMatchListSize();
	ShowMenu(); //View
	return 0;
};