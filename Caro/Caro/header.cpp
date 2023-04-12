#include "header.h"

_POINT _A[BOARD_SIZE][BOARD_SIZE];
_POINT _MENU[MENU_OPTIONS] = {
	_POINT{40,10,1},
	_POINT{40,12,2},
	_POINT{40,14,3},
	_POINT{40,16,4}
};

bool _TURN;
int _COMMAND;
int _X, _Y;
int MODE; 