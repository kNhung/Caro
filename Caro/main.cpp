#include "header.h"
#include "control.h"
#include "model.h"
#include "view.h"
#include "page.h"

int main() {
	FixConsoleWindows(); //View
	GetMatchListSize();
	ShowMenu(); //View
	return 0;
};