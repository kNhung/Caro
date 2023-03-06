#include "header.h"

_POINT _A[BOARD_SIZE][BOARD_SIZE];
_POINT _MENU[MENU_SIZE] = {
	_POINT{40,10,1},
	_POINT{40,12,2},
	_POINT{40,14,3},
	_POINT{40,16,4}
};

bool _TURN;
int _COMMAND;
int _X, _Y;
int MODE; 
bool NEW_GAME;
ofstream _MATCH_LIST_FILE;
int MATCH_LIST_SIZE;
vector<_LIST> _MATCH_LIST;